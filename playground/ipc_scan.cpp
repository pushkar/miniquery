#include <arrow/api.h>
#include <arrow/io/api.h>
#include <arrow/ipc/api.h>
#include <iostream>

int main() {
    std::string filename = "../data/transactions.arrow"; // Arrow IPC file (Feather v2)

    // Open the IPC file using the modern Arrow API
    auto infile_result = arrow::io::ReadableFile::Open(filename);
    if (!infile_result.ok()) {
        std::cerr << "Failed to open IPC file: " << infile_result.status().ToString() << std::endl;
        return 1;
    }
    auto infile = infile_result.ValueOrDie();

    // Create a reader using the modern Arrow API
    auto reader_result = arrow::ipc::RecordBatchFileReader::Open(infile);
    if (!reader_result.ok()) {
        std::cerr << "Error opening Arrow reader: " << reader_result.status().ToString() << std::endl;
        return 1;
    }
    auto reader = reader_result.ValueOrDie();

    double sum_sales = 0.0;

    for (int i = 0; i < reader->num_record_batches(); ++i) {
        auto batch_result = reader->ReadRecordBatch(i);
        if (!batch_result.ok()) continue;
        auto batch = batch_result.ValueOrDie();

        auto region_array = std::static_pointer_cast<arrow::StringArray>(batch->GetColumnByName("region"));
        auto sales_array = std::static_pointer_cast<arrow::DoubleArray>(batch->GetColumnByName("sales"));

        for (int64_t j = 0; j < region_array->length(); ++j) {
            if (region_array->IsValid(j) && region_array->GetString(j) == "US") {
                if (sales_array->IsValid(j)) {
                    sum_sales += sales_array->Value(j);
                }
            }
        }
    }

    std::cout << "Total sales in US: " << sum_sales << std::endl;
    return 0;
}