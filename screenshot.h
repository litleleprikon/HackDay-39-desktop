#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QPixmap>
#include <QScreen>

class screenshot
{
public:
    screenshot();
    static QString makeScreenshot();
    static QString grabActiveWindow();
signals:
public slots:

};

#endif // SCREENSHOT_H
