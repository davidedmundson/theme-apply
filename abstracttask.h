#pragma once

#include <QThread>

class AbstractTask : public QThread
{
    Q_OBJECT
public:
    static AbstractTask * create(const QString &type, const QString &value);
    virtual ~AbstractTask();

protected:
    AbstractTask();
    QString desktopEnvironment() const;
};
