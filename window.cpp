
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
    #if defined(Q_OS_WIN32)
        g = new winapi();
    #elif defined(Q_OS_MACOSX)
        g = new winapi();
    #else
        g = new xlib();
    #endif
    ui->setupUi(this);

}

QList<uint> Window::keyboardActivity =QList<uint>();
QList<uint> Window::mouseActivity = QList<uint>();


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
    uint mousec = Window::mouseActivity.count();
    uint keyc = keyboardActivity.count();
    QString text = "Keyboard: " + QString::number(keyc)
            + ", mouse: " + QString::number(mousec);
    ui->label->setText(text);
}

void Window::on_pushButton_2_clicked()
{
    this->ui->pushButton_2->setEnabled(false);
    this->ui->pushButton_3->setEnabled(true);
    g->startKeyboardMouseCapture();
}

void Window::on_pushButton_3_clicked()
{
    this->ui->pushButton_2->setEnabled(true);
    this->ui->pushButton_3->setEnabled(false);
    g->stopKeyboardMouseCapture();
    Window::keyboardActivity.clear();
    Window::mouseActivity.clear();

}

void Window::addActivity(bool keyboard, uint unixTime)
{
    if (keyboard)
    {
        keyboardActivity.append(unixTime);
    }
    else
    {
        mouseActivity.append(unixTime);
    }
}

uint Window::lastMouseActivity()
{
    return mouseActivity.last();
}
