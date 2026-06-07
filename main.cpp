#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include "calculator.h"

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

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
    std::cout << "║  8. 阶乘                             ║\n";
    std::cout << "║  —— 三角函数 (弧度) ——               ║\n";
    std::cout << "║  9. sin / cos / tan                  ║\n";
    std::cout << "║  —— 对数 & 其他 ——                   ║\n";
    std::cout << "║  10. ln / log / log2                 ║\n";
    std::cout << "║  11. abs / exp                       ║\n";
    std::cout << "║  —— 统计 ——                          ║\n";
    std::cout << "║  12. 统计 (均值/中位数/标准差)        ║\n";
    std::cout << "║  —— 表达式 ——                        ║\n";
    std::cout << "║  13. 表达式求值                      ║\n";
    std::cout << "║      支持: + - * / % ^ () 函数       ║\n";
    std::cout << "║      sin cos tan sqrt ln log log2    ║\n";
    std::cout << "║      abs exp 常量: pi e             ║\n";
    std::cout << "║  0. 退出                             ║\n";
    std::cout << "╚══════════════════════════════════════╝\n";
    std::cout << "请选择 [0-13]: ";
}

void handleTrig() {
    std::cout << "  a. sin\n";
    std::cout << "  b. cos\n";
    std::cout << "  c. tan\n";
    std::cout << "选择 [a-c]: ";
    char c;
    std::cin >> c;
    clearInput();

    double val;
    std::cout << "输入弧度值: ";
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
}

void handleLog() {
    std::cout << "  a. ln  (自然对数，底 e)\n";
    std::cout << "  b. log (常用对数，底 10)\n";
    std::cout << "  c. log2 (底 2)\n";
    std::cout << "选择 [a-c]: ";
    char c;
    std::cin >> c;
    clearInput();

    double val;
    std::cout << "输入正数: ";
    std::cin >> val;

    double result;
    switch (c) {
    case 'a': result = Calculator::ln(val); break;
    case 'b': result = Calculator::log(val); break;
    case 'c': result = Calculator::log2(val); break;
    default:
        std::cout << "无效选择。\n";
        return;
    }
    std::cout << "结果: " << std::setprecision(10) << result << "\n";
}

void handleAbsExp() {
    std::cout << "  a. abs (绝对值)\n";
    std::cout << "  b. exp (e^x)\n";
    std::cout << "选择 [a-b]: ";
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
    default:
        std::cout << "无效选择。\n";
        return;
    }
    std::cout << "结果: " << std::setprecision(10) << result << "\n";
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
    } catch (const std::exception& e) {
        std::cout << "错误: " << e.what() << "\n";
    }
}

int main() {
    std::cout << "欢迎使用 C++ 科学计算器！\n";
    std::cout << "常数: pi = " << Calculator::PI << ", e = " << Calculator::E << "\n";

    while (true) {
        printMenu();
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "再见！\n";
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
                if (choice == 1)
                    std::cout << a << " + " << b << " = " << Calculator::add(a, b) << "\n";
                else if (choice == 2)
                    std::cout << a << " - " << b << " = " << Calculator::subtract(a, b) << "\n";
                else if (choice == 3)
                    std::cout << a << " * " << b << " = " << Calculator::multiply(a, b) << "\n";
                else if (choice == 4)
                    std::cout << a << " / " << b << " = " << Calculator::divide(a, b) << "\n";
                else
                    std::cout << a << " % " << b << " = " << Calculator::modulo(a, b) << "\n";
                break;
            }
            case 6: {
                double a, b;
                std::cout << "输入 base exp: ";
                std::cin >> a >> b;
                std::cout << a << " ^ " << b << " = " << Calculator::power(a, b) << "\n";
                break;
            }
            case 7: {
                double a;
                std::cout << "输入非负数: ";
                std::cin >> a;
                std::cout << "√" << a << " = " << Calculator::sqrt(a) << "\n";
                break;
            }
            case 8: {
                std::cout << "输入非负整数 (0-20): ";
                int n;
                std::cin >> n;
                std::cout << n << "! = " << Calculator::factorial(n) << "\n";
                break;
            }
            case 9:
                handleTrig();
                break;
            case 10:
                handleLog();
                break;
            case 11:
                handleAbsExp();
                break;
            case 12:
                handleStatistics();
                break;
            case 13: {
                std::cout << "输入表达式:\n";
                std::cout << "  例: 3+5*(2-8), sin(pi/2), 2^10, sqrt(16)+ln(e)\n> ";
                clearInput();
                std::string expr;
                std::getline(std::cin, expr);
                if (expr.empty()) {
                    std::cout << "未输入表达式。\n";
                    break;
                }
                double result = Calculator::evaluate(expr);
                std::cout << "= " << std::setprecision(10) << result << "\n";
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

    return 0;
}
