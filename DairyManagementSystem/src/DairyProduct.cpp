#include "DairyProduct.hpp"

// --- DairyProduct (Abstract Base) ---
DairyProduct::DairyProduct(int productId, const std::string& productName, double quantity, double unitPrice)
    : productId(productId), productName(productName), quantity(quantity), unitPrice(unitPrice) {}

void DairyProduct::displayProduct() const {
    std::cout << "Product [ID: " << productId << "] " << productName 
              << " | Quantity: " << quantity << " | Unit Price: " << unitPrice 
              << " | Shelf Life: " << getShelfLifeDays() << " days"
              << " | Cost: " << calculateProductionCost() << "\n";
}

int DairyProduct::getProductId() const { return productId; }
std::string DairyProduct::getProductName() const { return productName; }
double DairyProduct::getQuantity() const { return quantity; }
double DairyProduct::getUnitPrice() const { return unitPrice; }

// --- Milk ---
Milk::Milk(int productId, const std::string& productName, double quantity, double unitPrice)
    : DairyProduct(productId, productName, quantity, unitPrice) {}

int Milk::getShelfLifeDays() const {
    return 2;
}

double Milk::calculateProductionCost() const {
    return quantity * 20.0;
}

// --- Curd ---
Curd::Curd(int productId, const std::string& productName, double quantity, double unitPrice)
    : DairyProduct(productId, productName, quantity, unitPrice) {}

int Curd::getShelfLifeDays() const {
    return 7;
}

double Curd::calculateProductionCost() const {
    return quantity * 30.0;
}

// --- Ghee ---
Ghee::Ghee(int productId, const std::string& productName, double quantity, double unitPrice)
    : DairyProduct(productId, productName, quantity, unitPrice) {}

int Ghee::getShelfLifeDays() const {
    return 180;
}

double Ghee::calculateProductionCost() const {
    return quantity * 120.0;
}
