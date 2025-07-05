#pragma once

#include <arrow/array.h>
#include <arrow/type.h>
#include <memory>
#include <vector>

class Expression {
public:
    virtual ~Expression() = default;

    // Returns a boolean mask for the valid rows in an array
    virtual std::vector<bool> Evaluate(const std::shared_ptr<arrow::Array>& column) const = 0;
};

class EqualsString : public Expression {
public:
    EqualsString(const std::string& value);
    std::vector<bool> Evaluate(const std::shared_ptr<arrow::Array>& column) const override;

private:
    std::string target_value;
};