//
// Created by Robert on 3/21/2021.
//

#include "ui.h"
#include <string>
#include <iostream>
#include <cstdlib>

ui::ui(Service *service, Validator *validator) {
    this->services = service;
    this->validator = validator;
}

void ui::ui_add_movie() {
    string title, genre, trailer, year_of_release_str, number_of_likes_str;

    int succes;
    int year_of_release;
    long long number_of_likes;
    cout << "Enter the title of the movie: \n";
    cin >> title;
    cout << "Enter the genre of the movie: \n";
    cin >> genre;
//    succes = this->validator->validate_genre(genre);
//    if (succes < 0) {
//        cout << "This genre is invalid!\n";
//        return;
//    }
    cout << "Enter the year of release: " << endl;
    cin >> year_of_release_str;
    while (!this->validator->is_integer(year_of_release_str)) {
        cout << "The year of release must be an integer!" << endl;
        cout << "Enter the year of release: " << endl;
        cin >> year_of_release_str;
    }

    year_of_release = atoi(year_of_release_str.c_str());

//    succes = this->validator->validate_year(year_of_release);
//    if(succes<0){
//        cout<<"This year is invalid!\n";
//        return;
//    }
    //std::atoi( year_of_release.c_str() );
    cout << "Enter the number of likes: \n";
    cin >> number_of_likes_str;
    while (!this->validator->is_integer(number_of_likes_str)) {
        cout << "The number of likes must be an integer!" << endl;
        cout << "Enter the number of likes: " << endl;
        cin >> number_of_likes_str;
    }
    number_of_likes = atoi(number_of_likes_str.c_str());
//    succes = this->validator->validate_number_of_likes(number_of_likes);
//    if (succes<0){
//        cout<<"Number of likes is invalid!\n";
//        return;
//    }

    cout << "Enter the trailer link: \n";
    cin >> trailer;
    succes = this->validator->validate_movie(title, genre, year_of_release, number_of_likes, trailer);
    if (succes == 1) {
        if (this->services->find_movie(title, year_of_release) > 0) {
            cout << "This movie already exists !\n";
            return;
        }
        Movie *movie = new Movie(title, genre, year_of_release, number_of_likes, trailer);
        this->services->add_movie(movie);
        cout << "Movie successfully added!\n";
    }
}

void ui::ui_delete_movie() {
    string title, year_of_release_str;
    int year_of_release;
    cout << "Enter the title of the movie\n";
    cin >> title;
    cout << "Enter the year of release: \n";
    cin >> year_of_release_str;
    while (!this->validator->is_integer(year_of_release_str)) {
        cout << "The year of release must be an integer!" << endl;
        cout << "Enter the year of release: " << endl;
        cin >> year_of_release_str;
    }
    year_of_release = atoi(year_of_release_str.c_str());
    if (this->services->find_movie(title, year_of_release) < 0) {
        cout << "This movie does not exists!\n";
        return;
    }
    this->services->remove_movie(title, year_of_release);
    cout << "Movie successfully deleted!\n";
}

void ui::ui_update_movie() {
    string trailer, title, genre, number_of_likes_str, year_of_release_str;
    long long number_of_likes;
    int index, year_of_release;
    cout << "Enter the title of the movie you want to update: ";
    cin >> title;
    cout << "Enter the year of release of the movie you want to update: ";
    cin >> year_of_release_str;
    while (!this->validator->is_integer(year_of_release_str)) {
        cout << "The year of release must be an integer!" << endl;
        cout << "Enter the year of release: " << endl;
        cin >> year_of_release_str;
    }

    year_of_release = atoi(year_of_release_str.c_str());

    index = this->services->find_movie(title, year_of_release);
    if (index == -1) {
        cout << "This movie does not exists!\n";
    } else {
        cout << "Enter the new number of likes: \n";
        cin >> number_of_likes_str;
        while (!this->validator->is_integer(number_of_likes_str)) {
            cout << "The number of likes must be an integer!" << endl;
            cout << "Enter the number of likes: " << endl;
            cin >> number_of_likes_str;
        }

        number_of_likes = atoi(number_of_likes_str.c_str());
        cout << "Enter the new trailer link: \n";
        cin >> trailer;
        Repository *array = this->services->get_elements();
        this->services->update_movie(title, year_of_release, array->elements[index]->get_genre(), number_of_likes,
                                     trailer);
    }

}

