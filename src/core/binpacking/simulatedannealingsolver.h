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

#ifndef SimulatedAnnealingSolver_H
#define SimulatedAnnealingSolver_H

#include "../solver.h"
#include "../problem.h"
#include "../solutioncontainer.h"
#include <vector>
#include <memory>
#include <ctime>

class SimulatedAnnealingSolver : public Solver
{
public:
	SimulatedAnnealingSolver(
	        std::vector<std::shared_ptr<Problem>>& problems,
	        std::vector<std::shared_ptr<SolutionContainer>>& solutions,
	        long long & max_solver_time
	        );

	std::shared_ptr<SolutionContainer> Solve(std::shared_ptr<Problem> the_problem);

    bool IsSameSolutionAsBefore(const std::list<unsigned int> & weights_a,const std::list<unsigned int> & weights_b);

	void SolveAll();


    void setRandomized_input(bool randomized_input);

	void SetNumberOfSteps(const unsigned & number_of_temperature_steps)
	{
	 m_number_of_temperature_steps = number_of_temperature_steps;
	}

private:

    void StartTimer();
    long long GetDuration() const;
	long long StopTimer() const;

	time_t m_start_time;
	std::vector<std::shared_ptr<Problem>> &m_problems;
	std::vector<std::shared_ptr<SolutionContainer>>&m_solutions;

	long long m_max_sim_time;

    bool m_randomized_input;

	unsigned m_number_of_temperature_steps;


	void PrintProblemWeights(const std::list<unsigned int> &problem_weights);
};



#endif // SimulatedAnnealingSolver_H
