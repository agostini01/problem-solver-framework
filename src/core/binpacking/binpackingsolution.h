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

#ifndef BINPACKINGSOLUTION_H
#define BINPACKINGSOLUTION_H

#include "../solution.h"
#include <list>
#include <vector>

///
/// \brief The Bin class is part of the solution for the bin packing problem
/// It has a size limit and the items inside that bin
///
class Bin
{
private:
    int m_max_size;
    int m_curr_size;
    std::vector<int> m_items;

public:
    bool AddItem(int item);
    int GetCurSize();
    int GetMaxSize();
    Bin(int max_weight);
    void PrintContents() const;
    void PrintContentsFormated() const;
};

///
/// \brief The BestFit class contains the bins of a solution
/// It keeps track what time this solution was found
///
class BestFit
{
public:
    BestFit();
    BestFit(const long long& seconds_taken);
    BestFit(const std::vector<Bin>& possible_fit, const long long& seconds_taken);

    std::vector<Bin> bins() const;

    long long SecondsTaken() const;
    float CalculateFitness();

private:
    long long m_seconds_taken;
    std::vector<Bin> m_bins;
};

/// Enumerations that holds possible fit types
enum FitType { best, equal, worse };

///
/// \brief The BinPackingSolution class has a list of all best solutions
/// Note that best solutions do not me the optimal.
/// It also keeps track of the number of possible solutions and how many were attempted
///
class BinPackingSolution : public Solution
{
public:
    BinPackingSolution();

    long long getSecondsTaken() const;
    void setSecondsTaken(const long long& seconds_taken);

    bool getFoundOptimal() const;
    void setFoundOptimal(const bool& found_optimal);

    void IncPermutationsDone();

    unsigned long long getNumberOfCombinations() const;
    void setNumberOfCombinations(const long long& number_of_combinations);

    FitType GetFitType(const unsigned int& n_of_bins);

    void Check(const std::vector<Bin>& possible_fit, const unsigned int& n_of_bins,
               const long long& seconds_taken);

    void PrintStatistics();



    void PrintBestFits();

    long long getPermutationsDone() const;

    unsigned int getBestNofBins() const;

private:

    /// List of the best combinations attempted so far
    std::list<BestFit> m_best_fits;

    // Best number of bins so far
    unsigned int m_best_n_of_bins;

    /// Information on how long it took to find the best solutions given
    long long m_seconds_taken;

    /// Keeps track of the total number of possible combinations attempted
    long long m_permutations_done;

    /// Variable is set to true when the solver signals that it found the optimal solution
    bool m_found_optimal;

    unsigned long long  m_number_of_combinations;

};




#endif // BINPACKINGSOLUTION_H
