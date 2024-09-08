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

#include <Interpreter.hpp>

// Main loop
int main() {
	C_Interpreter interpreter = C_Interpreter();
	while (true) {
		if (interpreter.parse_next_line()) break;
	}
  
  return 0;
}
