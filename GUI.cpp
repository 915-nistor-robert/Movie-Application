//
// Created by Robert on 5/13/2021.
//

#include "GUI.h"
#include <sstream>
#include <QDesktopWidget>
#include "QCoreApplication"
#include "validators.h"

void GUI::starting_window() {
    this->setStyleSheet("background-color:#1FE09D;");
    this->setWindowTitle("Movie app");
    QGridLayout *layout = new QGridLayout{this};
    this->admin_button = new QPushButton{"Admin"};
    //color changing
    this->admin_button->setStyleSheet("background-color:#E01F62");
    //
    this->user_button = new QPushButton{"User"};
    QColor user_col = QColor(Qt::green);
    if (user_col.isValid()) {
        QString qss = QString("background-color: %1").arg(user_col.name());
        this->user_button->setStyleSheet(qss);
    }
    this->exit_main_button = new QPushButton{"Exit"};
    this->exit_main_button->setAutoFillBackground(true);
    this->exit_main_button->setStyleSheet("background-color: white");
    this->choose_repo_button = new QPushButton{"Choose"};
    this->choose_repo_button->setStyleSheet("background-color:white; color:black;");

    QLabel *label2 = new QLabel("Repository type : ");
    label2->setStyleSheet("QLabel {color : white; }");
    csv_repo = new QRadioButton("CSV");
    csv_repo->setStyleSheet("color:white");
    html_repo = new QRadioButton("HTML");
    html_repo->setStyleSheet("color:white");
    layout->addWidget(label2, 1, 0);
    layout->addWidget(csv_repo, 1, 1);
    layout->addWidget(html_repo, 1, 2);
    layout->addWidget(choose_repo_button, 2, 0);

    layout->addWidget(admin_button, 0, 0);
    layout->addWidget(user_button, 0, 1);
    layout->addWidget(exit_main_button, 0, 2);


    QObject::connect(this->admin_button, SIGNAL(clicked()), this, SLOT(admin_window()));
    QObject::connect(this->user_button, SIGNAL(clicked()), this, SLOT(user_window()));
    QObject::connect(this->exit_main_button, SIGNAL(clicked()), this, SLOT(exit()));
    QObject::connect(this->choose_repo_button, SIGNAL(clicked()), this, SLOT(repo_option()));
    this->admin_widget = new QWidget;
    this->user_widget = new QWidget;


}

void GUI::admin_window() {
    QDesktopWidget desktopWidget;
    QRect screen_size = desktopWidget.availableGeometry(admin_widget);
    admin_widget->setFixedSize(screen_size.width() * 0.85, screen_size.height() * 0.4);
    admin_widget->setWindowTitle("Admin mode");
    admin_widget->setStyleSheet("background-color:lightBlue");
    admin_widget->show();

    hide();

    this->initialize_admin(admin_widget);
}

