#include "binpackingneighborhood.h"

BinPackingNeighborhood::BinPackingNeighborhood()
{

}

std::list<BPNeighbor> BinPackingNeighborhood::GetNeighborsList()
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
