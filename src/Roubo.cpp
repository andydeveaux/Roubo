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
        StartPrompt();
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
        cout << "CONFIG\t\tSteps through configuration prompt\n";
        cout << "SETTINGS\tShows current settings\n";
        cout << "CLEAR\t\tDeletes the table from memory\n";
        cout << "EXIT\t\tExits the program\n\n";
    }

    void Roubo::DisplayCommandHelp(char* command)
    {
        using namespace std;
        string cmd = Common::ToUpper(string(command));
        cout << "\n";
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

        else if (cmd == "CONFIG")
        {
            cout << "Steps user through the formatter and parser settings\n\n";
            cout << "Usage: CONFIG\n\n";
            cout << "NOTE: Leave any setting blank for default value.\n";
            cout << "      Use SETTINGS command to show current configuration.\n\n";

            cout << "Formatter Settings\n-----------------\n";
            cout << "Border width:\t\t\tIntegral value; number of characters\n";
            cout << "Border char - horizontal:\thorizontal border character\n";
            cout << "Border char - vertical:\t\tVertical border character\n";
            cout << "Border char - corner:\t\tCorner border character\n";
            cout << "Border char - header separator:\tThe bottom of the header row\n";
            cout << "Border char - row separator:\tInserted between rows\n";
            cout << "Max column width:\t\tWidth of column before word wrap is applied\n\n";

            cout << "Parser Settings\n-----------------\n";
            cout << "Cell delimiter:\t\t\tCharacter used to separate cell data\n";
            cout << "Enable header label prefix:\tMakes header row optional\n";
            cout << "Header label prefix:\t\tPrefix that indicates a header row\n\n";
        }

        else if (cmd == "SETTINGS")
        {
            cout << "Shows current configuration settings";
        }

        else if (cmd == "CLEAR")
        {
            cout << "Deletes the entire table from memory";
        }

        else
        {
            cout << "Invalid command";
        }

        cout << "\n\n";
    }

    /**
     * Here be prompt!
     */
    void Roubo::StartPrompt()
    {
        using namespace std;
        string input;
        string upper;
        mParserObject = new Parser(true);
        do
        {
            cout<<" >> ";
            getline(cin, input);
           
            mParserObject->SetString(input);
            string cmd = Common::ToUpper(mParserObject->GetNext());

            if (cmd == "QUIT" || cmd == "EXIT")
            {
                break;
            }

            else if (cmd == "HELP")
            {
                string value = Common::ToUpper(mParserObject->GetNext());
                if (!value.empty())
                    DisplayCommandHelp(const_cast<char*>(value.c_str()));
                else
                    DisplayCommands();
            }

            else if (cmd == "INPUT")
            {
                string value = mParserObject->GetNext();
                if (value.empty())
                {
                    TableDataPrompt();
                }

                else
                {
                    mFileHandlerObject.Close();
                    if (!mFileHandlerObject.OpenFile(value, false))
                    {
                        cout << "There was an error opening the file\n";
                        continue;
                    }
                }
            }

            else if (cmd == "OUTPUT")
            {
            }

            else if (cmd == "CONFIG")
            {
                ConfigPrompt();
            }

            else if (cmd == "SETTINGS")
            {
            }

            else if (cmd == "CLEAR")
            {
                mTableObject.Clear();
                cout << "\nCleared\n\n";
            }

            else
            {
                cout << "\nInvalid command\n\n";
            }

        } while (cin);
    }

    /**
     * Formatter configuration prompt
     */
    void Roubo::ConfigPrompt()
    {
        using namespace std;
        string input;
    }

    /**
     * Prompt for table data
     */
    void Roubo::TableDataPrompt()
    {
        using namespace std;
        cout << "\nInput Mode (CTRL+Z then ENTER to end)\n\n";

        string input;
        Parser data_parser(false);

        int row = 0;
        bool loop = true;
        do
        {
            cout << mTableObject.GetNumberOfRows();
            cout << " ::> ";
            getline(cin, input);

            // Strip the EOF character if present
            if (!input.empty() && input.at(input.length() - 1) == 26)
            {
                input = input.substr(0, input.length() - 1);
                loop = false;
            }

            if (input.empty())
                continue;

            data_parser.SetString(input);
            string next;
            mTableObject.AddRow();

            int column = 0;
            while (!(next = data_parser.GetNext()).empty())
            {
                if (mTableObject.GetNumberOfColumns() <= column)
                    mTableObject.AddColumn();

                mTableObject.SetCell(row, column, next);
                column += 1;
            }

            row += 1;
        } while (cin && loop);

        cout << "\n";
        cin.clear();            // Prevent outer loop from exiting
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