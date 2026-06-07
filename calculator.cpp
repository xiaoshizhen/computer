#include "calculator.h"
#include <algorithm>
#include <numeric>
#include <sstream>
#include <cctype>
#include <unordered_map>
#include <functional>

// ==================== 静态变量定义 ====================
Calculator::AngleMode Calculator::angleMode = Calculator::AngleMode::RAD;
double Calculator::ans = 0.0;

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

double Calculator::cbrt(double value) {
    // cbrt 对负数也有效
    return std::cbrt(value);
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
    if (angleMode == AngleMode::DEG) {
        value = value * PI / 180.0;
    }
    return std::sin(value);
}

double Calculator::cos(double value) {
    if (angleMode == AngleMode::DEG) {
        value = value * PI / 180.0;
    }
    return std::cos(value);
}

double Calculator::tan(double value) {
    if (angleMode == AngleMode::DEG) {
        value = value * PI / 180.0;
    }
    double c = std::cos(value);
    if (std::abs(c) < 1e-15) {
        throw std::invalid_argument("tan 未定义（cos 接近零）");
    }
    return std::tan(value);
}

// ==================== 反三角函数 ====================

double Calculator::asin(double value) {
    if (value < -1.0 || value > 1.0) {
        throw std::invalid_argument("asin 的参数必须在 [-1, 1] 范围内");
    }
    double result = std::asin(value);
    if (angleMode == AngleMode::DEG) {
        result = result * 180.0 / PI;
    }
    return result;
}

double Calculator::acos(double value) {
    if (value < -1.0 || value > 1.0) {
        throw std::invalid_argument("acos 的参数必须在 [-1, 1] 范围内");
    }
    double result = std::acos(value);
    if (angleMode == AngleMode::DEG) {
        result = result * 180.0 / PI;
    }
    return result;
}

double Calculator::atan(double value) {
    double result = std::atan(value);
    if (angleMode == AngleMode::DEG) {
        result = result * 180.0 / PI;
    }
    return result;
}

double Calculator::atan2(double y, double x) {
    double result = std::atan2(y, x);
    if (angleMode == AngleMode::DEG) {
        result = result * 180.0 / PI;
    }
    return result;
}

// ==================== 双曲函数 ====================

double Calculator::sinh(double value) {
    return std::sinh(value);
}

double Calculator::cosh(double value) {
    return std::cosh(value);
}

double Calculator::tanh(double value) {
    return std::tanh(value);
}

// ==================== 反双曲函数 ====================

double Calculator::asinh(double value) {
    return std::asinh(value);
}

double Calculator::acosh(double value) {
    if (value < 1.0) {
        throw std::invalid_argument("acosh 的参数必须 >= 1");
    }
    return std::acosh(value);
}

double Calculator::atanh(double value) {
    if (value <= -1.0 || value >= 1.0) {
        throw std::invalid_argument("atanh 的参数必须在 (-1, 1) 范围内");
    }
    return std::atanh(value);
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

double Calculator::logb(double value, double base) {
    if (value <= 0) {
        throw std::invalid_argument("对数函数的真数必须为正数");
    }
    if (base <= 0 || base == 1.0) {
        throw std::invalid_argument("对数的底数必须为正数且不等于 1");
    }
    return std::log(value) / std::log(base);
}

// ==================== 取整函数 ====================

double Calculator::floor(double value) {
    return std::floor(value);
}

double Calculator::ceil(double value) {
    return std::ceil(value);
}

double Calculator::round(double value) {
    return std::round(value);
}

double Calculator::trunc(double value) {
    return std::trunc(value);
}

// ==================== 其他函数 ====================

double Calculator::abs(double value) {
    return std::abs(value);
}

double Calculator::exp(double value) {
    return std::exp(value);
}

double Calculator::sign(double value) {
    if (value > 0.0) return 1.0;
    if (value < 0.0) return -1.0;
    return 0.0;
}

double Calculator::gamma(double value) {
    // tgamma 在非正整数处极点
    if (value <= 0.0 && std::floor(value) == value) {
        throw std::invalid_argument("Gamma 函数在非正整数处无定义");
    }
    return std::tgamma(value);
}

double Calculator::hypot(double x, double y) {
    return std::hypot(x, y);
}

double Calculator::isPrime(long long n) {
    if (n < 2) return 0.0;
    if (n == 2) return 1.0;
    if (n % 2 == 0) return 0.0;
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0.0;
    }
    return 1.0;
}

