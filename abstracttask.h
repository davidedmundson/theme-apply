#pragma once

#include <QObject>

class AbstractTask : public QObject
{
    Q_OBJECT
public:
    static AbstractTask * create(const QString &type, const QString &value);
    virtual ~AbstractTask();

Q_SIGNALS:
    void finished(bool success);

public Q_SLOTS:
    virtual void start() = 0;

protected:
    AbstractTask();
    QString desktopEnvironment() const;

    /*
     * Helper function as we end up writing the same code a lot
     */
    void runProcessAndFinish(const QString &program, const QStringList &arguments, int successErrorCode);
};
