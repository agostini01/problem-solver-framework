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

#ifndef PROBLEM_H
#define PROBLEM_H

#include <list>
#include <string>

class Problem
{
public:

  Problem();

  Problem ( std::list<unsigned int> a_problem
          , unsigned int bucket_size
          , unsigned int problem_id);

  /// Convert the problem to a human readable string
  std::string ToString() const;

  /// Push Back value to problem_instance
  void PushBackValue(const unsigned int& value);

  unsigned int GetMaxSizeOfBucket() const;
  unsigned int GetMaxNumberOfBucketsK() const;
  unsigned int GetProblemId() const;

  std::list<unsigned int> GetWeights() const;


private:

  /// List of weights
  std::list<unsigned int> m_weights;

  /// Bucket size
  unsigned int m_max_size_of_bucket;

  /// Maximun number of buckets
  unsigned int m_max_number_of_buckets_k;

  /// Problem
  unsigned int m_problem_id;
};

#endif // PROBLEM_H
