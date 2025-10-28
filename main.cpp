#include <iostream>
#include <iomanip>
#include <exception>
#include "Calculator.h"

void print_separator(const std::string& title) {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << " " << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void test_basic_operations() {
    print_separator("Testing Basic Operations");
    
    Calculator calc;
    
    try {
        std::cout << "Addition: 10 + 5 = " << calc.add(10, 5) << std::endl;
        std::cout << "Subtraction: 10 - 3 = " << calc.subtract(10, 3) << std::endl;
        std::cout << "Multiplication: 4 * 6 = " << calc.multiply(4, 6) << std::endl;
        std::cout << "Division: 20 / 4 = " << calc.divide(20, 4) << std::endl;
        
        std::cout << "\nCalculator status: " << calc << std::endl;
        std::cout << "Total operations performed globally: " 
                  << Calculator::get_operation_count() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void test_advanced_operations() {
    print_separator("Testing Advanced Operations");
    
    Calculator calc;
    
    try {
        std::cout << "Power: 2^8 = " << calc.power(2, 8) << std::endl;
        std::cout << "Square root: sqrt(64) = " << calc.sqrt(64) << std::endl;
        std::cout << "Factorial: 5! = " << calc.factorial(5) << std::endl;
        
        std::cout << "\nCalculator status: " << calc << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void test_cpp23_features() {
    print_separator("Testing C++23 Features");
    
    Calculator calc;
    
    // Template variadic function
    double avg1 = calc.calculate_average(10, 20, 30, 40);
    std::cout << "Average of (10, 20, 30, 40): " << avg1 << std::endl;
    
    double avg2 = calc.calculate_average(1.5, 2.5, 3.5);
    std::cout << "Average of (1.5, 2.5, 3.5): " << avg2 << std::endl;
    
    // Smart pointer demonstration
    auto calc_copy = calc.create_copy();
    std::cout << "Created copy using smart pointer: " << *calc_copy << std::endl;
}

void test_error_handling() {
    print_separator("Testing Error Handling");
    
    Calculator calc;
    
    // Test division by zero
    try {
        calc.divide(10, 0);
    } catch (const std::exception& e) {
        std::cout << "Caught expected error - Division by zero: " << e.what() << std::endl;
    }
    
    // Test negative square root
    try {
        calc.sqrt(-25);
    } catch (const std::exception& e) {
        std::cout << "Caught expected error - Negative sqrt: " << e.what() << std::endl;
    }
    
    // Test negative factorial
    try {
        calc.factorial(-5);
    } catch (const std::exception& e) {
        std::cout << "Caught expected error - Negative factorial: " << e.what() << std::endl;
    }
}

void test_history_and_operators() {
    print_separator("Testing History and Operators");
    
    Calculator calc1, calc2;
    
    // Add some operations to each calculator
    calc1.add(10, 5);
    calc1.multiply(3, 7);
    
    calc2.subtract(20, 8);
    calc2.divide(100, 4);
    
    std::cout << "Calculator 1: " << calc1 << std::endl;
    std::cout << "Calculator 2: " << calc2 << std::endl;
    
    // Combine calculators using + operator
    Calculator combined = calc1 + calc2;
    std::cout << "Combined calculator: " << combined << std::endl;
    
    // Show history details
    const auto& history = combined.get_history();
    std::cout << "\nDetailed history (" << history.size() << " operations):" << std::endl;
    for (size_t i = 0; i < history.size(); ++i) {
        std::cout << "  Operation " << (i + 1) << ": " << std::fixed 
                  << std::setprecision(2) << history[i] << std::endl;
    }
}

int main() {
    std::cout << "C++23 Calculator Test Program" << std::endl;
    std::cout << "=============================" << std::endl;
    
    try {
        test_basic_operations();
        test_advanced_operations();
        test_cpp23_features();
        test_error_handling();
        test_history_and_operators();
        
        print_separator("Test Summary");
        std::cout << "All tests completed successfully!" << std::endl;
        std::cout << "Total operations performed: " 
                  << Calculator::get_operation_count() << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "\nUnexpected error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}