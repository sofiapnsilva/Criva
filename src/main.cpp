#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "calculator/calculator.h"
#include "calculator/arithmetic_command.h"

using namespace std;
using namespace calculator;

void process_command(Calculator& calc, const std::string& line) {
    std::stringstream ss(line);
    std::string var, equals, op, lhs, rhs;
    ss >> var >> equals;

    if (equals != "=") {
        std::cout << "Error: Invalid command format" << std::endl;
        return;
    }

    // Read the rest of the line as the expression
    std::getline(ss, lhs);

    // Use stringstream to parse lhs into lhs, op, rhs
    std::stringstream expr_ss(lhs);
    expr_ss >> lhs >> op >> rhs;

    if (op != "+" && op != "-" && op != "*" && op != "/") {
        std::cout << "Error: Invalid operation" << std::endl;
        return;
    }

    try {
        int lhs_value = 0, rhs_value = 0;

        // Check if lhs is a number or a variable
        if (std::isdigit(lhs[0])) {
            lhs_value = std::stoi(lhs);
        } else {
            if (!calc.is_variable_defined(lhs)) {
                std::cout << "'" << lhs << "' not yet defined" << std::endl;
                return;
            }
            lhs_value = calc.get_variable(lhs);
        }

        // Check if rhs is a number or a variable
        if (std::isdigit(rhs[0])) {
            rhs_value = std::stoi(rhs);
        } else {
            if (!calc.is_variable_defined(rhs)) {
                std::cout << "'" << rhs << "' not yet defined" << std::endl;
                return;
            }
            rhs_value = calc.get_variable(rhs);
        }

        // Execute the arithmetic operation and assign the result
        int result = 0;
        if (op == "+") {
            result = lhs_value + rhs_value;
        } else if (op == "-") {
            result = lhs_value - rhs_value;
        } else if (op == "*") {
            result = lhs_value * rhs_value;
        } else if (op == "/") {
            if (rhs_value == 0) {
                std::cout << "Error: Division by zero" << std::endl;
                return;
            }
            result = lhs_value / rhs_value;
        }

        calc.assign_variable(var, result);
        calc.track_dependency(var, lhs); 
        calc.track_dependency(var, rhs); 
        calc.print_variables();
    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Out of range: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

int main() {
    Calculator calc;
    string line;

    cout << "Welcome to the calculator!" << endl;
    cout << "Available commands:" << endl;
    cout << "1. Variable assignment with arithmetic operations:" << endl;
    cout << "   Example: a = 2 + 3" << endl;
    cout << "   Supported operations: + (add), - (sub), * (mul), / (div)" << endl;
    cout << "2. Undo the last N operations:" << endl;
    cout << "   Example: undo 2" << endl;
    cout << "3. Exit the calculator:" << endl;
    cout << "   Example: exit" << endl;
    cout << endl;

    while (true) {
        cout << "> ";
        getline(cin, line);

        if (line == "exit") {
            break;
        } else if (line.substr(0, 4) == "undo") {
            int count;
            stringstream(line.substr(5)) >> count;
            calc.undo(count);
            cout << "undo " << count << endl;
        } else {
            process_command(calc, line);
        }
    }

    return 0;
}
