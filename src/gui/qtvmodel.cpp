#include "qtvmodel.h"

void QTVModelBase::reset()
{
    beginResetModel();
    endResetModel();
}

void QTVModelBase::update(unsigned count)
{
    if (count)
    {
        beginInsertRows(QModelIndex(), 0, count - 1);
        endInsertRows();
    }
}

////////////////////////////////////////////////////////////////////////////////////

QVariant QTVModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0:
            return container[index.row()]->Type();
        case 1:
            return container[index.row()]->R1();
        case 2:
            if (container[index.row()]->R2() > 0.f)
                return container[index.row()]->R2();
            break;
        case 3:
        {
            Fvector ct = container[index.row()]->C_t(param);
            return QString::asprintf("(%.7f,%.7f,%.7f)", ct.x, ct.y, ct.z);
        }
        case 4:
        {
            Fvector dct = container[index.row()]->dC_t(param);
            return QString::asprintf("{%.7f,%.7f,%.7f}", dct.x, dct.y, dct.z);
        }
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
        case 1:
            return QString("Radius|X-Radius");
        case 2:
            return QString("Step|Y-Radius");
        case 3:
            return QString("C(t)");
        case 4:
            return QString("C'(t)");
        }
    }

    return inherited::headerData(section, orientation, role);
}

void QTVModel::update(unsigned count, float p)
{
    param = p;
    inherited::update(count);
}

////////////////////////////////////////////////////////////////////////////////////

QVariant QTVModelSecond::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole && index.column() == 0)
        return container[index.row()]->R1();
    return QVariant();
}

QVariant QTVModelSecond::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal && section == 0)
        return QString("Radius");
    return inherited::headerData(section, orientation, role);
}
