#pragma once

#include "Person.hpp"

class Supplier : public Person {
private:
    double totalMilkSupplied;

public:
    Supplier(int id, const std::string& name, const std::string& contact, double totalMilkSupplied = 0.0);

    void addMilkSupply(double quantity);
    double getTotalMilkSupplied() const;

    void displayRole() const override;
};
