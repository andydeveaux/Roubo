/**
 * @file Formatter.cpp
 * @brief Implementation of the Formatter class
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

#include <iostream>
#include <sstream>
#include <deque>
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

    void Formatter::SetCenterData(bool center)
    {
        mCenterData = center;
    }


    /* Output */
    void Formatter::Output(Table& t, Parser* p)
    {
        using namespace std;

        mTablePointer = &t;
        //mParserPointer = p;
        unsigned int* column_widths = GetColumnWidths();
        GenerateBorders(column_widths);
        int num_of_rows = mTablePointer->GetNumberOfRows();

        cout << mCachedTopBottomBorder;

        for (int i=0, last=num_of_rows-1; i<num_of_rows; i++)
        {
            Row* r = mTablePointer->GetRow(i);
            bool is_header = p->IsHeaderRow(r, i);
            cout << GenerateRowString(r, column_widths, is_header, is_header && p->GetUsingLabelPrefix());

            if (is_header)
                cout << mCachedHeaderBorder;
            
            else if (mRowSeparatorBorder != BLANK_CHARACTER && i != last)
                cout << mCachedRowBorder;
        }
        
        // Don't forget the outer border
        cout << mCachedTopBottomBorder << "\n";

        delete[] column_widths;
    }

    void Formatter::Output(FileHandler& fh, Table& t, Parser* p)
    {
        using namespace std;

        mTablePointer = &t;
        unsigned int* column_widths = GetColumnWidths();
        GenerateBorders(column_widths);
        int num_of_rows = mTablePointer->GetNumberOfRows();
        try
        {
            fh.Write(mCachedTopBottomBorder);

            for (int i=0, last=num_of_rows-1; i<num_of_rows; i++)
            {
                Row* r = mTablePointer->GetRow(i);
                bool is_header = p->IsHeaderRow(r, i);
                fh.Write(GenerateRowString(r, column_widths, is_header, is_header && p->GetUsingLabelPrefix()) );

                if (is_header)
                    fh.Write(mCachedHeaderBorder);
            
                else if (mRowSeparatorBorder != BLANK_CHARACTER && i != last)
                    fh.Write(mCachedRowBorder);
            }

            // Don't forget the outer border
            fh.Write(mCachedTopBottomBorder + "\n");
        }
        catch (exception& e)
        {
            cout << e.what() << "\n";
        }

        cout << "Table generated to file successfully.\n\n";
        delete[] column_widths;
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

    /**
     * Calculates all of the column widths
     */
    unsigned int* Formatter::GetColumnWidths()
    {
        int num_of_rows = mTablePointer->GetNumberOfRows();
        int num_of_columns = mTablePointer->GetNumberOfColumns();

        // Store column widths so they don't have to be recalculated for every row
        unsigned int* column_widths = new unsigned int[num_of_columns];
        for (int col=0; col<num_of_columns; col++)
        {
            column_widths[col] = CalculateColumnWidth(col);
        }

        return column_widths;
    }

    /**
     * Repeat a string a set number of times
     */
    std::string Formatter::RepeatString(std::string& str, unsigned int times)
    {
        std::string output = "";
        for (unsigned int i=0; i<times; i++)
            output.append(str);

        return output;
    }

    /**
     * Trail padding method
     */
    std::string& Formatter::Pad(std::string& str, unsigned int size)
    {
        while (str.length() < size)
            str.append(" ");

        return str;
    }

    /**
     * String centering method
     */
    std::string& Formatter::Center(std::string& str, unsigned int size)
    {
        /* @note Formula for calculating center: floor( (ceil(cell_width / 2.f) - (str_length / 2.f)) ) */
        int length = str.length();
        int center_index = (int)floor( (ceil(size / 2.f) - (length / 2.f)) );
        
        std::string header_space;
        for (int i=0; i<center_index; i++)
            header_space.append(" ");

        str = header_space + str;
        Pad(str, size);
        return str;
    }

    std::string Formatter::GenerateRowString(Row* row, const unsigned int* widths, bool is_header, bool is_prefix_header)
    {
        using namespace std;

        string output = mVerticalBorderStr;
        // Queues used for processing multiple lines
        deque<string> row_data_queue;
        deque<int>    row_index_queue;
        bool constrained = (mMaxColumnWidth != 0);         // Might be a bit faster in the loop

        int num_of_columns = mTablePointer->GetNumberOfColumns();        
        for (int col=0; col<num_of_columns; col++)
        {
            string data;
            if (is_prefix_header && col == 0)
                data = row->GetCell(col)->GetData().substr(1);
            else
                data = row->GetCell(col)->GetData();

            unsigned int length = data.length();
            // Wordwrap
            if (constrained && length > mMaxColumnWidth)
            {
                row_data_queue.push_back(data.substr(mMaxColumnWidth, (length - mMaxColumnWidth) + 1));
                row_index_queue.push_back(col);
                output.append(" " + data.substr(0, mMaxColumnWidth) + " ")
                      .append(mVerticalBorderStr);
            }
            // No wordwrap
            else
            {
                if (is_header || mCenterData)
                    output.append(" " + Center(data, widths[col]) + " ")
                          .append(mVerticalBorderStr);
                else
                    output.append(" " + Pad(data, widths[col]) + " ")
                          .append(mVerticalBorderStr);
            }
        }

        // Process queues
        if (!row_index_queue.empty())
        {
            Row r = Row(num_of_columns);
            for (int col=0; col<num_of_columns; col++)
            {
                int front = (!row_index_queue.empty() ? row_index_queue.front() : -1);          // If the queues are empty, col will never reach -1
                if (col != front)
                {
                    r.AddCell();
                }
                else
                {
                    r.AddCell();
                    r.SetCell(col, row_data_queue.front());
                    row_data_queue.pop_front();
                    row_index_queue.pop_front();
                }
            }

            // Hooray for recursion
            output.append("\n" + GenerateRowString(&r, widths));
        }
        else
        {
            output.append("\n");

            // Header separator
            /*
            if (header)
                output.append(mCachedHeaderBorder);

            // Row separator
            else if (mRowSeparatorBorder != BLANK_CHARACTER)
                output.append(mCachedRowBorder);
                */
        }

        return output;
    }

    /**
     * @date 9/9/2012
     * Optimized this function a bit better and made it look less ugly, it also now generates border caches
     */
    void Formatter::GenerateBorders(unsigned int* column_widths)
    {
        using namespace std;

        stringstream vertical, horizontal, corner, row, header;
        horizontal << mHorizontalBorder;
        header     << mHeaderSeparatorBorder;
        row        << mRowSeparatorBorder;
        for (unsigned int i=0; i<mBorderWidth; i++)
        {
            vertical   << mVerticalBorder;
            corner     << mCornerBorder;
        }

        mVerticalBorderStr   = vertical.str();
        mHorizontalBorderStr = horizontal.str();
        mCornerBorderStr     = corner.str();
        mHeaderBorderStr     = header.str();

        // Caching starts here
        int num_of_columns = mTablePointer->GetNumberOfColumns();

        // Border width
        mCachedRowBorder       = "";
        mCachedTopBottomBorder = "";
        mCachedHeaderBorder    = "";
        for (unsigned int i=0; i<mBorderWidth; i++)
        {
            mCachedRowBorder.append(mCornerBorderStr);
            mCachedTopBottomBorder.append(mCornerBorderStr);
            mCachedHeaderBorder.append(mCornerBorderStr);
            for (int j=0; j<num_of_columns; j++)
            {
                mCachedRowBorder.append(RepeatString(row.str(), column_widths[j] + CELL_PADDING))
                                .append(mCornerBorderStr);

                mCachedTopBottomBorder.append(RepeatString(horizontal.str(), column_widths[j] + CELL_PADDING))
                                      .append(mCornerBorderStr);

                mCachedHeaderBorder.append(RepeatString(header.str(), column_widths[j] + CELL_PADDING))
                                   .append(mCornerBorderStr);
            }

            mCachedRowBorder.append("\n");
            mCachedTopBottomBorder.append("\n");
            mCachedHeaderBorder.append("\n");
        }
    }
}
