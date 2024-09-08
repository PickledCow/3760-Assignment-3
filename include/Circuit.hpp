#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <vector>
#include <map>
#include <string>

#include <Component.hpp>

// Class for housing different components
class C_Circuit {
    public:
    void add_component(C_Component* p_component, std::string p_name);
    
    void connect_component_output_to_component_input(std::string p_out_name, std::string p_in_name, int p_input_index);

    void drive_compontent_input(std::string p_name, int p_input_index, ELogicLevel p_logic_level);

    ELogicLevel get_component_output(std::string p_name);

    private:
    C_Component* get_component_from_string(std::string p_name);

    int component_count = 0;
    std::vector<C_Component*> components;
    std::map<std::string, int> component_index_map;
};

#endif