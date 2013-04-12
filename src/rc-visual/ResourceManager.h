/*==============================================================================

	ResourceManager.h

	rc-visual: a simple, osc-controlled 2d graphics engine
  
	Copyright (C) 2007, 2010, 2011  Dan Wilcox <danomatika@gmail.com>

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
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Common.h"
#include <map>

class ResourceManager
{
    public:

        ~ResourceManager();

		void clear();

		/// fonts
        bool addFont(const string& name, const string& file, unsigned int size);
        void removeFont(const string& name);
		bool fontExists(const string& name);
		visual::Font* getFont(const string& name);
		void clearFonts();
		
		/// fonts
        bool addImage(const string& name, const string& file);
        void removeImage(const string& name);
		bool imageExists(const string& name);
		visual::Image* getImage(const string& name);
		void clearImages();

    protected:

        std::map<string,visual::Font*> fonts;
		std::map<string,visual::Image*> images;
};

#endif // RESOURCE_MANAGER_H
