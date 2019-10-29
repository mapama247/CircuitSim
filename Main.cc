#include <iostream>
#include <vector>
#include "Component.h"
using namespace std;

int main(int argc, char *argv[])
{
    int iterations{};
    int print_lines{};
    double time_step{};
    double battery_voltage{};

    if (argc < 5)
    {
        cerr << "Error: Not enough arguments given" << endl;
        cerr << "Usage: a.out [integer] [integer] [double] [double]" << endl;
        exit(EXIT_FAILURE);
    }
    else if (argc > 1)
    {
        try
        {
            iterations = stoi(argv[1]);
            print_lines = stoi(argv[2]);
            time_step = stod(argv[3]);
            battery_voltage = stod(argv[4]);
        }
        catch (exception &e)
        {
            cerr << "Error: Wrong arguments" << endl;
            cerr << "Usage: a.out [integer] [integer] [double] [double]" << endl;
            exit(EXIT_FAILURE);
        }
    }

    if (iterations < 0 || print_lines < 0 || time_step < 0 || battery_voltage < 0)
    {
        cout << "Wrong arguments" << endl;
        exit(EXIT_FAILURE);
    }

    vector<Node *> nodes;
    
    Node *p = new Node{0.0};
    nodes.push_back(p);
    Node *l = new Node{0.0};
    nodes.push_back(l);
    Node *r = new Node{0.0};
    nodes.push_back(r);
    Node *n = new Node{0.0};
    nodes.push_back(n);

    Circuit * circuit1 = new Circuit();
    vector<Component *> net1;
    net1.push_back(new Battery{"BAT", p, n, battery_voltage});
    net1.push_back(new Resistor{"R1", p, l, 6.0});
    net1.push_back(new Resistor{"R2", l, r, 4.0});
    net1.push_back(new Resistor{"R3", r, n, 8.0});
    net1.push_back(new Resistor{"R4", l, n, 12.0});
    circuit1 -> simulate(net1, iterations, print_lines, time_step);
    circuit1 -> set_nodes_to_zero(nodes);
    circuit1 -> deallocate_components(net1);
    delete circuit1;

    Circuit * circuit2 = new Circuit();
    vector<Component *> net2;
    net2.push_back(new Battery{"BAT", p, n, battery_voltage});
    net2.push_back(new Resistor{"R1", p, l, 150.0});
    net2.push_back(new Resistor{"R2", p, r, 50.0});
    net2.push_back(new Resistor{"R3", l, r, 100.0});
    net2.push_back(new Resistor{"R4", l, n, 300.0});
    net2.push_back(new Resistor{"R5", r, n, 250.0});
    circuit2 -> simulate(net2, iterations, print_lines, time_step);
    circuit2 -> set_nodes_to_zero(nodes);
    circuit2 -> deallocate_components(net2);
    delete circuit2;

    Circuit * circuit3 = new Circuit();
    vector<Component *> net3;
    net3.push_back(new Battery{"BAT", p, n, battery_voltage});
    net3.push_back(new Resistor{"R1", p, l, 150.0});
    net3.push_back(new Resistor{"R2", p, r, 50.0});
    net3.push_back(new Capacitor{"C3", r, l, 1.0});
    net3.push_back(new Resistor{"R4", l, n, 300.0});
    net3.push_back(new Capacitor{"C5", r, n, 0.75});
    circuit3 -> simulate(net3, iterations, print_lines, time_step);
    circuit3 -> set_nodes_to_zero(nodes);
    circuit3 -> deallocate_components(net3);
    delete circuit3;

    delete p;
    delete n;
    delete l;
    delete r;

    return 0;
}