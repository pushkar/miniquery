#include "query_planner.h"
#include <sstream>
#include <regex>

QueryPlan QueryPlanner::ParseQuery(const std::string& query) {
    QueryPlan plan;

    // Pattern: SELECT col WHERE col = 'value'
    std::regex pattern(R"(SELECT\s+(\w+)\s+WHERE\s+(\w+)\s*=\s*'([^']+)')", std::regex::icase);
    std::smatch match;

    if (std::regex_search(query, match, pattern)) {
        plan.select_column = match[1];
        plan.filter_column = match[2];
        plan.filter_value = match[3];
    } else {
        throw std::runtime_error("Invalid query format.");
    }

    return plan;
}