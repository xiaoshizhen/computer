#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

class Calculator {
public:
    // ==================== 常量 ====================
    static constexpr double PI    = 3.14159265358979323846;
    static constexpr double E     = 2.71828182845904523536;
    static constexpr double PHI   = 1.61803398874989484820;   // 黄金比例
    static constexpr double SQRT2 = 1.41421356237309504880;   // √2
    static constexpr double LN2   = 0.69314718055994530942;   // ln(2)
    static constexpr double LN10  = 2.30258509299404568402;   // ln(10)

    // ==================== 角度模式 ====================
    enum class AngleMode { RAD, DEG };
    static AngleMode angleMode;

    // ==================== 上次计算结果 ====================
    static double ans;

    // ==================== 基本运算 ====================
    static double add(double a, double b);
    static double subtract(double a, double b);
    static double multiply(double a, double b);
    static double divide(double a, double b);
    static double modulo(double a, double b);

    // ==================== 高级运算 ====================
    static double power(double base, double exp);
    static double sqrt(double value);
    static double cbrt(double value);          // 立方根
    static long long factorial(int n);

    // ==================== 三角函数（受角度模式影响） ====================
    static double sin(double value);
    static double cos(double value);
    static double tan(double value);

    // ==================== 反三角函数（受角度模式影响） ====================
    static double asin(double value);
    static double acos(double value);
    static double atan(double value);
    static double atan2(double y, double x);   // 双参数

    // ==================== 双曲函数 ====================
    static double sinh(double value);
    static double cosh(double value);
    static double tanh(double value);

    // ==================== 反双曲函数 ====================
    static double asinh(double value);
    static double acosh(double value);
    static double atanh(double value);

    // ==================== 对数函数 ====================
    static double ln(double value);            // 自然对数
    static double log(double value);           // 常用对数（底 10）
    static double log2(double value);          // 底 2 对数
    static double logb(double value, double base); // 任意底对数

    // ==================== 取整函数 ====================
    static double floor(double value);
    static double ceil(double value);
    static double round(double value);
    static double trunc(double value);

    // ==================== 其他函数 ====================
    static double abs(double value);
    static double exp(double value);
    static double sign(double value);          // 符号函数
    static double gamma(double value);         // Gamma 函数
    static double hypot(double x, double y);   // 斜边长度
    static double isPrime(long long n);         // 质数判断 (1.0=质数, 0.0=非质数)

    // ==================== 组合数学 ====================
    static long long perm(int n, int r);       // 排列 P(n,r)
    static long long comb(int n, int r);       // 组合 C(n,r)

    // ==================== 数论 ====================
    static long long gcd(long long a, long long b);
    static long long lcm(long long a, long long b);

    // ==================== 角度转换 ====================
    static double degToRad(double deg);
    static double radToDeg(double rad);

    // ==================== 统计运算 ====================
    static double mean(const std::vector<double>& numbers);
    static double median(const std::vector<double>& numbers);
    static double stddev(const std::vector<double>& numbers);

    // ==================== 表达式计算 ====================
    // 支持 + - * / % ^ () 函数 常量 ans 隐式乘法 科学记数法
    static double evaluate(const std::string& expr);
};

#endif // CALCULATOR_H