void GUI::initialize_admin(QWidget *parent) {
    QHBoxLayout *layout = new QHBoxLayout{parent};
    this->movies_list_widget = new QListWidget{};
    this->movies_list_widget->setSelectionMode(QAbstractItemView::SingleSelection);
    this->movies_list_widget->setStyleSheet("background-color:white;");

    QWidget *data_widget = new QWidget{};
    QFormLayout *form_layout = new QFormLayout{data_widget};

    this->title_line = new QLineEdit{};
    this->title_line->setStyleSheet("background-color:white;");
    this->genre_line = new QLineEdit{};
    this->genre_line->setStyleSheet("background-color:white;");
    this->year_line = new QLineEdit{};
    this->year_line->setStyleSheet("background-color:white;");
    this->likes_line = new QLineEdit{};
    this->likes_line->setStyleSheet("background-color:white;");
    this->link_line = new QLineEdit{};
    this->link_line->setStyleSheet("background-color:white;");

    form_layout->addRow("Title:", title_line);
    form_layout->addRow("Genre:", genre_line);
    form_layout->addRow("Year:", year_line);
    form_layout->addRow("Likes:", likes_line);
    form_layout->addRow("Link:", link_line);

    QWidget *button_widget = new QWidget{};
    this->add_button = new QPushButton{"Add"};
    this->add_button->setStyleSheet("background-color: orange");
    this->delete_button = new QPushButton{"Delete"};
    this->delete_button->setStyleSheet("background-color: orange");
    this->update_button = new QPushButton{"Update"};
    this->update_button->setStyleSheet("background-color: orange");
    this->exit_admin_button = new QPushButton{"Exit"};
    this->exit_admin_button->setStyleSheet("background-color: orange");
    form_layout->addWidget(add_button);
    form_layout->addWidget(delete_button);
    form_layout->addWidget(update_button);



    // UNDO REDO BUTTONS

//    QHBoxLayout* undo_redo_layout = new QHBoxLayout{};

    this->undo_button = new QPushButton{"Undo"};
    this->undo_button->setStyleSheet("background-color: orange");
    this->undo_button->setShortcut(QKeySequence("Ctrl+Z"));
    this->redo_button = new QPushButton{"Redo"};
    this->redo_button->setStyleSheet("background-color: orange");
    this->redo_button->setShortcut(QKeySequence("Ctrl+Y"));

//    undo_redo_layout->addWidget(undo_button);
//    undo_redo_layout->addWidget(redo_button);

    form_layout->addWidget(undo_button);
    form_layout->addWidget(redo_button);
    form_layout->addWidget(exit_admin_button);


    QObject::connect(this->exit_admin_button, SIGNAL(clicked()), this, SLOT(exit_admin()));
    QObject::connect(this->add_button, SIGNAL(clicked()), this, SLOT(add_movie()));
    QObject::connect(this->delete_button, SIGNAL(clicked()), this, SLOT(delete_movie()));
    QObject::connect(this->update_button, SIGNAL(clicked()), this, SLOT(update_movie()));
    QObject::connect(this->undo_button, SIGNAL(clicked()), this, SLOT(undo_gui()));
    QObject::connect(this->redo_button, SIGNAL(clicked()), this, SLOT(redo_gui()));

    layout->addWidget(data_widget);
    layout->addWidget(movies_list_widget);
    layout->addWidget(new QLabel{"Movies"});
    layout->addWidget(button_widget);
    this->from_repo_to_list_widget();


}

void GUI::user_window() {
    this->user_widget->setWindowTitle("User mode");
    this->user_widget->setStyleSheet("background-color:lightGreen");
    this->user_widget->show();
    hide();
    this->initialize_user(user_widget);
}

