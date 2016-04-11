#pragma once

#include "abstracttask.h"

class WmThemeTask : public AbstractTask
{
    Q_OBJECT
public:
    WmThemeTask(const QString &filePath);
    void run() override;
    void startXfce();
private:
    QString m_name;
};
