
#include "window.h"
#include "ui_window.h"
#include "screenshot.h"
#include "winapi.h"
#include "xlib.h"

#include <QTimer>
#include <QKeyEvent>

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(window_screen_updated()));
    timer->start(100);
    #ifdef Q_OS_WIN32
        g = new winapi();
    #elif defined(Q_OS_MACOSX)
        g = new winapi();
    #else
        g = new xlib();
    #endif
    ui->setupUi(this);


}

Window::~Window()
{
    delete ui;
}

void Window::on_pushButton_clicked()
{
    g->makeScreenshot();
}

void Window::window_screen_updated()
{
    ui->label_2->setText(g->grabActiveWindow());
    uint mousec = g->mouseActivity->count();
    uint keyc = g->keyboardActivity->count();
    QString text = "Keyboard: " + QString::number(keyc)
            + ", mouse: " + QString::number(mousec);
    ui->label->setText(text);
}

void Window::on_pushButton_2_clicked()
{
    g->startKeyboardMouseCapture();
}

void Window::on_pushButton_3_clicked()
{
    g->stopKeyboardMouseCapture();
}
