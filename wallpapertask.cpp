#include "wallpapertask.h"

#include <QProcess>
#include <QScreen>
#include <QUrl>
#include <QGuiApplication>

#include <QDebug>

#include <kwindowsystem.h>

WallpaperTask::WallpaperTask(const QString &filePath)
    :AbstractTask()
{
    m_filePath = filePath;
}

void WallpaperTask::run() {
    const QString de = desktopEnvironment();
    if (de == "xfce") {
        startXfce();
    } else if (de == "kde") {
        startPlasma();
    } else if (de == "gnome") {
	startGnome3();
    } else {
        setError("unsupported desktop " + de);
    }
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
}


void WallpaperTask::startPlasma() {
    setError("Cannot set wallpaper on Plasma");
}

void WallpaperTask::startGnome2() {
    QProcess::execute("gconftool-2", QStringList({"--type=string", "--set", "/desktop/gnome/background/picture_filename", m_filePath}));
}

void WallpaperTask::startGnome3() {
    QProcess::execute("gsettings", QStringList({"set","org.gnome.desktop.background", "picture-uri", QUrl::fromLocalFile(m_filePath).toString()}));
}
