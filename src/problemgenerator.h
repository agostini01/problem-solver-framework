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

#ifndef PROBLEMGENERATOR_H
#define PROBLEMGENERATOR_H

#include <vector>
#include <memory>
#include "problem.h"

class ProblemGenerator
{
public:
    ProblemGenerator(std::vector<std::shared_ptr<Problem>>& problems);

    /// Generate a Problem instance using util.h list generation
    void GetProblem(const unsigned int & problem_size,
                    const unsigned int & bucket_size=100);

    unsigned int GenerateProblemId();

private:
  std::vector<std::shared_ptr<Problem>>& m_problems;
  unsigned int m_next_id;
};

#endif // PROBLEMGENERATOR_H
