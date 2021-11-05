#include "widget.h"
#include "ui_widget.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include "formheddump.h"
#include "list_model.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {

  ui->setupUi(this);

  // computer file list
  _modelComputer = new QStringListModel(this);
  _modelDevice = new QStringListModel(this);
  ui->computerListView->setModel(_modelComputer);
  ui->DeviceListView->setModel(_modelDevice);

  // ui singal
  connect(ui->toolButtonSerialRefresh, &QToolButton::clicked, this,
          &Widget::serialRefresh);
  connect(ui->pushButtonToComputer, &QToolButton::clicked, this,
          &Widget::toComputer);
  connect(ui->pushButtonToDevice, &QToolButton::clicked, this,
          &Widget::toDevice);
  connect(ui->pushButtonStop, &QToolButton::clicked, this,
          &Widget::stopOperation);
  connect(ui->toolButtonDir, &QToolButton::clicked, this,
          &Widget::selectDirectory);

  connect(ui->computerListView, &QListView::doubleClicked, this,
          &Widget::selectViewFile);

  // result handler
  connect(&_transferWorker, SIGNAL(progress(bool, const std::string &)), this,
          SLOT(handleProgress(bool, const std::string &)));

  // error handler
  connect(&_transferWorker, SIGNAL(error(QString)), this,
          SLOT(handlerError(QString)));

  // finish handler
  connect(&_transferWorker, SIGNAL(finished()), this, SLOT(finishedJob()));

  // control worker
  connect(this, SIGNAL(startWork()), &_transferWorker, SLOT(startJob()));

  // trasfer file worker
  _transferWorker.moveToThread(&_thread);
  _thread.start();
  uiDisableState(false);

  // fill up combo - serial port
  serialRefresh();

  // fill up combos speed, parity, stop bits....
  for (const auto &i : fv::serial::all_speeds) {
    ui->comboBoxSpeed->addItem(QString::number(static_cast<int>(i)),
                               static_cast<int>(i));
  }

  for (const auto &i : fv::serial::all_bits) {
    ui->comboBoxBits->addItem(QString::number(static_cast<int>(i)),
                              static_cast<int>(i));
  }

  // serial combo combo params
  ui->comboBoxStop->addItem("1",
                            static_cast<int>(fv::serial::StopBits::stop_1));
  ui->comboBoxStop->addItem("1.5",
                            static_cast<int>(fv::serial::StopBits::stop_1_5));
  ui->comboBoxStop->addItem("2",
                            static_cast<int>(fv::serial::StopBits::stop_2));

  ui->comboBoxControl->addItem("none",
                               static_cast<int>(fv::serial::FlowControl::none));
  ui->comboBoxControl->addItem(
      "xon/xoff", static_cast<int>(fv::serial::FlowControl::xonff));
  ui->comboBoxControl->addItem("hardware",
                               static_cast<int>(fv::serial::FlowControl::hw));

  ui->comboBoxStopParity->addItem("none",
                                  static_cast<int>(fv::serial::Parity::none));
  ui->comboBoxStopParity->addItem("odd",
                                  static_cast<int>(fv::serial::Parity::odd));
  ui->comboBoxStopParity->addItem("even",
                                  static_cast<int>(fv::serial::Parity::even));

  // filters
  ui->comboBoxFilter->addItem("none", static_cast<int>(0));
  //ui->comboBoxFilter->addItem("uuencode", static_cast<int>(1));

  // protocol
  ui->comboBoxProtocol->addItem("xmodem", static_cast<int>(0));

  // read configuration
  Configuration::read(_cfg);

  // apply configuration into UI
  setFromConfigToW();

  // refresh computer side
  refreshDir();
}

