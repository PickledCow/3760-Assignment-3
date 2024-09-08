#include <Interpreter.hpp>

C_Interpreter::C_Interpreter() {
    circuit = new C_Circuit();
}

// --------------------

int C_Interpreter::parse_next_line() {
    std::string Request;
    std::cin >> Request;  // get the next word from the input stream

    if (Request[0] == '#') {
        // a comment line
        // get the rest of the line and ignore it
        std::string DummyVar;
        getline( std::cin, DummyVar );

    } else if (Request.compare( "add" ) == 0 ) { 
        // An add component line
        std::string GateType;
        std::string GateName;
        std::cin >> GateType;
        std::cin >> GateName;

        C_Component* component = new C_Component(convert_gate_type(GateType));
        
        circuit->add_component(component, GateName);

        std::cout << "Added component " << GateType << " with name \"" << GateName << "\"" << std::endl;

    } else if (Request.compare( "connect" ) == 0) {
        // A connect components line
        std::string OutName;
        std::string InName;
        std::string InputIndexString;
        std::cin >> OutName;
        std::cin >> InName;
        std::cin >> InputIndexString;

        int inputIndex = InputIndexString[0] - '0';

        circuit->connect_component_output_to_component_input(OutName, InName, inputIndex);

        std::cout << "Gate \"" << OutName << "\" connected to Gate \"" << InName << "\" at input index " << InputIndexString << std::endl;

    } else if (Request.compare( "drive" ) == 0) {
        // A drive component input line
        
        std::string GateName;
        std::string InputIndexString;
        std::string DriveLevelString;
        std::cin >> GateName;
        std::cin >> InputIndexString;
        std::cin >> DriveLevelString;

        int inputIndex = InputIndexString[0] - '0';
        ELogicLevel driveLevel = convert_logic_level(DriveLevelString);

        circuit->drive_compontent_input(GateName, inputIndex, driveLevel);

        std::cout << "Driving gate \"" << GateName << "\" at input " << inputIndex << " with value " << DriveLevelString << std::endl;

    } else if (Request.compare( "query" ) == 0) {
        // A query component output line
        std::string GateName;
        std::cin >> GateName;

        ELogicLevel output_level = circuit->get_component_output(GateName);

        std::string outputString;

        switch (output_level)
        {
        case LOGIC_LOW:
            outputString = "LOW";
            break;
        case LOGIC_HIGH:
            outputString = "HIGH";
            break;
        
        default:
            outputString = "UNDEFINED";
            break;
        }

        std::cout << "Output at gate \"" << GateName << "\" is " << outputString << std::endl;

    } else if( Request.compare( "end" ) == 0 ) {
        // End of simulation line, returns signalling to end the script
        return 1;

    } else {
        std::cout << "Unrecognised command " << Request << std::endl;
        std::cout << "Continuing to next line" << std::endl;
        // get the rest of the line and ignore it
        std::string DummyVar;
        getline( std::cin, DummyVar );

    }

    return 0;
}

// --------------------

ELogicLevel C_Interpreter::convert_logic_level(std::string const& p_string) {
    if (p_string == "LOW") return LOGIC_LOW;
    else if (p_string == "HIGH") return LOGIC_HIGH;
    else return LOGIC_UNDEFINED;
}

// --------------------

EComponentType C_Interpreter::convert_gate_type(std::string const& p_string) {
    if (p_string == "wire") return WIRE;
    else if (p_string == "not") return NOT_GATE;
    else if (p_string == "and") return AND_GATE;
    else if (p_string == "or") return OR_GATE;
    else if (p_string == "xor") return XOR_GATE;
    else return TYPE_UNDEFINED;
}

// --------------------
