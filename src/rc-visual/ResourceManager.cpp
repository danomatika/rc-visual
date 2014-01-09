/*==============================================================================

	ResourceManager.cpp

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
#include "ResourceManager.h"

using namespace visual;

ResourceManager::~ResourceManager()
{
	clear();
}

void ResourceManager::clear()
{
	clearFonts();
	clearImages();
}

// FONT

bool ResourceManager::addFont(const string& name, const string& file, unsigned int size)
{
	Font *f = new Font(file, size);
	if(!f->isLoaded())
		return false;
	fonts.insert(pair<string,Font*>(name, f));
	return true;
}

void ResourceManager::removeFont(const string& name)
{
	map<string,Font*>::iterator iter = fonts.find(name);
	if(iter != fonts.end())
	{
		delete iter->second;
		fonts.erase(iter);
	}
}

bool ResourceManager::fontExists(const string& name)
{
	map<string,Font*>::iterator iter = fonts.find(name);
	if(iter != fonts.end())
	{
		return true;
	}
	return false;
}

Font* ResourceManager::getFont(const string& name)
{
	map<string,Font*>::iterator iter = fonts.find(name);
	if(iter != fonts.end())
		return iter->second;
	else
		return NULL;
}

void ResourceManager::clearFonts()
{
	map<string,Font*>::iterator iter;
	for(iter = fonts.begin(); iter != fonts.end(); iter++)
		delete iter->second;
	fonts.clear();
}

// IMAGE

bool ResourceManager::addImage(const string& name, const string& file)
{
	Image *i = new Image(file);
	if(!i->isLoaded())
		return false;
	images.insert(pair<string,Image*>(name, i));
	return true;
}

void ResourceManager::removeImage(const string& name)
{
	map<string,Image*>::iterator iter = images.find(name);
	if(iter != images.end())
	{
		delete iter->second;
		images.erase(iter);
	}
}

bool ResourceManager::imageExists(const string& name)
{
	map<string,Image*>::iterator iter = images.find(name);
	if(iter != images.end())
	{
		return true;
	}
	return false;
}

visual::Image* ResourceManager::getImage(const string& name)
{
	map<string,Image*>::iterator iter = images.find(name);
	if(iter != images.end())
		return iter->second;
	else
		return NULL;
}

void ResourceManager::clearImages()
{
	map<string,Image*>::iterator iter;
	for(iter = images.begin(); iter != images.end(); iter++)
		delete iter->second;
	images.clear();
}
