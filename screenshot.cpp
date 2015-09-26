#include "screenshot.h"
#include <QGuiApplication>
#include <QDir>
#include <QDateTime>
#include <QApplication>
#include <QWidget>

screenshot::screenshot()
{

}

//QString winapi::makeScreenshot()
//{
//    QPixmap originalPixmap;
//    QDateTime* dt = new QDateTime();
//    QScreen *screen = QGuiApplication::primaryScreen();
//    if (screen)
//        originalPixmap = screen->grabWindow(0);
//    QString format = "png";
//    //QString initialPath = QDir::currentPath() + "/untitled." + format;
//    QString fileName = QString::number(dt->toTime_t());
//    if (!fileName.isEmpty())
//    {
//        originalPixmap.save(fileName, format.toLatin1().constData());
//        return fileName;
//    }
//    else
//    {
//        return QString("");
//    }
//}

//QString winapi::grabActiveWindow()
//{
//    /// xdotool getwindowfocus getwindowname
//    QProcess *process = new QProcess(this);
//    QString cmd = "xdotool getwindowfocus getwindowname";
//    QString answer;
//    process->start(file);
//    if(!process.waitForFinished())
//    {
//        answer = QString("Error!");
//    }
//    else
//    {
//        answer = QString(process.readAllStandardOutput());
//    }
//    return answer;

//}

