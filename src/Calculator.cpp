#include "Calculator.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <algorithm>

// Basic arithmetic operations
double Calculator::add(double a, double b) {
    double result = a + b;
    history_.push_back(result);
    ++operation_count_;
    return result;
}

double Calculator::subtract(double a, double b) {
    double result = a - b;
    history_.push_back(result);
    ++operation_count_;
    return result;
}

double Calculator::multiply(double a, double b) {
    double result = a * b;
    history_.push_back(result);
    ++operation_count_;
    return result;
}

double Calculator::divide(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("Division by zero is not allowed");
    }
    double result = a / b;
    history_.push_back(result);
    ++operation_count_;
    return result;
}

// Advanced operations
double Calculator::power(double base, double exponent) {
    double result = std::pow(base, exponent);
    history_.push_back(result);
    ++operation_count_;
    return result;
}

double Calculator::sqrt(double value) {
    if (value < 0) {
        throw std::invalid_argument("Square root of negative number is not allowed");
    }
    double result = std::sqrt(value);
    history_.push_back(result);
    ++operation_count_;
    return result;
}

double Calculator::factorial(int n) {
    if (n < 0) {
        throw std::invalid_argument("Factorial of negative number is not allowed");
    }
    
    double result = 1.0;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    
    history_.push_back(result);
    ++operation_count_;
    return result;
}

// Utility functions
void Calculator::clear_history() {
    history_.clear();
}

const std::vector<double>& Calculator::get_history() const {
    return history_;
}

size_t Calculator::get_history_size() const {
    return history_.size();
}

int Calculator::get_operation_count() {
    return operation_count_;
}

std::unique_ptr<Calculator> Calculator::create_copy() const {
    auto copy = std::make_unique<Calculator>();
    copy->history_ = this->history_;
    return copy;
}

// Operator overloading
Calculator Calculator::operator+(const Calculator& other) const {
    Calculator result;
    
    // Combine histories
    result.history_ = this->history_;
    result.history_.insert(result.history_.end(), 
                          other.history_.begin(), 
                          other.history_.end());
    
    return result;
}

// Friend function for output
std::ostream& operator<<(std::ostream& os, const Calculator& calc) {
    os << "Calculator with " << calc.history_.size() << " operations in history";
    if (!calc.history_.empty()) {
        os << " (last result: " << calc.history_.back() << ")";
    }
    return os;
}