void GUI::initialize_user(QWidget *parent) {
    if (user_widget == nullptr)
        user_widget = new QWidget;
    parent = user_widget;
    if (parent->layout() != nullptr) {
        QLayoutItem *item;
        while ((item = parent->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete parent->layout();
    }

    QVBoxLayout *layout = new QVBoxLayout{parent};

//    this->movies_watchlist_widget = new QListWidget{};
//    this->movies_watchlist_widget->setStyleSheet("background-color:white");
    this->table_model = new MovieTableModel{service};
    this->table_view = new QTableView{};
    this->table_view->setModel(table_model);

    this->filter_widget = new QWidget{};
//
    QWidget *watchlist_button_widget = new QWidget{};

    QHBoxLayout *watchlist_buttons_layout = new QHBoxLayout{watchlist_button_widget};

    this->filter_button = new QPushButton{"Filter"};
    this->filter_button->setStyleSheet("background-color: #DDCDDF; color: black");
    this->delete_button = new QPushButton{"Delete"};
    this->delete_button->setStyleSheet("background-color: #DDCDDF; color: black");
    this->open_in_app_button = new QPushButton{"Open in app"};
    this->open_in_app_button->setStyleSheet("background-color: #DDCDDF; color: black");
    this->exit_user_button = new QPushButton{"Exit"};
    this->exit_user_button->setStyleSheet("background-color: #DDCDDF; color: black");

    watchlist_buttons_layout->addWidget(filter_button);
    watchlist_buttons_layout->addWidget(delete_button);
    watchlist_buttons_layout->addWidget(open_in_app_button);
    watchlist_buttons_layout->addWidget(exit_user_button);
//
    QWidget *genre_widget = new QWidget{};
    QFormLayout *form_layout = new QFormLayout{genre_widget};

    QLabel *genre_label = new QLabel("Genre");
    this->genre_line = new QLineEdit{};
    this->genre_line->setStyleSheet("background-color:white");
    form_layout->addRow(genre_label, this->genre_line);
//
    QObject::connect(this->exit_user_button, SIGNAL(clicked()), this, SLOT(exit_user()));
    QObject::connect(this->filter_button, SIGNAL(clicked()), this, SLOT(filter_watchlist()));
    QObject::connect(this->open_in_app_button, SIGNAL(clicked()), this, SLOT(open_app()));
    QObject::connect(this->delete_button, SIGNAL(clicked()), this, SLOT(delete_from_watchlist_window()));
//
    layout->addWidget(genre_widget);
//
    layout->addWidget(watchlist_button_widget);
//
//    layout->addWidget(movies_watchlist_widget);
    QLabel *W_list = new QLabel{"Watchlist"};
    W_list->setAlignment(Qt::AlignCenter);
    layout->addWidget(W_list);
    layout->addWidget(table_view);


//    this->from_repo_to_watchlist_widget();
}

void GUI::exit_admin() {
    this->admin_widget->hide();
    this->show();
}

void GUI::exit_user() {
    this->user_widget->hide();
    this->show();
}

void GUI::repo_option() {
    if (csv_repo->isChecked() || html_repo->isChecked()) {
        if (csv_repo->isChecked()) {
            string path = "D:\\C_Problems\\a89-915-nistor-robert\\example.csv";
            CSVRepository *repo = new CSVRepository(path);
            this->service->set_repo(repo);
        } else {
            string path = "D:\\C_Problems\\a89-915-nistor-robert\\example.html";
            HTMLRepository *repo = new HTMLRepository(path);
            this->service->set_repo(repo);
        }

    }
    this->html_repo->setEnabled(false);
    this->csv_repo->setEnabled(false);

}

void GUI::add_movie() {
    string title = this->title_line->text().toStdString();
    string genre = this->genre_line->text().toStdString();
    int year;
    try {
        year = stoi(this->likes_line->text().toStdString());
    }
    catch (invalid_argument &argument) {
        QMessageBox message;
        message.critical(0, "Input error", QString::fromStdString("Wrong input!"));
        return;

    }
    int likes;
    try {
        likes = stoi(this->likes_line->text().toStdString());
    }
    catch (invalid_argument &argument) {
        QMessageBox message;
        message.critical(0, "Input error", QString::fromStdString("Wrong input!"));
        return;

    }
    string link = this->link_line->text().toStdString();

    Movie *movie = new Movie(title, genre, year, likes, link);
    title_line->setText("");
    genre_line->setText("");
    year_line->setText("");
    likes_line->setText("");
    link_line->setText("");
    try {
        this->service->add_movie(movie);
        this->from_repo_to_list_widget();
    }
    catch (RepositoryException &exception){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("this movie exists!"));
    }

}

void GUI::undo_gui() {
    try {
        this->service->undo();
        this->from_repo_to_list_widget();
    }
    catch (UndoException &exception) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("no more undos"));
    }
}

void GUI::redo_gui() {
    try {
        this->service->redo();
        this->from_repo_to_list_widget();
    }
    catch (RedoException &exception) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("no more redos"));
    }
}

void GUI::delete_movie() {
    string title = this->title_line->text().toStdString();
    int year = stoi(this->year_line->text().toStdString());
    title_line->setText("");
    genre_line->setText("");
    year_line->setText("");
    likes_line->setText("");
    link_line->setText("");
    try {
        this->service->remove_movie(title,year);
        this->from_repo_to_list_widget();
    }
    catch (RepositoryException &exception){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", QString::fromStdString("this movie does not exists!"));
    }
}

void GUI::update_movie() {
    string title = this->title_line->text().toStdString();
    string genre = this->genre_line->text().toStdString();
    int year = stoi(this->year_line->text().toStdString());
    int likes = stoi(this->likes_line->text().toStdString());
    string link = this->link_line->text().toStdString();
    title_line->setText("");
    genre_line->setText("");
    year_line->setText("");
    likes_line->setText("");
    link_line->setText("");
    this->service->update_movie(title, year, genre, likes, link);
    this->from_repo_to_list_widget();
}

