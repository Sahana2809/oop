# Dairy Production and Quality Management System

## 1. Project Overview
This project is a C++17 console application simulating a simple dairy factory workflow. It is built as a student OOP project, focusing on fundamental Object-Oriented Programming principles using the Standard Template Library (STL) and basic file handling.

## 2. Background
The project is inspired by a DBMS case study of milk factory operations (like KMF, Dharwad). It redesigns the database domain—encompassing Suppliers, Milk Quality, Production, Quality Control, Inventory, Sales, and Employees—into an Object-Oriented paradigm.

## 3. Workflow
The system simulates the following sequential workflow:
`Supplier -> Milk Batch Received -> Milk Quality Evaluation -> Accepted/Rejected -> Production Batch -> Dairy Product Created -> Product Quality Control -> Pass/Fail -> Inventory -> Sales Order`

## 4. OOP Concepts Used
* **Encapsulation:** The `MilkBatch` status is private and can only be modified internally through the `evaluateQuality()` method, ensuring state integrity.
* **Abstraction:** Concepts like `Person`, `DairyProduct`, and `QualityTest` are abstract base classes, defining interfaces without full implementation.
* **Inheritance:** `Supplier` and `Employee` inherit from `Person`. `Milk`, `Curd`, and `Ghee` inherit from `DairyProduct`. Specific quality tests inherit from `QualityTest`.
* **Runtime Polymorphism:** Various dairy products are managed via a `std::vector<std::unique_ptr<DairyProduct>>`. Similarly, quality tests are evaluated using `QualityTest` pointers, allowing the same code to execute different specific logic.
* **Composition:** `DairyManagementSystem` is composed of collections of the factory's entities (Suppliers, Employees, Batches, Inventory, etc.), managing their lifecycles and interactions.

## 5. STL Used
* `std::vector` for lists of entities (employees, batches).
* `std::unordered_map` for the inventory system mapping product IDs to available quantities.
* `std::unique_ptr` for managing the lifecycle of polymorphic objects.
* `std::string` for robust text handling.

## 6. File Handling
The application uses standard `std::ifstream` and `std::ofstream` to read and write Comma-Separated Values (CSV) files. This allows data to persist across application restarts.

## 7. Exception Handling
Exceptions like `std::runtime_error` are used to handle business logic failures, such as attempting a sales order when there is insufficient inventory.

## 8. Class Structure
```text
Person (Abstract)
  ├── Supplier
  └── Employee

DairyProduct (Abstract)
  ├── Milk
  ├── Curd
  └── Ghee

QualityTest (Abstract)
  ├── PHQualityTest
  ├── QuantityQualityTest
  └── ProductionQualityTest

MilkBatch
ProductionBatch
Inventory
SalesOrder
DairyManagementSystem
```

## 9. Build Instructions
From the project root:
```bash
mkdir build
cd build
cmake ..
cmake --build .
./DairyManagementSystem
```

## 10. Sample Workflow
1. Register a supplier.
2. Receive 500 litres of milk.
3. Enter pH 6.7, fat 4.0%, SNF 8.8%.
4. Milk batch is evaluated and accepted.
5. Create a Curd product.
6. Start a production batch for the curd using the accepted milk.
7. Run quality tests on the production batch.
8. Quality passes, and inventory is automatically updated.
9. Create a sales order to sell the product.

## 11. How to Explain This Project in an Interview
**"Why the project was built and the problem it models:"**
I built this project to model a real-world Dairy Production workflow (inspired by a KMF factory case study). It simulates the journey of milk from supplier reception, quality evaluation, product manufacturing, final quality control, inventory management, and sales.

**"The main workflow:"**
Suppliers provide milk. The milk undergoes pH and fat tests. If accepted, it's processed into products like Milk, Curd, or Ghee. These products pass a final quality check before entering the inventory for sales.

**"Where OOP is used:"**
I heavily utilized OOP principles:
- **Abstraction & Inheritance:** To model general concepts like `Person` and `DairyProduct`, with specific implementations like `Supplier` or `Curd`.
- **Encapsulation:** Protecting critical state, like ensuring a milk batch's quality status can only be modified by the internal evaluation method.
- **Runtime Polymorphism:** Handling different dairy products uniformly in collections via smart pointers and executing diverse quality tests through a common interface.
