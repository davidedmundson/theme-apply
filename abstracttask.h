#pragma once

#include <QThread>

class AbstractTask : public QThread
{
    Q_OBJECT
public:
    static AbstractTask * create(const QString &type, const QString &value);
    virtual ~AbstractTask();

    bool success() const;
    QString errorMessage() const;

protected:
    AbstractTask();
    void setError(const QString &errorMessage);

    QString desktopEnvironment() const;
private:
    QString m_errorMessage;
};
