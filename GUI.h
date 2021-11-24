//
// Created by Robert on 5/13/2021.
//

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qbuttongroup.h>
#include <iostream>
#include <QtWidgets/QMainWindow>
#include "Service.h"
#include <QTableWidget>
#include "MovieTableModel.h"

class GUI : public QWidget{
    Q_OBJECT
public:
    GUI(QWidget *parent, Service* services) : QWidget(parent), service{services}{
        this->starting_window();
    }

private:
    QWidget* user_widget;
    QWidget* admin_widget;
    QWidget* delete_widget;
    QWidget* display_widget;
    QWidget* filter_widget;

    QListWidget* movies_list_widget;
    QListWidget* movies_watchlist_widget;

    Service * service;

    QPushButton * admin_button;
    QPushButton* user_button;
    QPushButton * exit_main_button;
    QPushButton * exit_admin_button;

    QPushButton* undo_button;
    QPushButton* redo_button;

    QPushButton* open_link_button;
    QPushButton* add_to_watchlist_button;
    QPushButton* next_movie_button;
    QPushButton* exit_watchlist_button;

    QPushButton * filter_button;
    QPushButton * open_in_app_button;
    QPushButton * exit_user_button;
    QPushButton * choose_repo_button;


    QPushButton * add_button;
    QPushButton* delete_button;
    QPushButton * update_button;


    QRadioButton* csv_repo;
    QRadioButton* html_repo;
    QRadioButton* yes_rate;
    QRadioButton* no_rate;

    MovieTableModel* table_model;
    QTableView* table_view;


    QLineEdit* title_line;
    QLineEdit* delete_title_line;
    QLineEdit* delete_year_line;

    QLineEdit* genre_line;
    QLineEdit* year_line;
    QLineEdit* likes_line;
    QLineEdit* link_line;
//    QPalette * pallete;
    QFormLayout* formLayout;
    QLabel* title_label;
    QLabel* genre_label;
    QLabel* year_label;
    QLabel* likes_label;
    QLabel* link_label;




    //    void initialize() ;
    vector<Movie*> filtered_movies;
    int index_watchlist;

    void initialize_user(QWidget* parent);
    void initialize_admin(QWidget* parent);

    void from_repo_to_list_widget();
    void from_repo_to_watchlist_widget();


private slots:
    void undo_gui();
    void redo_gui();
    void start_user();
    void add_movie();
    void delete_movie();
    void update_movie();
    void filter_watchlist();
    void exit_admin();
    void exit_user();
    void starting_window();
    void user_window();
    void admin_window();
    void repo_option();
    void open_link();
    void open_app();
    void delete_from_watchlist_window();
    void delete_from_watchlist();
    void add_to_watchlist();
    void next_movie();
    void exit_delete_widget();
    void exit_filter_widget();
    void exit(){
        std::exit(0);
    }

};
