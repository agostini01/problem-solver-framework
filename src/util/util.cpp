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

#include "util.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>

int InitialTest()
{
    return 1;
}

void SetRandomSeed(const unsigned int & seed_number)
{
  srand(seed_number);
}


std::list<unsigned int> GetRandomList(const unsigned int & list_size)
{
  std::list<unsigned int> a_list;
  int i;
  for (i = 0; i < list_size; i++) {
    a_list.push_back(rand()%100);
  }

  a_list.sort();
  a_list.reverse();

  return a_list;
}

void PermuteList(std::list<unsigned int> input_list)
{
    int array_size = input_list.size();
    unsigned int* input_array =  new unsigned int[array_size];
    copy(input_list.begin(),input_list.end(),input_array);

    int i;
    do
    {
        // Just print for visualization
        std::cerr <<"Array\t";
        for (i=0;i<array_size;++i)
        {
            std::cerr << input_array[i] << ' ';
        }
        std::cerr << '\n';

        // Does the copying form array to list
        std::list<unsigned int> tempList(input_array,input_array+array_size);

        // Just print for visualization
        std::cerr <<"List\t";
        for (auto it=tempList.begin();it !=tempList.end(); ++it)
        {
            std::cerr << *it << ' ';
        }
        std::cerr << '\n';

    }
    while ( std::next_permutation(input_array,input_array+input_list.size()) );

    delete[] input_array;
}

long long Factorial(const unsigned int &n)
{
    return (n == 1 || n == 0) ? 1 : Factorial(n - 1) * n;
}

void Comb(int N, int K=2)
{
	std::string bitmask(K, 1); // K leading 1's
	bitmask.resize(N, 0); // N-K trailing 0's

	// print integers and permute bitmask
	do {
		for (int i = 0; i < N; ++i) // [0..N-1] integers
		{
			if (bitmask[i]) std::cout << " " << i;
		}
		std::cout << std::endl;
	} while (std::prev_permutation(bitmask.begin(), bitmask.end()));
}

std::list<std::pair<unsigned, unsigned> > Comb2(int N)
{
	std::list<std::pair<unsigned, unsigned> > comb_list;
	unsigned elements [2];

	std::string bitmask(2, 1); // 2 leading 1's
	bitmask.resize(N, 0); // N-2 trailing 0's

	// print integers and permute bitmask
	do {
		unsigned count = 0;
		for (int i = 0; i < N; ++i) // [0..N-1] integers
		{
			if (bitmask[i])
			{
				elements[count] = i;
				++count;
				if (count>=2) break;
			}
		}
		count =0;
		comb_list.push_back(std::make_pair(elements[0],elements[1]));
	} while (std::prev_permutation(bitmask.begin(), bitmask.end()));

//	for (const auto& p : comb_list)
//	{
//	  std::cout << p.first << ", " << p.second << std::endl;
//	}

	return comb_list;
}

int myrandom(int i) { return std::rand()%i;}

float getRandomFromZeroToOne()
{
	std::srand (static_cast <unsigned> (std::time(0)));
	return static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
}

unsigned getRandomInRange(const unsigned &max_range)
{
	std::srand (static_cast <unsigned> (std::time(0)));
	return std::rand()%max_range;
}
