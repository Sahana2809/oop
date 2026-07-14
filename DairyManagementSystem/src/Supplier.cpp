#include "Supplier.hpp"

Supplier::Supplier(int id, const std::string& name, const std::string& contact, double totalMilkSupplied)
    : Person(id, name, contact), totalMilkSupplied(totalMilkSupplied) {}

void Supplier::addMilkSupply(double quantity) {
    totalMilkSupplied += quantity;
}

double Supplier::getTotalMilkSupplied() const {
    return totalMilkSupplied;
}

void Supplier::displayRole() const {
    std::cout << "Role: Supplier [ID: " << id << "] " << name 
              << ", Total Milk Supplied: " << totalMilkSupplied << " Litres\n";
}
