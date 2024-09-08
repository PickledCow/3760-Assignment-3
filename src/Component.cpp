#include <Component.hpp>

C_Component::C_Component(EComponentType p_type) {
    mode = p_type;

    switch (p_type) {
        case WIRE:
            input_count = 1;
            input_values.resize(1, LOGIC_UNDEFINED);
            break;
        case NOT_GATE:
            input_count = 1;
            input_values.resize(1, LOGIC_UNDEFINED);
            break;
        case AND_GATE:
            input_count = 2;
            input_values.resize(2, LOGIC_UNDEFINED);
            break;
        case OR_GATE:
            input_count = 2;
            input_values.resize(2, LOGIC_UNDEFINED);
            break;
        case XOR_GATE:
            input_count = 2;
            input_values.resize(2, LOGIC_UNDEFINED);
            break;
        
        default:
            break;
    }
}

// --------------------

void C_Component::connect_output_to_component_input(C_Component *p_component, int p_input_index) {
    connected_components.push_back(p_component);
    connection_input_indices.push_back(p_input_index);
    connection_count++;
}

// --------------------

void C_Component::drive_input(int p_input_index, ELogicLevel p_logic_level) {
    input_values[p_input_index] = p_logic_level;
    recalculate_output();
}

// --------------------

ELogicLevel C_Component::get_output() {
    return output_value;
}

// --------------------

void C_Component::recalculate_output() {
    switch (mode) {
        case WIRE:
            output_value = input_values[0];

            break;
        case NOT_GATE:
            if (input_values[0] == LOGIC_UNDEFINED) {
                output_value = LOGIC_UNDEFINED;
            } else if (input_values[0] == LOGIC_LOW) {
                output_value = LOGIC_HIGH;
            } else {
                output_value = LOGIC_LOW;
            }

            break;
        case AND_GATE:
            if (input_values[0] == LOGIC_UNDEFINED || input_values[1] == LOGIC_UNDEFINED) {
                output_value = LOGIC_UNDEFINED;
            } else if (input_values[0] == LOGIC_HIGH && input_values[1] == LOGIC_HIGH) {
                output_value = LOGIC_HIGH;
            } else {
                output_value = LOGIC_LOW;
            }

            break;
        case OR_GATE:
            if (input_values[0] == LOGIC_UNDEFINED || input_values[1] == LOGIC_UNDEFINED) {
                output_value = LOGIC_UNDEFINED;
            } else if (input_values[0] == LOGIC_HIGH || input_values[1] == LOGIC_HIGH) {
                output_value = LOGIC_HIGH;
            } else {
                output_value = LOGIC_LOW;
            }
            
            break;
        case XOR_GATE:
            if (input_values[0] == LOGIC_UNDEFINED || input_values[1] == LOGIC_UNDEFINED) {
                output_value = LOGIC_UNDEFINED;
            } else if (input_values[0] !=  input_values[1]) {
                output_value = LOGIC_HIGH;
            } else {
                output_value = LOGIC_LOW;
            }
            
            break;
        
        default:
            output_value = LOGIC_UNDEFINED;
    }

    drive_output();
}

// --------------------


void C_Component::drive_output() {
    for (int i = 0; i < connection_count; ++i) {
        connected_components[i]->drive_input(connection_input_indices[i], output_value);
    }
}

// --------------------
