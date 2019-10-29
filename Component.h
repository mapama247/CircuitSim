#include <string>
#include <vector>

//NODE
class Node{
public:
  Node(double voltage);
  double getVoltage();
  void setVoltage(double v);
private:
  double voltage{};
};

//COMPONENT
class Component{
public:
  Component(std::string const &name, Node *p, Node *n);
  virtual ~Component(); //making base class destructor virtual guarantees that objects of child classes are destructed properly (both base class and child class destructors will be called)
  virtual double move_charge(double time_step) = 0; //pure virtual function makes the class abstract
  virtual double getCurrent(double time_step) = 0;
  std::string getName();
protected:
  std::string name;
  Node *p;
  Node *n;
};

//BATTERY
class Battery : public Component{
public:
  Battery(std::string const &name, Node *p, Node *n, double const &voltage);
  double move_charge(double time_step) override;
  double getCurrent(double time_step) override;
private:
  double voltage;
};

//RESISTOR
class Resistor : public Component{
public:
  Resistor(std::string const &name, Node *p, Node *n, double const &resistance);
  double move_charge(double time_step) override;
  double getCurrent(double time_step) override;
  double getResistance();
private:
  double resistance{};
};

//CAPACITOR
class Capacitor : public Component{
public:
  Capacitor(std::string const &name, Node *p, Node *n, double const &capacitance);
  double move_charge(double time_step) override;
  double getCurrent(double time_step) override;
  double getCapacitance();
private:
  double stored_charge{};
  double capacitance{};
};

//CIRCUIT
class Circuit{
public:
  Circuit();
  void simulate(std::vector<Component *> net, int iterations, int lines, double time_step);
  void deallocate_components(std::vector<Component *> net);
  void set_nodes_to_zero(std::vector<Node *> nodes);
private:
};
