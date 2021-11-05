#include "formheddump.h"
#include "ui_formheddump.h"


FormHedDump::FormHedDump(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormHedDump)
{
    ui->setupUi(this);
    connect(ui->pushButtonClose, &QPushButton::clicked, this,
            &FormHedDump::closeView);
}

void FormHedDump::closeEvent(QCloseEvent *event) {
    event->accept();
}

void FormHedDump::closeView() {
    close();
}

FormHedDump::~FormHedDump()
{
    delete ui;
}


void FormHedDump::withRawContnet(const std::string_view& data) {
    
    ui->textEdit->setTextColor(QColor("green"));
    std::stringstream ss;
    ss << fv::utils::HexDumper<const std::vector<uint8_t>>(
        {data.begin(), data.end()}, 16);

    ui->textEdit->insertPlainText(QString::fromUtf8(ss.str()));
    
}
