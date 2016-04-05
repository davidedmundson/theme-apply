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

void AbstractTask::runProcessAndFinish(const QString &program, const QStringList &arguments, int successExitCode)
{
    auto proc = new QProcess(this);

    connect(proc, static_cast<void (QProcess::*)(int,QProcess::ExitStatus)>(&QProcess::finished),
            this, [=](int exitCode, QProcess::ExitStatus exitStatus) {
        if (exitStatus == QProcess::NormalExit && exitCode == successExitCode) {
            emit finished(true);
        } else {
            emit finished(false);
        }
    });

    proc->start(program, arguments);

    if (!proc->waitForStarted() ) {
        emit finished(false);
    }
}
