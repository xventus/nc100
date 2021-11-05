//
//  configuration.cpp
//  nc100
//
//  Created by Petr Vanek on 05.10.2021.
//

#include "configuration.h"

// MAC path:    $HOME/Library/Preferences/cz.fotoventus.nc100.plist

void Configuration::read(Cfg &cfg)  {
    QSettings settings;
    auto p =settings.value("serial/speed").toInt();
    qDebug() << p;
    cfg._speedS = static_cast<fv::serial::BDSpeed> (settings.value("serial/speed").toInt());
    cfg._flowS = static_cast<fv::serial::FlowControl> (settings.value("serial/flow").toInt());
    cfg._bitsS = static_cast<fv::serial::DataBits> (settings.value("serial/bits").toInt());
    cfg._stopsS = static_cast<fv::serial::StopBits> (settings.value("serial/stop").toInt());
    cfg._parityS = static_cast<fv::serial::Parity> (settings.value("serial/parity").toInt());
    
    cfg._filter =   settings.value("filter").toInt();
    cfg._protocol = settings.value("protocol").toInt();
       
    cfg._autoincrement = settings.value("autoinc").toBool();
    cfg._toFile = settings.value("tofile").toBool();
    
#ifdef _WIN32
    cfg._base = settings.value("base").toString().toStdWString();
    cfg._recName = settings.value("recname").toString().toStdWString();
#else
    cfg._base = settings.value("base").toString().toStdString();
    cfg._recName = settings.value("recname").toString().toStdString();
#endif
}



void  Configuration::write(const Cfg &cfg) {
    QSettings settings;
    settings.setValue("serial/speed", static_cast<int>(cfg._speedS));
    settings.setValue("serial/bits", static_cast<int>(cfg._bitsS));
    settings.setValue("serial/flow", static_cast<int>(cfg._flowS));
    settings.setValue("serial/parity", static_cast<int>(cfg._parityS));
    settings.setValue("serial/stop", static_cast<int>(cfg._stopsS));
    
    settings.setValue("filter", static_cast<int>(cfg._filter));
    settings.setValue("protocol", static_cast<int>(cfg._protocol));
    
    settings.setValue("autoinc", cfg._autoincrement);
    settings.setValue("tofile", cfg._toFile);
#ifdef _WIN32
    settings.setValue("recname", QString::fromStdWString(cfg._recName));
    settings.setValue("base", QString::fromStdWString(cfg._base));
#else
    settings.setValue("recname", QString::fromStdString(cfg._recName));
    settings.setValue("base", QString::fromStdString(cfg._base));
#endif
    
}
