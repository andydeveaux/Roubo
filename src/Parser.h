/**
 * @file Parser.h
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

#pragma once

#include <string>
#include "utf8.h"
#include "Row.h"

namespace Roubo
{
    class Parser
    {
    public:
        Parser(std::string str, bool command);
        Parser(bool command);
        std::string GetNext();
        void SetString(std::string str);            // set new parse string
        std::string GetCellSeparator();
        bool SetCellSeparator(std::string delimiter);
        bool GetUsingLabelPrefix();
        void SetUsingLabelPrefix(bool value);
        unsigned char GetPrefixLabel();
        bool SetLabelPrefix(unsigned char prefix);
        bool IsHeaderRow(Row& row, int index);

        // constants
        static const std::string DEFAULT_CELL_SEPARATOR;
        static const bool DEFAULT_USE_LABEL_PREFIX      = false;
        static const unsigned char DEFAULT_LABEL_PREFIX = '@';

    private:
        std::string mString;
        int mPointerIndex;                          // current index the parser is at in the string
        bool mCommandMode;                          // command or data mode
        std::string mCellSeparator;                 // default is tab
        bool mUseLabelPrefix;                       // enables header label prefix
        unsigned char mLabelPrefix;                 // character that indicates header label (default='@'), exists so that they are optional
    };
}
