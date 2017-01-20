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
{

}

Problem::Problem(std::list<unsigned int> a_problem)
  : m_problem_instance(a_problem)
{

}

std::string Problem::ToString() const
{
  std::stringstream combinded_string;

  for (std::list<unsigned int>::const_iterator it=m_problem_instance.begin();
    it != m_problem_instance.end(); ++it)
  {
    combinded_string << ' ' << *it;
  }
  return combinded_string.str();
}

void Problem::PushBackValue(const unsigned int& value)
{
  m_problem_instance.push_back(value);
}
