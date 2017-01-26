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

#include "exhaustivesolver.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "binpackingsolution.h"

#include "util.h" // factorial()

ExhaustiveSolver::ExhaustiveSolver(
  std::vector<std::shared_ptr<Problem>>& problems,
  std::vector<std::shared_ptr<Solution>>& solutions)
  : m_problems(problems)
  , m_solutions(solutions)
  , m_start_time(0)
{

}

void ExhaustiveSolver::PrintProblemWeights(
        const std::list<unsigned int>& problem_weights)
{
    for (auto it=problem_weights.begin();
         it != problem_weights.end(); ++it)
    {
        std::cerr << *it << ' ';
    }
    std::cerr << std::endl;
}

std::shared_ptr<Solution> ExhaustiveSolver::Solve(std::shared_ptr<Problem> the_problem)
{

    // Variables used to create a solution
    // Everything is passed by copy (not by reference)
    unsigned int bucket_capacity =  the_problem->GetMaxSizeOfBucket();
    unsigned int max_number_of_buckets =  the_problem->GetMaxNumberOfBucketsK();
    unsigned int problem_id = the_problem->GetProblemId();
    std::list<unsigned int> problem_weights =  the_problem->GetWeights();

    // Shared solution that will be added to the list of solutions
    std::shared_ptr<BinPackingSolution> the_solution = std::make_shared<BinPackingSolution>();


    // Just for the sake of sanity: printing Everything
    std::cerr<<std::endl;
    std::cerr<<std::endl;
    std::cerr<<std::endl;
    std::cerr<<"====================================================="<<std::endl;
    std::cerr<<"=================Starting Solution=================="<<std::endl;
    std::cerr<< "Problem id: " << problem_id<<'\n';
    std::cerr<< "Max Size of Bucket: " << bucket_capacity<<'\n';
    std::cerr<< "Target number of buckets: " << max_number_of_buckets<<'\n';

    std::cerr<< "Item weights: \n";

    // Start timing the solution
    StartTimer();
    do { // This body will execute once for each permutation

        // Create the variables to store a solution
        std::vector<Bin> list_of_bins;
        list_of_bins.push_back(Bin(bucket_capacity));

        // Print can be removed later
        PrintProblemWeights(problem_weights);

        // Try to fit weights inside the bins
        for (std::list<unsigned int>::iterator it=problem_weights.begin();
             it != problem_weights.end(); ++it)
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

        // We have a possible solution here in list_of_bins

        the_solution->Check(list_of_bins,list_of_bins.size(), GetDuration());

        std::cerr << "Fit in " << list_of_bins.size() << " Bins." << std::endl;
        for (auto it = list_of_bins.begin(); it!=list_of_bins.end();++it)
        {
            (*it).PrintContents();
        }
        std::cerr<<std::endl;
    } while (std::next_permutation(problem_weights.begin(), problem_weights.end()));
    std::cerr<<std::endl;
    std::cerr<<std::endl;
    std::cerr<<"-----------------------------------------------------"<<std::endl;

    // TODO REMOVE!!! EXAMPLE ON HOW TO DO PERMUTATION
    // PermuteList(problem_weights);
    // TODO REMOVE!!! EXAMPLE ON HOW TO DO PERMUTATION


    // TODO MATAN - Execute Algorithm
    // TODO MATAN - Implement Timing
    // TODO MATAN - As we have talked, we should keep track of all the best
    // To do that, we will have to use nested containers.
    // I was thinking that the possible solution should be a
    //    list (or vector) of X optimal lists (or vectors) of K lists (or vectors)
    //                           - one for each bucket - that contain the weights.
    // std::list< std::list< std::list< unsigned int > > > optimal_solutions_list
    // std::list< std::list<unsigned int > >            a_optimal_solution_with_k_buckets
    // std::list< unsigned int > >                      weights_in_a_bucket

    // ps. In old c we could not have <<<>>> with spaces in between.

    // TODO MATAN - You can change the order of the files in
    //              root/res/list_of_files.txt, to select a simple instance

    // TODO Solution class is not ready yet. I can implement it later,
    return the_solution;
}

void ExhaustiveSolver::SolveAll()
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

}

void ExhaustiveSolver::StartTimer()
{
    time(&m_start_time);
}

long long ExhaustiveSolver::GetDuration() const
{
    return difftime(time(0),m_start_time);
}

long long ExhaustiveSolver::StopTimer() const
{
    return GetDuration();
}
