/**
 * @file Formatter.cpp
 * @brief Implementation of the Formatter class
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

#include <iostream>
#include <sstream>
#include "Formatter.h"
#include "Parser.h"
#include "Common.h"

namespace Roubo
{
    Formatter::Formatter()
    {
        mVerticalBorder        = DEFAULT_VERTICAL_BORDER;
        mHorizontalBorder      = DEFAULT_HORIZONTAL_BORDER;
        mCornerBorder          = DEFAULT_CORNER_BORDER;
        mHeaderSeparatorBorder = DEFAULT_HEADER_SEPARATOR_BORDER;
        mRowSeparatorBorder    = DEFAULT_ROW_SEPARATOR_BORDER;

        mMaxColumnWidth = DEFAULT_MAX_COLUMN_WIDTH;
        mBorderWidth    = DEFAULT_BORDER_WIDTH;
        mCenterData     = DEFAULT_CENTER_DATA;

        mTablePointer = NULL;
    }

    /* Vertical Border */
    unsigned char Formatter::GetVerticalBorder()
    {
        return mVerticalBorder;
    }

    void Formatter::SetVerticalBorder(unsigned char value)
    {
        if (value == BLANK_CHARACTER)
            mVerticalBorder = DEFAULT_VERTICAL_BORDER;

        else
            mVerticalBorder = value;
    }

    /* Horizontal Border */
    unsigned char Formatter::GetHorizontalBorder()
    {
        return mHorizontalBorder;
    }

    void Formatter::SetHorizontalBorder(unsigned char value)
    {
        if (value == BLANK_CHARACTER)
            mHorizontalBorder = DEFAULT_HORIZONTAL_BORDER;

        else
            mHorizontalBorder = value;
    }

    /* Corner Border */
    unsigned char Formatter::GetCornerBorder()
    {
        return mCornerBorder;
    }
    void Formatter::SetCornerBorder(unsigned char value)
    {
        if (value == BLANK_CHARACTER)
            mCornerBorder = DEFAULT_CORNER_BORDER;

        else
            mCornerBorder = value;
    }

    /* Header Separator Border */
    unsigned char Formatter::GetHeaderSeparatorBorder()
    {
        return mHeaderSeparatorBorder;
    }

    void Formatter::SetHeaderSeparatorBorder(unsigned char value)
    {
        if (value == BLANK_CHARACTER)
            mHeaderSeparatorBorder = DEFAULT_HEADER_SEPARATOR_BORDER;

        else
            mHeaderSeparatorBorder = value;
    }

    /* Row Separator Border */
    unsigned char Formatter::GetRowSeparatorBorder()
    {
        return mRowSeparatorBorder;
    }

    void Formatter::SetRowSeparatorBorder(unsigned char value)
    {
        if (value == BLANK_CHARACTER)
            mRowSeparatorBorder = DEFAULT_ROW_SEPARATOR_BORDER;

        else
            mRowSeparatorBorder = value;
    }

    /* Max Column Width */
    unsigned int Formatter::GetMaxColumnWidth()
    {
        return mMaxColumnWidth;
    }

    void Formatter::SetMaxColumnWidth(unsigned int width)
    {
        mMaxColumnWidth = width;
    }

    /* Border Width */
    unsigned int Formatter::GetBorderWidth()
    {
        return mBorderWidth;
    }

    void Formatter::SetBorderWidth(unsigned int width)
    {
        mBorderWidth = width;
    }

    /* Center Data */
    bool Formatter::GetCenterData()
    {
        return mCenterData;
    }

    void Formatter::CenterData(bool center)
    {
        mCenterData = center;
    }

    /* Output */
    void Formatter::Output(Table& t)
    {
        using namespace std;

        mTablePointer = &t;
        int num_of_rows = t.GetNumberOfRows();
        int num_of_columns = t.GetNumberOfColumns();
        // Store column widths so they don't have to recalculated for every row
        unsigned int* column_widths = new unsigned int[num_of_columns];
        unsigned int table_width = (mBorderWidth * num_of_columns) + (2 * num_of_columns);
        for (int col=0; col<num_of_columns; col++)
        {
            column_widths[col] = CalculateColumnWidth(col);
            table_width += column_widths[col];
        }

        // Prepare the border strings
        string vertical;
        string horizontal;
        string corner;
        for (unsigned int i=0; i<mBorderWidth; i++)
        {
            stringstream ss;
            ss << mVerticalBorder;
            vertical.append(ss.str());
            ss.str("");

            ss << mHorizontalBorder;
            horizontal.append(ss.str());
            ss.str("");

            ss << mCornerBorder;
            corner.append(ss.str());
        }

        for (int row=0; row<num_of_rows; row++)
        {
            Row* data = mTablePointer->GetRow(row);

            cout << vertical;
            // Careful row formatting goes here;
            for (int col=0; col<num_of_columns; col++)
            {
                cout << " ";    // heading pad
                cout << Common::PadString(data->GetCell(col)->GetData(), column_widths[col]);
                cout << " ";    // trailing pad
                cout << vertical;
            }
            cout << "\n";
        }

        delete[] column_widths;
    }

    void Formatter::Output(FileHandler& fh, Table& t)
    {
        mTablePointer = &t;
        int num_of_rows = t.GetNumberOfRows();
    }

    /* Private methods */
    /**
     * Returns the size of a column by examining cell data
     */
    unsigned int Formatter::CalculateColumnWidth(int column_index)
    {
        int num_of_rows = mTablePointer->GetNumberOfRows();
        unsigned int result = 0;
        bool constrain = (mMaxColumnWidth > 0);
        for (int row=0; row<num_of_rows; row++)
        {
            unsigned int length = mTablePointer->GetCell(row, column_index)->GetData().length();
            if (!constrain && (length > result))
                result = length;

            else if (constrain && (length >= mMaxColumnWidth))
                result = mMaxColumnWidth;

            else if (constrain && (length > result))
                result = length;
        }

        return result;
    }

    std::string Formatter::GetRow(int index)
    {
        std::string rowstr;
        int num_of_columns = mTablePointer->GetNumberOfColumns();
        Row* r = mTablePointer->GetRow(index);
        for (int i=0; i<num_of_columns; i++)
        {
            rowstr.append(r->GetCell(i)->GetData());
        }

        return rowstr.append("\n");
    }
}
