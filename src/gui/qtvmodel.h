#pragma once

#include <QModelIndex>
#include "api.h"

class QTVModelBase : public QAbstractListModel
{
public:
    void reset();
    void update(unsigned count);
};

class QTVModel : public QTVModelBase
{
private:
    typedef QTVModelBase inherited;

public:
    QTVModel(const Curves& _container) : container(_container) { param = 0.f; }

private:
    const Curves& container;
    float param;

public:
    int rowCount(const QModelIndex&) const override { return container.size(); }
    int columnCount(const QModelIndex& parent) const override { return 5; }

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void update(unsigned count, float p);
};

class QTVModelSecond : public QTVModelBase
{
private:
    typedef QTVModelBase inherited;

public:
    QTVModelSecond(const CurvesData& _container) : container(_container) {}

private:
    const CurvesData& container;

public:
    int rowCount(const QModelIndex&) const override { return container.size(); }
    int columnCount(const QModelIndex& parent) const override { return 1; }

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};
