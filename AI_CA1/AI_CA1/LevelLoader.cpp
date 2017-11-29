#include "stdafx.h"
#include "LevelLoader.h"

int GameData::m_maxGameObjects;
std::vector<GameData::GObject> GameData::m_gameObjectVector;
std::string GameData::fontFile;
	
////////////////////////////////////////////////////////////
LevelLoader::LevelLoader(std::string const & filename)
{

	loadJSONData(filename);
	m_value = JSON::Parse(m_JSONData.c_str());
	if (NULL == m_value)
	{
		std::string s("Could not parse json in " + filename);
		throw std::exception(s.c_str());
	}
}

////////////////////////////////////////////////////////////
LevelLoader::~LevelLoader() {
	delete m_value;
}

////////////////////////////////////////////////////////////
void LevelLoader::load(std::string const & filename)
{
	loadJSONData(filename);
	m_value = JSON::Parse(m_JSONData.c_str());
	if (NULL == m_value)
	{
		std::string s("Could not parse json in " + filename);
		throw std::exception(s.c_str());
	}
	
}

////////////////////////////////////////////////////////////
void LevelLoader::loadJSONData(std::string const & filename)
{
	m_JSONData.clear();

	// Loads all the data in the file into a std::string.
	std::ifstream myfile(filename);
	std::string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			m_JSONData.append(line);
		}
		myfile.close();
	}
	else
	{
		std::string errorMessage = "Could not open " + filename + " exiting!";
		std::cout << "Could not open " + filename + " exiting!" << std::endl;
		throw std::exception(errorMessage.c_str());
	}
}

////////////////////////////////////////////////////////////
void LevelLoader::loadLevelData(int level)
{
	
	m_gameData.m_gameObjectVector.clear();
	// Retrieve the main (root) object
	JSONObject root = getTopLevelJSONObject();

	JSONObject gameData = root[L"general_game_data"]->AsObject();
	// Load the time to place towers field and related text settings.
	JSONObject globalSettings = gameData[L"global_settings"]->AsObject();
	m_gameData.fontFile = wStringToString(globalSettings[L"font_file"]->AsString());
	//use level to find the correct object in the json
	std::string word("level" + std::to_string(level));
	std::wstring wWord;
	wWord.assign(word.begin(), word.end());
	JSONObject m_level = gameData[wWord]->AsObject();
	//m_gameData.m_levelBackgroundFile = wStringToString(m_level[L"level_background_file"]->AsString());
	m_gameData.m_maxGameObjects = m_level[L"max_game_objects"]->AsNumber();
	JSONArray gameObjects = m_level[L"GameObjects"]->AsArray();
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		JSONObject object = gameObjects[i]->AsObject();
		m_gameData.m_gameObjectVector.push_back(GameData::GObject(object[L"x"]->AsNumber(), object[L"y"]->AsNumber(), 
			wStringToString(object[L"Texture"]->AsString()),
			wStringToString(object[L"Type"]->AsString())));
	}
}

////////////////////////////////////////////////////////////
void LevelLoader::loadLevelData(string level)
{

	m_gameData.m_gameObjectVector.clear();
	// Retrieve the main (root) object
	JSONObject root = getTopLevelJSONObject();

	JSONObject gameData = root[L"general_game_data"]->AsObject();
	// Load the time to place towers field and related text settings.
	JSONObject globalSettings = gameData[L"global_settings"]->AsObject();
	m_gameData.fontFile = wStringToString(globalSettings[L"font_file"]->AsString());
	//use level to find the correct object in the json
	std::string word(level);
	std::wstring wWord;
	wWord.assign(word.begin(), word.end());
	JSONObject m_level = gameData[wWord]->AsObject();
	//m_gameData.m_levelBackgroundFile = wStringToString(m_level[L"level_background_file"]->AsString());
	m_gameData.m_maxGameObjects = m_level[L"max_game_objects"]->AsNumber();
	JSONArray gameObjects = m_level[L"GameObjects"]->AsArray();
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		JSONObject object = gameObjects[i]->AsObject();
		m_gameData.m_gameObjectVector.push_back(GameData::GObject(object[L"x"]->AsNumber(), object[L"y"]->AsNumber(),
			wStringToString(object[L"Texture"]->AsString()),
			wStringToString(object[L"Type"]->AsString())));
	}
}

GameData & LevelLoader::getGameData(int level)
{
	loadLevelData(level);
	return m_gameData;
}

GameData & LevelLoader::getGameData(string level)
{
	loadLevelData(level);
	return m_gameData;
}

////////////////////////////////////////////////////////////
JSONObject LevelLoader::getTopLevelJSONObject() {
	// Retrieve the main (root) object
	JSONObject root;

	if (m_value->IsObject() == false)
	{
		throw std::exception("Problem with root element in json file, exiting");
	}
	root = m_value->AsObject();

	return root;
}

////////////////////////////////////////////////////////////
std::string LevelLoader::wStringToString(std::wstring const & wstr)
{
	std::string s(wstr.begin(), wstr.end());
	return s;
}

