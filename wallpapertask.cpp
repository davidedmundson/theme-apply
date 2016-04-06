#include "wallpapertask.h"

#include <QProcess>
#include <QScreen>
#include <QGuiApplication>

#include <QDebug>

#include <kwindowsystem.h>

WallpaperTask::WallpaperTask(const QString &filePath)
    :AbstractTask()
{
    m_filePath = filePath;
}

void WallpaperTask::start() {
    const QString de = desktopEnvironment();
    if (de == "xfce") {
        startXfce();
        return;
    } else if (de == "kde") {
        qWarning() << "Cannot set wallpaper on Plasma";
        emit finished(false);
        return;
    }

    qWarning() << "unsupported desktop " << de;
    emit finished(false);
    return;
}

void WallpaperTask::startXfce() {
    foreach(const QScreen *screen, qApp->screens()) {
            const QString monitorName = "monitor" + screen->name();
            for (int i=0;i<KWindowSystem::numberOfDesktops();i++) {
                const QString workspaceName = "workspace" + QString::number(i);
                QProcess proc;
                proc.start("xfconf-query", QStringList({
                                    "--channel",
                                    "xfce4-desktop",
                                    "--property",
                                    "/backdrop/screen0/" + monitorName + "/" + workspaceName + "/last-image",
                                    "--set",
                                    m_filePath}));
                proc.waitForFinished();
            }
    }
    emit finished(true);
}


void WallpaperTask::startPlasma() {
}

void WallpaperTask::startGnome() {
}
