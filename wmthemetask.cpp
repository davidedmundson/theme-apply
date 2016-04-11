#include "wmthemetask.h"

#include <QProcess>
#include <QScreen>
#include <QUrl>
#include <QGuiApplication>

#include <QDebug>

#include <kwindowsystem.h>

WmThemeTask::WmThemeTask(const QString &name)
    :AbstractTask()
{
    m_name = name;
}

void WmThemeTask::run() {
    const QString de = desktopEnvironment();
    if (de == "xfce") {
        startXfce();
    }
}

void WmThemeTask::startXfce() {
    QProcess proc;
    proc.start("xfconf-query", QStringList({
                        "--channel",
                        "xfwm4",
                        "--property",
                        "/general/theme",
                        "--set",
                        m_name}));
    proc.waitForFinished();
}
