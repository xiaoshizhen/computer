#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cctype>
#include "calculator.h"

// ==================== 工具函数 ====================

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string toLower(const std::string& s) {
    std::string result;
    for (char c : s)
        result += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return result;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ==================== 全局状态 ====================

std::vector<std::string> history; // 计算历史
const size_t MAX_HISTORY = 50;

// ==================== 输出函数 ====================

void printWelcome() {
    std::cout << R"(
╔══════════════════════════════════════════════╗
║         C++ 多功能科学计算器  v3.0            ║
╠══════════════════════════════════════════════╣
║  直接输入表达式即可计算                        ║
║  输入 'help' 查看帮助  |  输入 'exit' 退出     ║
║  角度模式: )";
    std::cout << (Calculator::angleMode == Calculator::AngleMode::RAD ? "弧度 (RAD)" : "角度 (DEG)");
    std::cout << R"(                        ║
╚══════════════════════════════════════════════╝
)";
}

void printHelp() {
    std::cout << R"(
╔══════════════════════════════════════════════╗
║              帮  助  信  息                   ║
╠══════════════════════════════════════════════╣
║  【基本运算】 +  -  *  /  %  ^               ║
║  【括号】    (...)  支持嵌套                  ║
║  【隐式乘法】2pi, 3(1+2), (2)(3), sin(x)cos(x)║
║  【科学记数】1.5e10, 2E-3                     ║
╠══════════════════════════════════════════════╣
║  【三角函数】(受角度模式影响)                  ║
║    sin(x)  cos(x)  tan(x)                    ║
║    asin(x) acos(x) atan(x) atan2(y,x)        ║
║  【双曲函数】                                  ║
║    sinh(x) cosh(x) tanh(x)                   ║
║    asinh(x) acosh(x) atanh(x)                ║
║  【对数】                                      ║
║    ln(x)  log(x)  log2(x)  logb(x,base)      ║
║  【幂/根】                                     ║
║    sqrt(x)  cbrt(x)  exp(x)                  ║
║  【取整】                                      ║
║    floor(x) ceil(x) round(x) trunc(x)        ║
║  【其他】                                      ║
║    abs(x)  sign(x)  gamma(x)  hypot(x,y)     ║
║  【组合/数论】                                 ║
║    perm(n,r) comb(n,r) gcd(a,b) lcm(a,b)     ║
║    isprime(n)                                 ║
╠══════════════════════════════════════════════╣
║  【常量】                                      ║
║    pi  e  phi  sqrt2  ln2  ln10  ans         ║
╠══════════════════════════════════════════════╣
║  【命令】(大小写不敏感)                        ║
║    help / ?     - 显示此帮助                  ║
║    exit / quit  - 退出程序                    ║
║    menu / m     - 传统菜单模式                ║
║    history / h  - 显示计算历史                ║
║    mode         - 切换角度模式 (RAD↔DEG)      ║
║    mode rad/deg - 设置角度模式                ║
║    clear / cls  - 清屏                        ║
║    version / ver- 显示版本                    ║
╚══════════════════════════════════════════════╝
)";
}

void printVersion() {
    std::cout << "C++ 多功能科学计算器 v3.0\n";
    std::cout << "编译标准: C++17\n";
    std::cout << "支持 40+ 数学函数和常量\n";
}

void printHistory() {
    if (history.empty()) {
        std::cout << "（暂无计算历史）\n";
        return;
    }
    std::cout << "\n── 计算历史（最近 " << history.size() << " 条）──\n";
    size_t start = history.size() > 20 ? history.size() - 20 : 0;
    for (size_t i = start; i < history.size(); ++i) {
        std::cout << " [" << (i + 1) << "] " << history[i] << "\n";
    }
    std::cout << std::endl;
}

// ==================== 传统菜单模式 ====================

