// Copyright 2024 JOK Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

#include <iostream>

class ITransportation {
 public:
  virtual ~ITransportation() {}
  virtual void transport() const = 0;
};

class Car : public ITransportation {
 public:
  void transport() const override {
    std::cout << "Go out by car\n";
  }
};

class Ship : public ITransportation {
 public:
  void transport() const override {
    std::cout << "Go out by ship\n";
  }
};

class IFactory {
 public:
  virtual ~IFactory() {}
  virtual ITransportation* createTransport() const = 0;

  void goOut() const {
    ITransportation* p = createTransport();
    p->transport();
    delete p;
  }
};

class CarFactory : public IFactory {
 public:
  ITransportation* createTransport() const override {
    return new Car();
  }
};

class ShipFactory : public IFactory {
 public:
  ITransportation* createTransport() const override {
    return new Ship();
  }
};

int main(int argc, char** argv) {
  IFactory* carF = new CarFactory();
  carF->goOut();
  delete carF;
  IFactory* shipF = new ShipFactory();
  shipF->goOut();
  delete shipF;
  return 0;
}
