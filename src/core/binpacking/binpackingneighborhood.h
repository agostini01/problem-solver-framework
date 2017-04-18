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

	///
	/// \brief GetNeighborBasedOnTemperature
	/// \param k is a float that ranges from 0 to 1 and is constantly incremented at each
	/// new neighborhood
	/// \return
	///
	BPNeighbor GetNeighborBasedOnTemperature(float k)
	{
		std::list<BPNeighbor>::iterator target_neighbor_it = m_list_of_neighbors.begin();

		// TODO!!! This function has to change

//		Let s = original neighbor
//		For k = 0 through kmax (exclusive):
//			T ← temperature(k ∕ kmax)
//			Pick a random neighbour, snew ← neighbour(s)
//			If P(E(s), E(snew), T) ≥ random(0, 1), move to the new state:
//				s ← snew
//		Output: the selected neighbor


		// Currently, m_best_neighbor_fitness is a pair that
		// points to the best neighbor. But we want it to point to a neighbor based on temperature k.

		float previous_fitness = target_neighbor_it->CalculateFitness();

		if (k>0)
		{
			// we have to advance the iterator to point to the new neighbor
			std::advance(target_neighbor_it, GetNeighborPositionBasedOnK(k,previous_fitness));
		}
		else // k=0 and we convered the sim. annealing algorithm
		{
			std::advance(target_neighbor_it, m_best_neighbor_fitness.first);
		}
		return *target_neighbor_it;

	}

	///
	/// \brief GetNeighborPositionBasedOnK returns the displaycement of the new position
	/// for the iterator that is applied on the neighbors list
	/// \param k
	/// \return
	///
	int GetNeighborPositionBasedOnK(const float& k, const float & previous_fitness)
	{
		unsigned n_of_neighbors = m_list_of_neighbors.size();
		std::list<BPNeighbor>::iterator target_neighbor_it = m_list_of_neighbors.begin();
		unsigned neighbor_current_displacement;

		float new_fitness;
		float r = getRandomFromZeroToOne();

		if(r<=k) // Random is smaller than temperature
		{
			do // Hence we have to get a bad neighboor
			{
				target_neighbor_it = m_list_of_neighbors.begin();
				neighbor_current_displacement = getRandomInRange(n_of_neighbors);
				std::advance(target_neighbor_it, neighbor_current_displacement );
				new_fitness = target_neighbor_it->CalculateFitness();

			} while (new_fitness<=previous_fitness);
			return neighbor_current_displacement;
		}
		else
		{
			return m_best_neighbor_fitness.first;
		}

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
