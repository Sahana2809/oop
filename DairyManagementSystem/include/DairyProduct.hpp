#pragma once

#include <string>
#include <iostream>

class DairyProduct {
protected:
    int productId;
    std::string productName;
    double quantity;
    double unitPrice;

public:
    DairyProduct(int productId, const std::string& productName, double quantity, double unitPrice);
    
    virtual ~DairyProduct() = default;

    virtual int getShelfLifeDays() const = 0;
    virtual double calculateProductionCost() const = 0;
    
    virtual void displayProduct() const;

    int getProductId() const;
    std::string getProductName() const;
    double getQuantity() const;
    double getUnitPrice() const;
};

class Milk : public DairyProduct {
public:
    Milk(int productId, const std::string& productName, double quantity, double unitPrice);
    
    int getShelfLifeDays() const override;
    double calculateProductionCost() const override;
};

class Curd : public DairyProduct {
public:
    Curd(int productId, const std::string& productName, double quantity, double unitPrice);
    
    int getShelfLifeDays() const override;
    double calculateProductionCost() const override;
};

class Ghee : public DairyProduct {
public:
    Ghee(int productId, const std::string& productName, double quantity, double unitPrice);
    
    int getShelfLifeDays() const override;
    double calculateProductionCost() const override;
};
