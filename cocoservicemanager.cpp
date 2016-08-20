#include "cocoservicemanager.h"

CocoServiceManager::CocoServiceManager()
{

}

bool CocoServiceManager::startServer()
{
    rpcServer.addService(new CocoService);
    if (!rpcServer.listen(QHostAddress::LocalHost, 8118)) {
        qDebug() << "can't start tcp server: " << rpcServer.errorString();
        this->serverIsRunning = false;
        //return -1;
    }else{
        qDebug() << "started server: " << rpcServer.serverAddress() << " " << rpcServer.serverPort();
        this->serverIsRunning = true;
    }
    return this->serverIsRunning;
}

bool CocoServiceManager::sendTest()
{
    QJsonRpcHttpClient client;
    client.setEndPoint("http://127.0.0.1:9090");

    QJsonArray test;

    test.append(QJsonValue("MIMU"));
    test.append(QJsonValue("MIMI"));
    test.append(QJsonValue("SISI"));

    QJsonObject test2;
    test2["wew"] = "SISI";

//    QJsonRpcMessage request = QJsonRpcMessage::createRequest("coco.testMethodWithParamsAndReturnValue", test2);

        QJsonRpcMessage request = QJsonRpcMessage::createRequest("coco.testMethodWithParamsAndReturnValue", QJsonValue("MIMU"));
    QJsonRpcMessage response = client.sendMessageBlocking(request);
    qDebug()  << request.toJson();
    qDebug()  << response.toJson();
}

bool CocoServiceManager::stopServer()
{
    return false;
}
