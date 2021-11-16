#include "eventlogmodel.h"

#include <QModelIndex>
#include <QDebug>

EventLogModel* EventLogModel::_obj = nullptr;
EventLogModel *EventLogModel::instance()
{
    if(_obj == nullptr)
        _obj = new EventLogModel();
    return _obj;
}

void EventLogModel::addEventLogRaw(EventLogRaw &data)
{

    m_data.append(data);

    beginResetModel();
    endResetModel();

}


EventLogModel::EventLogModel(QObject *parent) : QAbstractTableModel(parent)
{
    //    EventLogRaw tmp ;
    //    tmp.path = "c:/";
    //    tmp.evenType = "Created";
    //    tmp.timeStamp = "15/11";
    //    tmp.isFolder = true;
    //  m_data.append(tmp);
    //  m_data.append(tmp);
    //     /*foods.append({ "Lizza", "12", "ASR1" });
    //     foods.append({ "SMilk", "34", "BE-23" });
    //     foods.append({ "YCoffe", "5", "QRTY8-9" });*/
}


int EventLogModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int EventLogModel::columnCount(const QModelIndex &parent) const
{
    return roleNames().size();
}

QVariant EventLogModel::data(const QModelIndex &index, int role) const
{
    QVariant variant;
    const int row = index.row();
    const int col = role;
    switch (col) {
    case EvetType: variant = m_data.at(row).evenType; break;
    case Path: variant = m_data.at(row).path; break;
    case IsFolder: variant = m_data.at(row).isFolder; break;
    case TimeStamp: variant = m_data.at(row).timeStamp; break;
    }
    return variant;
}

QHash<int, QByteArray> EventLogModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(EvetType, "EvetType");
    roles.insert(Path, "Path");
    roles.insert(IsFolder, "IsFolder");
    roles.insert(TimeStamp, "TimeStamp");
    return roles;
}

bool EventLogModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == EvetType) {
        m_data[index.row()].evenType = value.toString();
        emit dataChanged(index, index);
        return true;
    }
    if(index.isValid() && role == Path) {
        m_data[index.row()].path = value.toString();
        emit dataChanged(index, index, { role });
        return true;
    }
    if(index.isValid() && role == IsFolder) {
        m_data[index.row()].isFolder = value.toBool();
        emit dataChanged(index, index, { role });
        return true;
    }
    if(index.isValid() && role == TimeStamp) {
        m_data[index.row()].timeStamp = value.toString();
        emit dataChanged(index, index, { role });
        return true;
    }
    return false;
}

void EventLogModel::checkTable(bool value)
{
    //    for (int i = 0; i < foods.size(); i++) {
    //        qDebug() << i << value;
    //        foods[i].check = value;
    //    }
}
