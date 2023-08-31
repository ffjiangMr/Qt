#ifndef QQUEUEDEPARTMENTDEFINITION_H
#define QQUEUEDEPARTMENTDEFINITION_H

#include<QString>

class QQueueDepartmentInfo
{
public:
    QQueueDepartmentInfo(const QString& displayName, const int& dep_id, const int& recordId = -1)
    {
        this->name = displayName;
        this->id = dep_id;
        this->recordId = recordId;        
    }

    inline QString getName()
    {
        return this->name;
    }

    inline quint32 getId()
    {
        return this->id;
    }


    inline int getRecordId()
    {
        return this->recordId;
    }

    inline void setName(const QString& name)
    {
        this->name = name;        
    }
    inline void setId(const quint32 id)
    {
        this->id = id;
    }

private:
    QString name;
    quint32 id;
    int recordId;    
};

#endif // QQUEUEDEPARTMENTDEFINITION_H
