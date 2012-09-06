/**
 * @file Roubo.h
 * @brief The main program class
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
#include "Parser.h"

namespace Roubo
{
    class Roubo
    {
    public:
        Roubo();
        ~Roubo();

        void Run(int& argc, char** argv);

    private:
        Table mTableObject;
        FileHandler mFileHandlerObject;
        Parser* mParserObject;
        std::string mOutputFilename;

        void DisplayHelp();
        void DisplayCommands();
        void DisplayCommandHelp(char* command);
        bool IsValidFilename(char* name);
    };
}