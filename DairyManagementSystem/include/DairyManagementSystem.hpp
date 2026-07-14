#pragma once

#include "Supplier.hpp"
#include "Employee.hpp"
#include "MilkBatch.hpp"
#include "DairyProduct.hpp"
#include "ProductionBatch.hpp"
#include "QualityTest.hpp"
#include "Inventory.hpp"
#include "SalesOrder.hpp"

#include <vector>
#include <memory>
#include <string>

class DairyManagementSystem {
private:
    std::vector<Supplier> suppliers;
    std::vector<Employee> employees;
    std::vector<MilkBatch> milkBatches;
    std::vector<std::unique_ptr<DairyProduct>> products;
    std::vector<ProductionBatch> productionBatches;
    std::vector<SalesOrder> salesOrders;
    Inventory inventory;

    std::string dataPath = "data/";

public:
    void registerSupplier();
    void registerEmployee();
    
    void receiveMilkBatch();
    void evaluateMilkBatch();
    
    void createProduct();
    void createProductionBatch();
    void performQualityControl();
    
    void viewInventory() const;
    void createSalesOrder();
    
    void displaySuppliers() const;
    void displayMilkBatches() const;
    void displayProducts() const;
    void displayProductionBatches() const;
    void displaySalesOrders() const;
    
    void saveData() const;
    void loadData();

    void run();
};
