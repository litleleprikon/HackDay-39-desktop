#ifndef XLIB_H
#define XLIB_H

#include "grabber.h"
#include <QProcess>

class xlib : public grabber
{
    QProcess* keycapture;
    QProcess* mousecapture;
public:
    xlib();
    QString makeScreenshot();
    QString grabActiveWindow();
    void startKeyboardMouseCapture();
    void stopKeyboardMouseCapture();

signals:

public slots:
    void parseOutput();
};

#endif // XLIB_H
