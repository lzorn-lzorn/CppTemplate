#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>
#include <memory>

/**
 * @brief A simple calculator class demonstrating C++23 features
 * 
 * This class provides basic mathematical operations and serves as
 * an example for the C++ project template.
 */
class Calculator {
private:
    std::vector<double> history_;
    static inline int operation_count_ = 0;

public:
    /**
     * @brief Default constructor
     */
    Calculator() = default;

    /**
     * @brief Copy constructor
     */
    Calculator(const Calculator& other) = default;

    /**
     * @brief Move constructor
     */
    Calculator(Calculator&& other) noexcept = default;

    /**
     * @brief Copy assignment operator
     */
    Calculator& operator=(const Calculator& other) = default;

    /**
     * @brief Move assignment operator
     */
    Calculator& operator=(Calculator&& other) noexcept = default;

    /**
     * @brief Destructor
     */
    ~Calculator() = default;

    // Basic arithmetic operations
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);

    // Advanced operations
    double power(double base, double exponent);
    double sqrt(double value);
    double factorial(int n);

    // Utility functions
    void clear_history();
    const std::vector<double>& get_history() const;
    size_t get_history_size() const;
    
    // Static function
    static int get_operation_count();

    // C++23 features demonstration
    template<typename... Args>
    auto calculate_average(Args... args) -> double {
        static_assert(sizeof...(args) > 0, "At least one argument required");
        return (args + ...) / sizeof...(args);
    }

    // Function to demonstrate modern C++ features
    std::unique_ptr<Calculator> create_copy() const;

    // Operator overloading
    Calculator operator+(const Calculator& other) const;
    
    // Friend function for output
    friend std::ostream& operator<<(std::ostream& os, const Calculator& calc);
};

#endif // CALCULATOR_H