#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "calculator.h"

void printMenu() {
    std::cout << "\n╔══════════════════════════════════╗\n";
    std::cout << "║        C++ 多功能计算器          ║\n";
    std::cout << "╠══════════════════════════════════╣\n";
    std::cout << "║  1. 加法 (+)                     ║\n";
    std::cout << "║  2. 减法 (-)                     ║\n";
    std::cout << "║  3. 乘法 (*)                     ║\n";
    std::cout << "║  4. 除法 (/)                     ║\n";
    std::cout << "║  5. 幂运算 (^)                   ║\n";
    std::cout << "║  6. 平方根                       ║\n";
    std::cout << "║  7. 阶乘                         ║\n";
    std::cout << "║  8. 统计 (均值/中位数/标准差)     ║\n";
    std::cout << "║  9. 表达式求值 (如: 3+5*(2-8))   ║\n";
    std::cout << "║  0. 退出                         ║\n";
    std::cout << "╚══════════════════════════════════╝\n";
    std::cout << "请选择 [0-9]: ";
}

void handleStatistics() {
    std::cout << "请输入一组数字（空格分隔），输入非数字结束:\n> ";
    std::vector<double> nums;
    double val;
    while (std::cin >> val) {
        nums.push_back(val);
    }
    std::cin.clear();
    std::cin.ignore(1000, '\n');

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
    std::cout << "欢迎使用 C++ 计算器！\n";

    while (true) {
        printMenu();
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "再见！\n";
            break;
        }

        double a, b;
        try {
            switch (choice) {
            case 1:
                std::cout << "输入 a b: ";
                std::cin >> a >> b;
                std::cout << a << " + " << b << " = " << Calculator::add(a, b) << "\n";
                break;
            case 2:
                std::cout << "输入 a b: ";
                std::cin >> a >> b;
                std::cout << a << " - " << b << " = " << Calculator::subtract(a, b) << "\n";
                break;
            case 3:
                std::cout << "输入 a b: ";
                std::cin >> a >> b;
                std::cout << a << " * " << b << " = " << Calculator::multiply(a, b) << "\n";
                break;
            case 4:
                std::cout << "输入 a b: ";
                std::cin >> a >> b;
                std::cout << a << " / " << b << " = " << Calculator::divide(a, b) << "\n";
                break;
            case 5:
                std::cout << "输入 base exp: ";
                std::cin >> a >> b;
                std::cout << a << " ^ " << b << " = " << Calculator::power(a, b) << "\n";
                break;
            case 6:
                std::cout << "输入数值: ";
                std::cin >> a;
                std::cout << "√" << a << " = " << Calculator::sqrt(a) << "\n";
                break;
            case 7: {
                std::cout << "输入非负整数: ";
                int n;
                std::cin >> n;
                std::cout << n << "! = " << Calculator::factorial(n) << "\n";
                break;
            }
            case 8:
                handleStatistics();
                break;
            case 9: {
                std::cout << "输入表达式 (如: 3+5*(2-8)):\n> ";
                std::string expr;
                std::cin.ignore();
                std::getline(std::cin, expr);
                std::cout << expr << " = " << Calculator::evaluate(expr) << "\n";
                break;
            }
            default:
                std::cout << "无效选择，请重试。\n";
                break;
            }
        } catch (const std::exception& e) {
            std::cout << "错误: " << e.what() << "\n";
        }
    }

    return 0;
}
