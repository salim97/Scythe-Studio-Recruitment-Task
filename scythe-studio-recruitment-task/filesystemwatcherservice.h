#ifndef FILESYSTEMWATCHERSERVICE_H
#define FILESYSTEMWATCHERSERVICE_H

#include <QObject>
#include <QDebug>
#include <qfilesystemwatcher.h>
class FileSystemWatcherService : public QObject
{
    Q_OBJECT
public:
    explicit FileSystemWatcherService(QObject *parent = nullptr);

public slots:

    void onAddClicked(QString path);
    void onClearClicked();
    void onStartClicked();
    void onStopClicked();
    void onRemove(QString path);
signals:

private slots:
    void onDirectoryChanged(QString path);

    void onFileChanged(QString path);

private:
     QFileSystemWatcher *watcher;
     bool running = false;

     QMap<QString, QStringList> _currContents; //maintain list of current contents of each watched directory

};

#endif // FILESYSTEMWATCHERSERVICE_H
