#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <qobject.h>
#include "screenshot.h"
#include "grabber.h"
#include "xlib.h"
#include "winapi.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{

    Q_OBJECT
public:

    #ifdef Q_OS_WIN32
        winapi * g;
    #elif defined(Q_OS_MACOSX)
        winapi * g;
    #else
        xlib * g;
    #endif

    static QList<uint> keyboardActivity;
    static QList<uint> mouseActivity;


    static void addActivity(bool keyboard, uint unixTime);
    static uint lastMouseActivity();
    static QList<uint> getMouseActivity();
    static QList<uint> getKeyboardActivity();


    explicit Window(QWidget *parent = 0);
    ~Window();

public slots:
    void on_pushButton_clicked();
    void window_screen_updated();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Window *ui;
    screenshot* s;

};

#endif // WINDOW_H
