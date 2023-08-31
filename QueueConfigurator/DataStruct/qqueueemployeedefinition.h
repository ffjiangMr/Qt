#ifndef QQUEUEEMPLOYEEDEFINITION_H
#define QQUEUEEMPLOYEEDEFINITION_H

#include<QString>

class QQueueEmployeeDefinition
{
public:
    QQueueEmployeeDefinition(const QString& displayName, const quint32& id,const QString& password= "",const int& level = -1,const int& departmentId = -1,const QString& title="",const QString& summary="", const int& recordId = -1)
    {
        this->name = displayName;
        this->id = id;
        this->psw = password;
        this->starLevel = level;
        this->depId = departmentId;
        this->title = title;
        this->summary = summary;
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

    inline QString getPassword()
    {
        return this->psw;
    }

    inline int getLevel()
    {
        return this->starLevel;
    }

    inline int getDepartment()
    {
       return this->depId;
    }

    inline QString getTitle()
    {
        return this->title;
    }

    inline QString getSummary()
    {
        return this->summary;
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

    inline void setPassword(const QString& password)
    {
        this->psw = password;
    }

    inline void setStarLevel(const int& level)
    {
        this->starLevel = level;
    }

    inline void setDepartment(const int& departmentId)
    {
        this->depId = departmentId;
    }

    inline  void setTitle(const QString& title)
    {
        this->title = title;
    }

    inline void setSummary(const QString& summary)
    {
        this->summary = summary;
    }


private:
    QString name;
    quint32 id;
    QString psw;
    int starLevel;
    int depId;
    QString title;
    QString summary;
    int recordId;
};

#endif // QQUEUEEMPLOYEEDEFINITION_H
