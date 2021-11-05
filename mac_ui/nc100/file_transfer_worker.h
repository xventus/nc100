//
//  file_transfer_thread.hpp
//  nc100
//
//  Created by Petr Vanek on 03.10.2021.
//

#ifndef file_transfer_thread_hpp
#define file_transfer_thread_hpp

#include <QObject>
#include <QMetaType>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

#include "../../include/serial_intf.h"


Q_DECLARE_METATYPE (std::string)


class FileTransferWorker : public QObject {
  
    Q_OBJECT

public:
    
    enum class Operation {
      none,
      xmodem128Send,
      xmodem128Receive
    };


    explicit FileTransferWorker(QObject *parent = 0);
    
    ~FileTransferWorker();
    
    void withPort(std::unique_ptr<fv::serial::ISerial> port, Operation op){
        _port = std::move(port);
        _cancel = false;
        _operation = op;
    };
    
    void withData(const std::string_view & data) {
        _data = data;
    }
    
    void cancel();
    
    bool isRunning() const {
        return _running;
    }
    
public slots:
    void doJob();
    void startJob();
    
signals:
    void finished();
    void error(QString err);
    void progress(bool payload, const std::string& data);
    
private:
    std::unique_ptr<fv::serial::ISerial> _port = {};
    std::atomic<bool>   _cancel {false};                    ///> cancel operation is active
    std::atomic<bool>   _running {false};                   ///> running flag
    Operation           _operation {Operation::none};       ///> operation mode
    std::string         _data;                              ///> outbound data
};


#endif /* file_transfer_thread_hpp */
