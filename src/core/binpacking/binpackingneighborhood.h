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
		GenerateNeighboorhood();
	}

	void GenerateNeighboorhood()
	{
		m_list_of_neighbors.push_back(BPNeighbor(m_original_weights));
		unsigned problem_size = m_original_weights.size();
		std::list<std::pair<unsigned, unsigned> > comb_list = Comb2(problem_size);

		for (const auto& p : comb_list)
		{
			std::list<unsigned> neighboor_weight_list = m_original_weights;
			auto pos0 = neighboor_weight_list.begin();
			auto pos1 = neighboor_weight_list.begin();
			std::advance(pos0,p.first);
			std::advance(pos1,p.second);
			std::iter_swap(pos0,pos1);

			m_list_of_neighbors.push_back(BPNeighbor(neighboor_weight_list));

		}
		std::cout<<"MY SIZE IS: "<<m_list_of_neighbors.size()<<std::endl;


	}

	void CalculateBestNeighboorFitness()
	{

	}

	std::list<BPNeighbor> GetNeighborsList();

private:
	std::list<unsigned> m_original_weights;
	std::list<BPNeighbor> m_list_of_neighbors;
	std::pair<unsigned,float> m_best_neighbor_fitness;
};

#endif // BINPACKINGNEIGHBORHOOD_H