void ui::ui_print_watchlist_options() {
    cout
            << "How do you want to continue?\n1. Add the movie to the watchlist\n2. Watch the next movie trailer\n3. Exit this genre\n";
}


void ui::ui_print_movies_given_genre() {
    int i, option;
    char link_to_char[101];
    string genre, link;
    Repository *array = this->services->get_elements();
    cout << "Enter the genre of the movies you like to watch: \n";
    getline(cin, genre);
    getline(cin, genre);
    if (genre.compare("") == 0) {
        i = 0;
        while (true) {
            if (i == array->elements.size())
                i = 0;
            array->elements[i]->print();
            link = "start ";
            link.append(array->elements[i]->get_trailer());
            strcpy(link_to_char, link.c_str());
            link_to_char[strlen(link_to_char)] = '\0';
            system(link_to_char);
            this->ui_print_watchlist_options();
            cin >> option;
            if (option == 1) {
                if (this->services->find_movie_from_watchlist(array->elements[i]->get_title(),
                                                              array->elements[i]->get_year_of_release()) < 0) {
                    this->services->add_movie_to_watchlist(array->elements[i]);
                    i++;
                } else {
                    cout << "This movie is already added in your watchlist!\n";
                    i++;
                }
                cout << "Movie added successfully!\n";
            } else if (option == 2)
                i++;
            else if (option == 3)
                break;
            else cout << "Invalid option!\n";
        }
    } else {
        i = 0;
        while (true) {
            if (array->elements.size() == i)
                i = 0;
            if (genre.compare(array->elements[i]->get_genre()) != 0)
                i++;
            else {
                array->elements[i]->print();
                link = "start ";
                link.append(array->elements[i]->get_trailer());
                strcpy(link_to_char, link.c_str());
                link_to_char[strlen(link_to_char)] = '\0';
                system(link_to_char);
                this->ui_print_watchlist_options();
                cin >> option;
                if (option == 1) {
                    if (this->services->find_movie_from_watchlist(array->elements[i]->get_title(),
                                                                  array->elements[i]->get_year_of_release()) < 0) {
                        this->services->add_movie_to_watchlist(array->elements[i]);
                        i++;
                    } else {
                        cout << "This movie is already added in your watchlist!\n";
                        i++;
                    }
                    cout << "Movie added successfully!\n";
                } else if (option == 2)
                    i++;
                else if (option == 3)
                    break;
                else cout << "Invalid option!\n";
            }
        }

    }
}

void ui::ui_remove_movie_from_watchlist() {
    string title, year_of_release_str;
    int year_of_release, option;
    cout << "Enter the title of the movie: \n";
    getline(cin, title);
    getline(cin, title);
    string title_string(title);
    cout << "Enter the year of release: \n";
    cin >> year_of_release_str;
    while (!this->validator->is_integer(year_of_release_str)) {
        cout << "The year of release must be an integer!" << endl;
        cout << "Enter the year of release: " << endl;
        cin >> year_of_release_str;
    }

    year_of_release = atoi(year_of_release_str.c_str());
    if (this->services->find_movie_from_watchlist(title, year_of_release) < 0) {
        cout << "This movie does not exists!\n";
        return;
    }
    this->services->remove_movie_from_watchlist(title, year_of_release);
    cout << "Movie successfully deleted!\n";
    cout << "Did you liked this movie?\n1. Yes\n2. No\n";
    cin >> option;
    if (option == 1) {
        this->services->rate_movie(title_string, year_of_release);
    } else if (option != 2) {
        cout << "This option does not exists!\n";
//        option = std::stoi(option);
    }
}

void ui::ui_open_in_app() {
    system(this->services->get_system_command().c_str());
}

void ui::ui_print_watchlist_movies() {
    int i;
    Repository *watchlist = this->services->get_watchlist();
    for (int i = 0; i < watchlist->elements.size(); ++i) {
        watchlist->elements[i]->print();
    }
}

void ui::ui_print_movies() {
    int i;
    Repository *array = this->services->get_elements();
    for (i = 0; i < array->elements.size(); i++) {
        array->elements[i]->print();

    }
}

