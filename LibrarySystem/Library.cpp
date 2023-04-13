// Library.cpp

#include "Library.h"
#include "Book.h"
#include <vector>
#include <sstream>
#include <iomanip>
Library::Library(const std::string& bookFile) : bookFile(bookFile) {
    // Constructor implementation
}
int Library::displayMenu() {
    int choice;
    std::cout << "========== Library Management System Menu ==========" << std::endl;
    std::cout << "1. Add New Book" << std::endl;
    std::cout << "2. Remove Book" << std::endl;
    std::cout << "3. Search Book" << std::endl;
    std::cout << "4. Display All Books" << std::endl;
    std::cout << "5. Add New Member" << std::endl;
    std::cout << "6. Remove Member" << std::endl;
    std::cout << "7. Search Member" << std::endl;
    std::cout << "8. Display All Members" << std::endl;
    std::cout << "9. Borrow Book" << std::endl;
    std::cout << "10. Return Book" << std::endl;
    std::cout << "11. Display Borrowed Books" << std::endl;
    std::cout << "12. Exit" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    return choice;
}
void Library::createNewBook() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input stream buffer
    std::cout << "Enter Book Title: ";
    std::string title;
    std::getline(std::cin, title);

    std::cout << "Enter Author: ";
    std::string author;
    std::getline(std::cin, author);

    std::cout << "Enter Genre: ";
    std::string genre;
    std::getline(std::cin, genre);

    Book newBook(title, author, genre);
    std::ofstream bookFileOut(bookFile, std::ios::app);

    if (bookFileOut.is_open()) {
        bookFileOut << title << "," << author << "," << genre << "," << newBook.getAvailability() << std::endl;
        bookFileOut.close();
        std::cout << "New book added successfully!" << std::endl;
    }
    else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}
void Library::displayAllBooks() {
    std::ifstream bookFileIn(bookFile);
    if (!bookFileIn.is_open()) {
        std::cerr << "Unable to open file for reading." << std::endl;
        return;
    }
    std::vector<std::string> books;
    std::string bookLine;
    while (std::getline(bookFileIn, bookLine)) {
        books.push_back(bookLine);
    }
    bookFileIn.close();

    // Display the list of all books to the user
    std::cout << "List Of All Books [" <<books.size()<<" Total]: "<<std::endl;
    std::cout << "Title\t\tAuthor\t\tGenre\t\tAvailability" << std::endl;
    for (size_t i = 0; i < books.size(); ++i) {
        std::cout << "[" << i + 1 << "] " << books[i] << std::endl;
    }

}

void Library::searchForBookByTitle() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input stream buffer

    std::cout << "Enter Book Title to Search: ";
    std::string title;
    std::getline(std::cin, title);

    std::ifstream bookFileIn(bookFile);
    if (!bookFileIn.is_open()) {
        std::cerr << "Unable to open file for reading." << std::endl;
        return;
    }

    std::string bookLine;
    bool found = false;
    while (std::getline(bookFileIn, bookLine)) {
        std::istringstream iss(bookLine);
        std::string bookTitle, author, genre, availability;
        std::getline(iss, bookTitle, ',');
        std::getline(iss, author, ',');
        std::getline(iss, genre, ',');
        std::getline(iss, availability, ',');

        // Perform substring matching to check if the search term is a part of the book title
        if (bookTitle.find(title) != std::string::npos) {
            std::cout << "Book Found:" << std::endl;
            std::cout << "Title: " << bookTitle << std::endl;
            std::cout << "Author: " << author << std::endl;
            std::cout << "Genre: " << genre << std::endl;
            std::cout << "Availability: " << availability << std::endl;
            found = true;
        }
    }

    bookFileIn.close();

    if (!found) {
        std::cout << "Book not found with title: " << title << std::endl;
    }
}

void Library::deleteBook() {
    std::ifstream bookFileIn(bookFile);
    if (!bookFileIn.is_open()) {
        std::cerr << "Unable to open file for reading." << std::endl;
        return;
    }
    std::vector<std::string> books;
    std::string bookLine;
    while (std::getline(bookFileIn, bookLine)) {
        books.push_back(bookLine);
    }
    bookFileIn.close();

    // Display the list of books to the user
    std::cout << "List of books:" << std::endl;
    for (size_t i = 0; i < books.size(); ++i) {
        std::cout << "[" << i + 1 << "] " << books[i] << std::endl;
    }
    std::cout << "Enter the index of the book to delete (1-" << books.size() << "): ";
    int choice;
    std::cin >> choice;

    // Remove the selected book from the vector
    if (choice >= 1 && choice <= books.size()) {
        books.erase(books.begin() + choice - 1);
        std::cout << "Book deleted successfully!" << std::endl;
        
    }
    else {
        std::cout << "Invalid choice. No book deleted." << std::endl;
        
    }

    // Write the updated vector of books back to the text file
    std::ofstream bookFileOut(bookFile);
    if (!bookFileOut.is_open()) {
        std::cerr << "Unable to open file for writing." << std::endl;
        return;
    }

    for (const std::string& book : books) {
        bookFileOut << book << std::endl;
    }
    bookFileOut.close();
}
// Other member function implementations
// ...
