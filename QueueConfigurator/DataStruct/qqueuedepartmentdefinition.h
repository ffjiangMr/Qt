#ifndef QQUEUEDEPARTMENTDEFINITION_H
#define QQUEUEDEPARTMENTDEFINITION_H

#include<QString>

class QQueueDepartmentInfo
{
public:
    QQueueDepartmentInfo(const QString& displayName, const int& dep_id,  const bool& isUpdate =false,const int& recordId = -1)
    {
        this->name = displayName;
        this->id = dep_id;
        this->recordId = recordId;
        this->isChanged = isUpdate;
    }

    inline QString getName()
    {
        return this->name;
    }

    inline quint32 getId()
    {
        return this->id;
    }

    inline bool getIsChanged()
    {
        return this->isChanged;
    }

    inline int getRecordId()
    {
        return this->recordId;
    }

    inline void setName(const QString& name)
    {
        this->name = name;
        this->isChanged = true;
    }
    inline void setId(const quint32 id)
    {
        this->id = id;
        this->isChanged = true;
    }

private:
    QString name;
    quint32 id;
    int recordId;
    bool isChanged;
};

#endif // QQUEUEDEPARTMENTDEFINITION_H
