#pragma once
#include "stdafx.h"
#include "Scene.h"
#include "TestScene.h"

class SceneManager
{
public:
	enum Scenes
	{
		Test = 0
	};

	SceneManager();
	SceneManager(RenderSystem *);
	~SceneManager();
	//Switches between the scenes
	static void ChangeStates(Scenes newScene);
	void LoadNextLevel(RenderWindow&, Scenes);


	Scenes GetCurrentState()
	{
		return m_currentScene;
	}
	void EventScene(RenderSystem * Renderer);
	void UpdateScene(unsigned int DeltaTime);
	void RenderScene(RenderSystem * Renderer);

	Scene* getScene()
	{
		return m_scene;
	};

private:
	static Scenes m_currentScene;
	static Scene* m_scene;
	static vector<Scene*> m_sceneList;
};