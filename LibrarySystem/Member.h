
// Member.h

#pragma once
#include <string>

class Member {
private:
    std::string name;
    int age;
    std::string address;
    static int nextId; // Static member variable to track next available member ID
    int id;
public:
    Member(const std::string& name, int age, const std::string& address);
    Member();


    std::string getName() const;
    void setName(const std::string& name);
    void createMember();
    void displayAllMembers();
    int getAge() const;
    void setAge(int age);
    int getId() const;
    void setId(int m);
    std::string getAddress() const;
    void setAddress(const std::string& address);
    void displayInfo() const;
    void deleteMember();
    void searchForMemberByName();
    void borrowBook();
    void returnBook();
    void displayBorrowedBooks() const;
    static void updateNextId();

    // Static member function to write nextId to file
    static void writeNextId();
    // Other member functions and variables as needed
};
