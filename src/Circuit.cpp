#include <Circuit.hpp>


void C_Circuit::add_component(C_Component* p_component, std::string p_name) {
    components.push_back(p_component);
    component_index_map[p_name] = component_count;
    component_count++;
}

// --------------------

void C_Circuit::connect_component_output_to_component_input(std::string p_out_name, std::string p_in_name, int p_input_index) {
    C_Component* o = get_component_from_string(p_out_name);
    C_Component* i = get_component_from_string(p_in_name);
    o->connect_output_to_component_input(i, p_input_index);
}

// --------------------

void C_Circuit::drive_compontent_input(std::string p_name, int p_input_index, ELogicLevel p_logic_level) {
    C_Component* comp = get_component_from_string(p_name);
    comp->drive_input(p_input_index, p_logic_level);
}

// --------------------

ELogicLevel C_Circuit::get_component_output(std::string p_name) {
    C_Component* comp = get_component_from_string(p_name);
    return comp->get_output();
}

// --------------------

ELogicLevel C_Component::convert_logic_level(std::string const& p_string) {
    if (p_string == "LOW") return LOGIC_LOW;
    else if (p_string == "HIGH") return LOGIC_HIGH;
    else return LOGIC_UNDEFINED;
}

// --------------------

EComponentType C_Component::convert_gate_type(std::string const& p_string) {
    if (p_string == "wire") return WIRE;
    else if (p_string == "not") return NOT_GATE;
    else if (p_string == "and") return AND_GATE;
    else if (p_string == "or") return OR_GATE;
    else if (p_string == "xor") return XOR_GATE;
    else return TYPE_UNDEFINED;
}

// --------------------

C_Component* C_Circuit::get_component_from_string(std::string p_name) {
    return components[component_index_map[p_name]];
}

// --------------------
