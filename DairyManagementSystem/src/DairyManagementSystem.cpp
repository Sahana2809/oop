#include "DairyManagementSystem.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

using namespace std;

void DairyManagementSystem::registerSupplier() {
    int id;
    string name, contact;
    cout << "Enter Supplier ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Supplier Name: ";
    getline(cin, name);
    cout << "Enter Supplier Contact: ";
    getline(cin, contact);

    suppliers.emplace_back(id, name, contact);
    cout << "Supplier registered successfully.\n";
}

void DairyManagementSystem::registerEmployee() {
    int id;
    string name, contact, role;
    cout << "Enter Employee ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Employee Name: ";
    getline(cin, name);
    cout << "Enter Employee Contact: ";
    getline(cin, contact);
    cout << "Enter Employee Role: ";
    getline(cin, role);

    employees.emplace_back(id, name, contact, role);
    cout << "Employee registered successfully.\n";
}

void DairyManagementSystem::receiveMilkBatch() {
    int batchId, supplierId;
    double quantity, ph, fat, snf;
    
    cout << "Enter Milk Batch ID: ";
    cin >> batchId;
    cout << "Enter Supplier ID: ";
    cin >> supplierId;
    cout << "Enter Quantity (Litres): ";
    cin >> quantity;
    cout << "Enter pH: ";
    cin >> ph;
    cout << "Enter Fat %: ";
    cin >> fat;
    cout << "Enter SNF %: ";
    cin >> snf;

    milkBatches.emplace_back(batchId, supplierId, quantity, ph, fat, snf);
    cout << "Milk batch received and is PENDING evaluation.\n";
}

void DairyManagementSystem::evaluateMilkBatch() {
    int batchId;
    cout << "Enter Milk Batch ID to evaluate: ";
    cin >> batchId;

    bool found = false;
    for (auto& batch : milkBatches) {
        if (batch.getBatchId() == batchId) {
            batch.evaluateQuality();
            cout << "Batch Evaluated. Result: ";
            if (batch.getStatus() == BatchStatus::ACCEPTED) {
                cout << "ACCEPTED\n";
                // Update supplier total milk
                for(auto& sup : suppliers) {
                    if(sup.getId() == batch.getSupplierId()) {
                        sup.addMilkSupply(batch.getQuantity());
                        break;
                    }
                }
            } else {
                cout << "REJECTED\n";
            }
            found = true;
            break;
        }
    }
    if (!found) cout << "Batch ID not found.\n";
}

void DairyManagementSystem::createProduct() {
    int type, id;
    string name;
    double quantity, price;

    cout << "Product Type (1: Milk, 2: Curd, 3: Ghee): ";
    cin >> type;
    cout << "Enter Product ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Product Name: ";
    getline(cin, name);
    cout << "Enter Expected Base Quantity for Costing: ";
    cin >> quantity;
    cout << "Enter Unit Price: ";
    cin >> price;

    if (type == 1) {
        products.push_back(make_unique<Milk>(id, name, quantity, price));
    } else if (type == 2) {
        products.push_back(make_unique<Curd>(id, name, quantity, price));
    } else if (type == 3) {
        products.push_back(make_unique<Ghee>(id, name, quantity, price));
    } else {
        cout << "Invalid product type.\n";
        return;
    }
    cout << "Product type registered.\n";
}

void DairyManagementSystem::createProductionBatch() {
    int prodId, milkBatchId, prodTypeId;
    double quantity;

    cout << "Enter Production Batch ID: ";
    cin >> prodId;
    cout << "Enter source Milk Batch ID: ";
    cin >> milkBatchId;

    // Check if milk batch is accepted
    bool accepted = false;
    for (const auto& batch : milkBatches) {
        if (batch.getBatchId() == milkBatchId) {
            if (batch.getStatus() == BatchStatus::ACCEPTED) {
                accepted = true;
            }
            break;
        }
    }

    if (!accepted) {
        cout << "Error: Cannot start production. Source milk batch must be ACCEPTED.\n";
        return;
    }

    cout << "Enter Target Product ID: ";
    cin >> prodTypeId;
    cout << "Enter Quantity Produced: ";
    cin >> quantity;

    productionBatches.emplace_back(prodId, milkBatchId, prodTypeId, quantity);
    cout << "Production batch created and waiting for quality control.\n";
}

