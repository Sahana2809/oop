#include "MilkBatch.hpp"

MilkBatch::MilkBatch(int batchId, int supplierId, double quantityLitres, double ph, double fatPercentage, double snfPercentage)
    : batchId(batchId), supplierId(supplierId), quantityLitres(quantityLitres), 
      ph(ph), fatPercentage(fatPercentage), snfPercentage(snfPercentage), status(BatchStatus::PENDING) {}

void MilkBatch::evaluateQuality() {
    // Quality rules:
    // pH must be between 6.5 and 6.8 inclusive.
    // Fat percentage must be at least 3.5.
    // SNF percentage must be at least 8.5.
    
    if (ph >= 6.5 && ph <= 6.8 && fatPercentage >= 3.5 && snfPercentage >= 8.5) {
        status = BatchStatus::ACCEPTED;
    } else {
        status = BatchStatus::REJECTED;
    }
}

BatchStatus MilkBatch::getStatus() const {
    return status;
}

int MilkBatch::getBatchId() const { return batchId; }
int MilkBatch::getSupplierId() const { return supplierId; }
double MilkBatch::getQuantity() const { return quantityLitres; }

void MilkBatch::displayBatchDetails() const {
    std::string statusStr;
    if (status == BatchStatus::PENDING) statusStr = "PENDING";
    else if (status == BatchStatus::ACCEPTED) statusStr = "ACCEPTED";
    else statusStr = "REJECTED";

    std::cout << "Milk Batch [ID: " << batchId << "] Supplier ID: " << supplierId 
              << "\n  Quantity: " << quantityLitres << " Litres"
              << "\n  pH: " << ph << ", Fat: " << fatPercentage << "%, SNF: " << snfPercentage << "%"
              << "\n  Status: " << statusStr << "\n";
}
