/**
 * @file Parser.cpp
 * @brief Defintion of the Parser class
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

#include "Parser.h"
#include "Common.h"

namespace Roubo
{
    Parser::Parser(std::string str, bool command)
    {
        SetString(str);
        mCommandMode   = command;
        mPointerIndex  = 0;
        mCellSeparator = "\t";
        mLabelPrefix   = '@';
    }

    Parser::Parser(bool command)
    {
        SetString("");
        mCommandMode   = command;
        mPointerIndex  = 0;
        mCellSeparator = "\t";
        mLabelPrefix   = '@';
    }

    std::string Parser::GetNext()
    {
        std::string temp;
        if (mCommandMode)
        {
            int find;
            // ignore leading spaces
            while ((find = mString.find(' ', mPointerIndex)) == mPointerIndex)
                mPointerIndex += 1;

            // found
            if (find != std::string::npos)
            {
                temp = mString.substr(mPointerIndex, Common::StringDistance(mPointerIndex, find - 1));
                mPointerIndex = find + 1;
            }
            // not found
            else
            {
                // Gotta return everything to the end of the string
                temp = mString.substr(mPointerIndex, mString.length() - mPointerIndex);
                mPointerIndex = mString.length();
            }
        }

        // Data mode
        else
        {
            int find = mString.find(mCellSeparator, mPointerIndex);
            // found
            if (find != std::string::npos)
            {
                temp = mString.substr(mPointerIndex, Common::StringDistance(mPointerIndex, find - 1));
                mPointerIndex = find + 1;
            }
            // not found
            else
            {
                // Gotta return everything to the end of the string
                temp = mString.substr(mPointerIndex, mString.length() - mPointerIndex);
                mPointerIndex = mString.length();
            }
        }

        return temp;
    }

    /**
     * For reusing the same parser object
     */
    void Parser::SetString(std::string str)
    {
        mString = Common::ValidateUTF8(str);
        mPointerIndex = 0;
    }

    /**
     * Sets the cell separator string
     */
    bool Parser::SetCellSeparator(std::string delimiter)
    {
        if (delimiter.empty())
            return false;

        if (delimiter.find("\n") != std::string::npos || 
            delimiter.find("\r") != std::string::npos || 
            delimiter.at(0) == mLabelPrefix)
            return false;

        mCellSeparator = delimiter;
        return true;
    }

    bool Parser::SetLabelPrefix(unsigned char prefix)
    {
        if (prefix == ' ' ||
            prefix == '\n' ||
            prefix == '\r' ||
            prefix == '\t' ||
            prefix == '\0' ||
            prefix == mCellSeparator.at(0))
            return false;

        mLabelPrefix = prefix;
        return true;
    }

    bool Parser::IsLabelPrefix(const std::string& str)
    {
        if (str.at(0) == mLabelPrefix)
            return true;
        
        return false;
    }
}
