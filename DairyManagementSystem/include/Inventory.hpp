#pragma once

#include <unordered_map>
#include <stdexcept>
#include <iostream>

class Inventory {
private:
    std::unordered_map<int, double> stock;

public:
    void addStock(int productId, double quantity);
    void removeStock(int productId, double quantity);
    double getStock(int productId) const;
    void displayInventory() const;
};
