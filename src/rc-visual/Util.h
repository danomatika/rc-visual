/*==============================================================================

	Util.h

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
#ifndef UTIL_H
#define UTIL_H

#include "Common.h"

/**
	\class  Util
	\brief  static class of useful utility functions
**/
class Util
{
	public:

		/* ***** PATH ***** */

		// returns the path to the executable
		static string executablePath();

		/* ***** OSC ***** */

		// get a message argument as a number and store it in dest
		static void asNumber(int *dest, const ReceivedMessage& message, int argIndex);
		static void asNumber(unsigned int *dest, const ReceivedMessage& message, int argIndex);
		static void asNumber(float *dest, const ReceivedMessage& message, int argIndex);
		
		// get a message argument as a bool and store it in dest
		static void asBool(bool *dest, const ReceivedMessage& message, int argIndex);
};

#endif // UTIL_H
