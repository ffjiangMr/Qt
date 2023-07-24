#ifndef SYSTEMSETTTINGTAB_H
#define SYSTEMSETTTINGTAB_H

#include <QObject>
#include <QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QFontDialog>
#include <QFont>
#include <QPushButton>
#include <QTimeEdit>

class SystemSetttingTab : public QWidget
{
    Q_OBJECT
public:
    explicit SystemSetttingTab(QWidget *parent = nullptr);

private:
    void initSiteInfo();
    void initTimeFormat();
    void initSystemInfo();
    void updateDateFormatItem();
    void updatePositionItem();

private:

    QVBoxLayout* tab_layout;   

    QLabel* site_code_lab;
    QLabel* site_name_lab;
    QLabel* time_format_lab;
    QLabel* time_position_lab;
    QLabel* system_cha_psw_lab;
    QLabel* system_point_lab;
    QLabel* system_close_lab;
    QLabel* system_clear_lab;

    QLineEdit* site_code_line;
    QLineEdit* site_name_line;
    QLineEdit* system_psw_old_line;
    QLineEdit* system_psw_fir_line;
    QLineEdit* system_psw_sed_line;
    QLineEdit* system_point_line;

    QCheckBox* time_info_chk;
    QCheckBox* sys_show_psw;

    QComboBox* time_format_cmb;
    QComboBox* time_position_cmb;

    QFont* font ;
    QPushButton* time_format_btn;

    QTimeEdit* sys_close_time;
    QTimeEdit* sys_clear_time;

signals:

};

#endif // SYSTEMSETTTINGTAB_H
