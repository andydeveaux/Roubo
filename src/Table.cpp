/**
 * @file Table.cpp
 * @brief Implementation of the Table class
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

#include "Table.h"

namespace Roubo
{
    Table::Table()
    {
        mColumns = NULL;
        mRows    = NULL;
        mNumberOfColumns = 0;
        mNumberOfRows    = 0;
    }

    Table::~Table()
    {
        DeleteAllRows();
        DeleteAllColumns();
    }

    Column* Table::AddColumn()
    {
        Column** temp = new Column*[mNumberOfColumns + 1];
        // copy old pointer array
        for (int i=0; i<mNumberOfColumns; i++)
            temp[i] = mColumns[i];

        temp[mNumberOfColumns] = new Column();
        DeleteColumnPointers();                 // cleanup old pointers
        mNumberOfColumns += 1;

        for (int i=0; i<mNumberOfRows; i++)
        {
            mRows[i]->AddCell();
        }

        mColumns = temp;
        return mColumns[mNumberOfColumns - 1];
    }

    Row* Table::AddRow()
    {
        Row** temp = new Row*[mNumberOfRows + 1];
        // copy old pointer array
        for (int i=0; i<mNumberOfRows; i++)
            temp[i] = mRows[i];

        temp[mNumberOfRows] = new Row(mNumberOfColumns);
        DeleteRowPointers();                   // cleanup old pointers
        mNumberOfRows += 1;

        mRows = temp;
        return mRows[mNumberOfRows - 1];
    }

    Row* Table::GetRow(int row_index)
    {
        if (!IsValidRowIndex(row_index))
            throw std::exception("Invalid row index");

        return mRows[row_index];
    }

    Column* Table::GetColumn(int column_index)
    {
        if (!IsValidColumnIndex(column_index))
            throw std::exception("Invalid column index");

        return mColumns[column_index];
    }

    int Table::GetNumberOfRows()
    {
        return mNumberOfRows;
    }

    int Table::GetNumberOfColumns()
    {
        return mNumberOfColumns;
    }

    Cell* Table::GetCell(int row_index, int column_index)
    {
        if (!IsValidRowIndex(row_index))
            throw std::exception("Invalid row index");

        return mRows[row_index]->GetCell(column_index);
    }

    void Table::SetCell(int row_index, int column_index, std::string data)
    {
        if (!IsValidRowIndex(row_index))
            throw std::exception("Invalid row index");

        else if (!IsValidColumnIndex(column_index))
            throw std::exception("Invalid column index");

        mRows[row_index]->SetCell(column_index, data);
    }

    void Table::Clear()
    {
        DeleteAllRows();
        DeleteAllColumns();
    }

    bool Table::IsValidRowIndex(int index)
    {
        if (index < 0 || index >= mNumberOfRows)
            return false;

        return true;
    }

    bool Table::IsValidColumnIndex(int index)
    {
        if (index < 0 || index >= mNumberOfColumns)
            return false;

        return true;
    }

    /**
     * @note This deletes the objects as well!
     */
    void Table::DeleteAllColumns()
    {
        for (int i=0; i<mNumberOfColumns; i++)
            delete mColumns[i];

        DeleteColumnPointers();
        mNumberOfColumns = 0;
    }

    void Table::DeleteColumnPointers()
    {
        // Array or not?
        if (mNumberOfColumns > 0)
            delete[] mColumns;
        else
            delete mColumns;

        mColumns = NULL;
    }

    /**
     * @note This deletes the objects as well!
     */
    void Table::DeleteAllRows()
    {
        for (int i=0; i<mNumberOfRows; i++)
            delete mRows[i];

        DeleteRowPointers();
        mNumberOfRows = 0;
    }

    void Table::DeleteRowPointers()
    {
        // Array or not?
        if (mNumberOfRows > 0)
            delete[] mRows;
        else
            delete mRows;

        mRows = NULL;
    }
}