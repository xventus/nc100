//
//  file_transfer_thread.cpp
//  nc100
//
//  Created by Petr Vanek on 03.10.2021.
//

#include "../../include/modem.h"
#include "../../include/hex_stream_formatter.h"
#include "file_transfer_worker.h"


FileTransferWorker::FileTransferWorker(QObject *parent):  QObject(parent), _cancel(false) {
}

FileTransferWorker::~FileTransferWorker() {
}

void FileTransferWorker::doJob() {
   
    if ( _cancel ) return;
    if (_port) {
        _running = true;
        fv::Modem modem(std::move(_port));
        modem.addCallback([&](auto s, auto p, auto data) {
            std::string info;
          if (s == fv::Modem::State::blockNum) {
              
            
              
              info = "\nBlock: ";
              info += std::to_string(p);
              info += "\n";
              
              if (!data.empty()) {
                  std::stringstream ss;
                  ss << fv::utils::HexDumper<const std::vector<uint8_t>>(
                      {data.begin(), data.end()}, 16);
                  info += ss.str();
              }
              
          } else if (s == fv::Modem::State::data) {
              info = ".";
          } else if (s == fv::Modem::State::end) {
              info = "\nDone";
          } else if (s == fv::Modem::State::timeouted) {
              info = "\nTimeouted";
          }
          emit progress(false, info);
          return !_cancel;
        });

        try {
            modem.open();
            if (_operation == Operation::xmodem128Receive) {
                auto msg = modem.X128Receive();
                emit progress(true, msg);
            } else if (_operation == Operation::xmodem128Send)  {
                modem.X128Send(_data);
                emit progress(true, "");
            }
        
        } catch (...) {
            std::string info;
            emit progress(false, info);
        }
        
        if (modem.isOpened()) {
           modem.close();
        }
    } else {
        emit error("invalid job");
    }
    _port.reset();
    emit finished();
    _running = false;
    _cancel = true;
    QMetaObject::invokeMethod( this, "doJob", Qt::QueuedConnection );
}

void FileTransferWorker::startJob() {
  _cancel = false;
  doJob();
}

void FileTransferWorker::cancel() {
    _cancel = true;
}
