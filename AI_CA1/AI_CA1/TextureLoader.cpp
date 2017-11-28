#include "TextureLoader.h"

TextureLoader* TextureLoader::TLInstance = 0;

void TextureLoader::addTexture(string Tag, string Path)
{
	Texture LoadTexture;
	if (!(LoadTexture.loadFromFile(Path)))
	{
		cout << "Failed to load in Texture" << endl;
	}
	else
	{
		Textures[Tag] = LoadTexture;
		cout << "Texture " << Tag << " successfully loaded" << endl;
	}
}

Texture TextureLoader::getTexture(string Tag)
{
	return Textures[Tag];
}