void DairyManagementSystem::performQualityControl() {
    int prodId;
    cout << "Enter Production Batch ID to test: ";
    cin >> prodId;

    for (auto& pbatch : productionBatches) {
        if (pbatch.getProductionId() == prodId) {
            if (pbatch.hasPassedQuality()) {
                cout << "Batch already passed quality.\n";
                return;
            }

            vector<unique_ptr<QualityTest>> tests;
            tests.push_back(make_unique<PHQualityTest>());
            tests.push_back(make_unique<QuantityQualityTest>());
            tests.push_back(make_unique<ProductionQualityTest>());

            bool allPassed = true;
            for (const auto& test : tests) {
                if (!test->execute(pbatch)) {
                    allPassed = false;
                    cout << test->getTestName() << " FAILED.\n";
                } else {
                    cout << test->getTestName() << " PASSED.\n";
                }
            }

            pbatch.markQualityResult(allPassed);
            if (allPassed) {
                cout << "Production Batch PASSED quality control. Adding to Inventory.\n";
                inventory.addStock(pbatch.getProductId(), pbatch.getQuantityProduced());
            } else {
                cout << "Production Batch FAILED quality control.\n";
            }
            return;
        }
    }
    cout << "Production Batch not found.\n";
}

void DairyManagementSystem::viewInventory() const {
    inventory.displayInventory();
}

void DairyManagementSystem::createSalesOrder() {
    int orderId, productId;
    double quantity;

    cout << "Enter Sales Order ID: ";
    cin >> orderId;
    cout << "Enter Product ID: ";
    cin >> productId;
    cout << "Enter Quantity to Sell: ";
    cin >> quantity;

    try {
        inventory.removeStock(productId, quantity);
        
        // Find unit price
        double unitPrice = 0.0;
        for (const auto& p : products) {
            if (p->getProductId() == productId) {
                unitPrice = p->getUnitPrice();
                break;
            }
        }
        if (unitPrice == 0.0) {
            cout << "Warning: Product ID not found in product list, price set to 0.\n";
        }

        SalesOrder order(orderId, productId, quantity);
        order.calculateTotal(unitPrice);
        salesOrders.push_back(order);
        
        cout << "Sales Order created successfully. Total Amount: $" << order.getTotalAmount() << "\n";
    } catch (const runtime_error& e) {
        cout << "Error creating Sales Order: " << e.what() << "\n";
    }
}

void DairyManagementSystem::displaySuppliers() const {
    for (const auto& s : suppliers) {
        s.displayRole();
    }
}

void DairyManagementSystem::displayMilkBatches() const {
    for (const auto& m : milkBatches) {
        m.displayBatchDetails();
    }
}

void DairyManagementSystem::displayProducts() const {
    for (const auto& p : products) {
        p->displayProduct();
    }
}

void DairyManagementSystem::displayProductionBatches() const {
    for (const auto& p : productionBatches) {
        p.displayProductionDetails();
    }
}

void DairyManagementSystem::displaySalesOrders() const {
    for (const auto& s : salesOrders) {
        s.displayOrder();
    }
}

// Basic CSV saving
void DairyManagementSystem::saveData() const {
    ofstream sf(dataPath + "suppliers.csv");
    for (const auto& s : suppliers) {
        sf << s.getId() << "," << s.getName() << "," << s.getContact() << "," << s.getTotalMilkSupplied() << "\n";
    }

    ofstream ef(dataPath + "employees.csv");
    for (const auto& e : employees) {
        ef << e.getId() << "," << e.getName() << "," << e.getContact() << "," << e.getRole() << "\n";
    }

    ofstream mf(dataPath + "milk_batches.csv");
    for (const auto& m : milkBatches) {
        mf << m.getBatchId() << "," << m.getSupplierId() << "," << m.getQuantity() << ",";
        // To maintain simplicity we just save values. Re-evaluating is better or save status.
        int stat = static_cast<int>(m.getStatus());
        mf << stat << "\n";
    }

    ofstream pf(dataPath + "products.csv");
    for (const auto& p : products) {
        string typeStr = "MILK";
        if (dynamic_cast<Curd*>(p.get())) typeStr = "CURD";
        else if (dynamic_cast<Ghee*>(p.get())) typeStr = "GHEE";
        
        pf << p->getProductId() << "," << typeStr << "," << p->getProductName() << "," 
           << p->getQuantity() << "," << p->getUnitPrice() << "\n";
    }

    ofstream prf(dataPath + "production.csv");
    for (const auto& p : productionBatches) {
        prf << p.getProductionId() << "," << p.getProductId() << "," << p.getQuantityProduced() << "," << p.hasPassedQuality() << "\n";
    }

    ofstream sof(dataPath + "sales.csv");
    for (const auto& s : salesOrders) {
        sof << s.getOrderId() << "," << s.getProductId() << "," << s.getQuantity() << "," << s.getTotalAmount() << "\n";
    }
    
    cout << "Data saved to CSV files in data/ directory.\n";
}

