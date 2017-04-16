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

#include "simulatedannealingsolver.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <utility>
#include "../../util/util.h" // random gen

#include "binpackingsolution.h"
#include "binpackingneighborhood.h"

SimulatedAnnealingSolver::SimulatedAnnealingSolver(std::vector<std::shared_ptr<Problem>>& problems,
  std::vector<std::shared_ptr<SolutionContainer>>& solutions, long long &max_solver_time)
  : m_problems(problems)
  , m_solutions(solutions)
  , m_start_time(0)
  , m_randomized_input(false)
  , m_max_sim_time(max_solver_time)
{

}

void SimulatedAnnealingSolver::PrintProblemWeights(
        const std::list<unsigned int>& problem_weights)
{
	for (auto it=problem_weights.begin();
	     it != problem_weights.end(); ++it)
	{
		std::cerr << *it << ' ';
	}
	std::cerr << std::endl;
}

std::shared_ptr<SolutionContainer> SimulatedAnnealingSolver::Solve(std::shared_ptr<Problem> the_problem)
{

	// Variables used to create a solution
	// Everything is passed by copy (not by reference)
	unsigned int bucket_capacity =  the_problem->GetMaxSizeOfBucket();
	unsigned int max_number_of_buckets =  the_problem->GetMaxNumberOfBucketsK();
	unsigned int problem_id = the_problem->GetProblemId();
	std::list<unsigned int> problem_weights =  the_problem->GetWeights();
    std::list<unsigned int> last_problem_weights =  the_problem->GetWeights();

	// Shared solution that will be added to the list of solutions
	std::shared_ptr<BinPackingSolution> the_solution = std::make_shared<BinPackingSolution>();
	the_solution->setNumberOfCombinations(1); // Greedy runs only once

	// Just for the sake of sanity: printing Everything
	std::cerr<<std::endl;
	std::cerr<<std::endl;
	std::cerr<<std::endl;
	std::cout<<"====================================================="<<std::endl;
	std::cout<<"=================Starting Solution=================="<<std::endl;
	std::cout<< "Problem id: " << problem_id<<'\n';
	std::cout<< "Max Size of Bucket: " << bucket_capacity<<'\n';
	std::cout<< "Target number of buckets: " << max_number_of_buckets<<'\n';


	// Start timing the solution
	StartTimer();
    if(m_randomized_input)
    {
        std::vector<unsigned> v{ std::begin(problem_weights), std::end(problem_weights) };
        std::random_shuffle(v.begin(), v.end(),myrandom);
        problem_weights = std::list<unsigned> {std::begin(v), std::end(v)};
        std::cerr<< "Random weights: ";
        for (const auto & a: problem_weights)
            std::cerr<< a<<" ";
        std::cerr<< std::endl;
    }
    else // reverse sorted input
    {
        problem_weights.sort();
        problem_weights.reverse(); // Reverse sort those weights
        for (const auto & a: problem_weights)
            std::cerr<< a<<" ";
        std::cerr<< std::endl;
    }


	float k = 1;
	do {
        last_problem_weights = problem_weights;
		BinPackingNeighborhood current_neighborhood = BinPackingNeighborhood(problem_weights);

		for (BPNeighbor& current_neighbor : current_neighborhood.GetNeighborsList())
		{ // This body will execute once for each neighbor
			std::list<unsigned int> current_problem_weights = current_neighbor.GetProblemWeights();
			// Create the variables to store a solution
			std::vector<Bin> list_of_bins;
			list_of_bins.push_back(Bin(bucket_capacity));

			// Print can be removed later
			//PrintProblemWeights(current_problem_weights);

			// Try to fit weights inside the bins
			for (std::list<unsigned int>::iterator it=current_problem_weights.begin();
			     it != current_problem_weights.end(); ++it)
			{
				bool added = false;
				//std::cerr << "Attempting to place item: " << *it << ' ' << std::endl ;
				for (int i = 0 ; i < list_of_bins.size(); i++) {
					// std::cerr << "Bin #: " << i << " Current bin's size: " << list_of_bins[i].get_size() << std::endl;
					if (list_of_bins[i].AddItem(*it)) {
						added = true;
						break;
						// std::cerr <<  "Item Didn't fit" << std::endl;
					}
				}
				if (!added) {
					Bin new_bin = Bin(bucket_capacity);
					new_bin.AddItem(*it);
					list_of_bins.push_back(new_bin);
				}
			}


			//std::cout<<"*****Number of bins: "<< list_of_bins.size()<<std::endl;
			current_neighbor.SetBins(list_of_bins);

			// From now on all the neighbors are set and solutions have been calculated
			// We calculate the fitness and best fitnes to get our next champion

		}

		current_neighborhood.CalculateBestNeighboorFitness();
		std::vector<Bin> best_list_of_bins = current_neighborhood.GetNeighborBasedOnTemperature(k).GetBins();
		problem_weights = current_neighborhood.GetNeighborBasedOnTemperature(k).GetProblemWeights(); // Update the weight list for next iteration
		// We have a possible solution here in best_list_of_bins
		//std::cout << "Took: " << GetDuration()<< std::endl;
		std::cout<<"Best neighbor at: "<<current_neighborhood.GetBestPosition()<<
		           "\t Fitness: "<< current_neighborhood.GetBestFitness()<<std::endl;
		the_solution->Check(best_list_of_bins,best_list_of_bins.size(), GetDuration());

		std::cerr << "Fit in " << best_list_of_bins.size() << " Bins." << std::endl;
		for (auto it = best_list_of_bins.begin(); it!=best_list_of_bins.end()-1;++it)
		{
			it->PrintContents();
		}
		(best_list_of_bins.end()-1)->PrintContents();
		std::cerr<<std::endl;

		// Wrap up solution
		the_solution->IncPermutationsDone();


		// Reseting the neighborhood (must implement a RESET function)

        if (GetDuration()>m_max_sim_time)
		{
			std::cout<< "Run out of time"<<std::endl;
			the_solution->setFoundOptimal(false);
			break;
		}

		// This does not apply anymore for simulated annealing
//        if (IsSameSolutionAsBefore(problem_weights, last_problem_weights))
//        {
//            std::cout<< "Break out of loop because same solution as before"<<std::endl;
//            the_solution->setFoundOptimal(false);
//            break;
//        }

		if (k<=0)
		{
			std::cout<< "k = 0 and best fitness was selected"<<std::endl;
			the_solution->setFoundOptimal(false);
			break;
		}
		else // k is bigger than zero (temperature still exists)
		{
			k = k-K_DECREMENT; // Defined on simulatedannealing.h
		}

		//neighbor->solution = the_solution;

		//delete current_neighborhood;
	} while (true);
	std::cout<<std::endl;
	std::cout<<std::endl;
	std::cout<<"-----------------------------------------------------"<<std::endl;

	the_solution->setSecondsTaken(GetDuration());

	the_solution->PrintStatistics();

	return the_solution;
}

