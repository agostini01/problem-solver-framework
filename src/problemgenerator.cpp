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

#include "problemgenerator.h"

#include "util.h"
#include "fileio.h"
#include <iostream>

ProblemGenerator::ProblemGenerator(
  std::vector<std::shared_ptr<Problem>>& problems)
  : m_problems(problems)
  , m_next_id(0)
{

}

void ProblemGenerator::GetProblem(const unsigned int & problem_size,
                                  const unsigned int & bucket_size)
{
  std::shared_ptr<Problem> a_problem(
              new Problem(GetRandomList(problem_size),
                                bucket_size,
                                GenerateProblemId()));
  m_problems.push_back(a_problem);

}

unsigned int ProblemGenerator::GenerateProblemId()
{
  return m_next_id++;
}

void ProblemGenerator::GetProblemFromFile(const std::string & file_name)
{
  FileIO file_io;

  std::list<unsigned int> l;
  l =  file_io.ReadFromFileToList(file_name);

  l.pop_front(); // Discarts the problem size
  unsigned int bucket_size= l.front();
  l.pop_front(); // Discarts the Bin capacity (bucket size)

  std::shared_ptr<Problem> a_problem(
              new Problem(l,
                          bucket_size,
                          GenerateProblemId()));

  m_problems.push_back(a_problem);
}

void ProblemGenerator::GetProblemsFromListOfFiles(const std::string & file_name)
{
  FileIO file_io;
  std::vector<std::string> v;
  v = file_io.ReadFilesList(file_name);
  for (auto it = v.begin(); it != v.end(); ++it)
  {
    std::cerr<<*it<<'\n';
    GetProblemFromFile(*it);
  }
}
