#pragma once

#include "ProductionBatch.hpp"
#include <string>

class QualityTest {
public:
    virtual ~QualityTest() = default;
    
    virtual bool execute(const ProductionBatch& batch) const = 0;
    virtual std::string getTestName() const = 0;
};

class PHQualityTest : public QualityTest {
public:
    bool execute(const ProductionBatch& batch) const override;
    std::string getTestName() const override;
};

class QuantityQualityTest : public QualityTest {
public:
    bool execute(const ProductionBatch& batch) const override;
    std::string getTestName() const override;
};

class ProductionQualityTest : public QualityTest {
public:
    bool execute(const ProductionBatch& batch) const override;
    std::string getTestName() const override;
};
