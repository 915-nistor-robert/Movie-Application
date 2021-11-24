//
// Created by Robert on 3/22/2021.
//
#pragma once
#include "Repository.h"
#include <string>

#ifndef A45_915_NISTOR_ROBERT_VALIDATORS_H
#define A45_915_NISTOR_ROBERT_VALIDATORS_H
class Validator{
private:
    Repository* repo;
public:
    Validator(Repository* repo);
    int validate_genre(string genre);
    int validate_year(string year);
    int validate_number_of_likes(string number_of_likes);
    int validate_movie(string title, string genre, int year_of_release, long long number_of_likes, string trailer);
    int is_integer(string& str);
};

class RepositoryException : public std::exception{
    string message;
public:
    RepositoryException(string message): message(message){};
    ~RepositoryException() throw(){};
    string getMessage(){ return this->message;};
};

class ValidatorException : public std::exception{
    string message;
public:
    ValidatorException(std::string message): message(message){};
    ~ValidatorException() throw(){};
    string getMessage(){ return this->message;};
};

class InputException : public std::exception{
    string message;
public:
    InputException(string message): message(message){};
    ~InputException() throw(){};
    string getMessage(){ return this->message;};
};

class UndoException : public std::exception{
    string message;
public:
    UndoException(string message): message(message){};
    ~UndoException() throw(){};
    string getMessage(){ return this->message;};
};

class RedoException : public std::exception{
    string message;
public:
    RedoException(string message): message(message){};
    ~RedoException() throw(){};
    string getMessage(){ return this->message;};
};


#endif //A45_915_NISTOR_ROBERT_VALIDATORS_H
