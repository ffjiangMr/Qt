#include "systemsetttingtab.h"
#include <QDateTime>



SystemSetttingTab::SystemSetttingTab(QWidget *parent) : QWidget(parent)
{
    tab_layout = new QVBoxLayout(this);
    tab_layout->setDirection(QBoxLayout::TopToBottom);
    if(nullptr != tab_layout)
    {
        this->initSiteInfo();
        this->initTimeFormat();
        this->initSystemInfo();
    }
}

void SystemSetttingTab::initSiteInfo()
{
    QGroupBox* siteInfo_group = new QGroupBox(QObject::tr("网点信息设置"));
    site_code_lab = new QLabel();
    site_code_lab->setText(QObject::tr("网点代码："));
    site_code_line = new QLineEdit();
    site_code_line->setObjectName(QString::fromUtf8("site_code_line"));
    site_code_lab->setBuddy(site_code_line);
    QHBoxLayout *site_info_hLayout = new QHBoxLayout();
    site_info_hLayout->addWidget(site_code_lab,1);
    site_info_hLayout->addWidget(site_code_line,4);
    site_info_hLayout->addStretch(1);
    site_name_lab = new QLabel();
    site_name_lab->setText(QObject::tr("网点名称："));
    QLineEdit* site_name_line = new QLineEdit();
    site_name_line->setObjectName(QString::fromUtf8("site_name_line"));
    site_name_lab->setBuddy(site_name_line);
    site_info_hLayout->addWidget(site_name_lab,1);
    site_info_hLayout->addWidget(site_name_line,4);
    site_info_hLayout->addStretch(8);
    siteInfo_group->setLayout(site_info_hLayout);
    tab_layout->addWidget(siteInfo_group,Qt::AlignHCenter);
}

void SystemSetttingTab::initTimeFormat()
{
    QGroupBox* timeInfo_group = new QGroupBox(QObject::tr("时间格式设置"));
    QHBoxLayout* time_info_hLayout = new QHBoxLayout();
    time_info_chk =new QCheckBox();
    time_format_lab = new QLabel();
    time_format_cmb = new QComboBox();
    time_format_btn = new QPushButton();
    time_position_lab = new QLabel();
    time_position_cmb = new QComboBox();

    this->updateDateFormatItem();
    this->updatePositionItem();

    time_info_chk->setText(QObject::tr("显示时间"));
    time_format_lab->setText(QObject::tr("显示格式："));
    time_format_btn->setText(QObject::tr("字体设置"));
    time_position_lab->setText(QObject::tr("显示位置："));

    time_format_lab->setBuddy(time_format_cmb);
    time_position_lab->setBuddy(time_position_cmb);


    time_info_hLayout->addWidget(time_info_chk,3);

    time_info_hLayout->addWidget(time_format_lab,2);

    time_info_hLayout->addWidget(time_format_cmb,10);
    time_info_hLayout->addStretch(1);
    time_info_hLayout->addWidget(time_format_btn,4);
    time_info_hLayout->addStretch(1);
    time_info_hLayout->addWidget(time_position_lab,2);

    time_info_hLayout->addWidget(time_position_cmb,4);
    time_info_hLayout->addStretch(1);

    timeInfo_group->setLayout(time_info_hLayout);
    tab_layout->addWidget(timeInfo_group,Qt::AlignHCenter);
}

void SystemSetttingTab::updateDateFormatItem()
{
    if(nullptr != this->time_format_cmb)
    {
        this->time_format_cmb->clear();
        auto now = QDateTime::currentDateTime();
        this->time_format_cmb->addItem(now.toString(QObject::tr("yyyy年MM月dd日 HH:mm:ss")));
        this->time_format_cmb->addItem(now.toString(QObject::tr("HH:mm:ss yyyy年MM月dd日")));
        this->time_format_cmb->addItem(now.toString(QObject::tr("yyyy年MM月dd日 HH:mm:ss ap")));
        this->time_format_cmb->addItem(now.toString(QObject::tr("HH:mm:ss ap yyyy年MM月dd日")));
    }
}

