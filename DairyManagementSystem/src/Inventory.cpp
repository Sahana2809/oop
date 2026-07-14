#include "Inventory.hpp"

void Inventory::addStock(int productId, double quantity) {
    if (quantity < 0) return;
    stock[productId] += quantity;
}

void Inventory::removeStock(int productId, double quantity) {
    if (quantity < 0) return;
    if (stock[productId] < quantity) {
        throw std::runtime_error("Insufficient stock");
    }
    stock[productId] -= quantity;
}

double Inventory::getStock(int productId) const {
    auto it = stock.find(productId);
    if (it != stock.end()) {
        return it->second;
    }
    return 0.0;
}

void Inventory::displayInventory() const {
    std::cout << "--- Current Inventory ---\n";
    if (stock.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }
    for (const auto& pair : stock) {
        std::cout << "Product ID: " << pair.first << " | Quantity Available: " << pair.second << "\n";
    }
}
