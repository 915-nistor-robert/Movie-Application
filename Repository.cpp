//
// Created by Robert on 3/18/2021.
//

#include "Repository.h"

#include "validators.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include "movie.h"
#include <assert.h>
#include <vector>

#include <utility>
#include <fstream>


Repository::Repository() {

}


Repository::~Repository() {
}


void Repository::add(TElement *element) {
    int index = this->find(element->title, element->year_of_release);
    if (index == -1) {
        this->elements.push_back(element);
    } else
        throw RepositoryException("This movie already exists!");

}

int Repository::find(const string &title, int year_of_release) {
    for (auto i = this->elements.begin(); i != this->elements.end(); i++) {
        if ((*i)->title.compare(title) == 0 && (*i)->year_of_release == year_of_release)
            return i - this->elements.begin();
    }
    return -1;
}

void Repository::update(TElement *element) {
    int element_position = this->find(element->title, element->year_of_release);
    if (element_position == -1)
        throw RepositoryException("This movie does not exists!");
    delete this->elements[element_position];
    this->elements[element_position] = element;
}

void Repository::remove(const string &title, int year_of_release) {

    int element_position = this->find(title, year_of_release);
    if (element_position == -1)
        throw RepositoryException("This movie does not exists!");
    else {
        this->elements.erase(this->elements.begin() + element_position);
    }

}

vector<Movie *> Repository::get_elements() {
    return this->elements;
}

string Repository::get_system_command() {
    return "";
}

//-------------------File Repo--------------------
FileRepository::FileRepository(string path) {
    this->path = path;
    this->load_from_file();
}

void FileRepository::save_to_file() {
    ofstream file(this->path.c_str());
    if (!file.is_open())
        return;
    for (auto el = this->elements.begin(); el != this->elements.end(); ++el) {
        file << **el << endl;
    }
    file.close();
}

void FileRepository::load_from_file() {
    ifstream file(this->path.c_str());
    Movie *movie = new Movie;
//    while(file >> reinterpret_cast<void *&>(movie)){
//        this->add(movie);
//        movie = new Movie;
//    }
    while (file >> movie) {
        this->add(movie);
        movie = new Movie;
    }
    file.close();
}

void FileRepository::add(TElement *element) {
    Repository::add(element);
    save_to_file();
}

void FileRepository::remove(const string &title, int year_of_release) {
    Repository::remove(title, year_of_release);
    save_to_file();
}

void FileRepository::update(TElement *element) {
    Repository::update(element);
    save_to_file();
}

//-------------------CSV Repo--------------------

CSVRepository::CSVRepository(string path) {
    this->path = path;
}

void CSVRepository::add(TElement *element) {
    Repository::add(element);
    this->save_to_file();
}

void CSVRepository::update(TElement *element) {
    Repository::update(element);
    this->save_to_file();
}

void CSVRepository::remove(const string &title, int year_of_release) {
    Repository::remove(title, year_of_release);
    this->save_to_file();
}

void CSVRepository::save_to_file() {
    ofstream file(this->path);
    if (!file.is_open())
        return;
    for (auto movie: this->get_elements())
        file<<*movie<<'\n';
    file.close();
}

string CSVRepository::get_system_command() {
    string command = "notepad ";
    string result = command + this->path;
    return result;
}

//-------------------HTML Repo--------------------

HTMLRepository::HTMLRepository(string path) {
    this->path = path;
}

void HTMLRepository::safe_to_file() {
    ofstream file(this->path);

    if (!file.is_open())
        return;

    file << "<!DOCTYPE html>\n"
            "<html>\n"
            "<head>\n"
            "    <title>Movie</title>\n"
            "</head>\n"
            "<body>\n"
            "<table border=\"1\">\n"
            "    <tr> \n"
            "    <td>Title</td>\n"
            "    <td>Genre</td>\n"
            "    <td>Year</td>\n"
            "    <td>Likes</td>\n"
            "    <td>Link</td>\n"
            "    </tr>\n";


    for (auto movie : this->get_elements()) {
        string likes = to_string(movie->number_of_likes);
        string year = to_string(movie->year_of_release);
        file << "<tr>\n";
        file << "<td>" << movie->get_title() << "</td>\n";
        file << "<td>" << movie->get_genre() << "</td>\n";
        file << "<td>" << likes << "</td>\n";
        file << "<td>" << year << "</td>\n";
        file << "<td><a href=\"" << movie->get_trailer() << "\">Link</a></td>\n";
        file << "</tr>\n";
    }
    file << "</tr>\n";
    file << "</table>\n";
    file << "</body>\n";
    file << "</html>\n";
    file.close();

}

void HTMLRepository::add(TElement *element) {
    Repository::add(element);
    this->safe_to_file();
}

void HTMLRepository::update(TElement *element) {
    Repository::update(element);
    this->safe_to_file();
}

void HTMLRepository::remove(const string &title, int year_of_release) {
    Repository::remove(title, year_of_release);
    this->safe_to_file();
}

string HTMLRepository::get_system_command() {
    string command = "start ";
    string result = command + this->path;
    return result;
}
