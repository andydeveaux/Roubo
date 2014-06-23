/**
 * @file Roubo.h
 * @brief The main program class
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

#include "Table.h"
#include "FileHandler.h"
#include "Parser.h"
#include "Formatter.h"

namespace Roubo
{
    class Roubo
    {
    public:
        Roubo();
        ~Roubo();

        void Run(int& argc, char** argv);

    private:
        Table       mTableObject;
        FileHandler mFileHandlerObject;
        Parser*     mParserObject;
        std::string mOutputFilename;
        Formatter   mFormatterObject;

        void DisplayHelp();                             // Displays help message
        void DisplayCommands();                         // Displays command list
        void DisplayCommandHelp(char* command);         // Displays help about a specific command
        void StartPrompt();                             // Implements the CLI
        void ConfigPrompt();                            // Prompts for formatter settings
        void TableDataPrompt();                         // Prompt for table data
        void ProcessFile();                             // Parses a loaded file
        bool IsValidFilename(char* name);
    };
}