#pragma once

#include <iostream>

enum class BatchStatus {
    PENDING,
    ACCEPTED,
    REJECTED
};

class MilkBatch {
private:
    int batchId;
    int supplierId;
    double quantityLitres;
    double ph;
    double fatPercentage;
    double snfPercentage;
    BatchStatus status;

public:
    MilkBatch(int batchId, int supplierId, double quantityLitres, double ph, double fatPercentage, double snfPercentage);

    void evaluateQuality();
    
    BatchStatus getStatus() const;
    int getBatchId() const;
    int getSupplierId() const;
    double getQuantity() const;

    void displayBatchDetails() const;
};
