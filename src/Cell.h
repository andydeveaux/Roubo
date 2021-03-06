/**
 * @file Cell.h
 * @brief Definition of the Cell class
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

#pragma once

#include <string>
#include "utf8.h"

namespace Roubo
{
    class Cell
    {
    public:
        // Constructor prototypes
        Cell(std::string data = "");

        std::string GetData();
        void SetData(std::string data);

    private:
        std::string mData;                  // data container
    };
}