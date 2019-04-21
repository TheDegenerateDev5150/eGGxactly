////////////////////////////////////////////////////////////////////////////////
///
/// @file       source/ReaderFactory.cpp
///
/// @project    ipxact
///
/// @brief      Factory for file readers
///
////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////
///
/// @copyright Copyright (c) 2019, Evan Lojewski
/// @cond
///
/// All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
/// 1. Redistributions of source code must retain the above copyright notice,
/// this list of conditions and the following disclaimer.
/// 2. Redistributions in binary form must reproduce the above copyright notice,
/// this list of conditions and the following disclaimer in the documentation
/// and/or other materials provided with the distribution.
/// 3. Neither the name of the <organization> nor the
/// names of its contributors may be used to endorse or promote products
/// derived from this software without specific prior written permission.
///
////////////////////////////////////////////////////////////////////////////////
///
/// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
/// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
/// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
/// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
/// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
/// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
/// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
/// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
/// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
/// POSSIBILITY OF SUCH DAMAGE.
/// @endcond
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <Reader.hpp>

#include <IPXACTReader.hpp>
#include <XHTMLReader.hpp>

using namespace std;

Reader* ReaderFactory::open(const char* filename, Components& components)
{
	Reader* myreader = NULL;
	char* file = strdup(filename);
	char* saveptr;
	char* partial = strtok_r(file, ".", &saveptr);

	// find file extension and return apropriate output writer.
	do
	{
		char* next = strtok_r(NULL, ".", &saveptr);
		if(!next)
		{
			printf("Checking extension '%s'\n", partial);

			     if(0 == strncmp("xml", partial, sizeof("xml"))) 		myreader = new IPXACTReader(filename, components);
			else if(0 == strncmp("xhtml", partial, sizeof("xhtml"))) 	myreader = new XHTMLReader(filename, components);
		}
		partial = next;
	} while(partial);

	free(file);
	printf("Reader: %p(%s)\n", myreader, filename);
	return myreader;
}


Reader::Reader(const char* filename, Components& components) : mComponents(components)
{    // Open output file
    mFile.open(filename, ios::in | ios::binary);
}

Reader::~Reader()
{
    mFile.close();

}
