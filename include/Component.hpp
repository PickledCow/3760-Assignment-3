#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>

// Values that a component can be driven at. Can be low, high, or undefined.
// Undefined values should propogate through the circuit.
enum ELogicLevel { LOGIC_UNDEFINED = -1, LOGIC_LOW, LOGIC_HIGH };

// Type of component for use during construction
enum EComponentType { TYPE_UNDEFINED = -1, WIRE, NOT_GATE, AND_GATE, OR_GATE, XOR_GATE };

// Components are the building blocks of circuits
// They can take in any number of inputs and have one output that can drive any number of other compontents' inputs
class C_Component {
    public:
    C_Component(EComponentType p_type);

    // Takes in a pointer to a component and the index to drive and registers it to be driven when updated
    void connect_output_to_component_input(C_Component *p_component, int p_input_index);

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