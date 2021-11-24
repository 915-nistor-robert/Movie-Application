//
// Created by Robert on 3/21/2021.
//

#include "ui.h"
#include "Service.h"
#include "validators.h"
#include "tests.h"
#include "GUI.h"
#include <iostream>
#include <cstdlib>
#include <QApplication>
#include <QLabel>


int main(int argc, char * argv[]){
    QApplication app{argc, argv};
    string path = "";
    string watchlist_path = "D:\\C_Problems\\a89-915-nistor-robert\\example.csv";
    FileRepository* file_repo = new FileRepository("D:\\C_Problems\\a89-915-nistor-robert\\movies.txt");
    Repository* watchlist_repo = new Repository();
    UndoService* undo_service = new UndoService(file_repo);
    Validator* validator = new Validator(file_repo);
    Service* service = new Service(file_repo, watchlist_repo, undo_service);
    GUI* gui = new GUI(nullptr, service);
    gui->show();
    return app.exec();




}