// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <iostream>
#include <memory>
#include <mutex>   // NOLINT
#include <thread>  // NOLINT

class Singleton {
 public:
  static std::shared_ptr<Singleton> getInstance() {
    struct SingletonT : Singleton {};
    if (instance_ == nullptr) {
      instance_ = std::make_shared<SingletonT>();
    }
    return instance_;
  }

 protected:
  Singleton() { std::cout << "New instance: " << this << "\n"; }
  ~Singleton() { std::cout << "Destroy instance: " << this << "\n"; }

 private:
  static std::shared_ptr<Singleton> instance_;

  Singleton(Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
};

std::shared_ptr<Singleton> Singleton::instance_ = nullptr;

class TSafeSingleton {
 public:
  static std::shared_ptr<TSafeSingleton> getInstance() {
    struct SingletonT : TSafeSingleton {};
    std::lock_guard<std::mutex> lock(m_);
    if (instance_ == nullptr) {
      instance_ = std::make_shared<SingletonT>();
    }
    return instance_;
  }

 protected:
  TSafeSingleton() { std::cout << "New instance: " << this << "\n"; }
  ~TSafeSingleton() { std::cout << "Destroy instance: " << this << "\n"; }

 private:
  static std::shared_ptr<TSafeSingleton> instance_;
  static std::mutex m_;

  TSafeSingleton(TSafeSingleton&) = delete;
  TSafeSingleton& operator=(const TSafeSingleton&) = delete;
};

std::shared_ptr<TSafeSingleton> TSafeSingleton::instance_ = nullptr;
std::mutex TSafeSingleton::m_;

int main(int argc, char** argv) {
  auto i = Singleton::getInstance();
  auto i2 = TSafeSingleton::getInstance();
  return 0;
}
