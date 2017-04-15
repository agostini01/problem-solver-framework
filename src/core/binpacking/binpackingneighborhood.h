#ifndef BINPACKINGNEIGHBORHOOD_H
#define BINPACKINGNEIGHBORHOOD_H

#include <list>
#include <vector>
#include <utility>
#include <algorithm> // swap
#include "binpackingsolution.h"

#include "../../util/util.h"

class BPNeighbor : public Solution
{
public:
	BPNeighbor();
	BPNeighbor(const long long& seconds_taken);
	BPNeighbor(const std::vector<Bin>& possible_fit, const long long& seconds_taken);
	BPNeighbor(std::list<unsigned> weights);

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
		CalculateBestNeighboorFitness();
	}

	void GenerateNeighboorhood()
	{
		m_list_of_neighbors.push_back(BPNeighbor(m_original_weights));
		unsigned problem_size = m_original_weights.size();
		std::list<std::pair<unsigned, unsigned> > comb_list = Comb2(problem_size);

		for (const auto& p : comb_list)
		{
			std::list<unsigned> neighboor_weight_list = m_original_weights;
			std::iter_swap(neighboor_weight_list.begin() +p.first
			               ,neighboor_weight_list.begin() +p.second);
			m_list_of_neighbors.push_back(BPNeighbor(neighboor_weight_list));
		}
		std::cout<<"MY SIZE IS: "<<m_list_of_neighbors.size()<<std::endl;


	}

	void CalculateBestNeighboorFitness()
	{

	}

private:
	std::list<unsigned> m_original_weights;
	std::list<BPNeighbor> m_list_of_neighbors;
	std::pair<unsigned,float> m_best_neighbor_fitness;
};

#endif // BINPACKINGNEIGHBORHOOD_H
