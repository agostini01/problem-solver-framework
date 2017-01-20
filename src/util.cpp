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