void printMenu() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════╗\n";
    std::cout << "║        C++ 多功能科学计算器          ║\n";
    std::cout << "╠══════════════════════════════════════╣\n";
    std::cout << "║  —— 基本运算 ——                      ║\n";
    std::cout << "║  1. 加法 (+)                         ║\n";
    std::cout << "║  2. 减法 (-)                         ║\n";
    std::cout << "║  3. 乘法 (*)                         ║\n";
    std::cout << "║  4. 除法 (/)                         ║\n";
    std::cout << "║  5. 取模 (%)                         ║\n";
    std::cout << "║  —— 高级运算 ——                      ║\n";
    std::cout << "║  6. 幂运算 (^)                       ║\n";
    std::cout << "║  7. 平方根                           ║\n";
    std::cout << "║  8. 立方根                           ║\n";
    std::cout << "║  9. 阶乘                             ║\n";
    std::cout << "║  —— 三角函数 ——                      ║\n";
    std::cout << "║  10. sin / cos / tan                 ║\n";
    std::cout << "║  11. asin / acos / atan              ║\n";
    std::cout << "║  —— 双曲函数 ——                      ║\n";
    std::cout << "║  12. sinh / cosh / tanh              ║\n";
    std::cout << "║  —— 对数 & 其他 ——                   ║\n";
    std::cout << "║  13. ln / log / log2 / logb          ║\n";
    std::cout << "║  14. abs / exp / floor / ceil        ║\n";
    std::cout << "║  —— 组合 & 统计 ——                   ║\n";
    std::cout << "║  15. perm / comb / gcd / lcm         ║\n";
    std::cout << "║  16. 统计 (均值/中位数/标准差)        ║\n";
    std::cout << "║  —— 表达式 ——                        ║\n";
    std::cout << "║  17. 表达式求值                      ║\n";
    std::cout << "║  0. 返回交互模式                     ║\n";
    std::cout << "╚══════════════════════════════════════╝\n";
    std::cout << "当前角度模式: "
              << (Calculator::angleMode == Calculator::AngleMode::RAD ? "弧度" : "角度")
              << " | ans = " << std::setprecision(6) << Calculator::ans << "\n";
    std::cout << "请选择 [0-17]: ";
}

void handleTrigMenu() {
    std::cout << "  a. sin    b. cos    c. tan\n";
    std::cout << "选择 [a-c]: ";
    char c;
    std::cin >> c;
    clearInput();

    double val;
    std::cout << "输入值: ";
    std::cin >> val;

    double result;
    switch (c) {
    case 'a': result = Calculator::sin(val); break;
    case 'b': result = Calculator::cos(val); break;
    case 'c': result = Calculator::tan(val); break;
    default:
        std::cout << "无效选择。\n";
        return;
    }
    std::cout << "结果: " << std::setprecision(10) << result << "\n";
    Calculator::ans = result;
}

void handleInvTrigMenu() {
    std::cout << "  a. asin    b. acos    c. atan    d. atan2\n";
    std::cout << "选择 [a-d]: ";
    char c;
    std::cin >> c;
    clearInput();

    double result;
    if (c == 'd') {
        double y, x;
        std::cout << "输入 y x: ";
        std::cin >> y >> x;
        result = Calculator::atan2(y, x);
    } else {
        double val;
        std::cout << "输入值: ";
        std::cin >> val;
        switch (c) {
        case 'a': result = Calculator::asin(val); break;
        case 'b': result = Calculator::acos(val); break;
        case 'c': result = Calculator::atan(val); break;
        default:
            std::cout << "无效选择。\n";
            return;
        }
    }
    std::cout << "结果: " << std::setprecision(10) << result << "\n";
    Calculator::ans = result;
}

void handleHyperbolicMenu() {
    std::cout << "  a. sinh    b. cosh    c. tanh\n";
    std::cout << "选择 [a-c]: ";
    char c;
    std::cin >> c;
    clearInput();

    double val;
    std::cout << "输入值: ";
    std::cin >> val;

    double result;
    switch (c) {
    case 'a': result = Calculator::sinh(val); break;
    case 'b': result = Calculator::cosh(val); break;
    case 'c': result = Calculator::tanh(val); break;
    default:
        std::cout << "无效选择。\n";
        return;
    }
    std::cout << "结果: " << std::setprecision(10) << result << "\n";
    Calculator::ans = result;
}

