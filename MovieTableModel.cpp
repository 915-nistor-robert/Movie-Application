//
// Created by Robert on 5/30/2021.
//

#include "MovieTableModel.h"

MovieTableModel::MovieTableModel(Service *service_movie) : service_movie(service_movie){
}

int MovieTableModel::rowCount(const QModelIndex &parent) const {
    return this->service_movie->get_watchlist()->get_elements().size();
}

int MovieTableModel::columnCount(const QModelIndex &parent) const {
    return 6;
}

QVariant MovieTableModel::data(const QModelIndex &index, int role) const {
    std::vector<Movie*> data = this->service_movie->get_watchlist()->get_elements();
    int row = index.row(), column = index.column();
    if (role == Qt::DisplayRole){
        if(data.empty())
            return QVariant();
        if (column == 0) {
            return QString::fromStdString(data[row]->get_title());
        }
        if (column == 1){
            return QString::fromStdString(data[row]->get_genre());
        }
        if (column == 2){
            return QString::number(data[row]->get_year_of_release());
        }
        if (column == 3){
            return QString::number(data[row]->get_number_of_likes());
        }
        if (column == 4){
            return QString::fromStdString(data[row]->get_trailer());
        }
        if (column == 5){
            return QString::fromStdString(data[row]->get_trailer());
        }
    }
    return QVariant();
}

QVariant MovieTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal){
        if (section == 0)
            return QString("Title");
        else if (section == 1)
            return QString("Genre");
        else if(section == 2)
            return QString("Year");
        else if(section == 3)
            return QString("Likes");
        else if(section == 4)
            return QString("Trailer");
        else if(section == 5)
            return QString("Play");
    }
    return QVariant();
}