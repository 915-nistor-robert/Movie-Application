//
// Created by Robert on 6/1/2021.
//
#include "Repository.h"

#pragma once

class Undo_Redo {
protected:
    Repository *repository;
    Movie movie;
public:
    Undo_Redo(Repository *repository, Movie movie);

    virtual void Undo() = 0;

    virtual void Redo() = 0;

};

class Undo_Redo_add : public Undo_Redo {
public:
    Undo_Redo_add(Repository *repository, Movie movie);

    void Undo() override;

    void Redo() override;
};

class Undo_Redo_remove : public Undo_Redo {
public:
    Undo_Redo_remove(Repository *repository, Movie movie);

    void Undo() override;

    void Redo() override;
};

class Undo_Redo_update : public Undo_Redo {
private:
    string old_title;
    string old_genre;
    int old_year_of_release;
    long long old_number_of_likes;
    string old_trailer;
public:
    Undo_Redo_update(Repository *repository,Movie movie, Movie* old_movie);

    void Undo() override;

    void Redo() override;
};

