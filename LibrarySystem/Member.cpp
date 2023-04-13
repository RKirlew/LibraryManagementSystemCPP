// Member.cpp

#include "Member.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
int Member::nextId = 1; // Initialize static member variable

Member::Member(const std::string& name, int age, const std::string& address)
    : id(nextId++), name(name), age(age), address(address) {
    // Constructor implementation
}
Member::Member() {
    // Default constructor implementation here
}

// Initialize static member variable
std::string Member::getName() const {
    return name;
}

void Member::setName(const std::string& name) {
    this->name = name;
}

int Member::getAge() const {
    return age;
}
int Member::getId()const{
    return id;
}
void Member::setId(int m) {
    this->id = m;
}

void Member::setAge(int age) {
    this->age = age;
}

std::string Member::getAddress() const {
    return address;
}

void Member::setAddress(const std::string& address) {
    this->address = address;
}
void Member::createMember() {
    std::string name, address;
    int age;

    // Get member details from user input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input stream buffer

    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter age: ";
    std::cin >> age;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore newline character
    std::cout << "Enter address: ";
    std::getline(std::cin, address);

    // Create Member object
    Member member(name, age, address);

    // Store member details in a text file
    std::ofstream outFile("members.txt", std::ios::app); // Open file in append mode
    if (outFile.is_open()) {
        Member::updateNextId(); // Update nextId value
        member.setId(Member::nextId); // Set member ID
        outFile << member.getId() << "," << member.getName() << "," << member.getAge() << "," << member.getAddress() << std::endl;
        outFile.close();
        Member::nextId++; // Increment nextId value
        Member::writeNextId(); // Persist nextId value
        std::cout << "Member created and details stored in members.txt file." << std::endl;
    }
    else {
        std::cout << "Failed to open file for writing." << std::endl;
    }
}
void Member::updateNextId() {
    std::ifstream inFile("nextId.txt");
    if (inFile.is_open()) {
        inFile >> nextId;
        inFile.close();
    }
}

void Member::writeNextId() {
    std::ofstream outFile("nextId.txt");
    if (outFile.is_open()) {
        outFile << nextId;
        outFile.close();
    }
}
void Member::displayInfo() const {
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Address: " << address << std::endl;
}

void Member::displayAllMembers() {
    std::ifstream memberFileIn("members.txt");
    if (!memberFileIn.is_open()) {
        std::cerr << "Unable to open file for reading." << std::endl;
        return;
    }
    std::vector<std::string> members;
    std::string memberLine;
    while (std::getline(memberFileIn, memberLine)) {
        members.push_back(memberLine);
    }
    memberFileIn.close();

    // Display the list of all the members to the user
    std::cout << "List Of All Members [" << members.size() << " Total]: " << std::endl;
    std::cout << "ID\tName\t\Age\t\Address\t" << std::endl;
    for (size_t i = 0; i < members.size(); ++i) {
        std::cout << "[" << i + 1 << "] " << members[i] << std::endl;
    }
}
void Member::borrowBook() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input stream buffer

    std::cout << "Enter Member ID: ";
    std::string memberId;
    std::getline(std::cin, memberId);

    std::cout << "Enter Book Title to Borrow: ";
    std::string title;
    std::getline(std::cin, title);

    std::ifstream bookFileIn("books.txt");
    if (!bookFileIn.is_open()) {
        std::cerr << "Unable to open file for reading." << std::endl;
        return;
    }

    std::ofstream bookFileOut("books_temp.txt"); // Temporary file for writing updated book information
    if (!bookFileOut.is_open()) {
        std::cerr << "Unable to open file for writing." << std::endl;
        bookFileIn.close();
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

        // Perform substring matching to check if the book title matches the search term
        if (bookTitle == title) {
            if (availability == "Available") {
                std::cout << "Book Borrowed Successfully!" << std::endl;
                bookFileOut << bookTitle << "," << author << "," << genre << "," << "Borrowed by Member ID: " << memberId << std::endl;
                found = true;
            }
            else {
                std::cout << "Book is not available for borrowing." << std::endl;
                bookFileOut << bookLine << std::endl;
            }
        }
        else {
            bookFileOut << bookLine << std::endl;
        }
    }

    bookFileIn.close();
    bookFileOut.close();

    if (!found) {
        std::cout << "Book not found with title: " << title << std::endl;
    }
    else {
        // Replace the original file with the updated file
        std::remove("books.txt");
        std::rename("books_temp.txt", "books.txt");
    }
}
void Member::returnBook() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input stream buffer

    std::cout << "Enter Member ID: ";
    std::string memberId;
    std::getline(std::cin, memberId);

    std::cout << "Enter Book Title to Return: ";
    std::string title;
    std::getline(std::cin, title);

    std::ifstream bookFileIn("books.txt");
    if (!bookFileIn.is_open()) {
        std::cerr << "Unable to open file for reading." << std::endl;
        return;
    }

    std::ofstream bookFileOut("books_temp.txt"); // Temporary file for writing updated book information
    if (!bookFileOut.is_open()) {
        std::cerr << "Unable to open file for writing." << std::endl;
        bookFileIn.close();
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

        // Perform substring matching to check if the book title matches the search term
        if (bookTitle == title && availability.find("Borrowed by Member ID: " + memberId) != std::string::npos) {
            std::cout << "Book Returned Successfully!" << std::endl;
            bookFileOut << bookTitle << "," << author << "," << genre << "," << "Available" << std::endl;
            found = true;
        }
        else {
            bookFileOut << bookLine << std::endl;
        }
    }

    bookFileIn.close();
    bookFileOut.close();

    if (!found) {
        std::cout << "Book not found with title: " << title << " or it was not borrowed by Member ID: " << memberId << std::endl;
    }
    else {
        // Replace the original file with the updated file
        std::remove("books.txt");
        std::rename("books_temp.txt", "books.txt");
    }
}
void Member::displayBorrowedBooks() const {
    std::ifstream bookFileIn("books.txt");
    if (!bookFileIn.is_open()) {
        std::cerr << "Unable to open file for reading." << std::endl;
        return;
    }

    std::string bookLine;
    bool found = false;
    std::cout << "Books with Borrowed Availability: " << std::endl;
    while (std::getline(bookFileIn, bookLine)) {
        std::istringstream iss(bookLine);
        std::string bookTitle, author, genre, availability, memberIdStr;
        std::getline(iss, bookTitle, ',');
        std::getline(iss, author, ',');
        std::getline(iss, genre, ',');
        std::getline(iss, availability, ',');
        std::getline(iss, memberIdStr, ':');
        if (availability != "Available") {
           // std::string memberId = memberIdStr.substr(memberIdStr.find_first_not_of(" \t"), memberIdStr.length() - 1);
            std::cout << "Title: " << bookTitle << std::endl;
            std::cout << "Author: " << author << std::endl;
            std::cout << "Genre: " << genre << std::endl;
            std::cout << "Availability: " << availability << std::endl;
           
            std::cout << "------------------------" << std::endl;
            found = true;
        }
    }
    bookFileIn.close();

    if (!found) {
        std::cout << "No books with borrowed availability found." << std::endl;
    }
}

