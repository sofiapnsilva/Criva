// test_calculator.cpp
#include <iostream>
#include <cassert>
#include "../include/calculator/calculator.h"
#include "../include/calculator/arithmetic_command.h"

void test_calculator_basic_operations() {
    calculator::Calculator calc;
    calc.assign_variable("a", 5);
    assert(calc.get_variable("a") == 5);

    calc.add_command(std::make_unique<calculator::ArithmeticCommand>(calc, "a", "+", "2", "3"));
    assert(calc.get_variable("a") == 10);

    calc.undo(1);
    assert(calc.get_variable("a") == 5);
}

int main() {
    test_calculator_basic_operations();

    std::cout << "All tests passed!\n";
    return 0;
}
