#include <iostream> 
#include <iomanip> 
#include <string>
#include <limits>
#include <vector>
#include <iostream> 
#include "Component.h"
using namespace std;

Node::Node(double voltage):voltage{voltage} {}

Circuit::Circuit(){}

Component::Component(string const& name, Node *p, Node *n):name{name}, p{p}, n{n} {}

Component::~Component(){
    cout << "DES" << endl;
}


Battery::Battery(string const& name, Node *p, Node *n, double const& volt)
:Component (name,p,n){
    voltage = volt;
}

Resistor::Resistor(string const& name, Node *p, Node *n, double const& res)
:Component (name,p,n){
    resistance = res;
}

Capacitor::Capacitor(string const& name, Node *p, Node *n, double const& cap)
:Component (name,p,n){
    capacitance = cap;
}

double Node::getVoltage(){
    return voltage;
}

void Node::setVoltage(double v){
    voltage = v;
}

string Component::getName(){
    return name;
}

double Resistor::getResistance(){
    return resistance;
}

double Capacitor::getCapacitance(){
    return capacitance;
}

double Battery::move_charge(double time_step){ 
    p -> setVoltage(voltage);
    n -> setVoltage(0.0);
    return voltage;
}

double Resistor::move_charge(double time_step){
    double x = abs((p -> getVoltage() - n -> getVoltage()))* time_step / resistance;
    if(p -> getVoltage() > n -> getVoltage() ){
        p -> setVoltage(p -> getVoltage() - x);
        n -> setVoltage(n -> getVoltage() + x);
        return p -> getVoltage() - n -> getVoltage();
    }
    else{
        p -> setVoltage(p -> getVoltage() + x);
        n -> setVoltage(n -> getVoltage() - x);
        return n -> getVoltage() - p -> getVoltage();
    }
}

double Capacitor::move_charge(double time_step){
    if(p -> getVoltage() > n -> getVoltage() ){
        double x = (p -> getVoltage() - n -> getVoltage() - stored_charge) * time_step * capacitance;
        stored_charge = stored_charge + x;
        p -> setVoltage(p -> getVoltage() - x);
        n -> setVoltage(n -> getVoltage() + x);
        return p -> getVoltage() - n -> getVoltage();
    }
    else{
        double x = (n -> getVoltage() - p -> getVoltage() - stored_charge) * time_step * capacitance;
        stored_charge = stored_charge + x;
        p -> setVoltage(p -> getVoltage() + x);
        n -> setVoltage(n -> getVoltage() - x);
        return n -> getVoltage() - p -> getVoltage();
    }
}

double Battery::getCurrent(double time_step){
    return 0.0;
}

double Resistor::getCurrent(double time_step){
    return move_charge(time_step) / getResistance();
}

double Capacitor::getCurrent(double time_step){
    return  abs((p -> getVoltage() - n -> getVoltage() - stored_charge)) * getCapacitance();
}

void Circuit::simulate (vector<Component*> net, int iterations, int lines, double time_step){
    cout << setw(12);
    for(int x = 0; x < net.size(); x++){
        cout << net.at(x) -> getName() << setw(14) << "";
    }
    cout << endl;
    cout <<  " ";
    for(int s = 0; s < net.size(); s++){
        cout << "Volt" << setw(8) << "Curr" << setw(4) << "";
    }
    cout << endl;

    for(int i = 1; i <= iterations; i++){
        for(int j = 0; j < net.size(); j++){
            if(i%(iterations/lines)==0)
                cout << setprecision(2) << fixed << net.at(j) -> move_charge(time_step) << setprecision(2) << setw(7) << net.at(j) -> getCurrent(time_step) << setw(5) << "";
            else
                net.at(j) -> move_charge(time_step);
        }
        if(i%(iterations/lines)==0)
            cout << endl;
    }

    cout << endl;
}

void Circuit::deallocate_components(vector<Component *> net){
    for(int i = 0; i < net.size(); i++){
        delete net.at(i);
    }
}

void Circuit::set_nodes_to_zero(vector<Node *> nodes){
    for(int j = 0; j < nodes.size(); j++){
        nodes.at(j) -> setVoltage(0.0);
    }
}