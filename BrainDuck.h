#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <vector>

class BrainDuckVM;
class Instruction {
public:
  // 返回下一条执行的指令距离当前指令的位置
  virtual int execute(std::istream &ss, BrainDuckVM &vm) = 0;
  virtual ~Instruction() {}
};

class IncrementInstruction : public Instruction {
public:
  int execute(std::istream &ss, BrainDuckVM &vm) override;
};

class DecrementInstruction : public Instruction {
public:
  int execute(std::istream &ss, BrainDuckVM &vm) override;
};

class MoveRightInstruction : public Instruction {
public:
  int execute(std::istream &ss, BrainDuckVM &vm) override;
};

class MoveLeftInstruction : public Instruction {
public:
  int execute(std::istream &ss, BrainDuckVM &vm) override;
};

class LoopBeginInstruction : public Instruction {
public:
  int execute(std::istream &ss, BrainDuckVM &vm) override;
};

class LoopEndInstruction : public Instruction {
public:
  int execute(std::istream &ss, BrainDuckVM &vm) override;
};

class OutputInstruction : public Instruction {
public:
  int execute(std::istream &ss, BrainDuckVM &vm) override;
};

class InputInstruction : public Instruction {
public:
  int execute(std::istream &ss, BrainDuckVM &vm) override;
};

class BrainDuckVM {
private:
  /* 待执行程序的状态 */
  size_t program_count_{0}; // 当前执行到的语句的编号
  std::string program_{}; // BrainDuck程序中的所有语句

  /* tape数组的状态 */
  size_t tape_index_{0}; // 当前指向的tape数组索引
  std::vector<char> tape_{}; // tape数组

  std::map<char, Instruction *> instruction_map_{
      {'+', new IncrementInstruction()}, {'-', new DecrementInstruction()},
      {'>', new MoveRightInstruction()}, {'<', new MoveLeftInstruction()},
      {'.', new OutputInstruction()},    {',', new InputInstruction()},
      {'[', new LoopBeginInstruction()}, {']', new LoopEndInstruction()}};

public:
  BrainDuckVM() {}
  ~BrainDuckVM() {
    for (auto &pair : instruction_map_) {
      delete pair.second;
      pair.second = nullptr;
    }
    instruction_map_.clear();
  }

  // [仅在测试中调用]init会读取输入的程序,并且会进行一系列初始化
  void init(const std::string &program) {
    program_ = program;
    program_count_ = 0;

    tape_.resize(100000, 0);
    tape_index_ = 0;
  }

  // [仅在测试中调用]使用输入流ss来执行当前程序
  void executeProgram(std::istream &ss) {
    while (program_count_ < program_.size()) {
      char instruction = program_[program_count_];

      if (instruction_map_.count(instruction) > 0) {
        program_count_ += instruction_map_[instruction]->execute(ss, *this);
      } else {
        program_count_ ++;
      }
    }
  }

  // 获取当前程序中所有语句(每个语句是一个字符)
  const std::string& getProgram() const{
    return program_;
  }

  // 返回当前执行到的语句编号(从0开始编号)
  size_t getProgramCount() const {
    return program_count_;
  }

  // 返回tape数组中tape_index指向的元素
  char getCurrentTape() { return tape_[tape_index_]; }

  // 使用in来设置tape数组中tape_index的值
  void setCurrentTape(char in) { tape_[tape_index_] = in; }

  // 增加tape_index的值
  void increaseTapeIndex() { tape_index_++; }

  // 减少tape_index的值
  void decreaseTapeIndex() { tape_index_--; }
};