void DairyManagementSystem::loadData() {
    string line;
    ifstream sf(dataPath + "suppliers.csv");
    if (sf.is_open()) {
        while (getline(sf, line)) {
            stringstream ss(line);
            string item;
            int id; string name, contact; double total;
            
            getline(ss, item, ','); id = stoi(item);
            getline(ss, name, ',');
            getline(ss, contact, ',');
            getline(ss, item, ','); total = stod(item);
            
            suppliers.emplace_back(id, name, contact, total);
        }
    }

    ifstream ef(dataPath + "employees.csv");
    if (ef.is_open()) {
        while (getline(ef, line)) {
            stringstream ss(line);
            string item;
            int id; string name, contact, role;
            
            getline(ss, item, ','); id = stoi(item);
            getline(ss, name, ',');
            getline(ss, contact, ',');
            getline(ss, role, ',');
            
            employees.emplace_back(id, name, contact, role);
        }
    }

    // Simplified load for products
    ifstream pf(dataPath + "products.csv");
    if (pf.is_open()) {
        while (getline(pf, line)) {
            stringstream ss(line);
            string item, typeStr, name;
            int id; double qty, price;
            
            getline(ss, item, ','); id = stoi(item);
            getline(ss, typeStr, ',');
            getline(ss, name, ',');
            getline(ss, item, ','); qty = stod(item);
            getline(ss, item, ','); price = stod(item);
            
            if (typeStr == "MILK") {
                products.push_back(make_unique<Milk>(id, name, qty, price));
            } else if (typeStr == "CURD") {
                products.push_back(make_unique<Curd>(id, name, qty, price));
            } else if (typeStr == "GHEE") {
                products.push_back(make_unique<Ghee>(id, name, qty, price));
            }
        }
    }

    cout << "Data loaded from CSV files (if they existed).\n";
}

void DairyManagementSystem::run() {
    loadData();
    int choice = -1;

    while (choice != 0) {
        cout << "\n============================================\n";
        cout << " DAIRY PRODUCTION & QUALITY MANAGEMENT SYSTEM\n";
        cout << "============================================\n";
        cout << "1. Register Supplier\n";
        cout << "2. Register Employee\n";
        cout << "3. Receive Milk Batch\n";
        cout << "4. Evaluate Milk Quality\n";
        cout << "5. Create Dairy Product\n";
        cout << "6. Start Production Batch\n";
        cout << "7. Perform Production Quality Control\n";
        cout << "8. View Inventory\n";
        cout << "9. Create Sales Order\n";
        cout << "10. View Suppliers\n";
        cout << "11. View Milk Batches\n";
        cout << "12. View Products\n";
        cout << "13. View Production Batches\n";
        cout << "14. View Sales Orders\n";
        cout << "15. Save Data\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        // Reset fail state if char is inputted
        if(cin.fail()) {
            cin.clear();
            string ignoreLine;
            getline(cin, ignoreLine);
            choice = -1;
            continue;
        }

        try {
            switch (choice) {
                case 1: registerSupplier(); break;
                case 2: registerEmployee(); break;
                case 3: receiveMilkBatch(); break;
                case 4: evaluateMilkBatch(); break;
                case 5: createProduct(); break;
                case 6: createProductionBatch(); break;
                case 7: performQualityControl(); break;
                case 8: viewInventory(); break;
                case 9: createSalesOrder(); break;
                case 10: displaySuppliers(); break;
                case 11: displayMilkBatches(); break;
                case 12: displayProducts(); break;
                case 13: displayProductionBatches(); break;
                case 14: displaySalesOrders(); break;
                case 15: saveData(); break;
                case 0: 
                    saveData();
                    cout << "Exiting...\n"; 
                    break;
                default: cout << "Invalid choice. Please try again.\n";
            }
        } catch (const exception& e) {
            cout << "An error occurred: " << e.what() << "\n";
        }
    }
}
