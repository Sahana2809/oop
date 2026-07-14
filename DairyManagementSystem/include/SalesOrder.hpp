#pragma once

#include <iostream>

class SalesOrder {
private:
    int orderId;
    int productId;
    double quantity;
    double totalAmount;

public:
    SalesOrder(int orderId, int productId, double quantity);
    
    void calculateTotal(double unitPrice);
    
    int getOrderId() const;
    int getProductId() const;
    double getQuantity() const;
    double getTotalAmount() const;

    void displayOrder() const;
};