void GUI::from_repo_to_list_widget() {
    this->movies_list_widget->clear();
    Repository *array = this->service->get_elements();
    for (auto element : array->get_elements()) {
//        string movie_string =
        QString list = QString::fromStdString(
                element->get_title() + "," + element->get_genre() + "," + to_string(element->get_year_of_release()) +
                "," + to_string(element->get_number_of_likes()) + "," + element->get_trailer());
        QListWidgetItem *listWidgetItem = new QListWidgetItem(list);
        this->movies_list_widget->addItem(listWidgetItem);
    }
}

void GUI::from_repo_to_watchlist_widget() {
    this->movies_watchlist_widget->clear();
    Repository *array = this->service->get_watchlist();
    for (auto element: array->get_elements()) {
        QString list = QString::fromStdString(
                element->get_title() + "," + element->get_genre() + "," + to_string(element->get_year_of_release()) +
                "," + to_string(element->get_number_of_likes()));
        QListWidgetItem *listWidgetItem = new QListWidgetItem(list);
        this->movies_watchlist_widget->addItem(listWidgetItem);
    }
}

void GUI::filter_watchlist() {
    this->filter_widget->show();
    QVBoxLayout *layout = new QVBoxLayout{filter_widget};
    QWidget *tutorialButtonsWidget = new QWidget{};
    QHBoxLayout *watchlistButtonsLayout = new QHBoxLayout{tutorialButtonsWidget};
    this->filter_widget->setWindowTitle("Filter");
    this->filter_widget->setStyleSheet("background-color: lightGreen");
    this->open_link_button = new QPushButton{"Open link"};
    this->open_link_button->setStyleSheet("background-color: #DDCDDF; color: black");
    this->add_to_watchlist_button = new QPushButton{"Add"};
    this->add_to_watchlist_button->setStyleSheet("background-color: #DDCDDF; color: black");
    this->next_movie_button = new QPushButton{"Next"};
    this->next_movie_button->setStyleSheet("background-color: #DDCDDF; color: black");
    this->exit_watchlist_button = new QPushButton{"Exit"};
    this->exit_watchlist_button->setStyleSheet("background-color: #DDCDDF; color: black");
    watchlistButtonsLayout->addWidget(this->add_to_watchlist_button);
    watchlistButtonsLayout->addWidget(this->next_movie_button);
    watchlistButtonsLayout->addWidget(this->open_link_button);
    watchlistButtonsLayout->addWidget(this->exit_watchlist_button);

    QObject::connect(this->open_link_button, SIGNAL(clicked()), this, SLOT(open_link()));
    QObject::connect(this->add_to_watchlist_button, SIGNAL(clicked()), this, SLOT(add_to_watchlist()));
    QObject::connect(this->next_movie_button, SIGNAL(clicked()), this, SLOT(next_movie()));
    QObject::connect(this->exit_watchlist_button, SIGNAL(clicked()), this, SLOT(exit_filter_widget()));

    string genre = this->genre_line->text().toStdString();
    filtered_movies = service->filter_movies_by_genre(genre);


    index_watchlist = 0;

    QWidget *tutorialsLabelsWidget = new QWidget{};
    formLayout = new QFormLayout{tutorialsLabelsWidget};


    QLabel *label1 = new QLabel("Title : ");
    title_label = new QLabel(filtered_movies[index_watchlist]->get_title().c_str());
    formLayout->addRow(label1, title_label);


    QLabel *label2 = new QLabel("Genre : ");
    genre_label = new QLabel(this->filtered_movies[index_watchlist]->get_genre().c_str());
    formLayout->addRow(label2, genre_label);

    string min = to_string(filtered_movies[index_watchlist]->get_year_of_release());
    QLabel *label3 = new QLabel("Year : ");
    year_label = new QLabel(QString::fromStdString(min));
    formLayout->addRow(label3, year_label);

    string sec = to_string(filtered_movies[index_watchlist]->get_number_of_likes());
    QLabel *label4 = new QLabel("Likes : ");
    likes_label = new QLabel(QString::fromStdString(sec));
    formLayout->addRow(label4, likes_label);


    QLabel *label5 = new QLabel("Link : ");
    link_label = new QLabel(filtered_movies[index_watchlist]->get_trailer().c_str());
    formLayout->addRow(label5, link_label);


    layout->addWidget(tutorialsLabelsWidget);
    layout->addWidget(tutorialButtonsWidget);
}