bool SimulatedAnnealingSolver::IsSameSolutionAsBefore(const std::list<unsigned int> &weights_a, const std::list<unsigned int> &weights_b)
{
    bool ret_value = true;
    std::list<unsigned int>::const_iterator it1 = weights_a.begin();
    std::list<unsigned int>::const_iterator it2 = weights_b.begin();
    do
    {
        if (*it1!=*it2)
        {
            ret_value = false;
            break;
        }
        ++it1;
        ++it2;

    } while (it1!=weights_a.end());

    if (ret_value)
        std::cout<<"Reached Local Maximal"<<std::endl;

    return ret_value;
}

void SimulatedAnnealingSolver::SolveAll()
{

    std::cerr<<std::endl;
    std::cerr<<std::endl;
    std::cerr<<std::endl;
    std::cerr<<"#####################################################"<<std::endl;
    std::cerr<<"=================Starting Solutions=================="<<std::endl;
    std::cerr<<"#####################################################"<<std::endl;

    for (auto it = m_problems.begin(); it != m_problems.end(); ++it)
    {
        // push back the solution for the problem
        m_solutions.push_back(Solve(*it));
    }

    //  for (auto it = m_solutions.begin(); it != m_solutions.end(); ++it)
//  {
//    // push back the solution for the problem
//    it->PrintStatistics();
//  }

}

void SimulatedAnnealingSolver::StartTimer()
{
	time(&m_start_time);
}

long long SimulatedAnnealingSolver::GetDuration() const
{
	return difftime(time(0),m_start_time);
}

long long SimulatedAnnealingSolver::StopTimer() const
{
	return GetDuration();
}

void SimulatedAnnealingSolver::setRandomized_input(bool randomized_input)
{
    m_randomized_input = randomized_input;
}

