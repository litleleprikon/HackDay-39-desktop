#include "winapi.h"
#include <QPixmap>
#include <QDateTime>
#include <QScreen>
#include <QGuiApplication>

winapi::winapi()
{

}

QString winapi::makeScreenshot()
{
    QPixmap originalPixmap;
    QDateTime* dt = new QDateTime();
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen)
        originalPixmap = screen->grabWindow(0);
    QString format = "png";
    //QString initialPath = QDir::currentPath() + "/untitled." + format;
    QString fileName = QString::number(dt->toTime_t());
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

QString winapi::grabActiveWindow()
{
    /// TODO: write WinAPI grabber of window
    return "";

}

