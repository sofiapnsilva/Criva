#include "calculator/calculator.h"
#include "calculator/arithmetic_command.h"
#include <stdexcept>

namespace calculator {

ArithmeticCommand::ArithmeticCommand(Calculator& calc, const std::string& var, const std::string& op,
                                     const std::string& lhs, const std::string& rhs)
    : calculator(calc), variable(var), operation(op), lhs_var(lhs), rhs_var(rhs), prev_value(0) {
}

void ArithmeticCommand::execute() {
    int lhs, rhs;

    try {
        lhs = std::stoi(lhs_var);
        rhs = std::stoi(rhs_var);
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Invalid argument: " + std::string(e.what()));
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("Out of range: " + std::string(e.what()));
    }

    prev_value = calculator.get_variable(variable);

    if (operation == "+") {
        calculator.assign_variable(variable, lhs + rhs);
    } else if (operation == "-") {
        calculator.assign_variable(variable, lhs - rhs);
    } else if (operation == "*") {
        calculator.assign_variable(variable, lhs * rhs);
    } else if (operation == "/") {
        if (rhs == 0) {
            throw std::runtime_error("Division by zero");
        }
        calculator.assign_variable(variable, lhs / rhs);
    } else {
        throw std::runtime_error("Unsupported operation: " + operation);
    }

    // Update dependencies for 'variable'
    calculator.get_dependencies()[variable] = {lhs_var, rhs_var};
}

void ArithmeticCommand::undo() {
    calculator.assign_variable(variable, prev_value);
}

}