void Member::searchForMemberByName() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input stream buffer

    std::cout << "Enter Member Name to Search: ";
    std::string name;
    std::getline(std::cin, name);

    std::ifstream memberFileIn("members.txt");
    if (!memberFileIn.is_open()) {
        std::cerr << "Unable to open file for reading." << std::endl;
        return;
    }

    std::string memberLine;
    bool found = false;
    while (std::getline(memberFileIn, memberLine)) {
        std::istringstream iss(memberLine);
        std::string memberId, memberName, memberAge, memberAddress;
        std::getline(iss, memberId, ',');
        std::getline(iss, memberName, ',');
        std::getline(iss, memberAge, ',');
        std::getline(iss, memberAddress, ',');

        // Perform substring matching to check if the search term is a part of the member name
        if (memberName.find(name) != std::string::npos) {
            std::cout << "Member Found:" << std::endl;
            std::cout << "ID: " << memberId << std::endl;
            std::cout << "Name: " << memberName << std::endl;
            std::cout << "Age: " << memberAge << std::endl;
            std::cout << "Address: " << memberAddress << std::endl;
            found = true;
        }
    }

    memberFileIn.close();

    if (!found) {
        std::cout << "Member not found with name: " << name << std::endl;
    }
}
void Member::deleteMember() {

    std::ifstream memberFileIn("members.txt");
    if (!memberFileIn.is_open()) {
        std::cerr << "Unable to open file for reading." << std::endl;
        return;
    }
    std::vector<std::string> members;
    std::string memberLine;
    while (std::getline(memberFileIn, memberLine)) {
        members.push_back(memberLine);
    }
    memberFileIn.close();

    // Display the list of members to the user
    std::cout << "List of members:" << std::endl;
    for (size_t i = 0; i < members.size(); ++i) {
        std::cout << "[" << i + 1 << "] " << members[i] << std::endl;
    }
    std::cout << "Enter the index of the member to delete (1-" << members.size() << "): ";
    int choice;
    std::cin >> choice;

    // Remove the selected member from the vector
    if (choice >= 1 && choice <= members.size()) {
        members.erase(members.begin() + choice - 1);
        std::cout << "Member deleted successfully!" << std::endl;
    }
    else {
        std::cout << "Invalid choice. No member deleted." << std::endl;
    }

    // Write the updated vector of members back to the text file
    std::ofstream memberFileOut("members.txt");
    if (!memberFileOut.is_open()) {
        std::cerr << "Unable to open file for writing." << std::endl;
        return;
    }

    for (const std::string& member : members) {
        memberFileOut << member << std::endl;
    }
    memberFileOut.close();

}
