// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <iostream>
#include <memory>
#include <optional>
#include <string>

class IStrategy {
 public:
  virtual ~IStrategy() = default;
  virtual std::string doSomething() const = 0;
};

class StrategyA : public IStrategy {
 public:
  std::string doSomething() const override { return "Do strategy from A"; }
};

class StrategyB : public IStrategy {
 public:
  std::string doSomething() const override { return "Do strategy from B"; }
};

class Context {
 public:
  explicit Context(std::unique_ptr<IStrategy>&& strategy)
      : strategy_(std::move(strategy)) {}

  void setStrategy(std::unique_ptr<IStrategy>&& strategy) {
    strategy_ = std::move(strategy);
  }

  std::optional<std::string> makeDecisions() const {
    if (strategy_.get() == nullptr) {
      std::cout << "Context: no strategy\n";
      return std::nullopt;
    }
    return strategy_->doSomething();
  }

 private:
  std::unique_ptr<IStrategy> strategy_;
};

int main(int argc, char** argv) {
  Context c(nullptr);
  auto res = c.makeDecisions();
  auto val = [&]() { std::cout << res.value_or("nullptr") << "\n"; };
  val();
  c.setStrategy(std::make_unique<StrategyA>());
  res = c.makeDecisions();
  val();
  c.setStrategy(std::make_unique<StrategyB>());
  res = c.makeDecisions();
  val();
  return 0;
}
