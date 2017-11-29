#ifndef LEVElLOADER_H
#define LEVElLOADER_H

#include "GameData.h"
#include "JSON.h"


////////////////////////////////////////////////////////////
/// \brief A class to load all the configuration data
///        required by the game. 
///
////////////////////////////////////////////////////////////

class LevelLoader {
public:
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// This constructor initialises the JSON parser and loads
	/// the menu and game level data.
	///
	/// \param filename The path and filename of the JSON file.
	///
	////////////////////////////////////////////////////////////
	LevelLoader(std::string const & filename);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	/// Frees resources acquired by the JSON parser.
	///
	////////////////////////////////////////////////////////////
	~LevelLoader();

	////////////////////////////////////////////////////////////
	/// \brief Loads the JSON data from the specified file.
	///
	/// \param filename The path and filename of the JSON file.
	///
	////////////////////////////////////////////////////////////
	void load(std::string const & filename);

	////////////////////////////////////////////////////////////
	/// \brief Get the game configuration data
	///
	/// \return A GameData instance containing config values
	///
	///	
	////////////////////////////////////////////////////////////
	GameData & getGameData(int level);
	GameData & getGameData(string level);


	void loadLevelData(int level);
	void loadLevelData(string level);

private:
	JSONValue *m_value;
	std::string m_JSONData;
	GameData m_gameData;

	void loadJSONData(std::string const & filename);

	void loadMenuData();

	


	// Utility methods.
	JSONObject getTopLevelJSONObject();
	std::string wStringToString(std::wstring const & wstr);

};

#endif