//
// Created by Robert on 3/21/2021.
//
#pragma once
#include "Repository.h"
#include "Service.h"
#include "validators.h"


class ui{
private:
    Service* services;
    Validator* validator;
public:
    ui(Service* service, Validator* validator);
    void ui_add_movie();
    void ui_delete_movie();
    void ui_print_movies_given_genre();
    void ui_print_watchlist_options();
    void ui_print_watchlist_movies();
    void ui_remove_movie_from_watchlist();
    void ui_print_movies();
    void ui_update_movie();
    void initialise();
    void print_menu_admin();
    void print_menu_user();
    void print_user_options();
    void ui_start();
    void ui_open_in_app();
};



