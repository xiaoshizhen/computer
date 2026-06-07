#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

class Calculator {
public:
    // 基本运算
    static double add(double a, double b);
    static double subtract(double a, double b);
    static double multiply(double a, double b);
    static double divide(double a, double b);

    // 高级运算
    static double power(double base, double exp);
    static double sqrt(double value);
    static long long factorial(int n);

    // 统计运算
    static double mean(const std::vector<double>& numbers);
    static double median(const std::vector<double>& numbers);
    static double stddev(const std::vector<double>& numbers);

    // 表达式计算
    static double evaluate(const std::string& expr);
};

#endif // CALCULATOR_H
