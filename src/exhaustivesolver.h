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

#ifndef EXHAUSTIVESOLVER_H
#define EXHAUSTIVESOLVER_H

#include "solver.h"
#include "problem.h"
#include "solution.h"
#include <vector>
#include <memory>

class ExhaustiveSolver : public Solver
{
public:
  ExhaustiveSolver(
    std::vector<std::shared_ptr<Problem>>& problems,
    std::vector<std::shared_ptr<Solution>>& solutions);

  std::shared_ptr<Solution> Solve(std::shared_ptr<Problem> the_problem);
  void SolveAll();
  

private:
  std::vector<std::shared_ptr<Problem>> &m_problems;
  std::vector<std::shared_ptr<Solution>>&m_solutions;
};

#endif // EXHAUSTIVESOLVER_H
