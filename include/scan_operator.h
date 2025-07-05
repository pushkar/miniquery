#pragma once

#include <arrow/record_batch.h>
#include <memory>
#include <string>

class ScanOperator {
public:
    // Load data from file and return a batch
    static std::shared_ptr<arrow::RecordBatch> LoadBatch(const std::string& filename, int batch_index);
};