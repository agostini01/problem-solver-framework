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
