#include "mousethemetask.h"

#include <QProcess>
#include <QScreen>
#include <QUrl>
#include <QGuiApplication>

#include <QDebug>

MouseThemeTask::MouseThemeTask(const QString &name)
    :AbstractTask()
{
    m_name = name;
}

void MouseThemeTask::run() {
    const QString de = desktopEnvironment();
    if (de == "xfce") {
        startXfce();
    }
}

void MouseThemeTask::startXfce() {
    QProcess proc;
    proc.start("xfconf-query", QStringList({
                        "--channel",
                        "xsettings",
                        "--property",
                        "/Gtk/CursorThemeName",
                        "--set",
                        m_name}));
    proc.waitForFinished();
}
