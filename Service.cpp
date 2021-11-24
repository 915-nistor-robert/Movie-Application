//
// Created by Robert on 3/20/2021.
//

#include "Service.h"
#include "validators.h"
#include <string>
#include <movie.h>
#include <Repository.h>
#include <algorithm>
#include <exception>

Service::Service(Repository *repo, Repository* watchlist_repo, UndoService* undo_service) {
    this->repo = repo;
    this->watchlist_repo = watchlist_repo;
    this->undo_service = undo_service;
}

void Service::add_movie(Movie* movie){
    this->repo->add(movie);
    Movie* recorded_movie = new Movie(movie);
    Undo_Redo_add* operation = new Undo_Redo_add(repo, *recorded_movie);
    this->undo_service->add_operation(operation);
}

void Service::remove_movie(string title, int year_of_release){
    int index = this->repo->find(title, year_of_release);
    Movie* recorded_movie = this->repo->get_elements()[index];
    this->repo->remove(title, year_of_release);
    Undo_Redo_remove* operation = new Undo_Redo_remove(this->repo, *recorded_movie);
    this->undo_service->add_operation(operation);
}

void Service::update_movie(string title, int year_of_release, string genre, long long new_number_of_likes, string new_trailer){
    int index = this->repo->find(title, year_of_release);
    Movie *old_movie = this->repo->get_elements()[index];
    Movie *new_movie = new Movie(title, genre, year_of_release, new_number_of_likes , new_trailer);
    this->repo->update(new_movie);
    Undo_Redo_update* operation = new Undo_Redo_update(this->repo,*new_movie, old_movie);
    this->undo_service->add_operation(operation);
}

int Service::find_movie(string title, int year_of_release){
    return this->repo->find(title, year_of_release);
}

int Service::find_movie_from_watchlist(string title, int year_of_release){
    return this->watchlist_repo->find(title, year_of_release);
}


Repository* Service::get_elements(){
    return this->repo;
}

Repository* Service::get_watchlist() {
    return this->watchlist_repo;
}

void Service::add_movie_to_watchlist(Movie *movie) {
    this->watchlist_repo->add(movie);
}

void Service::remove_movie_from_watchlist(string title, int year_of_release) {
    this->watchlist_repo->remove(title,year_of_release);
}

void Service::rate_movie(string title, int year_of_release) {
    int position = this->find_movie(title, year_of_release);
    this->repo->elements[position]->number_of_likes++;
}

void Service::set_repo(Repository *repo) {
    this->watchlist_repo = repo;
}

string Service::get_system_command() {
    return this->watchlist_repo->get_system_command();
}

void Service::print_watchlist() {
    for(auto movie : this->watchlist_repo->get_elements())
        movie->print();
}

vector<Movie*> Service::filter_movies_by_genre(string genre) {
    if (genre.compare("")==0)
        return this->repo->get_elements();

    vector<Movie *> movies = this->repo->get_elements();

    auto it_f = movies.begin();
    auto it_l=movies.end();

    movies.erase(remove_if(it_f, it_l, [&genre](Movie* movie) {return genre.compare(movie->genre) != 0; }), it_l);
    return movies;
}

void Service::undo() {
    this->undo_service->undo();
}

void Service::redo() {
    this->undo_service->redo();
}

UndoService::UndoService(Repository *repository) {
    this->repository = repository;
    this->index = -1;
}

void UndoService::add_operation(Undo_Redo *operation) {
    if (index != history.size()-1 )
        history.erase(history.begin()+index+1,history.end());
    history.push_back(operation);
    index++;
}

void UndoService::undo() {
    if(index == -1)
        throw UndoException("No more undos\n");
    history[index]->Undo();
    index--;
}

void UndoService::redo() {
    if (index == history.size()-1)
        throw RedoException("No more redos\n");
    history[index+1]->Redo();
    index++;
}



