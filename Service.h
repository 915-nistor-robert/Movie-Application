//
// Created by Robert on 3/20/2021.
//
#pragma once
#include <string>
#include "Repository.h"
#include "movie.h"
#include "Undo_Redo.h"

using namespace std;


class UndoService{
private:
    vector<Undo_Redo*> history;
    Repository* repository;
    int index;
public:
    UndoService(Repository* repository);
    void undo();
    void redo();
    void add_operation(Undo_Redo* operation);
};

class Service{
private:
    Repository* repo;
    Repository* watchlist_repo;
    UndoService* undo_service;
public:
    Service(Repository* repo, Repository* watchlist_repo, UndoService* undo_service);
    /***
     * Constructor for the service
     */
    void add_movie(Movie* movie);
    /***
     * Adds a movie to the repo
     * param : movie - Movie object
     */
    void remove_movie(string title, int year_of_release);
    /***
     * removes a movie from the repo
     * param: title - string
     * param: year_of_release - int
     */
    void update_movie(string title, int year_of_release, string genre,long long new_number_of_likes, string new_trailer);
    /***
     * updates a movie with the specified title and year of release in the repo by replacing
     * the number of likes and trailer link with their new values
     */
    int find_movie(string title, int year_of_release);
    /***
     * Return the position of the movie searched by the title and year of release
     * If not found returns -1
     */
    int get_length();
    Repository* get_elements();
    void add_movie_to_watchlist(Movie* movie);
    void remove_movie_from_watchlist(string title, int year_of_release);
    void rate_movie(string title, int year_of_release);
    Repository* get_watchlist();
    int find_movie_from_watchlist(string title, int year_of_release);
    void set_repo(Repository* repo);
    vector<Movie*> filter_movies_by_genre(string genre);
    string get_system_command();
    void print_watchlist();
    void undo();
    void redo();
};


//void find_movie(string title);



#ifndef A45_915_NISTOR_ROBERT_SERVICES_H
#define A45_915_NISTOR_ROBERT_SERVICES_H

#endif //A45_915_NISTOR_ROBERT_SERVICES_H