void GUI::open_link() {
    string link = "start ";
    link = link + filtered_movies[index_watchlist]->get_trailer();
    link = link + " 2> nul";
    system(link.c_str());
}

void GUI::exit_filter_widget() {
    this->filter_widget->hide();
    start_user();
    this->initialize_user(user_widget);
    QCoreApplication::processEvents();

}

void GUI::start_user() {
    hide();
    initialize_user(this);
}

void GUI::add_to_watchlist() {
    this->service->add_movie_to_watchlist(filtered_movies[index_watchlist]);
    this->service->print_watchlist();
//    this->from_repo_to_watchlist_widget();
    table_model = new MovieTableModel{service};
    table_view = new QTableView{};
    table_view->setModel(table_model);
    start_user();
    this->next_movie();
}

void GUI::next_movie() {
    this->index_watchlist++;
    if (this->index_watchlist == filtered_movies.size())
        this->index_watchlist = 0;
    this->title_label->setText(filtered_movies[index_watchlist]->get_title().c_str());
    this->genre_label->setText(filtered_movies[index_watchlist]->get_genre().c_str());
    this->link_label->setText(filtered_movies[index_watchlist]->get_trailer().c_str());
    this->likes_label->setText(to_string(filtered_movies[index_watchlist]->get_number_of_likes()).c_str());
    this->year_label->setText(to_string(filtered_movies[index_watchlist]->get_year_of_release()).c_str());


}

void GUI::open_app() {
    system(this->service->get_system_command().c_str());
}

void GUI::delete_from_watchlist_window() {
    this->delete_widget = new QWidget;
    this->delete_widget->setWindowTitle("Delete");
    this->delete_widget->setStyleSheet("background-color: lightGreen");
    QGridLayout *layout = new QGridLayout{delete_widget};

    QLabel *label1 = new QLabel("Title : ");
    delete_title_line = new QLineEdit{delete_widget};
    delete_title_line->setEnabled(true);
    this->delete_title_line->setStyleSheet("background-color:white");
    QPushButton *delete_button_watchlist = new QPushButton("Delete");
    delete_button_watchlist->setStyleSheet("background-color:#DDCDDF; color:black");
    QPushButton *exit_button_watchlist = new QPushButton("Exit");
    exit_button_watchlist->setStyleSheet("background-color:#DDCDDF; color:black");


    layout->addWidget(label1, 0, 0);
    layout->addWidget(delete_title_line, 0, 1);


    QLabel *label3 = new QLabel("Year : ");
    delete_year_line = new QLineEdit{delete_widget};
    delete_year_line->setEnabled(true);
    this->delete_year_line->setStyleSheet("background-color:white");
    layout->addWidget(label3, 1, 0);
    layout->addWidget(delete_year_line, 1, 1);

    QLabel *label2 = new QLabel("Did you like the movie? ");
    yes_rate = new QRadioButton("Yes");
    no_rate = new QRadioButton("No");
    layout->addWidget(label2, 2, 0);
    layout->addWidget(yes_rate, 2, 1);
    layout->addWidget(no_rate, 2, 2);
    layout->addWidget(delete_button_watchlist, 3, 0);
    layout->addWidget(exit_button_watchlist, 3, 1);

    QObject::connect(delete_button_watchlist, SIGNAL(clicked()), this, SLOT(delete_from_watchlist()));
    QObject::connect(exit_button_watchlist, SIGNAL(clicked()), this, SLOT(exit_delete_widget()));

    delete_widget->show();

}

void GUI::exit_delete_widget() {
    this->delete_widget->hide();

}

void GUI::delete_from_watchlist() {
    string title = this->delete_title_line->text().toStdString();
    int year = stoi(this->delete_year_line->text().toStdString());
    this->service->remove_movie_from_watchlist(title, year);
    if (this->yes_rate->isChecked())
        this->service->rate_movie(title, year);
//    this->from_repo_to_watchlist_widget();
}