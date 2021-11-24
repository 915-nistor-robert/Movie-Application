//
// Created by Robert on 3/18/2021.
//

#include "movie.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

//int Movie::find_movie

Movie::Movie(string title, string genre, int year_of_release, long long number_of_likes, string trailer) {
    this->title = title;
    this->genre = genre;
    this->year_of_release = year_of_release;
    this->number_of_likes = number_of_likes;
    this->trailer = trailer;
}

Movie::Movie() {

}
Movie::Movie(Movie *movie) {
    this->title = movie->get_title();
    this->genre = movie->get_genre();
    this->year_of_release = movie->get_year_of_release();
    this->number_of_likes = movie->get_number_of_likes();
    this->trailer = movie->get_trailer();
}

void Movie::print() {
    std::cout << "Title: " << this->title << " | Genre: " << this->genre << " | Year: " << this->year_of_release
              << " | Likes: " << this->number_of_likes <<"|"<<this->trailer<< "\n";
}

std::ostream &operator<<(ostream &output, const Movie &movie) {
    output << movie.title << "," << movie.genre << "," << movie.year_of_release << "," << movie.number_of_likes << ","
           << movie.trailer;
    return output;
}

std::istream &operator>>(istream &input, Movie *movie) {
    string line;
    getline(input, line);

    vector<string> attributes;
    string separator = ",";
    size_t position;
    string attribute;
    while((position = line.find(separator))!= string::npos){
        attribute = line.substr(0, position);
        attributes.push_back(attribute);
        line.erase(0, position+separator.length());
    }
    attributes.push_back(line);
    if (attributes.size() != 5)
        return input;
    movie->title = attributes[0];
    movie->genre = attributes[1];
    movie->year_of_release = atoi(attributes[2].c_str());
    movie->number_of_likes = atoi(attributes[3].c_str());
    movie->trailer = attributes[4];
    return input;
}





//Movie *create_movie(string title, string genre, int year_of_release, long long number_of_likes, string trailer) {
//    Movie *movie = (Movie *) malloc(sizeof(Movie));
//    movie->title = (char *) malloc(sizeof(char) * 101 + 1);
//    movie->title = title;
//    movie->genre = (char *) malloc(sizeof(char) * 51 + 1);
//    movie->genre = genre;
//    movie->year_of_release = year_of_release;
//    movie->number_of_likes = number_of_likes;
//    movie->trailer = trailer;
//    return movie;
//}

//int main() {
//    //cout<<"ghena";
//    Movie movie;
//    movie.title = "Avengers";
//    cout<<movie.get_title()<<'\n';
//    movie.create_movie("Avatar"," Action", 2012, 1000003, "https://www.youtube.com/watch?v=5PSNL1qE6VY");
//    movie.print();
//}