void Widget::setFromConfigToW() {

  auto index = ui->comboBoxSpeed->findData(static_cast<int>(_cfg._speedS));
  if (index != -1) {
    ui->comboBoxSpeed->setCurrentIndex(index);
  }

  index = ui->comboBoxBits->findData(static_cast<int>(_cfg._bitsS));
  if (index != -1) {
    ui->comboBoxBits->setCurrentIndex(index);
  }

  index = ui->comboBoxStop->findData(static_cast<int>(_cfg._stopsS));
  if (index != -1) {
    ui->comboBoxStop->setCurrentIndex(index);
  }

  index = ui->comboBoxStopParity->findData(static_cast<int>(_cfg._parityS));
  if (index != -1) {
    ui->comboBoxStopParity->setCurrentIndex(index);
  }

  index = ui->comboBoxControl->findData(static_cast<int>(_cfg._flowS));
  if (index != -1) {
    ui->comboBoxControl->setCurrentIndex(index);
  }

  ui->checkBoxReceiveFile->setChecked(_cfg._toFile);

  index = ui->comboBoxFilter->findData(static_cast<int>(_cfg._filter));
  if (index != -1) {
    ui->comboBoxFilter->setCurrentIndex(index);
  }

  index = ui->comboBoxProtocol->findData(static_cast<int>(_cfg._protocol));
  if (index != -1) {
    ui->comboBoxProtocol->setCurrentIndex(index);
  }

#ifdef _WIN32
  ui->lineEditDir->setText(QString::fromWCharArray(_cfg._base.c_str()));
  ui->lineEditBaseName->setText(QString::fromWCharArray(_cfg._recName.c_str()));
#else
  ui->lineEditDir->setText(QString::fromUtf8(_cfg._base.c_str()));
  ui->lineEditBaseName->setText(QString::fromUtf8(_cfg._recName.c_str()));
#endif
}

void Widget::setToConfigFromW() {
  _cfg._speedS = static_cast<fv::serial::BDSpeed>(
      ui->comboBoxSpeed->currentData().toInt());
  _cfg._bitsS = static_cast<fv::serial::DataBits>(
      ui->comboBoxBits->currentData().toInt());
  _cfg._stopsS = static_cast<fv::serial::StopBits>(
      ui->comboBoxStop->currentData().toInt());
  _cfg._parityS = static_cast<fv::serial::Parity>(
      ui->comboBoxStopParity->currentData().toInt());
  _cfg._flowS = static_cast<fv::serial::FlowControl>(
      ui->comboBoxControl->currentData().toInt());

  _cfg._filter = ui->comboBoxFilter->currentData().toInt();
  _cfg._protocol = ui->comboBoxProtocol->currentData().toInt();

  _cfg._toFile = ui->checkBoxReceiveFile->isChecked();

#ifdef _WIN32
  _cfg._base = ui->lineEditDir->text().toStdWString();
  _cfg._recName = ui->lineEditBaseName->text().toStdWString();
#else
  _cfg._base = ui->lineEditDir->text().toStdString();
  _cfg._recName = ui->lineEditBaseName->text().toStdString();
#endif
}

void Widget::selectViewFile() {

  auto i = ui->computerListView->currentIndex();
  QString itemText = i.data(Qt::DisplayRole).toString();
  if (!itemText.isEmpty()) {
    size_t flsize = 0;
#ifndef _WIN32
    flsize = fv::utils::Dirs::fileSize(ui->lineEditDir->text().toStdString(),
                                       itemText.toStdString());
#else
    flsize = fv::utils::Dirs::fileSize(ui->lineEditDir->text().toStdWString(),
                                       itemText.toStdWString());
#endif

    if (flsize < 1024 * 1024) {
      FormHedDump *hdump = new FormHedDump(nullptr);
      hdump->setWindowTitle(itemText);
      hdump->withRawContnet(getFileContnet(ui->lineEditDir->text(), itemText));
      hdump->show();
    } else {
      QMessageBox msgBox;
      msgBox.setText("Too big file to display.");
      msgBox.exec();
    }
  }
}

void Widget::selectDirectory() {

  QString dir = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), ui->lineEditDir->text(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  ui->lineEditDir->setText(dir);
}

