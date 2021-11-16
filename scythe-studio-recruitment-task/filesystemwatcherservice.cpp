#include "eventlogmodel.h"
#include "filesystemwatcherservice.h"
#include "watchpathmodel.h"

#include <QDateTime>
#include <QFileDialog>

FileSystemWatcherService::FileSystemWatcherService(QObject *parent) : QObject(parent)
{
    watcher = new QFileSystemWatcher(this);


}


void FileSystemWatcherService::onAddClicked(QString path)
{
    qDebug() << Q_FUNC_INFO << path.replace("file:///", "") ;
    watcher->addPath(path);
    WatchPathModel::instance()->paths(watcher->directories());
    // Save the list of current contents if the added path is a directory

    QFileInfo f(path);

    if(f.isDir())
    {
        const QDir dirw(path);
        _currContents[path] = dirw.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    }
}

void FileSystemWatcherService::onRemove(QString path)
{
    qDebug() << Q_FUNC_INFO << path ;
    watcher->removePath(path);
    WatchPathModel::instance()->paths(watcher->directories());
}


void FileSystemWatcherService::onClearClicked()
{

    watcher->removePaths(watcher->directories()) ;
    watcher->removePaths(watcher->files()) ;
}


void FileSystemWatcherService::onStartClicked()
{

    qDebug() << Q_FUNC_INFO ;
    if(running == true) return ;

    running = true;


    QObject::connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(onDirectoryChanged(QString)));
    QObject::connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(onFileChanged(QString)));

}

void FileSystemWatcherService::onStopClicked()
{
    if(running == false ) return ;
    running = false;

    QObject::disconnect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(onDirectoryChanged(QString)));
    QObject::disconnect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(onFileChanged(QString)));

}

void FileSystemWatcherService::onDirectoryChanged(QString path)
{
    qDebug() << Q_FUNC_INFO ;
    qDebug() << path ;
    //

    // Compare the latest contents to saved contents for the dir updated to find out the difference(change)

    QStringList currEntryList = _currContents[path];
    const QDir dir(path);

    QStringList newEntryList = dir.entryList(QDir::NoDotAndDotDot  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);

    QSet<QString> newDirSet = QSet<QString>::fromList( newEntryList );

    QSet<QString> currentDirSet = QSet<QString>::fromList( currEntryList );

    // Files that have been added
    QSet<QString> newFiles = newDirSet - currentDirSet;
    QStringList newFile = newFiles.toList();

    // Files that have been removed
    QSet<QString> deletedFiles = currentDirSet - newDirSet;
    QStringList deleteFile = deletedFiles.toList();

    // Update the current set
    _currContents[path] = newEntryList;

    EventLogModel *eventLogModel =  EventLogModel::instance();





    if(!newFile.isEmpty() && !deleteFile.isEmpty())
    {
        // File/Dir is renamed

        if(newFile.count() == 1 && deleteFile.count() == 1)
        {
            qDebug()<<"File Renamed from "<<newFile.first()<<" to "<<deleteFile.first();
            QString file = path + "/"+newFile.first() ;
            EventLogRaw EventLogRaw;
            EventLogRaw.evenType = "Edited";
            EventLogRaw.path = file;
            EventLogRaw.isFolder =   QFileInfo(file).isDir();
            EventLogRaw.timeStamp = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm") ;

            eventLogModel->addEventLogRaw(EventLogRaw);
        }
    }

    else
    {
        // New File/Dir Added to Dir
        if(!newFile.isEmpty())
        {

            qDebug()<<"New Files/Dirs added: "<<newFile;

            foreach(QString file, newFile)
            {
file = path + "/"+file;

                EventLogRaw EventLogRaw;
                EventLogRaw.evenType = "Created";
                EventLogRaw.path = file;
                EventLogRaw.isFolder = QFileInfo(file).isDir();
                EventLogRaw.timeStamp = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm") ;

                eventLogModel->addEventLogRaw(EventLogRaw);


            }
        }

        // File/Dir is deleted from Dir

        if(!deleteFile.isEmpty())
        {
            qDebug()<<"Files/Dirs deleted: "<<deleteFile;
            foreach(QString file, deleteFile)
            {
                file = path + "/"+file;
                EventLogRaw EventLogRaw;
                EventLogRaw.evenType = "Removed";
                EventLogRaw.path = file;
                 EventLogRaw.isFolder = QFileInfo(file).isDir();
                EventLogRaw.timeStamp = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm") ;

                eventLogModel->addEventLogRaw(EventLogRaw);
            }
        }

    }
}


void FileSystemWatcherService::onFileChanged(QString path)
{
    qDebug() << Q_FUNC_INFO ;
    qDebug() << path ;
}