void SystemSetttingTab::updatePositionItem()
{
    if(nullptr != this->time_position_cmb)
    {
        this->time_position_cmb->clear();
        this->time_position_cmb->addItem(QObject::tr("左上角"));
        this->time_position_cmb->addItem(QObject::tr("左下角"));
        this->time_position_cmb->addItem(QObject::tr("右上角"));
        this->time_position_cmb->addItem(QObject::tr("右上角"));
    }
}

void SystemSetttingTab::initSystemInfo()
{
    QGroupBox* systemInfo_group = new QGroupBox(QObject::tr("其他信息设置"));
    QVBoxLayout* vlayout = new QVBoxLayout();
    systemInfo_group->setLayout(vlayout);
    system_cha_psw_lab = new QLabel();
    system_cha_psw_lab->setText(QObject::tr("更改密码："));
    system_psw_old_line = new QLineEdit();
    system_psw_old_line->setContextMenuPolicy(Qt::NoContextMenu);//设置无右键菜单
    system_psw_old_line->setPlaceholderText(QString::fromUtf8("原始密码"));//设置密码提示
    system_psw_old_line->setEchoMode(QLineEdit::Password);//设置密码隐藏
    system_psw_old_line->setMaxLength(16);//设置最大长度16位
    system_psw_fir_line = new QLineEdit();
    system_psw_fir_line->setContextMenuPolicy(Qt::NoContextMenu);//设置无右键菜单
    system_psw_fir_line->setPlaceholderText(QString::fromUtf8("新密码"));//设置密码提示
    system_psw_fir_line->setEchoMode(QLineEdit::Password);//设置密码隐藏
    system_psw_fir_line->setMaxLength(16);//设置最大长度16位
    system_psw_sed_line = new QLineEdit();
    system_psw_sed_line->setContextMenuPolicy(Qt::NoContextMenu);//设置无右键菜单
    system_psw_sed_line->setPlaceholderText(QString::fromUtf8("确认设置密码"));//设置密码提示
    system_psw_sed_line->setEchoMode(QLineEdit::Password);//设置密码隐藏
    system_psw_sed_line->setMaxLength(16);//设置最大长度16位
    sys_show_psw = new QCheckBox();
    sys_show_psw->setText(QObject::tr("显示密码"));
    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addWidget(system_cha_psw_lab, 2);
    hLayout->addWidget(system_psw_old_line, 4);
    hLayout->addWidget(system_psw_fir_line, 4);
    hLayout->addWidget(system_psw_sed_line, 4);
    hLayout->addWidget(sys_show_psw, 2);
    hLayout->addStretch(8);
    vlayout->addLayout(hLayout);

    system_close_lab = new QLabel();
    system_close_lab->setText(QObject::tr("关机时间："));
    sys_close_time = new QTimeEdit();
    system_close_lab->setBuddy(sys_close_time);

    system_clear_lab = new QLabel();
    system_clear_lab->setText(QObject::tr("清零时间："));
    sys_clear_time = new QTimeEdit();
    system_clear_lab->setBuddy(sys_clear_time);

    QHBoxLayout* hLayout_close = new QHBoxLayout();
    hLayout_close->addWidget(system_close_lab,4);
    hLayout_close->addWidget(sys_close_time,2);
    hLayout_close->addStretch(1);
    hLayout_close->addWidget(system_clear_lab,4);
    hLayout_close->addWidget(sys_clear_time,2);
    hLayout_close->addStretch(30);
    vlayout->addLayout(hLayout_close);


    system_point_lab = new QLabel();
    system_point_lab->setText(QObject::tr("监听端口："));
    system_point_line = new QLineEdit();
    system_point_lab->setBuddy(system_point_line);

    QHBoxLayout* hLayout_point = new QHBoxLayout();
    hLayout_point->addWidget(system_point_lab,1);
    hLayout_point->addWidget(system_point_line,2);
    hLayout_point->addStretch(20);
    vlayout->addLayout(hLayout_point);

    tab_layout->addWidget(systemInfo_group,Qt::AlignHCenter);
}
