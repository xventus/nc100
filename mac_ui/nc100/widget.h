#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringListModel>
#include "file_transfer_worker.h"

// core
#include "../../include/crosstypes.h"
#include "../../include/serial_enumerator_intf.h"
#include "../../include/hex_stream_formatter.h"
#include "../../include/modem.h"
#include "../../utils/dirs.h"
#include "../../utils/file.h"

#include "configuration.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = nullptr);
   
    ~Widget();
    
    void closeEvent(QCloseEvent *event);

signals:
  void startWork();
  void stopWork();
    
private slots:
    void handleProgress(bool payload, const std::string&  data);
    void handlerError(QString data);
    void finishedJob();
    void stopOperation();
    void serialRefresh();
    void toComputer();
    void toDevice();
    void selectDirectory();
    void selectViewFile();
    
private:
    
    void uiDisableState(bool disable);
    QString getPortPrintableString(std::unique_ptr<fv::serial::ISerial> const &port);
    std::unique_ptr<fv::serial::ISerial> findSelectedPort(const QString& port);
    void setFromConfigToW();
    void setToConfigFromW();
    void saveToFile(const QString dir, const QString filename, const std::string_view& contnet);
    std::string getFileContnet(const QString dir, const QString filename);
    bool isReplaceFile();
    void refreshDir();
    
    Ui::Widget *ui;
    QThread             _thread;
    FileTransferWorker  _transferWorker;
    bool                _terminate {false} ; ///> if sets terminate application
    Configuration::Cfg                 _cfg;
    
    QStringListModel *  _modelComputer {nullptr};
    QStringListModel *  _modelDevice {nullptr};
   
    
};
#endif // WIDGET_H
