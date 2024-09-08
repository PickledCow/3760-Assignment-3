// A realtime circuit simulator. Supports AND, OR, NOT, and XOR gates.
// Additional components are currently limited to 10 inputs max and 1 output.
//
// Current supported functions are:
// add <type> <name>
//		Adds a new component to the simulation with the requested type and name
//
// connect <output component name> <input component name> <input index>
//		Connects two components output and input given component names and index
//
// drive <component name> <logic value>
//		Manually sets the value of a component input
//
// query <component name>
//		Reads and prints the output of a requested component
//
// end
//		Ends the simulation and closes the program
// 
//
// Copyright (c) Donald Dansereau, 2023; Joon Suh, 2024


#include <iostream>
#include <string>

#include <Component.hpp>
#include <Circuit.hpp>

// Main loop
int main() {
	C_Circuit circuit = C_Circuit();
	while (true) {
		std::string Request;
		std::cin >> Request;  // get the next word from the input stream

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

			C_Component* component = new C_Component(circuit.convert_gate_type(GateType));
			
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
			ELogicLevel driveLevel = circuit.convert_logic_level(DriveLevelString);

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
