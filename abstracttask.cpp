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

bool AbstractTask::success() const
{
    return m_errorMessage.isNull();
}

QString AbstractTask::errorMessage() const
{
    return m_errorMessage;
}

void AbstractTask::setError(const QString &errorMessage)
{
    m_errorMessage = errorMessage;
}

QString AbstractTask::desktopEnvironment() const
{
    return QString::fromLatin1(qgetenv("XDG_CURRENT_DESKTOP")).toLower();
}


