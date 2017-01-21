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

#include "problem.h"
#include <sstream>

Problem::Problem()
  : m_weights(std::list<unsigned int>())
  , m_max_size_of_bucket(0)
  , m_max_number_of_buckets_k(0)
  , m_problem_id(0)
{

}

Problem::Problem(std::list<unsigned int> weights,
                  unsigned int bucket_size,
                  unsigned int problem_id)
  : m_weights(weights)
  , m_max_size_of_bucket(bucket_size)
  , m_max_number_of_buckets_k(0)
  , m_problem_id(problem_id)
{

}

std::string Problem::ToString() const
{
  std::stringstream combinded_string;
  combinded_string<< "Problem id: " << GetProblemId()<<'\n';
  combinded_string<< "Max Size of Bucket: " << GetMaxSizeOfBucket()<<'\n';

  combinded_string<< "Item weights: \n";
  for (std::list<unsigned int>::const_iterator it=m_weights.begin();
    it != m_weights.end(); ++it)
  {
    combinded_string << *it << ' ' ;
  }
  return combinded_string.str();
}

void Problem::PushBackValue(const unsigned int& value)
{
  m_weights.push_back(value);
}

unsigned int Problem::GetMaxSizeOfBucket() const
{
  return m_max_size_of_bucket;
}

unsigned int Problem::GetMaxNumberOfBucketsK() const
{
  return m_max_number_of_buckets_k;
}

unsigned int Problem::GetProblemId() const
{
  return m_problem_id;
}
