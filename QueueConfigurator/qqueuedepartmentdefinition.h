#ifndef QQUEUEDEPARTMENTDEFINITION_H
#define QQUEUEDEPARTMENTDEFINITION_H

#include<QString>

class QQueueDepartmentInfo
{
public:
    QQueueDepartmentInfo(const QString& displayName, const int& id)
    {
        this->name = displayName;
        this->id = id;
    }

    inline QString getName()
    {
        return this->name;
    }

    inline quint32 getId()
    {
        return this->id;
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

};

#endif // QQUEUEDEPARTMENTDEFINITION_H
