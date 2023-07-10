TARGET   = QQueueService
TEMPLATE = app
CONFIG   += console qt
QT = core network

SOURCES  = main.cpp \
    tcpserver.cpp

include(./qtservice/src/qtservice.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    tcpserver.h
