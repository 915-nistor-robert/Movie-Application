////
//// Created by Robert on 3/22/2021.
////
//
//#include "tests.h"
//#include "array.h"
//#include <cassert>
//#include <iostream>
//#include "services.h"
//#include "movie.h"
//
//
////______________________________Domain________________________
//void Test::test_create_movie(){
//    Movie* movie = new Movie("Avengers", "Action", 2012, 247000, "https://www.youtube.com/watch?v=eOrNdBpGMv8");
//    assert(movie->get_title().compare("Avengers") == 0);
//    assert(movie->get_genre().compare("Action") == 0);
//    assert(movie->get_year_of_release()==2012);
//    assert(movie->get_number_of_likes()==247000);
//    assert(movie->get_trailer().compare("https://www.youtube.com/watch?v=eOrNdBpGMv8")==0);
//}
//
//void Test::test_getters(){
//    Movie* movie = new Movie("Avengers", "Action", 2012, 247000, "https://www.youtube.com/watch?v=eOrNdBpGMv8");
//    assert(movie->get_title().compare(movie->title)==0);
//    assert(movie->get_genre().compare(movie->genre)==0);
//    assert(movie->get_year_of_release() == movie->year_of_release);
//    assert(movie->get_number_of_likes() == movie->number_of_likes);
//    assert(movie->get_trailer().compare(movie->trailer)==0);
//}
//
//
////void Test::test_constructor_and_destructor_dynamic_array(){
////    Repository* array = new DynamicArray(15);
////    assert(array->capacity==15);
////    assert(array->length==0);
////    array->destroy();
////}
//
//void Test::test_resize(){
//    Repository* array = new DynamicArray(5);
//    Movie* movie = new Movie("Avengers", "Action", 2012, 247000, "https://www.youtube.com/watch?v=eOrNdBpGMv8");
//    array->add(movie);
//    assert(array->capacity == 5);
//    assert(array->length==1);
//    array->resize();
//    assert(array->capacity==10);
//    assert(array->length == 1);
//    array->destroy();
//}
//
//void Test::test_add_to_array(){
//    Repository* array = new DynamicArray(5);
//    Movie* movie = new Movie("Avengers", "Action", 2012, 247000, "https://www.youtube.com/watch?v=eOrNdBpGMv8");
//    array->add(movie);
//    assert(array->length==1);
//    assert(array->elements[0]->get_title().compare(movie->title)==0);
//    assert(array->elements[0]->get_genre().compare(movie->genre)==0);
//    assert(array->elements[0]->get_year_of_release() == movie->year_of_release);
//    assert(array->elements[0]->get_number_of_likes() == movie->number_of_likes);
//    assert(array->elements[0]->get_trailer().compare(movie->trailer)==0);
//    array->destroy();
//
//}
//
//void Test::test_remove_from_array(){
//    Repository* array = new DynamicArray(5);
//    Movie* movie = new Movie("Avengers", "Action", 2012, 247000, "https://www.youtube.com/watch?v=eOrNdBpGMv8");
//    array->add(movie);
//    Movie* movie2 = new Movie("Inception", "Aventure", 2010, 94000, "https://www.youtube.com/watch?v=YoHD9XEInc0");
//    array->add(movie2);
//    assert(array->length==2);
//    array->remove(movie2->title, movie2->year_of_release);
//    assert(array->length==1);
//    assert(array->elements[0]->get_title().compare(movie->title)==0);
//    assert(array->elements[0]->get_genre().compare(movie->genre)==0);
//    assert(array->elements[0]->get_year_of_release() == movie->year_of_release);
//    assert(array->elements[0]->get_number_of_likes() == movie->number_of_likes);
//    assert(array->elements[0]->get_trailer().compare(movie->trailer)==0);
//    array->destroy();
//
//}
//
//void Test::test_find(){
//    Repository* array = new DynamicArray(5);
//    Movie* movie = new Movie("Avengers", "Action", 2012, 247000, "https://www.youtube.com/watch?v=eOrNdBpGMv8");
//    array->add(movie);
//    Movie* movie2 = new Movie("Inception", "Aventure", 2010, 94000, "https://www.youtube.com/watch?v=YoHD9XEInc0");
//    array->add(movie2);
//    assert(array->length==2);
//    int index_watchlist = array->find("Avengers", 2012);
//    assert(index_watchlist == 0);
//    index_watchlist = array->find("Inception", 2010);
//    assert(index_watchlist == 1);
//    array->destroy();
//
//}
//
//void Test::test_length_array(){
//    Repository* array = new DynamicArray(5);
//    Movie* movie = new Movie("Avengers", "Action", 2012, 247000, "https://www.youtube.com/watch?v=eOrNdBpGMv8");
//    array->add(movie);
//    Movie* movie2 = new Movie("Inception", "Aventure", 2010, 94000, "https://www.youtube.com/watch?v=YoHD9XEInc0");
//    array->add(movie2);
//    assert(array->length_array()==2);
//    array->destroy();
//
//}
//
////___________________________________________Service_____________________________
//void Test::test_add_movie() {
//    Repository* array = new DynamicArray(5);
//    Repository* watchlist = new DynamicArray(5);
//    Service* service = new Service(array, watchlist);
//    Movie* movie = new Movie("Avengers", "Action", 2012, 247000, "https://www.youtube.com/watch?v=eOrNdBpGMv8");
//    service->add_movie(movie);
//    assert(array->length==1);
//    assert(array->elements[0]->get_title().compare(movie->title)==0);
//    assert(array->elements[0]->get_genre().compare(movie->genre)==0);
//    assert(array->elements[0]->get_year_of_release() == movie->year_of_release);
//    assert(array->elements[0]->get_number_of_likes() == movie->number_of_likes);
//    assert(array->elements[0]->get_trailer().compare(movie->trailer)==0);
//}
//
//void Test::test_remove_movie() {
//    Repository* array = new DynamicArray(5);
//    Repository* watchlist = new DynamicArray(5);
//    Service* service = new Service(array, watchlist);
//    Movie* movie = new Movie("Avengers", "Action", 2012, 247000, "https://www.youtube.com/watch?v=eOrNdBpGMv8");
//    service->add_movie(movie);
//    service->remove_movie("Avengers", 2012);
//    assert(array->length_array()==0);
//}
//
//void Test::test_find_movie() {
//    Repository* array = new DynamicArray(5);
//    Repository* watchlist = new DynamicArray(5);
//    Service* service = new Service(array, watchlist);
//    Movie* movie = new Movie("Avengers", "Action", 2012, 247000, "https://www.youtube.com/watch?v=eOrNdBpGMv8");
//    service->add_movie(movie);
//    int index_watchlist = service->find_movie("Avengers", 2012);
//    assert(index_watchlist == 0);
//}
//
//void Test::test_update_movie(){
//    Repository* array = new DynamicArray(5);
//    Repository* watchlist = new DynamicArray(5);
//    Service* service = new Service(array, watchlist);
//    Movie* movie = new Movie("Avengers", "Action", 2012, 247000, "https://www.youtube.com/watch?v=eOrNdBpGMv8");
//    service->add_movie(movie);
//    service->update_movie("Avengers", 2012, 131321, "yt.com");
//    assert(array->elements[0]->get_number_of_likes() == 131321);
//    assert(array->elements[0]->get_trailer().compare("yt.com") == 0);
//
//}
//
//
//
//
//void Test::test_all(){
//    test_find();
//    test_add_to_array();
//    test_resize();
//    test_constructor_and_destructor_dynamic_array();
//    test_create_movie();
//    test_getters();
//    test_length_array();
//    test_find_movie();
//    test_remove_movie();
//    test_add_movie();
//    test_update_movie();
//    test_remove_from_array();
//}