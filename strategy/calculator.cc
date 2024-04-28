// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <iostream>

class IStrategy {
 public:
  virtual int execute(int, int) const = 0;
};

class AddStrategy : public IStrategy {
 public:
  int execute(int a, int b) const override { return a + b; }
};

class SubtractStrategy : public IStrategy {
 public:
  int execute(int a, int b) const override { return a - b; }
};

class MultiplyStrategy : public IStrategy {
 public:
  int execute(int a, int b) const override { return a * b; }
};

class Context {
 public:
  explicit Context(const IStrategy* strategy) : strategy_(strategy) {}

  void setStrategy(const IStrategy* strategy) { strategy_ = strategy; }

  int executeStrategy(int a, int b) const {
    if (strategy_) return strategy_->execute(a, b);
    return 0;
  }

 private:
  const IStrategy* strategy_;
};

int main(int argc, char** argv) {
  AddStrategy add;
  SubtractStrategy sub;
  MultiplyStrategy mul;
  Context c(&add);
  std::cout << "1 + 2 = " << c.executeStrategy(1, 2) << "\n";
  c.setStrategy(&sub);
  std::cout << "1 - 2 = " << c.executeStrategy(1, 2) << "\n";
  c.setStrategy(&mul);
  std::cout << "1 * 2 = " << c.executeStrategy(1, 2) << "\n";
  return 0;
}
