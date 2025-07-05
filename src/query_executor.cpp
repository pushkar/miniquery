#include "query_executor.h"
#include "scan_operator.h"
#include "expression.h"
#include "query_planner.h"

#include <arrow/api.h>
#include <iostream>

void QueryExecutor::Run(const std::string& filename, const std::string& query) {
    auto plan = QueryPlanner::ParseQuery(query);
    auto batch = ScanOperator::LoadBatch(filename, 0);
    if (!batch) return;

    auto filter_array = batch->GetColumnByName(plan.filter_column);
    auto select_array = std::static_pointer_cast<arrow::DoubleArray>(batch->GetColumnByName(plan.select_column));

    EqualsString filter_expr(plan.filter_value);
    auto mask = filter_expr.Evaluate(filter_array);

    double sum = 0.0;
    for (int64_t i = 0; i < select_array->length(); ++i) {
        if (mask[i] && select_array->IsValid(i)) {
            sum += select_array->Value(i);
        }
    }

    std::cout << "Total " << plan.select_column << " (" << plan.filter_column << " = '" << plan.filter_value << "'): " << sum << std::endl;
}