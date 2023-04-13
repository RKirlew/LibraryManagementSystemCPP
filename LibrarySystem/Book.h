#pragma once
// Book.h

#include <string>

class Book {
private:
    std::string title;
    std::string author;
    std::string genre;
    bool isAvailable;

public:
    Book(const std::string& title, const std::string& author, const std::string& genre);
    // Other member functions and variables
    // ...
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getGenre() const;
    std::string getAvailability()const;
};
