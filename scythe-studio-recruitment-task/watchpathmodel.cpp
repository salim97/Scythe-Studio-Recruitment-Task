#include "watchpathmodel.h"



WatchPathModel* WatchPathModel::_obj = nullptr;
WatchPathModel *WatchPathModel::instance()
{
    if(_obj == nullptr)
        _obj = new WatchPathModel();
    return _obj;
}


WatchPathModel::WatchPathModel(QObject *parent) : QObject(parent)
{

}

