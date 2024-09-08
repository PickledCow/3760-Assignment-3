#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <string>

#include <Circuit.hpp>

// Goes through each line of the input file and interprets it.
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
class C_Interpreter {
    public:
    C_Interpreter();

    // Parses and acts upon the next line of the file,
    // Returns 0 if there are more lines, and 1 if it reaches the end
    int parse_next_line();

    private:
    // Helper function for converting between user strings and ELogicLevel
    ELogicLevel convert_logic_level(std::string const& p_string);

    // Helper function for converting between user strings and EComponentType
    EComponentType convert_gate_type(std::string const& p_string);

    // A circuit object to keep track of the different components
    C_Circuit* circuit;
};

#endif