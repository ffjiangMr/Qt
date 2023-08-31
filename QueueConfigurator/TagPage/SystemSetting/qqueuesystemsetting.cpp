#include "qqueuesystemsetting.h"
#include "ui_qqueuesystemsetting.h"
#include "../../include/qqueuesqlhelper.h"

#include <QSettings>
#include <QLineEdit>
#include <QDebug>
#include <QTextCodec>
#include <QDateTime>
#include <QFontDialog>
#include <QIntValidator>
#include <QByteArray>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QTextCodec>

QQueueSystemSetting::QQueueSystemSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQueueSystemSetting)
{
    ui->setupUi(this);
    this->initData();
    this->initDefaultData();
    connect(ui->checkBox_ShowPsw, SIGNAL(stateChanged(int)), this, SLOT(onShowPassword(int)));
    connect(ui->checkBox_showTime, SIGNAL(stateChanged(int)), this, SLOT(onShowTime(int)));
    connect(ui->checkBox_enableIdCard, SIGNAL(stateChanged(int)), this, SLOT(onShowIdCard(int)));
    connect(ui->pushButton_fontSet, SIGNAL(clicked()), this, SLOT(onBtnFontSetting()));
    connect(ui->lineEdit_oldPsw, SIGNAL(editingFinished()), this, SLOT(onOldPswChanged()));
    connect(ui->lineEdit_newPsw, SIGNAL(editingFinished()), this, SLOT(onNewPswChanged()));
    connect(ui->lineEdit_confPsw, SIGNAL(editingFinished()), this, SLOT(onNewPswChanged()));
}

 QQueueSystemSetting::QQueueSystemSetting(const QQueueSystemSetting& object):
     QWidget(static_cast<QWidget*>(object.parent())),
     ui(new Ui::QQueueSystemSetting)
 {
     ui->setupUi(this);
 }

QQueueSystemSetting::~QQueueSystemSetting()
{
    if(this->timeFont != nullptr)
    {
        delete this->timeFont;
        this->timeFont = nullptr;
    }
    delete ui;
}

