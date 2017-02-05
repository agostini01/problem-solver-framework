/*
 *  Problem Solver
 *  Copyright (C) 2017  Nicolas Agostini (n.b.agostini@gmail.com)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include <iostream>
#include <sys/time.h>
#include <memory>
#include <vector>

#include "core/problemgenerator.h"
#include "core/problem.h"
#include "core/solution.h"
#include "util/util.h"
#include "util/fileio.h"
#include "core/binpacking/exhaustivesolver.h"






#include "../lib/cpp/Terminal.h"
#include "../lib/cpp/String.h"
#include "../lib/cpp/Error.h"
#include "../lib/cpp/Misc.h"
#include "../lib/cpp/CommandLine.h"

#define VERSION "0.1.0v"

////////////////////////////////////////////////////////////////////////////////
// Configuration options
////////////////////////////////////////////////////////////////////////////////

bool binary_hex_dump=0;

////////////////////////////////////////////////////////////////////////////////
// Variable declarations
////////////////////////////////////////////////////////////////////////////////

/// Container to hold instances of problems
std::vector<std::shared_ptr<Problem>> g_my_problems;

/// Container to hold instances of solutions
std::vector<std::shared_ptr<Solution>> g_my_solutions;

////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

/// Print welcome message
void WelcomeMessage(std::ostream &os) {   
    // Compute simulation ID
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned min_id = misc::StringAlnumToInt("10000");
    unsigned max_id = misc::StringAlnumToInt("ZZZZZ");
    unsigned id = (tv.tv_sec * 1000000000 + tv.tv_usec)
            % (max_id - min_id + 1)
            + min_id;
    std::string alnum_id = misc::StringIntToAlnum(id);

    // Blue color
    misc::Terminal::Blue(os);

    // Print welcome message in the standard error output
    os << '\n' << "; Problem Solver " << VERSION << " \n";
    os << "; Please use command 'main --help' for a list of command-line options.\n";
    os << "; Simulation alpha-numeric ID: " << alnum_id << '\n';
    os << '\n';
    // Reset terminal color
    misc::Terminal::Reset(os);
}

/// Read command line
void RegisterOptions(){
    // Parse the command line and set flags or file output names

    // Set error message
    misc::CommandLine *command_line = misc::CommandLine::getInstance();
    command_line->setErrorMessage("\nPlease type 'main --help' for a list of "
                                  "valid main command-line options.");

    // Set help message
    command_line->setHelp("Syntax:"
                          "\n\n"
                          "$ main [<options>]"
                          "\n\n"
                          "main's command line can take arguments "
                          "The following list of command-line options can be used "
                          "for <options>:");

    //
    // General Problem Solver Options
    //

    // Set category for following options
    command_line->setCategory("default", "General Problem Solver Options");

    // Help message for memory system
        command_line->RegisterBool("--binary-hex-dump",
                                   binary_hex_dump,
                                   "Print the binary file in hex format"
                                   );
}

/// Process command line
void ProcessOptions(){

}

/// Main simulation loop
int MainLoop(){

  FileIO file_io;

  ProblemGenerator problem_generator(g_my_problems);
  problem_generator.GetProblemsFromListOfFiles("../res/list_of_files.txt");

  std::cerr<<"Number of instances: "<< g_my_problems.size()<<std::endl;
  for (auto it = g_my_problems.begin(); it != g_my_problems.end(); ++it)
  {
    std::cerr<<(*it)->ToString()<<std::endl<<std::endl<<std::endl;
  }

  ExhaustiveSolver problem_solver(g_my_problems, g_my_solutions);
  //problem_solver.Solve(*g_my_problems.begin()); // To solve only the first problem
  problem_solver.SolveAll();

}

/// Dump statistics
void DumpReports(){

}

/// Main loop
int MainProgram(int argc, char **argv){

    // Print welcome message in standard error output
    WelcomeMessage(std::cerr);

    // Read command line
    RegisterOptions();
    misc::CommandLine *command_line = misc::CommandLine::getInstance();
    command_line->Process(argc, argv, false);

    // Process command line
    ProcessOptions();

    // Main simulation loop
    MainLoop();

    DumpReports();

    // Success
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Main loop
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
    // Main exception handler
    try {
        // Run main program
        return MainProgram(argc, argv);
    } catch (misc::Exception &e) {
        e.Dump();
        return 1;
    }
}
