#pragma once

#include <QModelIndex>
#include "api.h"

class QTVModel : public QAbstractListModel
{
private:
    typedef QAbstractListModel inherited;

public:
    QTVModel(const Curves& _curves) : curves(_curves) {}

private:
    const Curves& curves;

public:
    int rowCount(const QModelIndex&) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void reset();
    void update(unsigned count);
};
