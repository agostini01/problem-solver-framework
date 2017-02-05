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

#ifndef UTIL_H
#define UTIL_H

#include <list>
#include <stdlib.h>

/// Returns (int) 1
int InitialTest();

/// Change default random seed
void SetRandomSeed(const unsigned int & seed_number = 1);

/// Generates a list of unsigned using a random uniform distribution. The list
/// is automatically reverse sorted.
///
/// list_size gives the size of the list
std::list<unsigned int> GetRandomList(const unsigned int & list_size);

void PermuteList(std::list<unsigned int> input_list);

long long Factorial(const unsigned int& n);


#endif // UTIL
