/**
 * @file FileHandler.h
 * @brief Defintion of the Column class
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

#include <fstream>
#include <string>

namespace Roubo
{
    class FileHandler
    {
    public:
        FileHandler();
        ~FileHandler();

        bool OpenFile(std::string filename, bool write); // opens a file
        std::string GetNextLine();                       // gets the next line in the file
        bool Write(std::string data);                   // writes to currently open file
        void Close();                                   // closes file and calls cleanup methods

    private:
        std::ifstream* mReadStream;
        std::ofstream* mWriteStream;
        void DestroyReadStream();
        void DestroyWriteStream();
    };
}
