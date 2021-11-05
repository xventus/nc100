//
//  list_model.hpp
//  nc100
//
//  Created by Petr Vanek on 05.10.2021.
//

#ifndef list_model_hpp
#define list_model_hpp

#include <QStringListModel>
#include <QString>


class ListModel : public QStringListModel {
public:
  
    void append (const QString& string){
    insertRows(rowCount(), 1);
    setData(index(rowCount()-1), string);
  }
    
    ListModel& operator<<(const QString& string){
    append(string);
    return *this;
  }
    
};



#endif /* list_model_hpp */