void handleLogMenu() {
    std::cout << "  a. ln  (自然对数，底 e)\n";
    std::cout << "  b. log (常用对数，底 10)\n";
    std::cout << "  c. log2 (底 2)\n";
    std::cout << "  d. logb (任意底)\n";
    std::cout << "选择 [a-d]: ";
    char c;
    std::cin >> c;
    clearInput();

    double result;
    if (c == 'd') {
        double val, base;
        std::cout << "输入真数 底数: ";
        std::cin >> val >> base;
        result = Calculator::logb(val, base);
    } else {
        double val;
        std::cout << "输入正数: ";
        std::cin >> val;
        switch (c) {
        case 'a': result = Calculator::ln(val); break;
        case 'b': result = Calculator::log(val); break;
        case 'c': result = Calculator::log2(val); break;
        default:
            std::cout << "无效选择。\n";
            return;
        }
    }
    std::cout << "结果: " << std::setprecision(10) << result << "\n";
    Calculator::ans = result;
}

void handleAbsExpMenu() {
    std::cout << "  a. abs (绝对值)\n";
    std::cout << "  b. exp (e^x)\n";
    std::cout << "  c. floor (向下取整)\n";
    std::cout << "  d. ceil (向上取整)\n";
    std::cout << "选择 [a-d]: ";
    char c;
    std::cin >> c;
    clearInput();

    double val;
    std::cout << "输入数值: ";
    std::cin >> val;

    double result;
    switch (c) {
    case 'a': result = Calculator::abs(val); break;
    case 'b': result = Calculator::exp(val); break;
    case 'c': result = Calculator::floor(val); break;
    case 'd': result = Calculator::ceil(val); break;
    default:
        std::cout << "无效选择。\n";
        return;
    }
    std::cout << "结果: " << std::setprecision(10) << result << "\n";
    Calculator::ans = result;
}

void handleComboMenu() {
    std::cout << "  a. perm(n,r) 排列\n";
    std::cout << "  b. comb(n,r) 组合\n";
    std::cout << "  c. gcd(a,b)  最大公约数\n";
    std::cout << "  d. lcm(a,b)  最小公倍数\n";
    std::cout << "选择 [a-d]: ";
    char c;
    std::cin >> c;
    clearInput();

    int a, b;
    std::cout << "输入两个整数: ";
    std::cin >> a >> b;

    double result;
    switch (c) {
    case 'a': result = static_cast<double>(Calculator::perm(a, b)); break;
    case 'b': result = static_cast<double>(Calculator::comb(a, b)); break;
    case 'c': result = static_cast<double>(Calculator::gcd(a, b)); break;
    case 'd': result = static_cast<double>(Calculator::lcm(a, b)); break;
    default:
        std::cout << "无效选择。\n";
        return;
    }
    std::cout << "结果: " << result << "\n";
    Calculator::ans = result;
}

void handleStatistics() {
    std::cout << "请输入一组数字（空格分隔），输入非数字结束:\n> ";
    std::vector<double> nums;
    double val;
    while (std::cin >> val) {
        nums.push_back(val);
    }
    clearInput();

    if (nums.empty()) {
        std::cout << "未输入有效数字。\n";
        return;
    }

    try {
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "均值:   " << Calculator::mean(nums) << "\n";
        std::cout << "中位数: " << Calculator::median(nums) << "\n";
        if (nums.size() >= 2) {
            std::cout << "标准差: " << Calculator::stddev(nums) << "\n";
        }
        Calculator::ans = Calculator::mean(nums);
    } catch (const std::exception& e) {
        std::cout << "错误: " << e.what() << "\n";
    }
}

