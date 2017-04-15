#include "binpackingneighborhood.h"

BinPackingNeighborhood::BinPackingNeighborhood()
{

}

BPNeighbor::BPNeighbor(std::list<unsigned> weights)
    : m_seconds_taken(0)
    , m_bins()
    , m_fitness(0)
    , m_problem_weights(weights)
{

}

BPNeighbor::BPNeighbor(const long long &seconds_taken)
    : m_seconds_taken(seconds_taken)
    , m_bins(std::vector<Bin>())
    , m_fitness(0)
    , m_problem_weights()
{

}

BPNeighbor::BPNeighbor(const std::vector<Bin> &possible_fit, const long long &seconds_taken)
    : m_seconds_taken(seconds_taken)
    , m_bins(possible_fit)
    , m_fitness(0)
    , m_problem_weights()
{

}
