/*
 * Copyright (C) 2012-2013 Matt Broadstone
 * Contact: http://bitbucket.org/devonit/qjsonrpc
 *
 * This file is part of the QJsonRpc Library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */
#include <QDebug>
#include <QTimer>
#include <QEventLoop>
#include <QThreadPool>
#include <QRunnable>

#include "cocoservice.h"

CocoService::CocoService(QObject *parent)
    : QJsonRpcService(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(10);
}

void CocoService::testMethod()
{
    qDebug() << Q_FUNC_INFO << "called" << endl;
}

void CocoService::testMethodWithParams(const QString &first, bool second, double third)
{
    qDebug() << Q_FUNC_INFO << "called with parameters: " << endl
             << " first: " << first << endl
             << "second: " << second << endl
             << " third: " << third << endl;
}


QString CocoService::uploadArduinoScript(const QString &code)
{

    QString tmpDir = "/tmp/CocoTmp/";
    QString tmpDirCompile = "/tmp/CocoTmpCompile/";
    QString scriptName = "CocoTmp.ino";
    QString uploadCmd = "/Users/xcorex/Documents/Arduino/hardware/CocoMake7/avr/tools/avrdude/macosx/avrdude -C/Users/xcorex/Documents/Arduino/hardware/CocoMake7/avr/tools/avrdude/macosx/avrdude.conf -pattiny85 -cusbasp -P/dev/cu.usbmodem1411 -b19200 -D -Uflash:w:" + tmpDirCompile + scriptName +  ".hex:i";
    QString workingdir =  QDir::currentPath();

    QProcess makeProcess;
    makeProcess.setProcessChannelMode(QProcess::MergedChannels);
    makeProcess.setWorkingDirectory(workingdir);

    makeProcess.start(uploadCmd);
    makeProcess.waitForFinished();
    qDebug() << makeProcess.readAll();

    return "DONE";
}

QString CocoService::compileArduinoScript(const QString &code)
{

    QString tmpDir = "/tmp/CocoTmp/";
    QString tmpDirCompile = "/tmp/CocoTmpCompile/";

    QString scriptName = "CocoTmp.ino";

    QDir tmp;
    tmp.mkdir(tmpDir);
    tmp.mkdir(tmpDirCompile);


    QFile tmpScript(tmpDir+scriptName);
    tmpScript.open(QIODevice::WriteOnly);
    QTextStream out(&tmpScript);
    out << code;
    tmpScript.close();

    QString scriptPath = tmpDir+scriptName;
    QString compileCmd = "/Users/xcorex/Downloads/Arduino-2.app/Contents/Java/arduino-builder -compile -logger=machine -hardware \"/Users/xcorex/Downloads/Arduino-2.app/Contents/Java/hardware\" -hardware \"/Users/xcorex/Library/Arduino15/packages\" -hardware \"/Users/xcorex/Documents/Arduino/hardware\" -tools \"/Users/xcorex/Downloads/Arduino-2.app/Contents/Java/tools-builder\" -tools \"/Users/xcorex/Downloads/Arduino-2.app/Contents/Java/hardware/tools/avr\" -tools \"/Users/xcorex/Library/Arduino15/packages\" -built-in-libraries \"/Users/xcorex/Downloads/Arduino-2.app/Contents/Java/libraries\" -libraries \"/Users/xcorex/Documents/Arduino/libraries\" -fqbn=CocoMake7:avr:cocomake -ide-version=10609 -build-path \"" + tmpDirCompile + "\" -warnings=none -prefs=build.warn_data_percentage=75 -verbose \"" + scriptPath + "\"";
    QString uploadCmd = "/Users/xcorex/Documents/Arduino/hardware/CocoMake7/avr/tools/avrdude/macosx/avrdude -C/Users/xcorex/Documents/Arduino/hardware/CocoMake7/avr/tools/avrdude/macosx/avrdude.conf -pattiny85 -cusbasp -P/dev/cu.usbmodem1411 -b19200 -D -Uflash:w:" + tmpDirCompile + scriptName +  ".hex:i";
    QString workingdir =  QDir::currentPath();

    QProcess makeProcess;
    makeProcess.setProcessChannelMode(QProcess::MergedChannels);
    makeProcess.setWorkingDirectory(workingdir);

    makeProcess.start(compileCmd);
    makeProcess.waitForFinished();
    qDebug() << makeProcess.readAll();

    makeProcess.start(uploadCmd);
    makeProcess.waitForFinished();
    qDebug() << makeProcess.readAll();

    return "DONE";
}


QString CocoService::testMethodWithParamsAndReturnValue(const QString &name)
{
    return QString("Hello %1").arg(name);
}

void CocoService::testMethodWithDefaultParameter(const QString &first, const QString &second)
{

    qDebug() << Q_FUNC_INFO << endl
             << "first: " << first << endl
             << (second.isEmpty() ? "not defined, default parameter" : second) << endl;
}

QString CocoService::immediateResponse()
{
    return "immediate";
}

QString CocoService::longTaskWithImmediateResponse()
{
    QEventLoop loop;
    QTimer::singleShot(1000, &loop, SLOT(quit()));
    loop.exec();
    return "long immediate";
}

class DelayedResponseJob : public QRunnable
{
public:
    DelayedResponseJob(const QJsonRpcServiceRequest &request)
        : m_request(request)
    {
    }

protected:
    virtual void run() {
        // do some work
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, SLOT(quit()));
        loop.exec();

        // respond
        QJsonRpcMessage response = m_request.request().createResponse(QLatin1String("long delayed"));
        m_request.respond(response);
    }

private:
    QJsonRpcServiceRequest m_request;

};

QString CocoService::longTaskWithDelayedResponse()
{
    beginDelayedResponse();
    QThreadPool::globalInstance()->start(new DelayedResponseJob(currentRequest()));
    return QString();
}
