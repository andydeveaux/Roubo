/**
 * @file FileHandler.cpp
 * @brief Implementation of the FileHandler class
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

#include "FileHandler.h"
#include "Common.h"

namespace Roubo
{
    FileHandler::FileHandler()
    {
        mWriteStream = NULL;
        mReadStream  = NULL;
    }

    FileHandler::~FileHandler()
    {
        Close();
    }

    /**
     * Open a file for reading or writing
     */
    bool FileHandler::OpenFile(std::string filename, bool write)
    {
        Close();
        if (!write)
        {
            mReadStream = new std::ifstream();
            mReadStream->open(filename);

            // Failure, cleanup
            if (!mReadStream->is_open())
            {
                DestroyReadStream();
                return false;
            }

            return true;
        }
        else
        {
            mWriteStream = new std::ofstream();
            mWriteStream->open(filename.c_str());

            // Failure, cleanup
            if (!mWriteStream->is_open())
            {
                DestroyWriteStream();
                return false;
            }

            return true;
        }
    }

    /**
     * Fetches the next line in the file
     */
    std::string FileHandler::GetNextLine()
    {
        if (!mReadStream)
            throw std::exception("Error reading: File not open");

        if (!mReadStream->good())
            return "";

        std::string temp;
        std::getline(*mReadStream, temp);
        temp = Common::ValidateUTF8(temp);
        return temp;
    }

    /**
     * Writes a line to currently open file
     */
    bool FileHandler::Write(std::string data)
    {
        if (!mWriteStream)
            throw std::exception("Error writing: File not open");

        *mWriteStream << data;
        mWriteStream->flush();
    }

    void FileHandler::Close()
    {
        if (mReadStream)
            mReadStream->close();

        if (mWriteStream)
            mWriteStream->close();

        DestroyReadStream();
        DestroyWriteStream();
    }

    void FileHandler::DestroyReadStream()
    {
        delete mReadStream;
        mReadStream = NULL;
    }

    void FileHandler::DestroyWriteStream()
    {
        delete mWriteStream;
        mWriteStream = NULL;
    }
}