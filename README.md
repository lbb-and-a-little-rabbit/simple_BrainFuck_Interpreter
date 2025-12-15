# simple_BrainFuck_Interpreter
A simple BrainFuck interpreter based on NJU c++ programming lesson.

## 功能
识别BrainFuck程序并运行

Brainfuck 语句说明

Brainfuck 一共有 8 种语句，并且每种语句都仅由 一个字符 组成。
在本项目中，我们将这些语句分为 四类：

1. 输入 / 输出语句

','	  从输入流（std::istream）读取一个字符，并将其写入当前 tape 元素

'.'	  读取当前 tape 元素，并通过 std::cout 输出到控制台

2. tape_index 移动语句

'<'	  将 tape_index 减 1

'>'	  将 tape_index 加 1

3. 修改当前数组元素语句

'+'	  将当前元素的值加 1

'-'	  将当前元素的值减 1

4. 循环语句

'['	  如果当前元素为 0（ASCII 值为 0，而不是字符 '0'），则跳转到与该 [ 匹配的 ] 后一条语句；否则继续执行下一条语句

']'	  如果当前元素 不为 0，则跳转回与该 ] 匹配的 [ 后的第一条语句；否则继续执行下一条语句

说明

所有非 Brainfuck 指令字符都会被解释器忽略

tape 元素以 ASCII 值 进行判断和输出

'[' 与 ']' 必须成对匹配，否则行为未定义

## 使用方法
```bash
g++ -std=c++17 BrainDuck.cpp main.cpp -o brainfuck
./brainfuck


