#ifndef COCOSERVICEMANAGER_H
#define COCOSERVICEMANAGER_H

#include <QLocalServer>
#include <QFile>
#include <QDir>

#include "qjsonrpchttpserver.h"
#include "qjsonrpchttpclient.h"
#include "cocoservice.h"

class CocoServiceManager
{
public:
    CocoServiceManager();
    bool startServer();
    bool stopServer();


    bool serverIsRunning;

    bool sendTest();
private:
    QJsonRpcHttpServer rpcServer;
};

#endif // COCOSERVICEMANAGER_H
