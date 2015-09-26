#include "xlib.h"

#include <QPixmap>
#include <QDateTime>
#include <QScreen>
#include <QGuiApplication>
#include <QProcess>
#include <QDebug>
#include <QRegExp>

xlib::xlib()
{
    this->keys_pressed = 0;
    this->keyboardActivity = new QList<long>;
    this->mouseActivity = new QList<long>;
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
    QProcess *process = new QProcess(this);
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
    keyboardActivity->clear();
    mouseActivity->clear();

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
            keyboardActivity->push_back(unixTime);
        break;
        case 5:
        case 16:
            mouseActivity->push_back(unixTime);
        break;
        case 6:
        case 17:
            if (!mouseActivity->isEmpty())
            {
                if (mouseActivity->last() != unixTime) {
                    mouseActivity->push_back(unixTime);
                }
            }
            else { mouseActivity->push_back(unixTime);}
        break;
    }
}


