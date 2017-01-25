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

#ifndef BINPACKINGSOLUTION_H
#define BINPACKINGSOLUTION_H

#include "solution.h"
#include <list>
#include <vector>


class Bin
{
private:
    int m_max_size;
    int m_curr_size;
    std::vector<int> m_items;

public:
    bool AddItem(int item);
    int GetMaxSize();
    Bin(int max_weight);
    void PrintContents() const;
};

class BestFit
{
public:
    BestFit();
};

class BinPackingSolution : public Solution
{
public:
    BinPackingSolution();

private:
    std::list<BestFit> m_best_fits;
};




#endif // BINPACKINGSOLUTION_H