// ==================== 组合数学 ====================

long long Calculator::perm(int n, int r) {
    if (n < 0 || r < 0) {
        throw std::invalid_argument("排列参数必须为非负整数");
    }
    if (r > n) {
        throw std::invalid_argument("排列中 r 不能大于 n");
    }
    if (n > 20) {
        throw std::invalid_argument("排列结果过大，最大支持 n=20");
    }
    long long result = 1;
    for (int i = 0; i < r; ++i) {
        result *= (n - i);
    }
    return result;
}

long long Calculator::comb(int n, int r) {
    if (n < 0 || r < 0) {
        throw std::invalid_argument("组合参数必须为非负整数");
    }
    if (r > n) {
        throw std::invalid_argument("组合中 r 不能大于 n");
    }
    if (n > 20) {
        throw std::invalid_argument("组合结果过大，最大支持 n=20");
    }
    // 利用对称性减少计算量
    if (r > n - r) {
        r = n - r;
    }
    long long result = 1;
    for (int i = 0; i < r; ++i) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

// ==================== 数论 ====================

long long Calculator::gcd(long long a, long long b) {
    return std::gcd(a, b);
}

long long Calculator::lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return std::lcm(a, b);
}

// ==================== 角度转换 ====================

double Calculator::degToRad(double deg) {
    return deg * PI / 180.0;
}

