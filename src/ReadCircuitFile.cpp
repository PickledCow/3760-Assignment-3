// A realtime circuit simulator. Supports AND, OR, NOT, and XOR gates.
// Additional components are currently limited to 10 inputs max and 1 output.
//
// Current supported functions are:
// add: 		Adds a new component to the simulation
// connect: 	Connects two components output and input given component names and index
// drive: 		Manually sets the value of a component input
// query:		Reads and prints the output of a requested component
// Copyright (c) Donald Dansereau, 2023


#include <iostream>
#include <string>

#include <Component.hpp>
#include <Circuit.hpp>

// Forwards definition of helper functions

// Helper function for converting a string to ELogicLevel
ELogicLevel hash_logic_level(std::string const& p_string);

// Helper function for converting a string to EComponentType
EComponentType hash_gate_type(std::string const& p_string);

// Main loop
int main() {
	C_Circuit circuit = C_Circuit();
	while (true) {
		std::string Request;
		std::cin >> Request;  // get the next word from the input stream
		//std::cout << "Processing input token: " << Request << std::endl;

		if (Request[0] == '#') {
			// a comment line
			// get the rest of the line and ignore it
			std::string DummyVar;
			getline( std::cin, DummyVar );
		} else if (Request.compare( "add" ) == 0 ) {
			std::string GateType;
			std::string GateName;
			std::cin >> GateType;
			std::cin >> GateName;
			std::cout << "Adding gate of type " << GateType << " named " << GateName << std::endl;

			C_Component* component = new C_Component(hash_gate_type(GateType));
			
			circuit.add_component(component, GateName);

			std::cout << "Added component " << GateType << " with name \"" << GateName << "\"" << std::endl;

		} else if (Request.compare( "connect" ) == 0) {
			std::string OutName;
			std::string InName;
			std::string InputIndexString;
			std::cin >> OutName;
			std::cin >> InName;
			std::cin >> InputIndexString;

			int inputIndex = InputIndexString[0] - '0';

			circuit.connect_component_output_to_component_input(OutName, InName, inputIndex);

			std::cout << "Gate \"" << OutName << "\" connected to Gate \"" << InName << "\" at input index " << InputIndexString << std::endl;

		} else if (Request.compare( "drive" ) == 0) {
			
			std::string GateName;
			std::string InputIndexString;
			std::string DriveLevelString;
			std::cin >> GateName;
			std::cin >> InputIndexString;
			std::cin >> DriveLevelString;

			int inputIndex = InputIndexString[0] - '0';
			ELogicLevel driveLevel = hash_logic_level(DriveLevelString);

			circuit.drive_compontent_input(GateName, inputIndex, driveLevel);

			std::cout << "Driving gate \"" << GateName << "\" at input " << inputIndex << " with value " << DriveLevelString << std::endl;

		} else if (Request.compare( "query" ) == 0) {
			std::string GateName;
			std::cin >> GateName;

			ELogicLevel output_level = circuit.get_component_output(GateName);

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
		}

		else if( Request.compare( "end" ) == 0 ) {
			break; // end of file
		} else {
			std::cout << "Unrecognised command " << Request << std::endl;
			std::cout << "Continuing to next line" << std::endl;
			// get the rest of the line and ignore it
			std::string DummyVar;
			getline( std::cin, DummyVar );
		}
	}
  
  return 0;
}


// Helper function implementations

ELogicLevel hash_logic_level(std::string const& p_string) {
    if (p_string == "LOW") return LOGIC_LOW;
    else if (p_string == "HIGH") return LOGIC_HIGH;
    else return LOGIC_UNDEFINED;
}

EComponentType hash_gate_type(std::string const& p_string) {
    if (p_string == "wire") return WIRE;
    else if (p_string == "not") return NOT_GATE;
    else if (p_string == "and") return AND_GATE;
    else if (p_string == "or") return OR_GATE;
    else if (p_string == "xor") return XOR_GATE;
    else return TYPE_UNDEFINED;
}