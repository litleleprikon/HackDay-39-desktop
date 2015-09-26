#ifndef WINAPI_H
#define WINAPI_H

#include "grabber.h"

class winapi : public grabber
{
public:
    winapi();
    QString makeScreenshot();
    QString grabActiveWindow();

signals:

public slots:
};

#endif // WINAPI_H
