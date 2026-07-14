#include "SalesOrder.hpp"

SalesOrder::SalesOrder(int orderId, int productId, double quantity)
    : orderId(orderId), productId(productId), quantity(quantity), totalAmount(0.0) {}

void SalesOrder::calculateTotal(double unitPrice) {
    totalAmount = quantity * unitPrice;
}

int SalesOrder::getOrderId() const { return orderId; }
int SalesOrder::getProductId() const { return productId; }
double SalesOrder::getQuantity() const { return quantity; }
double SalesOrder::getTotalAmount() const { return totalAmount; }

void SalesOrder::displayOrder() const {
    std::cout << "Sales Order [ID: " << orderId << "] Product ID: " << productId 
              << ", Quantity: " << quantity << ", Total Amount: $" << totalAmount << "\n";
}
