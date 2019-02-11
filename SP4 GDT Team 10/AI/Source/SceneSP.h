#ifndef SCENE_SP_H
#define SCENE_SP_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "Maze.h"
#include <queue>
#include "Graph.h"

class SceneSP : public SceneBase
{
public:
	SceneSP();
	~SceneSP();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	virtual bool Handle(Message* message);

	void RenderGO(GameObject *go);
	GameObject* FetchGO(GameObject::GAMEOBJECT_TYPE type);

	//void AStar(GameObject* go, Vector3 target);
	//void DFSOnce(GameObject* go);

	void Reset();

	enum GAME_STATE
	{
		G_TOTAL
	};
protected:

	std::vector<GameObject *> m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	int m_objectCount;

	GAME_STATE game_state;
};

#endif