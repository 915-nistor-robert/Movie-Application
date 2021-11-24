//
// Created by Robert on 3/18/2021.
//
#include <string.h>
#include <iostream>
#include <string>
#pragma once
using namespace std;
class Movie {
public:
    string title;
    string genre;
    int year_of_release;
    long long number_of_likes;
    string trailer;

public:
    Movie(string title, string genre, int year_of_release, long long number_of_likes, string trailer);
    /***
     * This is the constructor
     */
     Movie();
     Movie(Movie* movie);
    void print();
    /***
     * Print the movie in a friendly format;
     */

    string get_title(void) {
        return title;
    }

    string get_genre(void) {
        return genre;
    }

    int get_year_of_release(void) {
        return year_of_release;
    }

    friend std::ostream &operator<<(std::ostream &output, const Movie &movie);
    friend std::istream &operator>>(std::istream &input, Movie* movie);



    long long get_number_of_likes(void) {
        return number_of_likes;
    }

    string get_trailer(void) {
        return trailer;
    }





};
