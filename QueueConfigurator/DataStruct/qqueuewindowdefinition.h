#ifndef QQUEUEWINDOWDEFINITION_H
#define QQUEUEWINDOWDEFINITION_H

#include<QString>

class QQueueWindowsDefinition
{
public:
    QQueueWindowsDefinition(const QString& displayName, const quint32& id,const QString& callName = "", const int& operatorId = -1,const int& screenId = -1,const int& evaluateId=-1,const QString& windowIP="", const QString& forwardIP = "", const int& employeeId = -1, const int& recordId = -1)
    {
        this->name = displayName;
        this->id = id;
        this->callName = callName;
        this->operatorId = operatorId;
        this->screenId = screenId;
        this->evaluateId = evaluateId;
        this->windowIP = windowIP;
        this->forwardIP = forwardIP;
        this->employeeId = employeeId;
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

    inline QString getCallName()
    {
        return this->callName;
    }

    inline int getOperatorAddr()
    {
        return this->operatorId;
    }

    inline int getScreenAddr()
    {
       return this->screenId;
    }

    inline int getEvaluateAddr()
    {
        return this->evaluateId;
    }

    inline QString getWindowIP()
    {
        return this->windowIP;
    }

    inline QString getForwardIP()
    {
        return this->forwardIP;
    }

    inline int getEmployeeId()
    {
        return this->employeeId;
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

    inline void setCallName(const QString& callName)
    {
        this->callName = callName;
    }

    inline void setOperatorAddr(const int& operatorAddr)
    {
        this->operatorId = operatorAddr;
    }

    inline void setScreenAddr(const int& screenAddr)
    {
        this->screenId = screenAddr;
    }

    inline  void setEvaluateAddr(const int& evaluateAddr)
    {
        this->evaluateId = evaluateAddr;
    }

    inline void setWindowIP(const QString& windowIP)
    {
        this->windowIP = windowIP;
    }

    inline void setForwardIP(const QString& forwardIP)
    {
        this->forwardIP = forwardIP;
    }

    inline void setEmployee(const int& employeeId)
    {
        this->employeeId = employeeId;
    }


private:
    QString name;
    QString callName;
    quint32 id;
    int operatorId;
    int screenId;
    int evaluateId;
    QString windowIP;
    QString forwardIP;
    int employeeId;
    int recordId;
};


#endif // QQUEUEWINDOWDEFINITION_H
