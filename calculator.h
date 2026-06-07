#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

class Calculator {
public:
    // 常量
    static constexpr double PI = 3.14159265358979323846;
    static constexpr double E  = 2.71828182845904523536;

    // 基本运算
    static double add(double a, double b);
    static double subtract(double a, double b);
    static double multiply(double a, double b);
    static double divide(double a, double b);
    static double modulo(double a, double b);

    // 高级运算
    static double power(double base, double exp);
    static double sqrt(double value);
    static long long factorial(int n);

    // 三角函数（输入为弧度）
    static double sin(double value);
    static double cos(double value);
    static double tan(double value);

    // 对数函数
    static double ln(double value);   // 自然对数
    static double log(double value);  // 常用对数（以10为底）
    static double log2(double value); // 以2为底的对数

    // 其他函数
    static double abs(double value);
    static double exp(double value);

    // 统计运算
    static double mean(const std::vector<double>& numbers);
    static double median(const std::vector<double>& numbers);
    static double stddev(const std::vector<double>& numbers);

    // 表达式计算（支持 + - * / ^ % 括号，函数，常量）
    static double evaluate(const std::string& expr);
};

#endif // CALCULATOR_H
