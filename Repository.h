//
// Created by Robert on 3/18/2021.
//
#pragma once
#include "movie.h"
#include <vector>
typedef Movie TElement;

class Repository {
public:
    vector<Movie*> elements;
    //int length;
    //int capacity;
public:

//    Repository *create_array(int capacity);
    Repository();
/***
 * This functions create a new Repository
 * param: capacity - the capacity of the array
 */

    virtual int find(const string& title, int year_of_release);
    /***
     * This function find an element in the Dynamic array by the title and year_of_release
     */

    ~Repository();
    /***
     * This is the destructor for the array
     */

    virtual void remove(const string& title, int year_of_release);
    /***
     * This function removes an item from the array with the matching title and year_of_release
     */


    virtual void add(TElement* element);
    /***
     * this functions adds the TElement element to the array
     */

    virtual void update(TElement *element);

    virtual vector<Movie*> get_elements();

    virtual string get_system_command();



};

class FileRepository : public Repository{
private:

    string path;
public:
    FileRepository(string path);
    void save_to_file();
    void load_from_file();
    void add(TElement* element) override;
    void update(TElement *element) override;
    void remove(const string& title, int year_of_release) override;

};

class CSVRepository : public Repository{
private:
    vector <Movie*> elements;
    string path;
public:
    CSVRepository(string path);
    void save_to_file();
    void load_from_file();
    void add(TElement* element) override;
    void update(TElement *element) override;
    void remove(const string& title, int year_of_release) override;
    string get_system_command();


};


class HTMLRepository : public Repository{
private:
    vector<Movie*> elements;
    string path;
public:
    HTMLRepository(string path);
    void safe_to_file();
    void add(TElement* element) override;
    void update(TElement *element) override;
    void remove(const string& title, int year_of_release) override;
    string get_system_command();
};

