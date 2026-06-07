# C++ 多功能计算器

一个用 C++17 编写的命令行多功能计算器。

## 功能

- ➕ **加 / ➖ 减 / ✖️ 乘 / ➗ 除** — 基本四则运算
- 🔢 **幂运算** — 计算任意底数和指数
- √ **平方根** — 计算非负数的平方根
- ❗ **阶乘** — 非负整数的阶乘
- 📊 **统计** — 计算一组数字的均值、中位数、标准差
- 📝 **表达式求值** — 支持括号的四则运算表达式解析（递归下降解析器）

## 编译和运行

### 使用 CMake

```bash
mkdir build && cd build
cmake ..
cmake --build .
./calculator   # Linux / macOS
calculator.exe  # Windows
```

### 直接编译

```bash
# g++
g++ -std=c++17 -o calculator main.cpp calculator.cpp

# MSVC
cl /EHsc /std:c++17 main.cpp calculator.cpp /Fe:calculator.exe
```

## 使用示例

```
欢迎使用 C++ 计算器！

╔══════════════════════════════════╗
║        C++ 多功能计算器          ║
╠══════════════════════════════════╣
║  1. 加法 (+)                     ║
║  2. 减法 (-)                     ║
║  3. 乘法 (*)                     ║
║  4. 除法 (/)                     ║
║  5. 幂运算 (^)                   ║
║  6. 平方根                       ║
║  7. 阶乘                         ║
║  8. 统计 (均值/中位数/标准差)     ║
║  9. 表达式求值 (如: 3+5*(2-8))   ║
║  0. 退出                         ║
╚══════════════════════════════════╝
```

## 项目结构

```
.
├── CMakeLists.txt    # CMake 构建配置
├── calculator.h      # 计算器类声明
├── calculator.cpp    # 计算器类实现
├── main.cpp          # 主程序入口
└── README.md
```

## 许可

MIT License
