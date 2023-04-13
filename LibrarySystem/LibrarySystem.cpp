// LibrarySystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Library.h"
#include "Book.h"
#include "Member.h"
int main()
{
    bool isRunning = true;
    Member member;

    while (isRunning) {
        Library library("books.txt");
        switch (library.displayMenu()) {
        case 1:
            library.createNewBook();
            break;
        case 2:
            library.deleteBook();
            break;
        case 3:
            library.searchForBookByTitle();
            break;
        case 4:
            library.displayAllBooks();
            break;
        case 5:
            member.createMember();
            break;
        case 6:
            member.deleteMember();
            break;
        case 7:
            member.searchForMemberByName();
            break;
        case 8:
            member.displayAllMembers();
            break;
        case 9:
            member.borrowBook();
            break;
        case 10:
            member.returnBook();
            break;
        case 11:
            member.displayBorrowedBooks();
            break;
        case 12:
            isRunning = false;
            break;
        default:
            std::cout << "Invalid option selected\n";
        }
    }
}

