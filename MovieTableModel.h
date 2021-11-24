//
// Created by Robert on 5/30/2021.
//
#pragma once
#include "QWidget"
#include "QAbstractTableModel"
#include "Service.h"

class MovieTableModel: public QAbstractTableModel{
    Q_OBJECT
private:
    Service* service_movie;
public:
    MovieTableModel(Service* service_movie);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};
