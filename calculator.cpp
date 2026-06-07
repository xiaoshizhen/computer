#include "calculator.h"
#include <algorithm>
#include <numeric>
#include <sstream>
#include <cctype>

// ==================== 基本运算 ====================

double Calculator::add(double a, double b) {
    return a + b;
}

double Calculator::subtract(double a, double b) {
    return a - b;
}

double Calculator::multiply(double a, double b) {
    return a * b;
}

double Calculator::divide(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("除数不能为零");
    }
    return a / b;
}

// ==================== 高级运算 ====================

double Calculator::power(double base, double exp) {
    return std::pow(base, exp);
}

double Calculator::sqrt(double value) {
    if (value < 0) {
        throw std::invalid_argument("不能对负数开平方根");
    }
    return std::sqrt(value);
}

long long Calculator::factorial(int n) {
    if (n < 0) {
        throw std::invalid_argument("阶乘只支持非负整数");
    }
    long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// ==================== 统计运算 ====================

double Calculator::mean(const std::vector<double>& numbers) {
    if (numbers.empty()) {
        throw std::invalid_argument("数组不能为空");
    }
    double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
    return sum / numbers.size();
}

double Calculator::median(const std::vector<double>& numbers) {
    if (numbers.empty()) {
        throw std::invalid_argument("数组不能为空");
    }
    std::vector<double> sorted = numbers;
    std::sort(sorted.begin(), sorted.end());
    size_t n = sorted.size();
    if (n % 2 == 0) {
        return (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
    }
    return sorted[n / 2];
}

double Calculator::stddev(const std::vector<double>& numbers) {
    if (numbers.size() < 2) {
        throw std::invalid_argument("计算标准差至少需要两个数");
    }
    double m = mean(numbers);
    double sum_sq = 0.0;
    for (double x : numbers) {
        sum_sq += (x - m) * (x - m);
    }
    return std::sqrt(sum_sq / (numbers.size() - 1)); // 样本标准差
}

// ==================== 简单表达式求值 ====================

// 简单的四则运算表达式求值（支持 + - * / 和括号）
// 使用递归下降解析器

namespace {

class ExprParser {
public:
    explicit ExprParser(const std::string& expr) : s_(expr), pos_(0) {}

    double parse() {
        double result = parseAddSub();
        skipSpaces();
        if (pos_ < s_.size()) {
            throw std::invalid_argument("表达式末尾存在意外字符: '" + std::string(1, s_[pos_]) + "'");
        }
        return result;
    }

private:
    std::string s_;
    size_t pos_;

    void skipSpaces() {
        while (pos_ < s_.size() && std::isspace(s_[pos_])) {
            ++pos_;
        }
    }

    // 加减法
    double parseAddSub() {
        double left = parseMulDiv();
        skipSpaces();
        while (pos_ < s_.size()) {
            char op = s_[pos_];
            if (op != '+' && op != '-') break;
            ++pos_;
            double right = parseMulDiv();
            if (op == '+')
                left = left + right;
            else
                left = left - right;
            skipSpaces();
        }
        return left;
    }

    // 乘除法
    double parseMulDiv() {
        double left = parseUnary();
        skipSpaces();
        while (pos_ < s_.size()) {
            char op = s_[pos_];
            if (op != '*' && op != '/') break;
            ++pos_;
            double right = parseUnary();
            if (op == '*')
                left = left * right;
            else {
                if (right == 0.0)
                    throw std::invalid_argument("除法表达式中的除数为零");
                left = left / right;
            }
            skipSpaces();
        }
        return left;
    }

    // 一元运算符（负号）
    double parseUnary() {
        skipSpaces();
        if (pos_ < s_.size() && s_[pos_] == '-') {
            ++pos_;
            return -parseAtom();
        }
        return parseAtom();
    }

    // 原子：数字或括号表达式
    double parseAtom() {
        skipSpaces();
        if (pos_ >= s_.size()) {
            throw std::invalid_argument("表达式不完整");
        }

        if (s_[pos_] == '(') {
            ++pos_; // 跳过 '('
            double value = parseAddSub();
            skipSpaces();
            if (pos_ >= s_.size() || s_[pos_] != ')') {
                throw std::invalid_argument("缺少右括号 ')'");
            }
            ++pos_; // 跳过 ')'
            return value;
        }

        // 解析数字
        size_t start = pos_;
        if (s_[pos_] == '-') ++pos_;
        while (pos_ < s_.size() && (std::isdigit(s_[pos_]) || s_[pos_] == '.')) {
            ++pos_;
        }
        if (start == pos_ || (start + 1 == pos_ && s_[start] == '-')) {
            throw std::invalid_argument("需要数字");
        }
        return std::stod(s_.substr(start, pos_ - start));
    }
};

} // anonymous namespace

double Calculator::evaluate(const std::string& expr) {
    ExprParser parser(expr);
    return parser.parse();
}
