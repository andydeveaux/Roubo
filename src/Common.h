/**
 * @file Common.h
 * @brief Commonly used functions
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
#include <sstream>
#include <iterator>
#include "utf8.h"
#include "Formatter.h"

namespace Roubo
{
    class Common
    {
    public:
        static std::string ValidateUTF8(std::string str)
        {
            std::string temp;
            utf8::replace_invalid(str.begin(), str.end(), back_inserter(temp));
            return temp;
        }

        /**
         * Returns length between two index positions
         */
        static int StringDistance(int start, int end)
        {
            return ((end+1) - start);
        }

        /**
         * Returns an uppercase version of a string
         */
        static std::string ToUpper(std::string str)
        {
            std::string temp;
            int length = str.length();
            for (int i=0; i<length; i++)
            {
                unsigned char c = str.at(i);
                if (c >= 97 && c <= 122)
                    temp += unsigned char(c - 32);
                else
                    temp += c;
            }

            return temp;
        }

        /**
         * Pads a string to specific size
         */
        static std::string PadString(std::string str, unsigned int size)
        {
            while (str.length() < size)
                str.append(" ");

            return str;
        }

        /**
         * Returns "YES" or "NO" from a boolean
         */
        static std::string SettingToString(bool value)
        {
            if (value)
                return "YES";
            else
                return "NO";
        }

        /**
         * Replaces instances in a string with another string
         */
        static void StringReplace(std::string& str, std::string replacement)
        {
            using namespace std;
            string::size_type pos;
            while ((pos = str.find("\t")) != string::npos)
                str.replace(pos, 1, replacement);
        }

        /**
         * Returns a more valuable string
         */
        static std::string SettingToString(unsigned char value)
        {
            std::stringstream ss;
            ss << value;

            if (value == Formatter::BLANK_CHARACTER)
                return "NONE";
            else
                return ss.str();
        }
    };
}