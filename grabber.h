#ifndef GRABBER_H
#define GRABBER_H

#include <QObject>
#include <QKeyEvent>

class grabber : public QObject
{
    Q_OBJECT
public:
    long long int keys_pressed;
    explicit grabber(QObject *parent = 0);
    virtual QString makeScreenshot() = 0;
    virtual QString grabActiveWindow() = 0;
    virtual void startKeyboardMouseCapture() = 0;
    virtual void stopKeyboardMouseCapture() = 0;

signals:

public slots:
    virtual void parseOutput() = 0;

};

#endif // GRABBER_H
