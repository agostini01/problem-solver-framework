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

#include "binpackingsolution.h"
#include <iostream>
#include <iomanip>


void Bin::PrintContents() const
{
    std::cerr<<"Bin: ";
    for (auto it = m_items.begin(); it!=m_items.end();++it)
    {
        std::cerr<<std::setw(3)<<*it;
    }
    std::cerr<<std::endl;
}

bool Bin::AddItem(int item) {
  //std::cerr << "Current Size: " << curr_size << " Item size: " << item << " Max Size: " << max_size << std::endl;
  if (m_curr_size + item <= m_max_size) {
    m_items.insert(m_items.end(), item);
    m_curr_size+= item;
    return true;
  } else {
    return false;
  }
}

int Bin::GetMaxSize() {
  return m_curr_size;
}

Bin::Bin(int max_weight) {
  m_max_size = max_weight;
  m_curr_size = 0;
//  std::cerr << "Making new Bin. Max size: " << max_size << " Current size: " << curr_size << std::endl;
}

BinPackingSolution::BinPackingSolution()
{

}