double Calculator::radToDeg(double rad) {
    return rad * 180.0 / PI;
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
//   - 一元负号/正号
//   - 括号
//   - 单参数函数: sin cos tan asin acos atan
//                 sinh cosh tanh asinh acosh atanh
//                 sqrt cbrt ln log log2 abs exp
//                 floor ceil round trunc sign gamma
//   - 双参数函数: hypot atan2 perm comb gcd lcm logb
//   - 常量: pi e phi sqrt2 ln2 ln10 ans
//   - 隐式乘法: 2pi, 3(1+2), (2)(3), pi(2)
//   - 科学记数法: 1.5e10, 2E-3

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

    double parsePower() {
        double left = parseUnary();
        skipSpaces();
        if (pos_ < s_.size() && s_[pos_] == '^') {
            ++pos_;
            double right = parsePower(); // 右结合
            if (left < 0 && std::floor(right) != right) {
                throw std::invalid_argument("负数不能进行非整数次幂运算");
            }
            left = std::pow(left, right);
            skipSpaces();
        }
        return left;
    }

    double parseUnary() {
        skipSpaces();

        if (pos_ < s_.size() && s_[pos_] == '-') {
            ++pos_;
            return -parseAtom();
        }
        if (pos_ < s_.size() && s_[pos_] == '+') {
            ++pos_;
            return parseAtom();
        }

        return parseAtom();
    }

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

    // 将字符串转为小写
    static std::string toLower(const std::string& s) {
        std::string result;
        for (char c : s)
            result += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        return result;
    }

    // 检查是否为双参数函数
    static bool isTwoArgFunc(const std::string& lower) {
        return lower == "hypot"  || lower == "atan2" ||
               lower == "perm"   || lower == "comb"  ||
               lower == "gcd"    || lower == "lcm"   ||
               lower == "logb";
    }

    // 解析函数调用或常量
    double parseFunctionOrConstant() {
        size_t start = pos_;
        while (pos_ < s_.size() && std::isalpha(static_cast<unsigned char>(s_[pos_]))) {
            ++pos_;
        }
        std::string name = s_.substr(start, pos_ - start);
        std::string lower = toLower(name);

        // ---- ans 变量 ----
        if (lower == "ans") {
            double val = Calculator::ans;
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

        // ---- 常量 ----
        double constVal = 0;
        bool isConst = false;
        if (lower == "pi")    { constVal = Calculator::PI;    isConst = true; }
        if (lower == "e")     { constVal = Calculator::E;     isConst = true; }
        if (lower == "phi")   { constVal = Calculator::PHI;   isConst = true; }
        if (lower == "sqrt2") { constVal = Calculator::SQRT2; isConst = true; }
        if (lower == "ln2")   { constVal = Calculator::LN2;   isConst = true; }
        if (lower == "ln10")  { constVal = Calculator::LN10;  isConst = true; }

        if (isConst) {
            skipSpaces();
            if (pos_ < s_.size()) {
                char nxt = s_[pos_];
                if (std::isdigit(static_cast<unsigned char>(nxt)) ||
                    nxt == '(' ||
                    std::isalpha(static_cast<unsigned char>(nxt))) {
                    return constVal * parseAtom();
                }
            }
            return constVal;
        }

        // ---- 函数 ----
        skipSpaces();
        if (pos_ >= s_.size() || s_[pos_] != '(') {
            throw std::invalid_argument("函数 '" + name + "' 后需要 '('，例如 " + name + "(...)");
        }
        ++pos_; // 跳过 '('

        // 解析第一个参数
        double arg1 = parseAddSub();
        skipSpaces();

        double arg2 = 0.0;
        bool hasSecondArg = false;

        // 检查是否有逗号（双参数函数）
        if (pos_ < s_.size() && s_[pos_] == ',') {
            ++pos_;
            arg2 = parseAddSub();
            skipSpaces();
            hasSecondArg = true;
        }

        // 期望右括号
        if (pos_ >= s_.size() || s_[pos_] != ')') {
            throw std::invalid_argument("函数 '" + name + "' 缺少右括号 ')'");
        }
        ++pos_; // 跳过 ')'

        // 验证参数个数
        bool needsTwo = isTwoArgFunc(lower);
        if (needsTwo && !hasSecondArg) {
            throw std::invalid_argument("函数 '" + name + "' 需要两个参数，如 " + name + "(x, y)");
        }
        if (!needsTwo && hasSecondArg) {
            throw std::invalid_argument("函数 '" + name + "' 只接受一个参数");
        }

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

        double result = dispatchFunction(lower, arg1, arg2);
        return result * implicitMul;
    }

    // 根据函数名分派调用
    double dispatchFunction(const std::string& lower, double arg1, double arg2) {
        // ---- 三角函数 ----
        if (lower == "sin") {
            if (Calculator::angleMode == Calculator::AngleMode::DEG)
                arg1 = arg1 * Calculator::PI / 180.0;
            return std::sin(arg1);
        }
        if (lower == "cos") {
            if (Calculator::angleMode == Calculator::AngleMode::DEG)
                arg1 = arg1 * Calculator::PI / 180.0;
            return std::cos(arg1);
        }
        if (lower == "tan") {
            if (Calculator::angleMode == Calculator::AngleMode::DEG)
                arg1 = arg1 * Calculator::PI / 180.0;
            double c = std::cos(arg1);
            if (std::abs(c) < 1e-15)
                throw std::invalid_argument("tan 未定义（cos 接近零）");
            return std::tan(arg1);
        }

        // ---- 反三角函数 ----
        if (lower == "asin") {
            if (arg1 < -1.0 || arg1 > 1.0)
                throw std::invalid_argument("asin 的参数必须在 [-1, 1] 范围内");
            double r = std::asin(arg1);
            if (Calculator::angleMode == Calculator::AngleMode::DEG)
                r = r * 180.0 / Calculator::PI;
            return r;
        }
        if (lower == "acos") {
            if (arg1 < -1.0 || arg1 > 1.0)
                throw std::invalid_argument("acos 的参数必须在 [-1, 1] 范围内");
            double r = std::acos(arg1);
            if (Calculator::angleMode == Calculator::AngleMode::DEG)
                r = r * 180.0 / Calculator::PI;
            return r;
        }
        if (lower == "atan") {
            double r = std::atan(arg1);
            if (Calculator::angleMode == Calculator::AngleMode::DEG)
                r = r * 180.0 / Calculator::PI;
            return r;
        }

        // ---- 双曲函数 ----
        if (lower == "sinh")  return std::sinh(arg1);
        if (lower == "cosh")  return std::cosh(arg1);
        if (lower == "tanh")  return std::tanh(arg1);

        // ---- 反双曲函数 ----
        if (lower == "asinh") return std::asinh(arg1);
        if (lower == "acosh") {
            if (arg1 < 1.0)
                throw std::invalid_argument("acosh 的参数必须 >= 1");
            return std::acosh(arg1);
        }
        if (lower == "atanh") {
            if (arg1 <= -1.0 || arg1 >= 1.0)
                throw std::invalid_argument("atanh 的参数必须在 (-1, 1) 范围内");
            return std::atanh(arg1);
        }

        // ---- 根号 ----
        if (lower == "sqrt") {
            if (arg1 < 0)
                throw std::invalid_argument("sqrt 的参数不能为负数");
            return std::sqrt(arg1);
        }
        if (lower == "cbrt") return std::cbrt(arg1);

        // ---- 对数 ----
        if (lower == "ln") {
            if (arg1 <= 0)
                throw std::invalid_argument("ln 的参数必须为正数");
            return std::log(arg1);
        }
        if (lower == "log") {
            if (arg1 <= 0)
                throw std::invalid_argument("log 的参数必须为正数");
            return std::log10(arg1);
        }
        if (lower == "log2") {
            if (arg1 <= 0)
                throw std::invalid_argument("log2 的参数必须为正数");
            return std::log2(arg1);
        }

        // ---- 取整 ----
        if (lower == "floor") return std::floor(arg1);
        if (lower == "ceil")  return std::ceil(arg1);
        if (lower == "round") return std::round(arg1);
        if (lower == "trunc") return std::trunc(arg1);

        // ---- 其他 ----
        if (lower == "abs")   return std::abs(arg1);
        if (lower == "exp")   return std::exp(arg1);
        if (lower == "sign") {
            if (arg1 > 0.0) return 1.0;
            if (arg1 < 0.0) return -1.0;
            return 0.0;
        }
        if (lower == "gamma") {
            if (arg1 <= 0.0 && std::floor(arg1) == arg1)
                throw std::invalid_argument("Gamma 函数在非正整数处无定义");
            return std::tgamma(arg1);
        }
        if (lower == "isprime") {
            long long n = static_cast<long long>(arg1);
            if (n < 2) return 0.0;
            if (n == 2) return 1.0;
            if (n % 2 == 0) return 0.0;
            for (long long i = 3; i * i <= n; i += 2) {
                if (n % i == 0) return 0.0;
            }
            return 1.0;
        }

        // ---- 双参数函数 ----
        if (lower == "hypot") return std::hypot(arg1, arg2);
        if (lower == "atan2") {
            double r = std::atan2(arg1, arg2);
            if (Calculator::angleMode == Calculator::AngleMode::DEG)
                r = r * 180.0 / Calculator::PI;
            return r;
        }
        if (lower == "logb") {
            if (arg1 <= 0)
                throw std::invalid_argument("logb 的真数必须为正数");
            if (arg2 <= 0 || arg2 == 1.0)
                throw std::invalid_argument("logb 的底数必须为正数且不等于 1");
            return std::log(arg1) / std::log(arg2);
        }
        if (lower == "perm") {
            int n = static_cast<int>(arg1);
            int r = static_cast<int>(arg2);
            return static_cast<double>(Calculator::perm(n, r));
        }
        if (lower == "comb") {
            int n = static_cast<int>(arg1);
            int r = static_cast<int>(arg2);
            return static_cast<double>(Calculator::comb(n, r));
        }
        if (lower == "gcd") {
            return static_cast<double>(Calculator::gcd(
                static_cast<long long>(arg1), static_cast<long long>(arg2)));
        }
        if (lower == "lcm") {
            return static_cast<double>(Calculator::lcm(
                static_cast<long long>(arg1), static_cast<long long>(arg2)));
        }

        throw std::invalid_argument("未知函数: '" + lower + "'");
    }

    // 解析数字（支持小数和科学记数法）
    double parseNumber() {
        skipSpaces();
        size_t start = pos_;

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
    double result = parser.parse();
    ans = result; // 自动更新 ans
    return result;
}
