#pragma once
#include "calculator/calculator.h"
#include <string>

namespace calculator {

class ArithmeticCommand : public Command {
public:
    ArithmeticCommand(Calculator& calc, const std::string& var, const std::string& op,
                      const std::string& lhs, const std::string& rhs);

    void execute() override;
    void undo() override;

private:
    Calculator& calculator;
    std::string variable;
    std::string operation;
    std::string lhs_var;
    std::string rhs_var;
    int prev_value;
};

}
