#include "expression.h"
#include <arrow/array.h>
#include <arrow/type.h>
#include <arrow/util/value_parsing.h>
#include <iostream>

EqualsString::EqualsString(const std::string& value) : target_value(value) {}

std::vector<bool> EqualsString::Evaluate(const std::shared_ptr<arrow::Array>& column) const {
    std::vector<bool> mask(column->length(), false);

    auto str_array = std::static_pointer_cast<arrow::StringArray>(column);
    for (int64_t i = 0; i < str_array->length(); ++i) {
        if (str_array->IsValid(i) && str_array->GetString(i) == target_value) {
            mask[i] = true;
        }
    }

    return mask;
}