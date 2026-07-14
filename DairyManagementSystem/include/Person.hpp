#pragma once

#include <string>
#include <iostream>

class Person {
protected:
    int id;
    std::string name;
    std::string contact;

public:
    Person(int id, const std::string& name, const std::string& contact)
        : id(id), name(name), contact(contact) {}

    virtual ~Person() = default;

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getContact() const { return contact; }

    // Pure virtual function demonstrating abstraction
    virtual void displayRole() const = 0;
};
