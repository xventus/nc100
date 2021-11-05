#ifndef FORMHEDDUMP_H
#define FORMHEDDUMP_H

#include <QWidget>
#include <QCloseEvent>
#include <string>
#include <iostream>
#include <sstream>
#include "../../include/hex_stream_formatter.h"

namespace Ui {
class FormHedDump;
}

class FormHedDump : public QWidget
{
    Q_OBJECT

public:
    explicit FormHedDump(QWidget *parent = nullptr);
    ~FormHedDump();
    void closeEvent(QCloseEvent *event);
    void closeView();
    void withRawContnet(const std::string_view& data);

private:
    Ui::FormHedDump *ui;
};

#endif // FORMHEDDUMP_H
