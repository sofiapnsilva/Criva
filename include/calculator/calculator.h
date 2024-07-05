#pragma once
#include <unordered_map>
#include <stack>
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>

namespace calculator {

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class Calculator {
private:
    std::unordered_map<std::string, int> variables;
    int last_result;
    std::stack<std::unique_ptr<Command>> history;
    std::unordered_map<std::string, std::vector<std::string>> dependencies;

public:
    Calculator();
    void assign_variable(const std::string& var, int value);
    int get_variable(const std::string& var) const;
    void add_command(std::unique_ptr<Command> cmd);
    void undo(int count);
    int get_result() const;
    void print_variables() const;
    void update_dependent_variables(const std::string& var);
    const std::unordered_map<std::string, int>& get_variables() const;
    std::unordered_map<std::string, std::vector<std::string>>& get_dependencies();
    bool is_variable_defined(const std::string& var) const {
        return variables.find(var) != variables.end();
    }
    void track_dependency(const std::string& dependent, const std::string& dependency);
    int evaluate_expression(const std::string& expr);
};
}
