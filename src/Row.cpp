/**
 * @file Row.cpp
 * @brief Implementation of the Row class
 *
 * ------------------------------------------------------------------------
 * Copyright 2012 Andy Deveaux
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

#include "Row.h"

namespace Roubo
{
    Row::Row(int num_of_cells)
    {
        mNumberOfCells = num_of_cells;
        if (num_of_cells <= 0)
        {
            mCells = NULL;
        }
        else
        {
            mCells = new Cell*[mNumberOfCells];

            for (int i=0; i<num_of_cells; i++)
                mCells[i] = new Cell();
        }
    }

    Row::~Row()
    {
        DeleteRow();
    }

    void Row::AddCell()
    {
        ExpandRow();
        mCells[mNumberOfCells - 1]  = new Cell();
    }

    void Row::AppendCell(Cell* c)
    {
        ExpandRow();
        mCells[mNumberOfCells - 1] = c;
    }

    Cell* Row::GetCell(int column)
    {
        if (column < 0 || column >= mNumberOfCells)
            throw std::exception("Invalid column index");

        return mCells[column];
    }

    /**
     * @note column is zero based index
     */
    bool Row::SetCell(int column, std::string data)
    {
        if (column < 0 || column >= mNumberOfCells)
            return false;

        mCells[column]->SetData(data);
        return true;
    }

    void Row::ExpandRow()
    {
        Cell** temp = new Cell*[mNumberOfCells + 1];
        for (int i=0; i<mNumberOfCells; i++)
            temp[i] = mCells[i];

        DeleteCellPointers();
        mNumberOfCells += 1;
        mCells = temp;
    }

    /**
     * @note Doesn't delete the objects!
     */
    void Row::DeleteCellPointers()
    {
        if (mNumberOfCells > 0)
            delete[] mCells;
        else
            delete mCells;

        mCells = NULL;
    }

    void Row::DeleteRow()
    {
        for (int i=0; i<mNumberOfCells; i++)
            delete mCells[i];

        DeleteCellPointers();
    }
}