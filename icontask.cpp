#include "icontask.h"

#include <QDebug>
#include <QProcess>


#include <gtk/gtk.h>

IconTask::IconTask(const QString &name)
    :AbstractTask()
{
    m_name = name;
}

void IconTask::run() {
    setGtk3();
}

void IconTask::setGtk3() {
    GtkSettings *settings = gtk_settings_get_default();
    g_object_set(settings, "gtk-icon-theme-name", m_name.toLatin1(), NULL);
    
    
    QProcess proc;
    proc.start("xfconf-query", QStringList({
                    "--channel",
                    "xsettings",
                    "--property",
                    "/Net/IconThemeName",
                    "--set",
                    m_name}));
    proc.waitForFinished();
}
