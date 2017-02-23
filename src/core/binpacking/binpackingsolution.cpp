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

#include "binpackingsolution.h"
#include <iostream>
#include <iomanip>


void Bin::PrintContents() const
{
    std::cerr<<"Bin: ";
    for (auto it = m_items.begin(); it!=m_items.end();++it)
    {
		std::cerr<<std::setw(7)<<*it;
    }
    std::cerr<<std::endl;
}

void Bin::PrintContentsFormated() const
{
    std::cout<<"{";
    for (auto it = m_items.begin(); it!=m_items.end()-1;++it)
    {
        std::cout<<*it <<",";
    }
    std::cout << *(m_items.end()-1)<<"}";
}


bool Bin::AddItem(int item) {
  //std::cerr << "Current Size: " << curr_size << " Item size: " << item << " Max Size: " << max_size << std::endl;
  if (m_curr_size + item <= m_max_size) {
    m_items.insert(m_items.end(), item);
    m_curr_size+= item;
    return true;
  } else {
    return false;
  }
}

int Bin::GetMaxSize() {
  return m_curr_size;
}

Bin::Bin(int max_weight) {
  m_max_size = max_weight;
  m_curr_size = 0;
//  std::cerr << "Making new Bin. Max size: " << max_size << " Current size: " << curr_size << std::endl;
}

BinPackingSolution::BinPackingSolution()
    : m_seconds_taken(0)
    , m_permutations_done(0)
    , m_found_optimal(true)
    , m_best_n_of_bins(1000000)
{

}

long long BinPackingSolution::getSecondsTaken() const
{
    return m_seconds_taken;
}

void BinPackingSolution::setSecondsTaken(const long long& seconds_taken)
{
    m_seconds_taken = seconds_taken;
}

bool BinPackingSolution::getFoundOptimal() const
{
    return m_found_optimal;
}

void BinPackingSolution::setFoundOptimal(const bool& found_optimal)
{
    m_found_optimal = found_optimal;
}

void BinPackingSolution::IncPermutationsDone()
{
    ++m_permutations_done;
}

unsigned long long BinPackingSolution::getNumberOfCombinations() const
{
    return m_number_of_combinations;
}

void BinPackingSolution::setNumberOfCombinations(const long long &number_of_combinations)
{
    m_number_of_combinations = number_of_combinations;
}

FitType BinPackingSolution::GetFitType(const unsigned int &n_of_bins)
{
    if(n_of_bins>m_best_n_of_bins)
        return worse;
    else if (n_of_bins==m_best_n_of_bins)
        return equal;
    else
        return best;

}

void BinPackingSolution::Check(const std::vector<Bin> &possible_fit, const unsigned int &n_of_bins, const long long &seconds_taken)
{
    FitType type_of_fit= GetFitType(n_of_bins);

    switch(type_of_fit)
    {
    case best:
        // Clean the previous fits
        m_best_fits.clear();
        // update the fit
        m_best_n_of_bins = n_of_bins;
        // add the new one
        m_best_fits.push_back(BestFit(possible_fit,seconds_taken));
        break;
    case equal:
        // add to the fits
        // check if there are too many fits already
        if(m_best_fits.size()<10)
            m_best_fits.push_back(BestFit(possible_fit,seconds_taken));
        break;
    case worse:
        // ignore the fit
        break;
    }
}

void BinPackingSolution::PrintBestFits()
{
    for(auto outer_it = m_best_fits.begin(); outer_it!= m_best_fits.end();++outer_it)
    {
        std::cout << "{";
        std::vector<Bin> sol_bins = outer_it->bins();
        for (auto it = sol_bins.begin(); it!=sol_bins.end()-1;++it)
        {
            it->PrintContentsFormated();
            std::cout << ",";
        }
        (sol_bins.end()-1)->PrintContentsFormated();
        std::cout << "}\t"<<outer_it->SecondsTaken()<<std::endl;
    }
}

long long BinPackingSolution::getPermutationsDone() const
{
    return m_permutations_done;
}

void BinPackingSolution::PrintStatistics()
{
    /*unsigned int problem_id = the_problem->GetProblemId(); 
    unsigned int bucket_capacity =  the_problem->GetMaxSizeOfBucket();
    unsigned int max_number_of_buckets =  the_problem->GetMaxNumberOfBucketsK();

    std::cout<< "Problem id: " << problem_id<<'\n';
    std::cout<< "Max Size of Bucket: " << bucket_capacity<<'\n';
    std::cout<< "Target number of buckets: " << max_number_of_buckets<<'\n';*/
    // Total running time
    std::cout<<"Total running time: "<<getSecondsTaken()<<std::endl;
    // Permutatins total
    std::cout<<"Permutatins total: "<<getNumberOfCombinations()<<std::endl;
    // Permutations Covered
    std::cout<<"Permutations Covered: "<<getPermutationsDone()<<std::endl;
    // % of permutations
    std::cout<<"% of permutations: "<<(float)getPermutationsDone()/(float)getNumberOfCombinations() << std::endl;

    // optimal solutions
    // solution - time to solutions

    PrintBestFits();


//    std::cout<<"{";
//    for (auto it = m_bins.begin(); it!=m_bins.end()-1;++it)
//    {
//        std::cout << "* ";
//        it->PrintContents();
//    }
//    (m_bins.end()-1)->PrintContents();



//    std::cout<<
}

BestFit::BestFit()
    : m_seconds_taken(0)
    , m_bins()
{

}

BestFit::BestFit(const long long& seconds_taken)
    : m_seconds_taken(seconds_taken)
    , m_bins(std::vector<Bin>())
{

}

BestFit::BestFit(const std::vector<Bin>& possible_fit, const long long& seconds_taken)
    : m_seconds_taken(seconds_taken)
    , m_bins(possible_fit)
{

}

std::vector<Bin> BestFit::bins() const
{
    return m_bins;
}

long long BestFit::SecondsTaken() const
{
    return m_seconds_taken;
}
