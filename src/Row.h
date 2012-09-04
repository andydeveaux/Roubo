/**
 * @file Row.h
 * @brief Definition of the Row class
 *
 * ------------------------------------------------------------------------
 * Copyright 2012 Syroglyph
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ------------------------------------------------------------------------
*/

#pragma once

#include "Cell.h"

namespace Roubo
{
    class Row
    {
    public:
        // Constructor prototypes
        Row(int num_of_cells = 0);

        ~Row();
 
        void AddCell();                                     // adds new cell
        void AppendCell(Cell* c);                           // appends existing cell
        bool SetCell(int column, std::string data);         // updates specific cell data

    private:
        int mNumberOfCells;
        Cell** mCells;                  // array of cell pointers
        
        void ExpandRow();               // expands the cell array
        void DeleteCellPointers();      // deletes the cell pointers (not the objects!)
        void DeleteRow();               // used for cleanup
    };
}