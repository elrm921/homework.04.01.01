#include <iostream>
#include <vector>

class SqlSelectQueryBuilder
{
public:
    SqlSelectQueryBuilder() = default;

    SqlSelectQueryBuilder& AddColumn(const std::string &column)
    {
        columns.push_back(column);
        return *this;
    }
    SqlSelectQueryBuilder& AddFrom(const std::string &table)
    {
        tables.push_back(table);
        return *this;
    }
    SqlSelectQueryBuilder& AddWhere(const std::string &key, const std::string &value)
    {
        conditions.push_back(std::pair(key,value));
        return *this;
    }

    std::string BuildQuery()
    {
        querry_string = "SELECT ";
        int columns_size = columns.size();
        for (int i=0; i<columns_size; i++)
        {
            querry_string += columns[i];
            if (i < columns_size-1) querry_string += ", ";
        }
        querry_string += " FROM ";
        int tables_size = tables.size();
        for (int i=0; i<tables_size; i++)
        {
            querry_string += tables[i];
            if (i < tables_size-1) querry_string += ", ";
        }
        querry_string += " WHERE ";
        int conditions_size = conditions.size();
        for (int i=0; i<conditions_size; i++)
        {
            querry_string += conditions[i].first + "=" + conditions[i].second;
            if (i < conditions_size-1) querry_string += " AND ";
        }
        querry_string += ';';

        return querry_string;
    }
private:
    std::vector<std::string> columns;
    std::vector<std::string> tables;
    std::vector<std::pair<std::string,std::string>> conditions;
    std::string querry_string;
};

int main()
{
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    auto test = query_builder.BuildQuery();
    std::cout << test << std::endl;
    
    assert(test == "SELECT name, phone FROM students WHERE id=42 AND name=John;");
    
    return 0;
}