// Book.cpp

#include "Book.h"

// Constructor implementation
Book::Book(const std::string& title, const std::string& author, const std::string& genre)
    : title(title), author(author), genre(genre), isAvailable(true) {
}

// Member function implementations
std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getGenre() const {
    return genre;
}

std::string Book::getAvailability() const {
    return (isAvailable ? "Available" : "Not Available");
}

// Other member function implementations
// ...
