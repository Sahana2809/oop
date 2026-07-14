#include "ProductionBatch.hpp"

ProductionBatch::ProductionBatch(int productionId, int milkBatchId, int productId, double quantityProduced)
    : productionId(productionId), milkBatchId(milkBatchId), productId(productId), 
      quantityProduced(quantityProduced), qualityPassed(false) {}

void ProductionBatch::markQualityResult(bool result) {
    qualityPassed = result;
}

bool ProductionBatch::hasPassedQuality() const {
    return qualityPassed;
}

int ProductionBatch::getProductionId() const { return productionId; }
int ProductionBatch::getProductId() const { return productId; }
double ProductionBatch::getQuantityProduced() const { return quantityProduced; }

void ProductionBatch::displayProductionDetails() const {
    std::cout << "Production Batch [ID: " << productionId << "] from Milk Batch: " << milkBatchId
              << "\n  Product ID: " << productId << ", Quantity Produced: " << quantityProduced
              << "\n  Quality Passed: " << (qualityPassed ? "Yes" : "No") << "\n";
}
