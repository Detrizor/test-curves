#include "qtvmodel.h"

int QTVModel::rowCount(const QModelIndex&) const
{
    return curves.size();
}

int QTVModel::columnCount(const QModelIndex&) const
{
    return 1;
}

QVariant QTVModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0:
            return curves[index.row()]->Type();
        }
    }

    return QVariant();
}

QVariant QTVModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return QString("Type");
        }
    }

    return inherited::headerData(section, orientation, role);
}

void QTVModel::reset()
{
    beginResetModel();
    endResetModel();
}

void QTVModel::update(unsigned count)
{
    beginInsertRows(QModelIndex(), 0, count - 1);
    endInsertRows();
}
