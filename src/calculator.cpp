#include "calculator/calculator.h"
#include "calculator/arithmetic_command.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>

namespace calculator {

Calculator::Calculator() : last_result(0) {}

void Calculator::assign_variable(const std::string& var, int value) {
    variables[var] = value;
    last_result = value;
    update_dependent_variables(var);
}

int Calculator::get_variable(const std::string& var) const {
    auto it = variables.find(var);
    if (it == variables.end()) {
        throw std::runtime_error("'" + var + "' not yet defined");
    }
    return it->second;
}

void Calculator::add_command(std::unique_ptr<Command> cmd) {
    cmd->execute();
    history.push(std::move(cmd));
}

void Calculator::undo(int count) {
    while (count > 0 && !history.empty()) {
        history.top()->undo();
        history.pop();
        --count;
    }
}

int Calculator::get_result() const {
    return last_result;
}

void Calculator::print_variables() const {
    for (const auto& [var, value] : variables) {
        std::cout << var << " = " << value;

        auto it = dependencies.find(var);
        if (it != dependencies.end()) {
            std::cout << ", ";
            for (size_t i = 0; i < it->second.size(); ++i) {
                std::cout << it->second[i];
                if (i < it->second.size() - 1) {
                    std::cout << ", ";
                }
            }
        }

        std::cout << std::endl;
    }
}

void Calculator::update_dependent_variables(const std::string& var) {
    auto it = dependencies.find(var);
    if (it != dependencies.end()) {
        for (const auto& dependent : it->second) {
            try {
                int value = evaluate_expression(dependent);
                variables[dependent] = value;
                std::cout << dependent << " = " << value << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error updating dependent variable '" << dependent << "': " << e.what() << std::endl;
            }
        }
    }
}

void Calculator::track_dependency(const std::string& dependent, const std::string& dependency) {
    dependencies[dependency].push_back(dependent);
}

const std::unordered_map<std::string, int>& Calculator::get_variables() const {
    return variables;
}

std::unordered_map<std::string, std::vector<std::string>>& Calculator::get_dependencies() {
    return dependencies;
}

int Calculator::evaluate_expression(const std::string& expr) {
    std::stringstream ss(expr);
    std::string lhs, op, rhs;
    ss >> lhs >> op >> rhs;

    int lhs_value = 0, rhs_value = 0;

    // Check if lhs is a number or a variable
    if (std::isdigit(lhs[0])) {
        lhs_value = std::stoi(lhs);
    } else {
        if (!is_variable_defined(lhs)) {
            throw std::runtime_error("'" + lhs + "' not yet defined");
        }
        lhs_value = get_variable(lhs);
    }

    // Check if rhs is a number or a variable
    if (std::isdigit(rhs[0])) {
        rhs_value = std::stoi(rhs);
    } else {
        if (!is_variable_defined(rhs)) {
            throw std::runtime_error("'" + rhs + "' not yet defined");
        }
        rhs_value = get_variable(rhs);
    }

    // Evaluate the expression based on the operator
    int result = 0;
    if (op == "+") {
        result = lhs_value + rhs_value;
    } else if (op == "-") {
        result = lhs_value - rhs_value;
    } else if (op == "*") {
        result = lhs_value * rhs_value;
    } else if (op == "/") {
        if (rhs_value == 0) {
            throw std::runtime_error("Division by zero");
        }
        result = lhs_value / rhs_value;
    } else {
        throw std::runtime_error("Unsupported operation: " + op);
    }

    return result;
}

}
