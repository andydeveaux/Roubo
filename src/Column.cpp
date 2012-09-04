/**
 * @file Column.cpp
 * @brief Implementation of the Column class
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

#include "Column.h"
#include "Common.h"

namespace Roubo
{
    Column::Column()
    {
        mWidth       = 0;
        mMaxWidth    = 0;
        mHeaderLabel = "";
    }

    Column::Column(int width, std::string header_label)
    {
        mWidth       = width;
        mMaxWidth    = 0;
        mHeaderLabel = header_label;
    }

    Column::Column(int width, int max_width, std::string header_label)
    {
        mWidth       = width;
        mMaxWidth    = max_width;
        mHeaderLabel = header_label;
    }

    int Column::GetWidth()
    {
        return mWidth;
    }

    void Column::SetWidth(int width)
    {
        if (width < 0)
            width = 0;

        mWidth = width;
    }

    int Column::GetMaxWidth()
    {
        return mMaxWidth;
    }

    void Column::SetMaxWidth(int max_width)
    {
        if (max_width < 0)
            max_width = 0;

        mMaxWidth = max_width;
    }

    std::string Column::GetHeaderLabel()
    {
        return mHeaderLabel;
    }

    void Column::SetHeaderLabel(std::string header_label)
    {
        mHeaderLabel = Common::ValidateUTF8(header_label);
    }
}