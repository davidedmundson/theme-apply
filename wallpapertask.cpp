#include "wallpapertask.h"

#include <QProcess>
#include <QDebug>

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
    runProcessAndFinish("xfconf-query", QStringList({
                            "--channel",
                            "xfce4-desktop",
                            "--property",
                            "/backdrop/screen0/monitor0/image-path",
                            "--set",
                            m_filePath}), 0);
}

void WallpaperTask::startPlasma() {
}

void WallpaperTask::startGnome() {
}
