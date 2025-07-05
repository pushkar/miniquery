#include "scan_operator.h"
#include <arrow/io/api.h>
#include <arrow/ipc/api.h>
#include <iostream>

std::shared_ptr<arrow::RecordBatch> ScanOperator::LoadBatch(const std::string& filename, int batch_index) {
    // Open the file using the modern Arrow API
    auto infile_result = arrow::io::ReadableFile::Open(filename);
    if (!infile_result.ok()) {
        std::cerr << "Failed to open file: " << infile_result.status().ToString() << std::endl;
        return nullptr;
    }
    auto infile = infile_result.ValueOrDie();

    // Open the record batch file reader
    auto reader_result = arrow::ipc::RecordBatchFileReader::Open(infile);
    if (!reader_result.ok()) {
        std::cerr << "Failed to open reader: " << reader_result.status().ToString() << std::endl;
        return nullptr;
    }
    auto reader = reader_result.ValueOrDie();

    // Read the specified batch
    auto batch_result = reader->ReadRecordBatch(batch_index);
    if (!batch_result.ok()) {
        std::cerr << "Failed to read batch: " << batch_result.status().ToString() << std::endl;
        return nullptr;
    }

    return batch_result.ValueOrDie();
}