
#include "winapi.h"
#include <QPixmap>
#include <QDateTime>
#include <QScreen>
#include <QGuiApplication>

#ifdef Q_OS_WIN32
#include "psapi.h"
#include "window.h"
#include "windows.h"
#endif

winapi::winapi()
{
}



#ifdef Q_OS_WIN32


HHOOK hHook = NULL;
HHOOK mHook = NULL;

LRESULT CALLBACK MyLowLevelKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_KEYDOWN)
    {
        QDateTime* dt = new QDateTime();
        Window::keyboardActivity.append(dt->toTime_t());
    }
    else if (wParam == WM_MOUSEMOVE)
    {
        QDateTime dt = QDateTime::currentDateTimeUtc();
        if (Window::mouseActivity.isEmpty())
        {
            Window::mouseActivity.append(dt.toTime_t());
        }
        else if (dt.toTime_t() != Window::lastMouseActivity())
        {
            Window::mouseActivity.append(dt.toTime_t());
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}
#endif

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
        originalPixmap.save(fileName+"."+format, format.toLatin1().constData());
        return fileName;
    }
    else
    {
        return QString("");
    }
}

#ifdef Q_OS_WIN32
QString winapi::grabActiveWindow()
{
    /// TODO: write WinAPI grabber of window
    HWND foreground = GetForegroundWindow();
    QString answer = "";
    if (foreground)
    {
        DWORD lpdwProcessId;
        GetWindowThreadProcessId(foreground, &lpdwProcessId);
        HANDLE Handle = OpenProcess(
                PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                FALSE,
                lpdwProcessId
            );
            if (Handle)
            {
                TCHAR Buffer[MAX_PATH];
                if (GetModuleFileNameEx(Handle, 0, Buffer, MAX_PATH))
                {
                    answer = QString::fromWCharArray(Buffer);
                    answer = answer.split('\\').last().split(' ').first();
                }
                else
                {
                    answer = QString::number(lpdwProcessId);
                }
                CloseHandle(Handle);
            }
    }
    return answer;
}

void winapi::startKeyboardMouseCapture()
{
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, MyLowLevelKeyBoardProc, NULL, 0);
    mHook = SetWindowsHookEx(WH_MOUSE_LL, MyLowLevelKeyBoardProc, NULL, 0);
}



void winapi::stopKeyboardMouseCapture()
{
    UnhookWindowsHookEx(hHook);
}

void winapi::keyPressed()
{

}

void winapi::parseOutput()
{

}


#endif


