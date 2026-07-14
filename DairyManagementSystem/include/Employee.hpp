#pragma once

#include "Person.hpp"

class Employee : public Person {
private:
    std::string role;

public:
    Employee(int id, const std::string& name, const std::string& contact, const std::string& role);

    std::string getRole() const;

    void displayRole() const override;
};