void QQueueSystemSetting::initData()
{
    QSettings settings("./config/setting.ini",QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    settings.beginGroup("DateTime");
    auto allkeys = settings.allKeys();
    foreach(auto key, allkeys)
    {
        auto formate = settings.value(key,"").toString();
        this->ui->comboBox_timeFormate->addItem(QDateTime::currentDateTime().toString(formate), formate);
    }
    settings.endGroup();                   
    this->ui->checkBox_ShowPsw->setCheckState(Qt::Unchecked);
    this->ui->checkBox_showTime->setCheckState(Qt::Checked);
    this->ui->checkBox_enableIdCard->setCheckState(Qt::Checked);
    this->isNewSetting = true;
    this->timeFont = nullptr;
    this->tempPsw = "";
    auto validator = new QIntValidator(0,65536,this);
    this->ui->lineEdit_IdCardCount->setValidator(validator);
    this->ui->lineEdit_listenPort->setValidator(validator);
    this->tempId= -1;
    this->isMatchOld = true;
    this->isMatchNew = false;
}

void QQueueSystemSetting::initDefaultData()
{
    /// 从数据库中进行检索
    QStringList columns;
    QVector<QVariant> values;
    auto records = QQueueSqlHelper::getQQueueSqlHelper()->queryRecord("System",columns,values);
    foreach(auto item , records)
    {
        this->ui->lineEdit_siteCode->setText(item["siteCode"].toString());
        this->ui->lineEdit_siteName->setText(item["siteName"].toString());
        this->ui->checkBox_showTime->setCheckState(static_cast<Qt::CheckState>(item["isShowTime"].toInt()));
        this->ui->comboBox_timeFormate->setCurrentIndex(this->ui->comboBox_timeFormate->findData(item["timeFormate"].toString()));
        this->timeFont = item["timeFont"].toString().isEmpty() == true? nullptr: new QFont();
        if(nullptr != this->timeFont)
        {
            this->timeFont->fromString(item["timeFont"].toString());
        }
        this->ui->comboBox_timePosition->setCurrentIndex(this->ui->comboBox_timePosition->findText(item["timePosition"].toString()));
        this->tempPsw = item["password"].toString();
        this->ui->timeEdit_shutdown->setTime(QTime::fromString(item["shutdownTime"].toString(),"HH:mm:ss"));
        this->ui->timeEdit_clear->setTime(QTime::fromString(item["clearTime"].toString(),"HH:mm:ss"));
        this->ui->lineEdit_listenPort->setText(item["listenPort"].toString());
        this->ui->checkBox_enableIdCard->setCheckState(static_cast<Qt::CheckState>(item["useIdCard"].toInt()));
        this->ui->checkBox_dupIdCard->setCheckState(static_cast<Qt::CheckState>(item["isDulp"].toInt()));
        this->ui->checkBox_hideInputIdCard->setCheckState(static_cast<Qt::CheckState>(item["isHideManuInput"].toInt()));
        this->ui->lineEdit_IdCardCount->setText(item["ticketCount"].toString());
        this->tempId = item["id"].toInt();
        this->isNewSetting = false;
        this->isMatchNew = true;
        this->onShowIdCard(static_cast<Qt::CheckState>(item["useIdCard"].toInt()));
        this->onShowTime(static_cast<Qt::CheckState>(item["isShowTime"].toInt()));
    }
}

void QQueueSystemSetting::onShowPassword(int state)
{
    if(static_cast<Qt::CheckState>( state) == Qt::Unchecked)
    {
        this->ui->lineEdit_oldPsw->setEchoMode(QLineEdit::Password);
        this->ui->lineEdit_newPsw->setEchoMode(QLineEdit::Password);
        this->ui->lineEdit_confPsw ->setEchoMode(QLineEdit::Password);
    }
    else if(static_cast<Qt::CheckState>( state) == Qt::Checked)
    {
        this->ui->lineEdit_oldPsw->setEchoMode(QLineEdit::Normal);
        this->ui->lineEdit_newPsw->setEchoMode(QLineEdit::Normal);
        this->ui->lineEdit_confPsw ->setEchoMode(QLineEdit::Normal);
    }
}

void QQueueSystemSetting::onShowTime(int state)
{
    if(static_cast<Qt::CheckState>( state) == Qt::Unchecked)
    {
        this->ui->comboBox_timeFormate->setEnabled(false);
        this->ui->pushButton_fontSet->setEnabled(false);
        this->ui->comboBox_timePosition->setEnabled(false);
    }
    else if(static_cast<Qt::CheckState>( state) == Qt::Checked)
    {
        this->ui->comboBox_timeFormate->setEnabled(true);
        this->ui->pushButton_fontSet->setEnabled(true);
        this->ui->comboBox_timePosition->setEnabled(true);
    }
}

void QQueueSystemSetting::onShowIdCard(int state)
{
    if(static_cast<Qt::CheckState>( state) == Qt::Unchecked)
    {
        this->ui->checkBox_dupIdCard->setEnabled(false);
        this->ui->checkBox_hideInputIdCard->setEnabled(false);
        this->ui->lineEdit_IdCardCount->setEnabled(false);
    }
    else if(static_cast<Qt::CheckState>( state) == Qt::Checked)
    {
        this->ui->checkBox_dupIdCard->setEnabled(true);
        this->ui->checkBox_hideInputIdCard->setEnabled(true);
        this->ui->lineEdit_IdCardCount->setEnabled(true);
    }
}

void QQueueSystemSetting::onBtnFontSetting()
{
    bool ok = false;
    auto font = QFontDialog::getFont(&ok,this);
    if(true == ok)
    {
        this->timeFont = new QFont(font);
    }
}

void QQueueSystemSetting::onOldPswChanged()
{
    this->isMatchOld = false;
    if((false == this->ui->lineEdit_oldPsw->text().isEmpty()) && (false == this->tempPsw.isEmpty()))
    {
        QByteArray hashData = QCryptographicHash::hash( this->ui->lineEdit_oldPsw->text().toLocal8Bit(),QCryptographicHash::Md5);        
        if(this->tempPsw != QString(hashData))
        {
            QMessageBox msgBox(this);
            msgBox.setText(QObject::tr(""
                                       "\r\n     原密码输入错误     \r\n"
                                       ""));
            msgBox.exec();
            this->ui->lineEdit_oldPsw->clear();
        }
        else
        {
            this->isMatchOld = true;
        }
    }
}

void QQueueSystemSetting::onNewPswChanged()
{
   this->isMatchNew = false;
   if((false == this->ui->lineEdit_newPsw->text().isEmpty()) && (false == this->ui->lineEdit_confPsw->text().isEmpty()))
   {
       if(this->ui->lineEdit_newPsw->text() != this->ui->lineEdit_confPsw->text())
       {
           QMessageBox msgBox(this);
           msgBox.setText(QObject::tr(""
                                      "\r\n     两次新密码设置不匹配，     \r\n"
                                      "\r\n     请确认后重新输入.     \r\n"
                                      ""));
           msgBox.exec();
           static_cast<QLineEdit*>(sender())->clear();
       }
       else
       {
           this->isMatchNew =true;
       }
   }
}

void QQueueSystemSetting::SaveUpdated()
{
    auto db = QQueueSqlHelper::getQQueueSqlHelper();
    QStringList columns{"siteCode","siteName","isShowTime","timeFormate","timeFont",
                        "timePosition","password","shutdownTime","clearTime","listenPort",
                        "useIdCard","isDulp","isHideManuInput","ticketCount"};
    qDebug()<<this->ui->comboBox_timeFormate->currentData();
    QVector<QVariant> values{this->ui->lineEdit_siteCode->text(),this->ui->lineEdit_siteName->text(),this->ui->checkBox_showTime->checkState(),
                            this->ui->comboBox_timeFormate->currentData(),this->timeFont == nullptr? "":this->timeFont->toString(),this->ui->comboBox_timePosition->currentText(),
                            this->tempPsw, this->ui->timeEdit_shutdown->time().toString("HH:mm:ss"), this->ui->timeEdit_clear->time().toString("HH:mm:ss"),
                            this->ui->lineEdit_listenPort->text(), this->ui->checkBox_enableIdCard->checkState(), this->ui->checkBox_dupIdCard->checkState(),
                            this->ui->checkBox_hideInputIdCard->checkState(), this->ui->lineEdit_IdCardCount->text().toInt()};
    if(true == this->isNewSetting)
    {
        if(false == this->isMatchNew)
        {
            QMessageBox msgBox(this);
            msgBox.setText(QObject::tr(""
                                       "\r\n     请设置新密码.     \r\n"
                                       ""));
            msgBox.exec();
        }
        else
        {
            values[6] = QString(QCryptographicHash::hash( this->ui->lineEdit_newPsw->text().toLocal8Bit(),QCryptographicHash::Md5));
            db->insertOneRecord("System", columns, values);
        }
    }
    else
    {
        if((true == this->isMatchOld)&&(true == this->isMatchNew))
        {
            values[6] = QString(QCryptographicHash::hash( this->ui->lineEdit_newPsw->text().toLocal8Bit(),QCryptographicHash::Md5));
        }
        db->updateOneRecord("System", this->tempId, columns, values);
    }
    this->initData();
}
