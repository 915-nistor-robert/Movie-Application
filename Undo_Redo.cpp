//
// Created by Robert on 6/1/2021.
//

#include "Undo_Redo.h"

Undo_Redo::Undo_Redo(Repository *repository, Movie movie) {
    this->repository = repository;
    this->movie = movie;
}

Undo_Redo_add::Undo_Redo_add(Repository *repository, Movie movie) : Undo_Redo(repository, movie) {

}

void Undo_Redo_add::Undo() {
    this->repository->remove(movie.get_title(), movie.get_year_of_release());
}

void Undo_Redo_add::Redo() {
    Movie* new_movie = new Movie(&this->movie);
    repository->add(new_movie);
}

Undo_Redo_remove::Undo_Redo_remove(Repository *repository, Movie movie) : Undo_Redo(repository, movie) {
}

void Undo_Redo_remove::Undo() {
    Movie* new_movie = new Movie(&this->movie);
    this->repository->add(new_movie);
}

void Undo_Redo_remove::Redo() {
    this->repository->remove(this->movie.get_title(), this->movie.get_year_of_release());
}

Undo_Redo_update::Undo_Redo_update(Repository *repository, Movie movie, Movie *old_movie) : Undo_Redo(repository,
                                                                                                      movie) {
    this->old_title = old_movie->get_title();
    this->old_genre = old_movie->get_genre();
    this->old_year_of_release = old_movie->get_year_of_release();
    this->old_number_of_likes = old_movie->get_number_of_likes();
    this->old_trailer = old_movie->get_trailer();
}

void Undo_Redo_update::Undo() {
    Movie *new_movie = new Movie(this->old_title, this->old_genre, this->old_year_of_release,
                                 this->old_number_of_likes, this->old_trailer);
    this->repository->update(new_movie);
}

void Undo_Redo_update::Redo() {
    Movie* new_movie = new Movie(&this->movie);
    this->repository->update(new_movie);
}


