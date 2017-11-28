#include "SceneManager.h"

SceneManager::Scenes SceneManager::m_currentScene;
Scene* SceneManager::m_scene;
vector<Scene*> SceneManager::m_sceneList;

SceneManager::SceneManager()
{

}

SceneManager::SceneManager(RenderSystem * renderer)
{
	m_sceneList.push_back(new TestScene);
	m_scene = m_sceneList.at(SceneManager::Test);
	m_currentScene = Scenes::Test;
}

SceneManager::~SceneManager() {}

void SceneManager::EventScene(RenderSystem * Renderer)
{
	m_scene->Event(Renderer);
}

void SceneManager::ChangeStates(SceneManager::Scenes newScene)
{
	switch (newScene)
	{
	case SceneManager::Test:
		cout << "going to: Start scene" << endl;
		m_scene = m_sceneList.at(SceneManager::Test);
		m_currentScene = Scenes::Test;
		break;
	}
}

void SceneManager::LoadNextLevel(RenderWindow& r, SceneManager::Scenes next)
{

}

void SceneManager::UpdateScene(unsigned int DeltaTime)
{
	m_scene->Update(DeltaTime);
}

void SceneManager::RenderScene(RenderSystem * Renderer)
{
	if (m_scene != nullptr)
	{
		m_scene->Render(Renderer);
	}
}