#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>

// Values that a component can be driven at. Can be low, high, or undefined.
// Undefined values should propogate through the circuit.
enum ELogicLevel { LOGIC_UNDEFINED = -1, LOGIC_LOW, LOGIC_HIGH };

// Type of component for use during construction
enum EComponentType { TYPE_UNDEFINED = -1, WIRE, NOT_GATE, AND_GATE, OR_GATE, XOR_GATE };

// Helper function for converting a string to EComponentType
EComponentType str_hash(std::string const& p_string) {
    if (p_string == "wire") return WIRE;
    else if (p_string == "not") return NOT_GATE;
    else if (p_string == "and") return AND_GATE;
    else if (p_string == "or") return OR_GATE;
    else if (p_string == "xor") return XOR_GATE;
    else return TYPE_UNDEFINED;
}

// Components are the building blocks of circuits
// They can take in any number of inputs and have one output that can drive any number of other compontents' inputs
class C_Component {
    public:
    C_Component(EComponentType p_type);

    // Takes in a pointer to a component and the index to drive (default 0) and registers it to be driven when updated
    void connect_output_to_component_input(C_Component *p_component, int p_input_index = 0);

    // Changes the desired input value and updates the output
    void drive_input(int p_input_index, ELogicLevel p_logic_level);
    
    // Reports the current output value of a specific output pin
    ELogicLevel get_output();


    protected:
    // Update the output value with respect to the current input values
    void recalculate_output();

    // Drive any component inputs connected to this component's output pin
    // Called after recalculating output 
    void drive_output();

    // Mode of operation for determining output
    EComponentType mode = TYPE_UNDEFINED;

    // Number of input gates 
    int input_count = 0;
    // Array of the current input values
    std::vector<ELogicLevel> input_values;
    // Current output value
    ELogicLevel output_value = LOGIC_UNDEFINED;
    // Number of connections made to the output pin
    int connection_count = 0;
    // Array of the components to drive
    std::vector<C_Component*> connected_components;
    // Input index of the input on the connected component to drive
    std::vector<int> connection_input_indices;
    


};

#endif