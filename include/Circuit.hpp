#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <vector>
#include <unordered_map>
#include <string>

#include <Component.hpp>

// Class for housing and managing C_Component objects
class C_Circuit {
    public:

    // Registers a new component to the circuit that can be later accessed with a stringname
    void add_component(C_Component* p_component, std::string p_name);
    
    // Connects the output of one component to the input of another given stringnames and input index
    void connect_component_output_to_component_input(std::string p_out_name, std::string p_in_name, int p_input_index);

    // Manually drives an input pin of a component given its stringname and the index of the input pin to drive
    void drive_compontent_input(std::string p_name, int p_input_index, ELogicLevel p_logic_level);

    // Returns the current output value of a component given its stringname
    ELogicLevel get_component_output(std::string p_name);

    private:
    // Internal function for getting the C_Component object pointer from a stringname
    C_Component* get_component_from_string(std::string p_name);

    // Number of components currently present in the circuit
    int component_count = 0;
    // List to house components defined by the user
    std::vector<C_Component*> components;
    // An unordered map for converting between a stringname and index of where the object is stored
    std::unordered_map<std::string, int> component_index_map;
};

#endif