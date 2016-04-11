#pragma once

#include "abstracttask.h"

class MouseThemeTask : public AbstractTask
{
    Q_OBJECT
public:
    MouseThemeTask(const QString &filePath);
    void run() override;
    void startXfce();
private:
    QString m_name;
};
