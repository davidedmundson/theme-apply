#pragma once

#include "abstracttask.h"

class IconTask : public AbstractTask
{
    Q_OBJECT
public:
    IconTask(const QString &filePath);
    void run() override;
    void setGtk2();
    void setGtk3();
    void setKDE4();
    void setKDE5();
private:
    QString m_name;
};
