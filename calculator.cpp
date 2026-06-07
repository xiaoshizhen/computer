#include "calculator.h"
#include <algorithm>
#include <numeric>
#include <sstream>
#include <cctype>
#include <unordered_map>
#include <functional>

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

double Calculator::modulo(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("取模运算中除数不能为零");
    }
    return std::fmod(a, b);
}

// ==================== 高级运算 ====================

double Calculator::power(double base, double exp) {
    // 处理特殊情形：负数的小数次幂
    if (base < 0 && std::floor(exp) != exp) {
        throw std::invalid_argument("负数不能进行非整数次幂运算");
    }
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
    if (n > 20) {
        throw std::invalid_argument("阶乘结果过大，最大支持 20!");
    }
    long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// ==================== 三角函数 ====================

double Calculator::sin(double value) {
    return std::sin(value);
}

double Calculator::cos(double value) {
    return std::cos(value);
}

double Calculator::tan(double value) {
    double c = std::cos(value);
    if (std::abs(c) < 1e-15) {
        throw std::invalid_argument("tan 未定义（cos 接近零）");
    }
    return std::tan(value);
}

// ==================== 对数函数 ====================

double Calculator::ln(double value) {
    if (value <= 0) {
        throw std::invalid_argument("对数函数的参数必须为正数");
    }
    return std::log(value);
}

double Calculator::log(double value) {
    if (value <= 0) {
        throw std::invalid_argument("对数函数的参数必须为正数");
    }
    return std::log10(value);
}

double Calculator::log2(double value) {
    if (value <= 0) {
        throw std::invalid_argument("对数函数的参数必须为正数");
    }
    return std::log2(value);
}

// ==================== 其他函数 ====================

double Calculator::abs(double value) {
    return std::abs(value);
}

double Calculator::exp(double value) {
    return std::exp(value);
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

// ==================== 表达式求值 ====================
// 递归下降解析器，支持:
//   - 基本运算: + - * / % ^
//   - 一元负号
//   - 括号
//   - 函数: sin cos tan sqrt ln log log2 abs exp
//   - 常量: pi e
//   - 隐式乘法: 2pi, 3(1+2), (2)(3)

namespace {

class ExprParser {
public:
    explicit ExprParser(const std::string& expr) : s_(expr), pos_(0) {}

    double parse() {
        double result = parseAddSub();
        skipSpaces();
        if (pos_ < s_.size()) {
            throw std::invalid_argument(
                "表达式末尾存在意外字符: '" + std::string(1, s_[pos_]) + "'"
            );
        }
        return result;
    }

private:
    std::string s_;
    size_t pos_;

    void skipSpaces() {
        while (pos_ < s_.size() && std::isspace(static_cast<unsigned char>(s_[pos_]))) {
            ++pos_;
        }
    }

    // ---- 运算符优先级（从低到高）----
    // level 1: + -
    // level 2: * / %
    // level 3: ^ (右结合)
    // level 4: 一元 - / 函数 / 常量 / 数字 / 括号

    // 加减法（最低优先级）
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

    // 乘除取模
    double parseMulDiv() {
        double left = parsePower();
        skipSpaces();
        while (pos_ < s_.size()) {
            char op = s_[pos_];
            if (op != '*' && op != '/' && op != '%') break;
            ++pos_;
            double right = parsePower();
            if (op == '*') {
                left = left * right;
            } else if (op == '/') {
                if (right == 0.0)
                    throw std::invalid_argument("除法表达式中的除数为零");
                left = left / right;
            } else { // '%'
                if (right == 0.0)
                    throw std::invalid_argument("取模运算中除数为零");
                left = std::fmod(left, right);
            }
            skipSpaces();
        }
        return left;
    }

    // 幂运算（右结合）
    double parsePower() {
        double left = parseUnary();
        skipSpaces();
        if (pos_ < s_.size() && s_[pos_] == '^') {
            ++pos_;
            double right = parsePower(); // 右结合：递归调用自身
            if (left < 0 && std::floor(right) != right) {
                throw std::invalid_argument("负数不能进行非整数次幂运算");
            }
            left = std::pow(left, right);
            skipSpaces();
        }
        return left;
    }

    // 一元运算符 / 隐式乘法
    double parseUnary() {
        skipSpaces();

        // 一元负号
        if (pos_ < s_.size() && s_[pos_] == '-') {
            ++pos_;
            return -parseAtom();
        }
        // 一元正号
        if (pos_ < s_.size() && s_[pos_] == '+') {
            ++pos_;
            return parseAtom();
        }

        return parseAtom();
    }

    // 原子：数字、括号、函数、常量
    double parseAtom() {
        skipSpaces();
        if (pos_ >= s_.size()) {
            throw std::invalid_argument("表达式不完整：需要操作数");
        }

        // ---- 括号 ----
        if (s_[pos_] == '(') {
            ++pos_;
            double value = parseAddSub();
            skipSpaces();
            if (pos_ >= s_.size() || s_[pos_] != ')') {
                throw std::invalid_argument("缺少右括号 ')'");
            }
            ++pos_;
            // 隐式乘法: (...)number 或 (...)(...) 或 (...)func
            skipSpaces();
            if (pos_ < s_.size()) {
                char nxt = s_[pos_];
                if (std::isdigit(static_cast<unsigned char>(nxt)) ||
                    nxt == '(' ||
                    std::isalpha(static_cast<unsigned char>(nxt))) {
                    // 隐式乘法
                    double right = parseAtom();
                    return value * right;
                }
            }
            return value;
        }

        // ---- 函数名或常量 ----
        if (std::isalpha(static_cast<unsigned char>(s_[pos_]))) {
            return parseFunctionOrConstant();
        }

        // ---- 数字 ----
        return parseNumber();
    }

    // 解析函数调用或常量
    double parseFunctionOrConstant() {
        size_t start = pos_;
        while (pos_ < s_.size() && std::isalpha(static_cast<unsigned char>(s_[pos_]))) {
            ++pos_;
        }
        std::string name = s_.substr(start, pos_ - start);

        // 将名称转为小写以便不区分大小写
        std::string lower;
        for (char c : name) lower += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

        // ---- 常量 ----
        if (lower == "pi") {
            double val = Calculator::PI;
            // 隐式乘法：pi 后直接跟数字/字母/括号
            skipSpaces();
            if (pos_ < s_.size()) {
                char nxt = s_[pos_];
                if (std::isdigit(static_cast<unsigned char>(nxt)) ||
                    nxt == '(' ||
                    std::isalpha(static_cast<unsigned char>(nxt))) {
                    return val * parseAtom();
                }
            }
            return val;
        }
        if (lower == "e") {
            double val = Calculator::E;
            skipSpaces();
            if (pos_ < s_.size()) {
                char nxt = s_[pos_];
                if (std::isdigit(static_cast<unsigned char>(nxt)) ||
                    nxt == '(' ||
                    std::isalpha(static_cast<unsigned char>(nxt))) {
                    return val * parseAtom();
                }
            }
            return val;
        }

        // ---- 函数 ----
        skipSpaces();
        if (pos_ >= s_.size() || s_[pos_] != '(') {
            throw std::invalid_argument("函数 '" + name + "' 后需要 '('，例如 " + name + "(...)");
        }
        ++pos_; // 跳过 '('
        double arg = parseAddSub();
        skipSpaces();
        if (pos_ >= s_.size() || s_[pos_] != ')') {
            throw std::invalid_argument("函数 '" + name + "' 缺少右括号 ')'");
        }
        ++pos_; // 跳过 ')'

        // 隐式乘法：func(...) 后接数字/字母/括号
        skipSpaces();
        double implicitMul = 1.0;
        if (pos_ < s_.size()) {
            char nxt = s_[pos_];
            if (std::isdigit(static_cast<unsigned char>(nxt)) ||
                nxt == '(' ||
                std::isalpha(static_cast<unsigned char>(nxt))) {
                implicitMul = parseAtom();
            }
        }

        double result;
        if (lower == "sin") {
            result = std::sin(arg);
        } else if (lower == "cos") {
            result = std::cos(arg);
        } else if (lower == "tan") {
            double c = std::cos(arg);
            if (std::abs(c) < 1e-15)
                throw std::invalid_argument("tan 未定义（cos 接近零）");
            result = std::tan(arg);
        } else if (lower == "sqrt") {
            if (arg < 0)
                throw std::invalid_argument("sqrt 的参数不能为负数");
            result = std::sqrt(arg);
        } else if (lower == "ln") {
            if (arg <= 0)
                throw std::invalid_argument("ln 的参数必须为正数");
            result = std::log(arg);
        } else if (lower == "log") {
            if (arg <= 0)
                throw std::invalid_argument("log 的参数必须为正数");
            result = std::log10(arg);
        } else if (lower == "log2") {
            if (arg <= 0)
                throw std::invalid_argument("log2 的参数必须为正数");
            result = std::log2(arg);
        } else if (lower == "abs") {
            result = std::abs(arg);
        } else if (lower == "exp") {
            result = std::exp(arg);
        } else {
            throw std::invalid_argument("未知函数: '" + name + "'");
        }

        return result * implicitMul;
    }

    // 解析数字（支持小数和科学记数法）
    double parseNumber() {
        skipSpaces();
        size_t start = pos_;

        // 可选负号（作为数字的一部分）
        if (pos_ < s_.size() && s_[pos_] == '-') ++pos_;

        bool hasDigits = false;

        // 整数部分
        while (pos_ < s_.size() && std::isdigit(static_cast<unsigned char>(s_[pos_]))) {
            ++pos_;
            hasDigits = true;
        }

        // 小数部分
        if (pos_ < s_.size() && s_[pos_] == '.') {
            ++pos_;
            while (pos_ < s_.size() && std::isdigit(static_cast<unsigned char>(s_[pos_]))) {
                ++pos_;
                hasDigits = true;
            }
        }

        // 科学记数法: e/E [+-]? digits
        if (pos_ < s_.size() && (s_[pos_] == 'e' || s_[pos_] == 'E')) {
            ++pos_;
            if (pos_ < s_.size() && (s_[pos_] == '+' || s_[pos_] == '-')) {
                ++pos_;
            }
            while (pos_ < s_.size() && std::isdigit(static_cast<unsigned char>(s_[pos_]))) {
                ++pos_;
            }
        }

        if (!hasDigits) {
            throw std::invalid_argument("需要数字，但得到 '" + std::string(1, s_[start]) + "'");
        }

        double value = std::stod(s_.substr(start, pos_ - start));

        // 隐式乘法：数字后直接跟字母或括号，如 2pi, 3(1+2)
        skipSpaces();
        if (pos_ < s_.size()) {
            char nxt = s_[pos_];
            if (std::isalpha(static_cast<unsigned char>(nxt)) || nxt == '(') {
                double right = parseAtom();
                return value * right;
            }
        }

        return value;
    }
};

} // anonymous namespace

double Calculator::evaluate(const std::string& expr) {
    ExprParser parser(expr);
    return parser.parse();
}
