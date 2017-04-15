#ifndef BINPACKINGNEIGHBORHOOD_H
#define BINPACKINGNEIGHBORHOOD_H

#include <list>
#include <vector>
#include <utility>
#include <algorithm> // swap
#include "binpackingsolution.h"
#include <iostream>

#include "../../util/util.h"

class BPNeighbor : public Solution
{
public:
	BPNeighbor();
	BPNeighbor(const long long& seconds_taken);
	BPNeighbor(const std::vector<Bin>& possible_fit, const long long& seconds_taken);
	BPNeighbor(std::list<unsigned> weights);

	std::list<unsigned> GetProblemWeights() const;

private:
	std::list<unsigned> m_problem_weights;

};

class BinPackingNeighborhood
{
public:
	BinPackingNeighborhood();

	BinPackingNeighborhood(std::list<unsigned> weights)
	    : m_original_weights(weights)
	    , m_list_of_neighbors()
	    , m_best_neighbor_fitness()
	{
		GenerateNeighborhood();
	}

	///
	/// \brief GenerateNeighboorhood sets the member list_of_neighbors
	/// by doing a combination of the weights
	///
	void GenerateNeighborhood();

	///
	/// \brief CalculateBestNeighboorFitness sets the pair best neighbor and fitness
	/// First it calculates the fitness for every neighbor, and then it selects the
	/// neighbor with best fitness
	///
	void CalculateBestNeighboorFitness()
	{
		unsigned best_neighbor_pos=0;
		float best_neighbor_value=0;

		unsigned current_pos=0;
		float current_value=0;

		for(BPNeighbor& current_neighbor : m_list_of_neighbors)
		{
			current_value = current_neighbor.CalculateFitness();
			if(current_value>best_neighbor_value)
			{
				best_neighbor_value=current_value;
				best_neighbor_pos=current_pos;
			}
			++current_pos;
		}
		m_best_neighbor_fitness = std::make_pair(best_neighbor_pos,best_neighbor_value);

	}

	BPNeighbor GetBestNeighbor()
	{
		std::list<BPNeighbor>::iterator target_neighbor_it = m_list_of_neighbors.begin();
		std::advance(target_neighbor_it, m_best_neighbor_fitness.first);
		return *target_neighbor_it;

	}

	unsigned GetBestPosition()
	{
		return m_best_neighbor_fitness.first;
	}

	float GetBestFitness()
	{
		return m_best_neighbor_fitness.second;
	}

	std::list<BPNeighbor> &GetNeighborsList();

private:
	std::list<unsigned> m_original_weights;
	std::list<BPNeighbor> m_list_of_neighbors;
	std::pair<unsigned,float> m_best_neighbor_fitness;
};

#endif // BINPACKINGNEIGHBORHOOD_H
