/*==============================================================================

	Uti;.cpp

	rc-visual: a simple, osc-controlled 2d graphics engine
  
	Copyright (C) 2007, 2010  Dan Wilcox <danomatika@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#include "Util.h"

/* ***** PATH ***** */

#if defined( __WIN32__ ) || defined( _WIN32 )
	#include <windows.h>
#elif defined( __APPLE_CC__)
	#include <mach-o/dyld.h>
#endif

// from http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
string Util::executablePath()
{
	char path[1024];
	
	#if defined( __WIN32__ ) || defined( _WIN32 )
		// Will contain exe path
		HMODULE hModule = GetModuleHandle(NULL);
		if(hModule != NULL)
		{
			// When passing NULL to GetModuleHandle, it returns handle of exe itself
			GetModuleFileName(hModule, path, (sizeof(path)));
		}
		else
			return "";
	#elif defined( __APPLE_CC__)
		uint32_t size = sizeof(path);
		if(_NSGetExecutablePath(path, &size) != 0)
			return "";
	#else // LINUX
		readlink("/proc/self/exe", path, sizeof(path));
	#endif
	
	return (string) path;
}

//string removeLastPathComponent(const string& path)
//{
//
//}

/* ***** OSC ***** */

void Util::asNumber(int *dest, const ReceivedMessage& message, int argIndex)
{
	if(message.isInt32(argIndex))
	{
		*dest = message.asInt32(argIndex);
	}
	else if(message.isFloat(argIndex))
	{
		*dest = (int) message.asFloat(argIndex);
	}
}

void Util::asNumber(unsigned int *dest, const ReceivedMessage& message, int argIndex)
{
	if(message.isInt32(argIndex))
	{
		*dest = (unsigned int) message.asInt32(argIndex);
	}
	else if(message.isFloat(argIndex))
	{
		*dest = (unsigned int) message.asFloat(argIndex);
	}
}

void Util::asNumber(float *dest, const ReceivedMessage& message, int argIndex)
{
	if(message.isInt32(argIndex))
	{
		*dest = (float) message.asInt32(argIndex);
	}
	else if(message.isFloat(argIndex))
	{
		*dest = message.asFloat(argIndex);
	}
}

void Util::asBool(bool *dest, const ReceivedMessage& message, int argIndex)
{
	if(message.isInt32(argIndex))
	{
		*dest = (bool) message.asInt32(argIndex);
	}
	else if(message.isFloat(argIndex))
	{
		*dest = (bool) message.asFloat(argIndex);
	}
}
