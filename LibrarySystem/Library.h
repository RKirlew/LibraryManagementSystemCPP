#pragma once
// Library.h

#include <string>

#include <iostream>
#include <fstream>
class Library {
private:
    std::string bookFile;

public:
    Library(const std::string& bookFile);
    void createNewBook();
    void deleteBook();
    void displayAllBooks();
    void searchForBookByTitle();
    int displayMenu();
    // Other member functions and variables
    // ...
};
