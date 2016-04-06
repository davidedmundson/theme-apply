#include <QGuiApplication>
#include <QDebug>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "abstracttask.h"

static const QStringList validTypes = QStringList({QString("wallpaper")});

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv); //QGui as we need monitor names and no. virtual desktops in some cases

    QCommandLineParser parser;
    parser.addPositionalArgument("type", "[wallpaper]");
    parser.addPositionalArgument("value", "the file/name of the setting to apply");

    parser.process(app);

    QStringList args = parser.positionalArguments();
    if (args.size() != 2) {
        parser.showHelp(-1);
    }
    const QString type = args[0];
    const QString value = args[1];

    qDebug() << args;

    if (! validTypes.contains(type)) {
        parser.showHelp();
    }

    QScopedPointer<AbstractTask> task(AbstractTask::create(type, value));
    QMetaObject::invokeMethod(task.data(), "start", Qt::QueuedConnection);

    app.connect(task.data(), &AbstractTask::finished, &app, [&](){
        if (task->success()) {
            app.exit(0);
        }
        qWarning() << task->errorMessage();
        app.exit(-1);
    }
    );

    return app.exec();
}
