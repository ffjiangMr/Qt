#include <QCoreApplication>
#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpServer server(9988);
    server.init();

    return a.exec();
}
