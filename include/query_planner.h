#pragma once
#include <string>

struct QueryPlan {
    std::string select_column;
    std::string filter_column;
    std::string filter_value;
};

class QueryPlanner {
public:
    static QueryPlan ParseQuery(const std::string& query);
};