#ifndef WINAPI_H
#define WINAPI_H

#include "grabber.h"
#include <QProcess>

#ifdef Q_OS_WIN32
#include <windows.h>
#endif

class winapi : QObject
{

    QProcess* keycapture;
public:
    winapi();
    QString makeScreenshot();
    #ifdef Q_OS_WIN32
    void catchKey(int nCode, WPARAM wParam, LPARAM lParam);
    QString grabActiveWindow();
    void startKeyboardMouseCapture();
    void stopKeyboardMouseCapture();
    #endif

signals:


public slots:
    #ifdef Q_OS_WIN32
    void keyPressed();
    void parseOutput();
    #endif

};

#endif // WINAPI_H
