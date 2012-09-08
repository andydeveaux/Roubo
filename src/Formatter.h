/**
 * @file Formatter.h
 * @brief Defintion of the Formatter class
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

#include "Table.h"
#include "FileHandler.h"

namespace Roubo
{
    class Formatter
    {
    public:
        Formatter();

        const static unsigned char BLANK_CHARACTER = '\0';

        void SetVerticalBorder(unsigned char value);
        void SetHorizontalBorder(unsigned char value);
        void SetCornerBorder(unsigned char value);
        void SetHeaderSeparatorBorder(unsigned char value);
        void SetRowSeparatorBorder(unsigned char value);
        
        void SetMaxColumnWidth(unsigned int value);
        void SetBorderWidth(unsigned int value);
        void CenterData(bool center);

        unsigned char GetVerticalBorder();
        unsigned char GetHorizontalBorder();
        unsigned char GetCornerBorder();
        unsigned char GetHeaderSeparatorBorder();
        unsigned char GetRowSeparatorBorder();

        unsigned int GetMaxColumnWidth();
        unsigned int GetBorderWidth();
        bool GetCenterData();

        void Output(Table& t);                              // standard output
        void Output(FileHandler& fh, Table& t);             // file output

        // constants
        const static unsigned char DEFAULT_VERTICAL_BORDER         = '|';
        const static unsigned char DEFAULT_HORIZONTAL_BORDER       = '-';
        const static unsigned char DEFAULT_CORNER_BORDER           = '+';
        const static unsigned char DEFAULT_HEADER_SEPARATOR_BORDER = '-';
        const static unsigned char DEFAULT_ROW_SEPARATOR_BORDER    = BLANK_CHARACTER;

        const static unsigned int DEFAULT_MAX_COLUMN_WIDTH = 0;
        const static unsigned int DEFAULT_BORDER_WIDTH     = 1;
        const static bool DEFAULT_CENTER_DATA              = false;

    private:
        unsigned char mVerticalBorder;
        unsigned char mHorizontalBorder;
        unsigned char mCornerBorder;
        unsigned char mHeaderSeparatorBorder;
        unsigned char mRowSeparatorBorder;
        
        unsigned int mMaxColumnWidth;
        unsigned int mBorderWidth;
        bool mCenterData;

        Table* mTablePointer;                               // most recent table pointer

        unsigned int CalculateColumnWidth(int column_index);    // examines cell data and determines column width

        std::string GetRow(int index);
        void Pad(std::string& data);
        void Center(std::string& data);
    };
}