void runMenuMode() {
    std::cout << "\n进入传统菜单模式（输入 0 返回交互模式）\n";

    while (true) {
        printMenu();
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "返回交互模式。\n";
            break;
        }

        if (std::cin.fail()) {
            clearInput();
            std::cout << "无效输入，请输入数字。\n";
            continue;
        }

        try {
            switch (choice) {
            case 1: case 2: case 3: case 4: case 5: {
                double a, b;
                std::cout << "输入 a b: ";
                std::cin >> a >> b;
                double result;
                if (choice == 1) {
                    result = Calculator::add(a, b);
                    std::cout << a << " + " << b << " = " << result << "\n";
                } else if (choice == 2) {
                    result = Calculator::subtract(a, b);
                    std::cout << a << " - " << b << " = " << result << "\n";
                } else if (choice == 3) {
                    result = Calculator::multiply(a, b);
                    std::cout << a << " * " << b << " = " << result << "\n";
                } else if (choice == 4) {
                    result = Calculator::divide(a, b);
                    std::cout << a << " / " << b << " = " << result << "\n";
                } else {
                    result = Calculator::modulo(a, b);
                    std::cout << a << " % " << b << " = " << result << "\n";
                }
                Calculator::ans = result;
                break;
            }
            case 6: {
                double a, b;
                std::cout << "输入 base exp: ";
                std::cin >> a >> b;
                double result = Calculator::power(a, b);
                std::cout << a << " ^ " << b << " = " << result << "\n";
                Calculator::ans = result;
                break;
            }
            case 7: {
                double a;
                std::cout << "输入非负数: ";
                std::cin >> a;
                double result = Calculator::sqrt(a);
                std::cout << "√" << a << " = " << result << "\n";
                Calculator::ans = result;
                break;
            }
            case 8: {
                double a;
                std::cout << "输入数值: ";
                std::cin >> a;
                double result = Calculator::cbrt(a);
                std::cout << "∛" << a << " = " << result << "\n";
                Calculator::ans = result;
                break;
            }
            case 9: {
                std::cout << "输入非负整数 (0-20): ";
                int n;
                std::cin >> n;
                long long result = Calculator::factorial(n);
                std::cout << n << "! = " << result << "\n";
                Calculator::ans = static_cast<double>(result);
                break;
            }
            case 10: handleTrigMenu(); break;
            case 11: handleInvTrigMenu(); break;
            case 12: handleHyperbolicMenu(); break;
            case 13: handleLogMenu(); break;
            case 14: handleAbsExpMenu(); break;
            case 15: handleComboMenu(); break;
            case 16: handleStatistics(); break;
            case 17: {
                std::cout << "输入表达式:\n> ";
                clearInput();
                std::string expr;
                std::getline(std::cin, expr);
                if (expr.empty()) {
                    std::cout << "未输入表达式。\n";
                    break;
                }
                double result = Calculator::evaluate(expr);
                std::cout << "= " << std::setprecision(10) << result << "\n";
                history.push_back(expr + " = " + std::to_string(result));
                if (history.size() > MAX_HISTORY) history.erase(history.begin());
                break;
            }
            default:
                std::cout << "无效选择，请重试。\n";
                clearInput();
                break;
            }
        } catch (const std::exception& e) {
            std::cout << "错误: " << e.what() << "\n";
            clearInput();
        }
    }
}

// ==================== 交互模式命令处理 ====================

