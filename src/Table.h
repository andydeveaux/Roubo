/**
 * @file Table.h
 * @brief Definition of the Table class
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

#include "Column.h"
#include "Row.h"

namespace Roubo
{
    class Table
    {
    public:
        Table();
        ~Table();

        Row*    AddRow();
        Column* AddColumn();
        
        Row*    GetRow(int row_index);
        Column* GetColumn(int column_index);
        int     GetNumberOfRows();
        int     GetNumberOfColumns();
        Cell*   GetCell(int row_index, int column_index);
        void    SetCell(int row_index, int column_index, std::string data);
        void    Clear();

    private:
        Column** mColumns;
        Row**    mRows;
        int mNumberOfColumns;
        int mNumberOfRows;

        // Array range checking
        bool IsValidRowIndex(int index);
        bool IsValidColumnIndex(int index);

        // cleanup routines
        void DeleteColumnPointers();
        void DeleteAllColumns();
        void DeleteRowPointers();
        void DeleteAllRows();
    };
}