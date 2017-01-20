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

#include <exception>
#include <iostream>
#include <memory>
#include <vector>

#include "problemgenerator.h"
#include "problem.h"
#include "solution.h"
#include "util.h"

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
  // Print welcome message in the standard error output
  os << '\n' << "; Problem Solver " << " - VERSION";
  os << '\n';
  os << '\n';
}

/// Read command line
void RegisterOptions(){

}

/// Process command line
void ProcessOptions(){

}

/// Main simulation loop
int MainLoop(){

  ProblemGenerator problem_generator(g_my_problems);
  problem_generator.GetProblem(100);
  problem_generator.GetProblem(100);
  problem_generator.GetProblem(100);

  //std::cout<<g_my_problems.size()<<std::endl;
  for (auto it = g_my_problems.begin(); it != g_my_problems.end(); ++it)
  {
    std::cerr<<(*it)->ToString()<<std::endl<<std::endl<<std::endl;
  }

}

/// Dump statistics
void DumpReports(){

}

/// Main loop
int MainProgram(int argc, char **argv){
  WelcomeMessage(std::cerr);

  RegisterOptions();

  ProcessOptions();

  MainLoop();

  DumpReports();

  // Success
}

////////////////////////////////////////////////////////////////////////////////
// Main loop
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
  // Main exception handler
  try {
    // Run main program
    return MainProgram(argc, argv);
  } catch (std::exception &e) {
    std::cerr << e.what();
    return 1;
  }
}
