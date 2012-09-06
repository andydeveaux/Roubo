/**
 * @file Roubo.cpp
 * @brief Implementation of Roubo class
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
#include "Roubo.h"
#include "Common.h"

namespace Roubo
{
    Roubo::Roubo()
    {
        mParserObject = NULL;
        mOutputFilename = "";
    }

    Roubo::~Roubo()
    {
        delete mParserObject;
        mParserObject = NULL;
    }

    void Roubo::Run(int& argc, char** argv)
    {
        using namespace std;
        
        // command line parameters
        try
        {
            if (argc > 1)
            {
                if (strcmp(argv[1], "help") == 0)
                {
                    if (argc == 3)
                        DisplayCommandHelp(argv[2]);
                    else
                        DisplayHelp();
                }

                else
                {
                    if (!mFileHandlerObject.OpenFile(argv[1], false))
                        throw exception("Failed to open input file");

                    // [output]
                    if (argc == 3 && IsValidFilename(argv[2]))
                        mOutputFilename = argv[2];

                    else if (argc == 3)
                        throw exception("Invalid output filename specified");
                }
            }
        }
        catch (exception& e)
        {
            cout << "Error: " << e.what() << "\n\n";
        }

        // CLI starts here
        cin.get();
    }

    void Roubo::DisplayHelp()
    {
        using namespace std;
        cout<< "Formats text into a table\n\n";
        cout<< "Usage: roubo [input] [output]\n\n";
        cout<< "       roubo HELP [command]\n\n";
        DisplayCommands();
    }

    void Roubo::DisplayCommands()
    {
        using namespace std;
        cout << "Use HELP [command] for detailed information\n\nCommands\n-----------------\n";
        cout << "INPUT\t\tBegins accepting input from keyboard or file\n";
        cout << "OUTPUT\t\tProcesses the input and spits out a table\n";
        cout << "SET\t\tConfigures a setting with the formatter\n";
        cout << "SETTINGS\tShows current settings\n";
    }

    void Roubo::DisplayCommandHelp(char* command)
    {
        using namespace std;
        string cmd = Common::ToUpper(string(command));
        if (cmd == "INPUT")
        {
            cout << "Begins accepting input from the keyboard, unless a filename is specified.\n\n";
            cout << "Usage: INPUT [filename]";
        }

        else if (cmd == "OUTPUT")
        {
            cout << "Processes input and spits a table out to the console or to a file if specified\n\n";
            cout << "Usage: OUTPUT [filename]";
        }

        else if (cmd == "SET")
        {
            cout << "Configures a formatter setting\n\n";
            cout << "Usage: SET setting [value1, ...]\n\n";
            cout << "Settings\n-----------------\n";
            cout << "";
        }

        else
        {
            cout << "Invalid command";
        }

        cout << "\n\n";
    }

    bool Roubo::IsValidFilename(char* name)
    {
        std::string temp = std::string(name);
        int length = temp.length();
        if (length < 1)
            return false;

        for (int i=0; i<length; i++)
        {
            unsigned char c = temp[i];
            if (c < 32 || c == ',' || c == '<' || c == '>' || c == '%' || c == '?' || c == '*' || c == ':' || c == '|' || c == '"')
                return false;
        }
        return true;
    }
}