//
// Created by Robert on 3/22/2021.
//

#include "validators.h"
Validator::Validator(Repository* repo){
    this->repo = repo;
}

int Validator::validate_year(string year){
    int i;
    for(i=0;i<year.length();i++){
        if(!(year[i]>='0' && year[i]<='9'))
            return -1;
    }
    return 1;
}

int Validator::validate_number_of_likes(string number_of_likes){
    int i;
    for(i=0;i<number_of_likes.length();i++){
        if(!(number_of_likes[i]>='0' && number_of_likes[i]<='9'))
            return -1;
    }
    return 1;
}

int Validator::validate_genre(string genre) {
    int i;
    for(i=0;i<genre.length();i++){
        if(!((genre[i]>='a' && genre[i]<='z') || (genre[i]>='A' && genre[i]<='Z')))
            return -1;
    }
    return 1;


}
int Validator::validate_movie(string title, string genre, int year_of_release, long long number_of_likes,
                              string trailer) {
    if (title.length() == 0)
        throw ValidatorException("The title cannot be empty!");
    if (genre.length() == 0)
        throw ValidatorException("The genre cannot be empty!");
    if (trailer.length()==0)
        throw ValidatorException("The trailer link cannot be empty!");
    if (year_of_release < 0)
        throw ValidatorException("The year of release must be a positive integer!");
    if (number_of_likes < 0)
        throw ValidatorException("The number of likes must be a positive integer!");
    return 1;

}

int Validator::is_integer(string& str){
//    for (char const &c : str) {
//        if (std::isdigit(c) == 0) return false;
//    }
    //char c;
    for (int i = 0; i < str.length()-1; ++i) {
        if (std::isdigit(str[i]) == 0)
            return false;

    }
    return true;
}

