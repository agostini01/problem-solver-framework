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

#ifndef SteepestDescentSolver_H
#define SteepestDescentSolver_H

#include "../solver.h"
#include "../problem.h"
#include "../solutioncontainer.h"
#include <vector>
#include <memory>
#include <ctime>

class SteepestDescentSolver : public Solver
{
public:
	SteepestDescentSolver(
	        std::vector<std::shared_ptr<Problem>>& problems,
	        std::vector<std::shared_ptr<SolutionContainer>>& solutions,
	        long long & max_solver_time
	        );

	std::shared_ptr<SolutionContainer> Solve(std::shared_ptr<Problem> the_problem);
	void SolveAll();


private:

	void StartTimer();
	long long GetDuration() const;
	long long StopTimer() const;

	time_t m_start_time;
	std::vector<std::shared_ptr<Problem>> &m_problems;
	std::vector<std::shared_ptr<SolutionContainer>>&m_solutions;

	long long m_max_sim_time;


	void PrintProblemWeights(const std::list<unsigned int> &problem_weights);
};



#endif // SteepestDescentSolver_H
