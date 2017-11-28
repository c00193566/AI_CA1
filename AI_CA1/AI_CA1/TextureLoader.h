#pragma once
#include "stdafx.h"
#include "SFML\Graphics.hpp"

using namespace sf;

class TextureLoader
{
private:
	static TextureLoader * TLInstance;
	map<string, Texture> Textures;
	TextureLoader()
	{
		Textures = map<string, Texture>();
	};

public:

	void addTexture(string Tag, string Path);

	Texture getTexture(string Tag);

	static TextureLoader * Instance()
	{
		if (!TLInstance)
		{
			TLInstance = new TextureLoader;
		}

		return TLInstance;
	}
};