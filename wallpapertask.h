#pragma once

#include "abstracttask.h"

class WallpaperTask : public AbstractTask
{
    Q_OBJECT
public:
    WallpaperTask(const QString &filePath);
    void run() override;
    void startXfce();
    void startPlasma();
    void startGnome2();
    void startGnome3();
private:
    QString m_filePath;
};
