#include "binpackingneighborhood.h"

BinPackingNeighborhood::BinPackingNeighborhood()
{

}

void BinPackingNeighborhood::GenerateNeighborhood()
{
	std::cout<<std::endl<<"Generating a new neighborhood..."<<std::endl;
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
	std::cout<<"Neighborhood has : "<<m_list_of_neighbors.size()
	        <<" neighbors."<<std::endl;
}

std::list<BPNeighbor>& BinPackingNeighborhood::GetNeighborsList()
{
	return m_list_of_neighbors;
}

BPNeighbor::BPNeighbor(std::list<unsigned> weights)
    : Solution()
    , m_problem_weights(weights)
{

}

std::list<unsigned> BPNeighbor::GetProblemWeights() const
{
	return m_problem_weights;
}

BPNeighbor::BPNeighbor(const long long &seconds_taken)
    : Solution(seconds_taken)
    , m_problem_weights()
{

}

BPNeighbor::BPNeighbor(const std::vector<Bin> &possible_fit, const long long &seconds_taken)
    : Solution(possible_fit,seconds_taken)
    , m_problem_weights()
{

}
