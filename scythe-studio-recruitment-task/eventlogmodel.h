#ifndef EVENTLOGMODEL_H
#define EVENTLOGMODEL_H

#include <QAbstractTableModel>
#include <mypropertyhelper.h>
#include <QList>

class EventLogRaw{
public:
    QString evenType;
    QString path;
    bool isFolder = false;
    QString timeStamp;
};

class EventLogModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit EventLogModel(QObject *parent = nullptr);

static EventLogModel* instance();

    enum RoleNames
    {
        EvetType = 0,
        Path = 1,
        IsFolder = 2,
        TimeStamp = 3
    };

    void addEventLogRaw( EventLogRaw &data);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Q_INVOKABLE void checkTable(bool value);


private:
    QList<EventLogRaw> m_data;
private:
    static EventLogModel* _obj;

};

#endif // EVENTLOGMODEL_H