void Widget::refreshDir() {

  do {

    QDir dir(ui->lineEditDir->text());
    dir.setFilter(QDir::Files /*| QDir::Hidden*/ | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = dir.entryInfoList();

    if (list.empty()) {
      _modelComputer->removeRows(0, _modelComputer->rowCount());
      break;
    }

    for (const auto &i : list) {
      if (_modelComputer->insertRow(_modelComputer->rowCount())) {
        QModelIndex index =
            _modelComputer->index(_modelComputer->rowCount() - 1, 0);
        _modelComputer->setData(index, i.fileName());
      }
    }

    int row = ui->computerListView->currentIndex().row();
    if (row == -1) {
      row = 0;
    }

    QModelIndex index = _modelComputer->index(row);
    ui->computerListView->setCurrentIndex(index);
  } while (false);
}

void Widget::closeEvent(QCloseEvent *event) {

  setToConfigFromW();
  Configuration::write(_cfg);

  if (_transferWorker.isRunning()) {

    QMessageBox::StandardButton resBtn = QMessageBox::question(
        this, tr(""), tr("Are you sure?\n"), QMessageBox::No | QMessageBox::Yes,
        QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
      event->ignore();
    } else {
      if (_transferWorker.isRunning()) {
        _terminate = true;
        _transferWorker.cancel();
        event->ignore();
        qDebug() << "Widget::closeEvent() - ignore";
      } else {
        event->accept();
        _thread.terminate();
        qDebug() << "Widget::closeEvent() - accept";
      }
    }
  } else {
    event->accept();
    _thread.terminate();
    qDebug() << "Widget::closeEvent()";
  }
}

void Widget::stopOperation() {
  qDebug() << "Widget::stopOperation()";
  _transferWorker.cancel();
  ui->pushButtonStop->setDisabled(true);
}

void Widget::uiDisableState(bool disable) {
  if (disable) {
    ui->toolButtonSerialRefresh->setDisabled(true);
    ui->pushButtonToComputer->setDisabled(true);
    ui->pushButtonToDevice->setDisabled(true);
    ui->pushButtonStop->setDisabled(false);
  } else {
    ui->toolButtonSerialRefresh->setDisabled(false);
    ui->pushButtonToComputer->setDisabled(false);
    ui->pushButtonToDevice->setDisabled(false);
    ui->pushButtonStop->setDisabled(true);
  }
}

bool Widget::isReplaceFile() {
  QMessageBox::StandardButton resBtn = QMessageBox::question(
      this, tr(""), tr("Overwrite an existing file?\n"),
      QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
  return (resBtn == QMessageBox::Yes);
}

void Widget::saveToFile(const QString dir, const QString filename,
                        const std::string_view &contnet) {

#ifndef _WIN32
  auto file = filename.toStdString();
  auto dirf = dir.toStdString();
  auto replace = true;
  if (fv::utils::Dirs::isFileExist(dirf, file, false)) {
    replace = isReplaceFile();
  }

  if (replace) {
    fv::utils::concat(dirf, file);
    fv::utils::SimpleFileOp::write(dirf, contnet);
  }
#else
  auto file = filename.toStdWString();
  auto dirf = dir.toStdWString();
  auto replace = true;
  if (fv::utils::Dirs::isFileExist(dirf, file, false)) {
    replace = isReplaceFile();
  }

  if (replace) {
    fv::utils::concat(dirf, file);
    fv::utils::SimpleFileOp::write(dirf, contnet);
  }
#endif
}

void Widget::handleProgress(bool payload, const std::string &data) {
  if (!payload) {
    ui->textEdit->setTextColor(QColor("green"));
    ui->textEdit->insertPlainText(QString::fromUtf8(data));
  } else {
    if (!data.empty()) {
      ui->textEdit->insertPlainText("\n");
      ui->textEdit->setTextColor(QColor("white"));
      std::stringstream ss;
      ss << fv::utils::HexDumper<const std::vector<uint8_t>>(
          {data.begin(), data.end()}, 16);

      ui->textEdit->insertPlainText(QString::fromUtf8(ss.str()));

      if (ui->checkBoxReceiveFile->isChecked()) {
        // save to file
        saveToFile(ui->lineEditDir->text(), ui->lineEditBaseName->text(), data);
        refreshDir();
      }
    }
  }
}

void Widget::handlerError(QString data) {
  ui->textEdit->setTextColor(QColor("red"));
  ui->textEdit->insertPlainText(data);
}

void Widget::finishedJob() {
  uiDisableState(false);
  if (_terminate) {
    qDebug() << "Widget::finishedJob() - term";
    _thread.terminate();
    qDebug() << "Widget::finishedJob() - quit";
    qApp->quit();
  }
}

void Widget::toComputer() {

  ui->textEdit->clear();
  QString path =
      QDir(ui->lineEditDir->text()).filePath(ui->lineEditBaseName->text());

#ifdef _WIN32
  emit handleProgress(false, path.toStdWString());
#else
  handleProgress(false, path.toStdString());
#endif

  uiDisableState(true);
  auto cb = ui->comboBoxSerial->currentText();

  auto port = findSelectedPort(cb);
  if (port) {
    setToConfigFromW();
    port->withParity(_cfg._parityS)
        .withBdSpeed(_cfg._speedS)
        .withStopBits(_cfg._stopsS)
        .withDataBits(_cfg._bitsS)
        .withFlowControl(_cfg._flowS);
    _transferWorker.withPort(std::move(port),
                             FileTransferWorker::Operation::xmodem128Receive);
    emit startWork();
  }
}

void Widget::toDevice() {

  auto i = ui->computerListView->currentIndex();
  QString itemText = i.data(Qt::DisplayRole).toString();
  if (itemText.isEmpty()) {
    QMessageBox msgBox;
    msgBox.setText("No file has been selected for transfer");
    msgBox.exec();
    return;
  }

  uiDisableState(true);
  auto cb = ui->comboBoxSerial->currentText();
  ui->textEdit->clear();
  QString path = QDir(ui->lineEditDir->text()).filePath(itemText);

#ifdef _WIN32
  emit handleProgress(false, path.toStdWString());
#else
  handleProgress(false, path.toStdString());
#endif

  auto port = findSelectedPort(cb);
  if (port) {
    setToConfigFromW();
    port->withParity(_cfg._parityS)
        .withBdSpeed(_cfg._speedS)
        .withStopBits(_cfg._stopsS)
        .withDataBits(_cfg._bitsS)
        .withFlowControl(_cfg._flowS);
    _transferWorker.withPort(std::move(port),
                             FileTransferWorker::Operation::xmodem128Send);

    if (_modelDevice->insertRow(_modelDevice->rowCount())) {
      QModelIndex index =
          _modelComputer->index(_modelDevice->rowCount() - 1, 0);
      _modelDevice->setData(index, itemText);
    }

    _transferWorker.withData(getFileContnet(ui->lineEditDir->text(), itemText));
    emit startWork();
  }
}

std::string Widget::getFileContnet(const QString dir, const QString filename) {
  std::string rc;
#ifndef _WIN32
  auto dirf = dir.toStdString();
  fv::utils::concat(dirf, filename.toStdString());
  fv::utils::SimpleFileOp::read(dirf, rc);

#else
  auto dirf = dir.toStdWString();
  fv::utils::concat(dirf, filename.toStdWString());
  fv::utils::SimpleFileOp::read(dirf, rc);
#endif

  return rc;
}

QString Widget::getPortPrintableString(
    std::unique_ptr<fv::serial::ISerial> const &port) {

  auto item = port->getLocation();
  if (!port->getDeviceName().empty()) {
    item += " [";
    item += port->getDeviceName();
    item += "]";
  }

  return QString::fromUtf8(item.c_str());
}

std::unique_ptr<fv::serial::ISerial>
Widget::findSelectedPort(const QString &port) {
  std::unique_ptr<fv::serial::ISerial> rc = {};
  auto enumerator = fv::serial::ISerialEnumerator::Factory::createUnique();
  auto eports = enumerator->scan();
  for (auto &it : eports) {
    if (getPortPrintableString(it) == port) {
      rc = std::move(it);
      break;
    }
  }
  return rc;
}

void Widget::serialRefresh() {

  auto enumerator = fv::serial::ISerialEnumerator::Factory::createUnique();
  auto eports = enumerator->scan();
  ui->comboBoxSerial->clear();
  for (const auto &it : eports) {
    ui->comboBoxSerial->addItem(getPortPrintableString(it));
  }
}

Widget::~Widget() { delete ui; }