// 返回 true 表示应退出程序
bool handleCommand(const std::string& input) {
    std::string cmd = toLower(input);

    // 去除尾部空格
    while (!cmd.empty() && std::isspace(cmd.back())) cmd.pop_back();

    if (cmd == "exit" || cmd == "quit" || cmd == "q") {
        std::cout << "再见！\n";
        return true;
    }

    if (cmd == "help" || cmd == "?") {
        printHelp();
        return false;
    }

    if (cmd == "menu" || cmd == "m") {
        runMenuMode();
        printWelcome();
        return false;
    }

    if (cmd == "history" || cmd == "hist" || cmd == "h") {
        printHistory();
        return false;
    }

    if (cmd == "mode") {
        // 切换模式
        if (Calculator::angleMode == Calculator::AngleMode::RAD) {
            Calculator::angleMode = Calculator::AngleMode::DEG;
            std::cout << "已切换为角度模式 (DEG)\n";
        } else {
            Calculator::angleMode = Calculator::AngleMode::RAD;
            std::cout << "已切换为弧度模式 (RAD)\n";
        }
        return false;
    }

    if (cmd == "mode rad" || cmd == "mode radians") {
        Calculator::angleMode = Calculator::AngleMode::RAD;
        std::cout << "已切换为弧度模式 (RAD)\n";
        return false;
    }

    if (cmd == "mode deg" || cmd == "mode degrees") {
        Calculator::angleMode = Calculator::AngleMode::DEG;
        std::cout << "已切换为角度模式 (DEG)\n";
        return false;
    }

    if (cmd == "clear" || cmd == "cls") {
        clearScreen();
        printWelcome();
        return false;
    }

    if (cmd == "version" || cmd == "ver") {
        printVersion();
        return false;
    }

    // 未识别的命令，可能是表达式
    return false;
}

bool isCommand(const std::string& input) {
    std::string cmd = toLower(input);
    while (!cmd.empty() && std::isspace(cmd.back())) cmd.pop_back();
    while (!cmd.empty() && std::isspace(cmd.front())) cmd.erase(0, 1);

    // 检查是否为完整命令匹配
    if (cmd == "exit"   || cmd == "quit"   || cmd == "q"    ||
        cmd == "help"   || cmd == "?"      ||
        cmd == "menu"   || cmd == "m"      ||
        cmd == "history"|| cmd == "hist"   || cmd == "h"    ||
        cmd == "mode"   ||
        cmd == "mode rad"  || cmd == "mode radians" ||
        cmd == "mode deg"  || cmd == "mode degrees" ||
        cmd == "clear"  || cmd == "cls"    ||
        cmd == "version"|| cmd == "ver") {
        return true;
    }
    return false;
}

// ==================== 交互模式主循环 ====================

void runInteractiveMode() {
    printWelcome();

    while (true) {
        // 显示提示符（包含角度模式指示）
        std::cout << (Calculator::angleMode == Calculator::AngleMode::RAD ? "[RAD]" : "[DEG]")
                  << " > ";

        std::string input;
        if (!std::getline(std::cin, input)) {
            // EOF (Ctrl+D / Ctrl+Z)
            std::cout << "\n再见！\n";
            break;
        }

        // 去除首尾空格
        size_t start = 0, end = input.size();
        while (start < end && std::isspace(static_cast<unsigned char>(input[start]))) ++start;
        while (end > start && std::isspace(static_cast<unsigned char>(input[end - 1]))) --end;
        std::string trimmed = input.substr(start, end - start);

        if (trimmed.empty()) continue;

        // 检查是否为命令
        if (isCommand(trimmed)) {
            bool shouldExit = handleCommand(trimmed);
            if (shouldExit) break;
            continue;
        }

        // 作为表达式求值
        try {
            double result = Calculator::evaluate(trimmed);
            std::cout << "= " << std::setprecision(10) << result << "\n";

            // 添加到历史
            std::string entry = trimmed + " = " + std::to_string(result);
            // 简化显示：如果太长则截断
            if (entry.size() > 120) {
                entry = trimmed.substr(0, 100) + "... = " + std::to_string(result);
            }
            history.push_back(entry);
            if (history.size() > MAX_HISTORY) {
                history.erase(history.begin());
            }
        } catch (const std::exception& e) {
            std::cout << "错误: " << e.what() << "\n";
        }
    }
}

// ==================== 程序入口 ====================

int main() {
    // 设置输出格式
    std::cout << std::fixed;

    runInteractiveMode();

    return 0;
}
