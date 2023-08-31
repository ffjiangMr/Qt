QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \    
    TagPage/DepartmentSetting/qqueuedepartmentsetting.cpp \
    TagPage/EmployeeSetting/qqueueemployeesetting.cpp\
    TagPage/PageSetting/qqueuepagesetting.cpp \
    TagPage/QueueSetting/qqueuequeuesetting.cpp \
    TagPage/SystemSetting/qqueuesystemsetting.cpp\
    TagPage/WindowSetting/qqueuewindowssetting.cpp \
    main.cpp \
    mainwindow.cpp \
    Componment/qqueuelabel.cpp \
    Componment/qqueuelistwidget.cpp \
    qqueuemachinewindow.cpp

HEADERS += \
    DataStruct/qqueueemployeedefinition.h \
    TagPage/DepartmentSetting/qqueuedepartmentsetting.h \
    TagPage/EmployeeSetting/qqueueemployeesetting.h\
    TagPage/PageSetting/qqueuepagesetting.h \
    TagPage/QueueSetting/qqueuequeuesetting.h \
    TagPage/SystemSetting/qqueuesystemsetting.h \
    TagPage/WindowSetting/qqueuewindowssetting.h \
    mainwindow.h \
    DataStruct/qqueuedepartmentdefinition.h \
    Componment/qqueuelabel.h \
    Componment/qqueuelistwidget.h \
    qqueuemachinewindow.h

FORMS += \
    TagPage/DepartmentSetting/qqueuedepartmentsetting.ui \
    TagPage/EmployeeSetting/qqueueemployeesetting.ui\
    TagPage/PageSetting/qqueuepagesetting.ui \
    TagPage/QueueSetting/qqueuequeuesetting.ui \
    TagPage/SystemSetting/qqueuesystemsetting.ui \
    TagPage/WindowSetting/qqueuewindowssetting.ui\
    mainwindow.ui \
    qqueuemachinewindow.ui

INCLUDEPATH += $$PWD/include
LIBS += -L$$PWD/library -lQQueueSqlHelper


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


CONFIG += file_copies

setting.files = $$PWD/config/setting.ini
setting.path = $$OUT_PWD/config/
COPIES += setting

RESOURCES += \
    config/config.qrc \
    image/image.qrc \
    script/script.qrc

DISTFILES += \
    config/setting.ini
