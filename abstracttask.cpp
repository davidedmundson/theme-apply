#include "abstracttask.h"

#include <QProcess>

#include "wallpapertask.h"

AbstractTask* AbstractTask::create(const QString &type, const QString &value) {
    if (type == "wallpaper") {
        return new WallpaperTask(value);
    }
    return 0;
}

AbstractTask::AbstractTask()
{
}

AbstractTask::~AbstractTask()
{
}

QString AbstractTask::desktopEnvironment() const
{
    return QString::fromLatin1(qgetenv("XDG_CURRENT_DESKTOP")).toLower();
}


