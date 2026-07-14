#include "Employee.hpp"

Employee::Employee(int id, const std::string& name, const std::string& contact, const std::string& role)
    : Person(id, name, contact), role(role) {}

std::string Employee::getRole() const {
    return role;
}

void Employee::displayRole() const {
    std::cout << "Role: Employee [ID: " << id << "] " << name 
              << ", Job Title: " << role << "\n";
}
