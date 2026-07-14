#include "QualityTest.hpp"
#include <iostream>

// --- PHQualityTest ---
bool PHQualityTest::execute(const ProductionBatch& batch) const {
    // Simplified simulation: Milk pH was already checked, so this passes if batch is valid.
    return batch.getQuantityProduced() >= 0;
}

std::string PHQualityTest::getTestName() const {
    return "PH Quality Test";
}

// --- QuantityQualityTest ---
bool QuantityQualityTest::execute(const ProductionBatch& batch) const {
    // Pass if quantityProduced > 0
    return batch.getQuantityProduced() > 0;
}

std::string QuantityQualityTest::getTestName() const {
    return "Quantity Quality Test";
}

// --- ProductionQualityTest ---
bool ProductionQualityTest::execute(const ProductionBatch& batch) const {
    // Pass if productionId and productId are valid positive values
    return batch.getProductionId() > 0 && batch.getProductId() > 0;
}

std::string ProductionQualityTest::getTestName() const {
    return "Production ID Quality Test";
}
