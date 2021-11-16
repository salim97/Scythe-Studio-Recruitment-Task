#ifndef WATCHPATHMODEL_H
#define WATCHPATHMODEL_H

#include <QObject>
#include <mypropertyhelper.h>



class WatchPathModel : public QObject
{
    Q_OBJECT
public:
    explicit WatchPathModel(QObject *parent = nullptr);

    static WatchPathModel* instance();

    ~WatchPathModel()
    {

    }

    AUTO_PROPERTY(QStringList, paths)

private:
    static WatchPathModel* _obj;
};

#endif // WATCHPATHMODEL_H