void ui::initialise() {
    Movie *movie1 = new Movie("Avengers", "Action", 2012, 247000, "https://www.youtube.com/watch?v=eOrNdBpGMv8");
    Movie *movie2 = new Movie("Inception", "Aventure", 2010, 94000, "https://www.youtube.com/watch?v=YoHD9XEInc0");
    Movie *movie3 = new Movie("Fast and furious 8", "Action", 2017, 192000,
                              "https://www.youtube.com/watch?v=uisBaTkQAEstop");
    Movie *movie4 = new Movie("The Godfather", "Drama", 1972, 50000, "https://www.youtube.com/watch?v=sY1S34973zA");
    Movie *movie5 = new Movie("Knives out", "Mister", 2019, 81000, "https://www.youtube.com/watch?v=xi-1NchUqMA");
    Movie *movie6 = new Movie("John Wick", "Action", 2014, 34000, "https://www.youtube.com/watch?v=2AUmvWm5ZDQ");
    Movie *movie7 = new Movie("The Martian", "SF", 2015, 75000, "https://www.youtube.com/watch?v=Ter3FElDq00");
    Movie *movie8 = new Movie("The Hangover", "Comedy", 2009, 15000, "https://www.youtube.com/watch?v=tcdUhdOlz9M");
    Movie *movie9 = new Movie("Tenet", "Action", 2020, 289000, "https://www.youtube.com/watch?v=L3pk_TBkihU");
    Movie *movie10 = new Movie("Hancock", "Action", 2008, 5300, "https://www.youtube.com/watch?v=SkX1VuXLRSc");
    this->services->add_movie(movie1);
    this->services->add_movie(movie2);
    this->services->add_movie(movie3);
    this->services->add_movie(movie4);
    this->services->add_movie(movie5);
    this->services->add_movie(movie6);
    this->services->add_movie(movie7);
    this->services->add_movie(movie8);
    this->services->add_movie(movie9);
    this->services->add_movie(movie10);
}

void ui::print_menu_admin() {
    cout
            << "____________________________________________\n0. Exit the program\n1. Add a movie.\n2. Delete a movie.\n3. Update a movie.\n4. Print all movies\n____________________________________________\n";

}

void ui::print_menu_user() {
    cout
            << "____________________________________________\n0. Exit the program\n1. Add a movie to the watchlist\n2. Delete a movie from the watchlist\n3. See the watchlist\n4. Open the watchlist\n____________________________________________\n";
}

void ui::print_user_options() {
    cout << "1. Administrator\n2. User\n";
}


void ui::ui_start() {
    //Repository *repo = new Repository();
    string option_str, user_option_str;
    int option, user_option;
//    initialise();
    this->print_user_options();
    cin >> user_option_str;
    if (!this->validator->is_integer(user_option_str)) {
        throw InputException("Invalid option!");
    }
    user_option = atoi(user_option_str.c_str());

    if (user_option == 1) {
        while (1) {
            print_menu_admin();
            cin >> option_str;
            if (!this->validator->is_integer(option_str))
                throw InputException("Invalid option!");
            option = atoi(option_str.c_str());
            if (option == 0) {
                cout << "Bye bye!";
//                ui_print_movies();
                return;
            } else if (option == 1) {
                ui_add_movie();
            } else if (option == 2)
                ui_delete_movie();
            else if (option == 3)
                ui_update_movie();
            else if (option == 4)
                ui_print_movies();
            else if (option == 5)
                ui_print_movies_given_genre();
            else
                cout << "This option does not exists!\n";
        }
    } else if (user_option == 2) {
        while (1) {
            print_menu_user();
            cin >> option_str;
            if (!this->validator->is_integer(option_str))
                throw InputException("Invalid option!");
            option = atoi(option_str.c_str());
            if (option == 0) {
                cout << "Bye bye!";
                return;
            } else if (option == 1) {
                ui_print_movies_given_genre();
            } else if (option == 2) {
                ui_remove_movie_from_watchlist();
            } else if (option == 3) {
                ui_print_watchlist_movies();
            } else if (option == 4) {
                ui_open_in_app();
            } else
                cout << "This option does not exists!\n";
        }
    }
}