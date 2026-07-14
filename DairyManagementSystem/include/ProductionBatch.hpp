#pragma once

#include <iostream>

class ProductionBatch {
private:
    int productionId;
    int milkBatchId;
    int productId;
    double quantityProduced;
    bool qualityPassed;

public:
    ProductionBatch(int productionId, int milkBatchId, int productId, double quantityProduced);

    void markQualityResult(bool result);
    bool hasPassedQuality() const;
    
    int getProductionId() const;
    int getProductId() const;
    double getQuantityProduced() const;

    void displayProductionDetails() const;
};
