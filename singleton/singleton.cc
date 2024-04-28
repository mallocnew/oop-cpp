// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <iostream>
#include <mutex>   // NOLINT
#include <thread>  // NOLINT

class Singleton {
 public:
  static Singleton* getInstance() {
    if (instance_ == nullptr) {
      instance_ = new Singleton();
    }
    return instance_;
  }

 protected:
  Singleton() { std::cout << "New instance: " << this << "\n"; }

 private:
  static Singleton* instance_;

  Singleton(Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
};

Singleton* Singleton::instance_ = nullptr;

class TSafeSingleton {
 public:
  static TSafeSingleton* getInstance() {
    std::lock_guard<std::mutex> lock(m_);
    if (instance_ == nullptr) {
      instance_ = new TSafeSingleton();
    }
    return instance_;
  }

 protected:
  TSafeSingleton() { std::cout << "New instance: " << this << "\n"; }

 private:
  static TSafeSingleton* instance_;
  static std::mutex m_;

  TSafeSingleton(TSafeSingleton&) = delete;
  TSafeSingleton& operator=(const TSafeSingleton&) = delete;
};

TSafeSingleton* TSafeSingleton::instance_ = nullptr;
std::mutex TSafeSingleton::m_;

int main(int argc, char** argv) {
  Singleton* i = Singleton::getInstance();
  TSafeSingleton* i2 = TSafeSingleton::getInstance();
  return 0;
}
