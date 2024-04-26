// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <iostream>
#include <list>
#include <string>

class IObserver {
 public:
  virtual ~IObserver() {}
  virtual void update(const std::string& msg) = 0;
};

class ISubject {
 public:
  virtual ~ISubject() {}
  virtual void attach(IObserver* observer) = 0;
  virtual void detach(IObserver* observer) = 0;
  virtual void notify() = 0;
};

class Subject : public ISubject {
 public:
  virtual ~Subject() = default;

  void attach(IObserver* observer) override { observers_.push_back(observer); }

  void detach(IObserver* observer) override { observers_.remove(observer); }

  void notify() override {
    std::cout << "There are " << observers_.size() << " observers.\n";
    for (auto it = observers_.begin(); it != observers_.end(); it++) {
      (*it)->update(msg_);
    }
  }

  void genMsg(const std::string& msg) {
    msg_ = msg;
    notify();
  }

 private:
  std::list<IObserver*> observers_;
  std::string msg_;
};

class Observer : public IObserver {
 public:
  explicit Observer(ISubject& s) : subject_(s) {
    subject_.attach(this);
    std::cout << "Observer " << ++count_ << "\n";
    num_ = count_;
  }

  virtual ~Observer() {}

  void update(const std::string& msg) override {
    printf("[%d] receive msg: %s\n", num_, msg.c_str());
  }

  void stopWatch() {
    subject_.detach(this);
    printf("[%d] stop watching\n", num_);
  }

 private:
  ISubject& subject_;
  static int count_;
  int num_;
};

int Observer::count_ = 0;

int main(int argc, char** argv) {
  Subject* subject = new Subject;
  Observer* o1 = new Observer(*subject);
  Observer* o2 = new Observer(*subject);
  Observer* o3 = new Observer(*subject);
  subject->genMsg("Hello world!");
  o3->stopWatch();

  Observer* o4 = new Observer(*subject);
  subject->genMsg("Msg2");

  o1->stopWatch();
  o2->stopWatch();
  o4->stopWatch();

  delete o1;
  delete o2;
  delete o3;
  delete o4;
  delete subject;
  return 0;
}
