#include "xlib.h"
#include "window.h"

#include <QPixmap>
#include <QDateTime>
#include <QScreen>
#include <QGuiApplication>
#include <QProcess>
#include <QDebug>
#include <QRegExp>
#include <QApplication>

xlib::xlib()
{
}

QString xlib::makeScreenshot()
{
    QPixmap originalPixmap;
    QDateTime dt = QDateTime::currentDateTimeUtc();
    long unixTime = dt.toTime_t();
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen)
        originalPixmap = screen->grabWindow(0);
    QString format = "png";
    //QString initialPath = QDir::currentPath() + "/untitled." + format;
    QString fileName = QString::number(unixTime);
    if (!fileName.isEmpty())
    {
        originalPixmap.save(fileName, format.toLatin1().constData());
        return fileName;
    }
    else
    {
        return QString("");
    }
}

QString xlib::grabActiveWindow()
{
    /// xdotool required for Linux
    QProcess *process = new QProcess(QApplication::instance());
    QString cmd = "xdotool getwindowfocus getwindowpid";
    QString pid;
    process->start(cmd);
    process->waitForFinished();
    pid = QString(process->readAllStandardOutput());
    cmd = QString("ps -p ") + pid + QString(" -o cmd=");
    process->start(cmd);
    process->waitForFinished();
    //QString answer = QString(process->readAllStandardOutput());
    //QString answer = QString(process->readAllStandardOutput()).split('/').last();
    QString answer = QString(process->readAllStandardOutput()).split(' ').first().split('/').last();
    return answer;
}

void xlib::startKeyboardMouseCapture()
{
    /// xinput required for Linux
    keycapture = new QProcess(this);
    QString cmd = "xinput test-xi2 --root";
    connect (keycapture, SIGNAL(readyReadStandardOutput()), this, SLOT(parseOutput()));
    keycapture->start(cmd);

}

void xlib::stopKeyboardMouseCapture()
{
    keycapture->kill();
    Window::keyboardActivity.clear();
    Window::mouseActivity.clear();

}

void xlib::parseOutput()
{
    QDateTime dt = QDateTime::currentDateTimeUtc();
    long unixTime = dt.toTime_t();
    //qDebug() << unixTime;
    QString xinputOutput = keycapture->readAllStandardOutput();
    QRegExp captureEvent = QRegExp("EVENT type ([0-9]+)");
    captureEvent.indexIn(xinputOutput);
    int eventCode = captureEvent.cap(1).toInt();
    switch(eventCode)
    {
        case 3:
        case 14:
            Window::addActivity(true, unixTime);
        break;
        case 5:
        case 16:
            Window::addActivity(false, unixTime);
        break;
        case 6:
        case 17:
            if (!Window::mouseActivity.isEmpty())
            {
                if (Window::lastMouseActivity() != unixTime) {
                    Window::addActivity(false, unixTime);
                }
            }
            else { Window::addActivity(false, unixTime);}
        break;
    }
}


