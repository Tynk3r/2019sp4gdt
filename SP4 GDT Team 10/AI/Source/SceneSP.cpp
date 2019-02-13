#include "SceneSP.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>
#include "SceneData.h"

#include "SceneData.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"
#include "ProjectileManager.h"
#include "UIManager.h"
#include "UIReligionBar.h"

#include "SMManager.h"
#include "MouseController.h"
#include "KeyboardController.h"

#include "Villager.h"
#include "Building.h"
#include "ChiefHut.h"
#include "Bush.h"
#include "Tree.h"

#define SEA_WIDTH	100.f
#define SEA_HEIGHT	100.f

SceneSP::SceneSP()
{
}

SceneSP::~SceneSP()
{
}

bool SceneSP::isTheCoastClear(GameObject* go, GridPt next, Grid::DIRECTION dir)
{
	if (go->iGridX > 0 && go->iGridZ > 0)
	{
		int iHalfGridX = go->iGridX * 0.5f;
		int iHalfGridZ = go->iGridZ * 0.5f;
		GridPt ptAhead;
		switch (dir)
		{
		case Grid::DIR_LEFT:
			for (int zAxis = 1; zAxis <= iHalfGridZ; ++zAxis)
			{
				ptAhead.Set(next.x - iHalfGridX, next.z + zAxis);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			for (int zAxis = 0; zAxis < (go->iGridZ - iHalfGridZ); ++zAxis)
			{
				ptAhead.Set(next.x - iHalfGridX, next.z - zAxis);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			break;
		case Grid::DIR_RIGHT:
			for (int zAxis = 1; zAxis <= iHalfGridZ; ++zAxis)
			{
				ptAhead.Set(next.x + iHalfGridX, next.z + zAxis);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			for (int zAxis = 0; zAxis < (go->iGridZ - iHalfGridZ); ++zAxis)
			{
				ptAhead.Set(next.x + iHalfGridX, next.z - zAxis);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			break;
		case Grid::DIR_UP:
			for (int xAxis = 1; xAxis <= iHalfGridX; ++xAxis)
			{
				ptAhead.Set(next.x + xAxis, next.z - iHalfGridZ);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}

			for (int xAxis = 0; xAxis < (go->iGridX - iHalfGridX); ++xAxis)
			{
				ptAhead.Set(next.x - xAxis, next.z - iHalfGridZ);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			break;
		case Grid::DIR_DOWN:
			for (int xAxis = 1; xAxis <= iHalfGridX; ++xAxis)
			{
				ptAhead.Set(next.x + xAxis, next.z + iHalfGridZ);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			for (int xAxis = 0; xAxis < (go->iGridX - iHalfGridX); ++xAxis)
			{
				ptAhead.Set(next.x - xAxis, next.z + iHalfGridZ);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			break;
		case Grid::DIR_LEFTUP:
			//Checking Left
			for (int zAxis = 1; zAxis <= iHalfGridZ; ++zAxis)
			{
				ptAhead.Set(next.x - iHalfGridX, next.z + zAxis);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			for (int zAxis = 0; zAxis < (go->iGridZ - iHalfGridZ); ++zAxis)
			{
				ptAhead.Set(next.x - iHalfGridX, next.z - zAxis);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			//Checking Up
			for (int xAxis = 1; xAxis <= iHalfGridX; ++xAxis)
			{
				ptAhead.Set(next.x + xAxis, next.z - iHalfGridZ);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			for (int xAxis = 0; xAxis < (go->iGridX - iHalfGridX); ++xAxis)
			{
				ptAhead.Set(next.x - xAxis, next.z - iHalfGridZ);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			break;
		case Grid::DIR_RIGHTUP:
			//Checking Right
			for (int zAxis = 1; zAxis <= iHalfGridZ; ++zAxis)
			{
				ptAhead.Set(next.x + iHalfGridX, next.z + zAxis);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			for (int zAxis = 0; zAxis < (go->iGridZ - iHalfGridZ); ++zAxis)
			{
				ptAhead.Set(next.x + iHalfGridX, next.z - zAxis);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			//Checking Up
			for (int xAxis = 1; xAxis <= iHalfGridX; ++xAxis)
			{
				ptAhead.Set(next.x + xAxis, next.z - iHalfGridZ);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			for (int xAxis = 0; xAxis < (go->iGridX - iHalfGridX); ++xAxis)
			{
				ptAhead.Set(next.x - xAxis, next.z - iHalfGridZ);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			break;
		case Grid::DIR_LEFTDOWN:
			//Checking Left
			for (int zAxis = 1; zAxis <= iHalfGridZ; ++zAxis)
			{
				ptAhead.Set(next.x - iHalfGridX, next.z + zAxis);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			for (int zAxis = 0; zAxis < (go->iGridZ - iHalfGridZ); ++zAxis)
			{
				ptAhead.Set(next.x - iHalfGridX, next.z - zAxis);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			//Checking Down
			for (int xAxis = 1; xAxis <= iHalfGridX; ++xAxis)
			{
				ptAhead.Set(next.x + xAxis, next.z + iHalfGridZ);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			for (int xAxis = 0; xAxis < (go->iGridX - iHalfGridX); ++xAxis)
			{
				ptAhead.Set(next.x - xAxis, next.z + iHalfGridZ);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			break;
		case Grid::DIR_RIGHTDOWN:
			//Checking Right
			for (int zAxis = 1; zAxis <= iHalfGridZ; ++zAxis)
			{
				ptAhead.Set(next.x + iHalfGridX, next.z + zAxis);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			for (int zAxis = 0; zAxis < (go->iGridZ - iHalfGridZ); ++zAxis)
			{
				ptAhead.Set(next.x + iHalfGridX, next.z - zAxis);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			//Checking Down
			for (int xAxis = 1; xAxis <= iHalfGridX; ++xAxis)
			{
				ptAhead.Set(next.x + xAxis, next.z + iHalfGridZ);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			for (int xAxis = 0; xAxis < (go->iGridX - iHalfGridX); ++xAxis)
			{
				ptAhead.Set(next.x - xAxis, next.z + iHalfGridZ);
				if (isPointInGrid(ptAhead))
				{
					if (m_grid[GetGridIndex(ptAhead)] == Grid::TILE_USED)
					{
						return false;
					}
				}
			}
			break;
		default:
			break;
		}
	}
	return true;
}

void SceneSP::Init()
{
	SceneData::GetInstance()->SetNoGrid(15);
	SceneData::GetInstance()->SetGridSize(1.f);
	SceneData::GetInstance()->SetGridOffset(0.5f);
	SceneBase::Init();

	m_grid.resize(SceneData::GetInstance()->GetNoGrid() * SceneData::GetInstance()->GetNoGrid());
	std::fill(m_grid.begin(), m_grid.end(), Grid::TILE_EMPTY);
	bShowGrid = false;
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	SceneData::GetInstance()->SetWorldHeight(m_worldHeight);
	SceneData::GetInstance()->SetWorldWidth(m_worldWidth);
	SceneData::GetInstance()->SetElapsedTime(0);
	SceneData::GetInstance()->SetReligionValue(0);
	PostOffice::GetInstance()->Register("Scene", this);

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	selected = NULL;

	//Objects from maya, bottom of object to be translated down
	goVillager = FetchGO(GameObject::GO_VILLAGER);
	goVillager->scale.y = 1.f;
	goVillager->pos.Set(0, goVillager->scale.y * 0.5f, 0);
	goVillager->iGridX = 1;
	goVillager->iGridZ = 1;
	goVillager->pos = GetGridPos(GridPt(5, 5));
	goVillager->pos.y = goVillager->scale.y * 0.5f;

	goChiefHut = FetchGO(GameObject::GO_CHIEFHUT);
	goChiefHut->pos = GetGridPos(GridPt(8, 7));
	goChiefHut->pos.y = goChiefHut->scale.y * 0.5f;

	goBush = FetchGO(GameObject::GO_BUSH);
	goBush->pos = GetGridPos(GridPt(1, 1));
	goBush->pos.y = goBush->scale.y * 0.5f;
	Bush* bGo = static_cast<Bush*>(goBush);
	bGo->eCurrState = Bush::LUSH;
	bGo->fTimer = 0;
	bGo->iFoodAmount = 10;

	goTree = FetchGO(GameObject::GO_TREE);
	goTree->pos = GetGridPos(GridPt(2, 8));
	goTree->pos.y = goTree->scale.y * 0.5f;
	goTree->iGridX = 2;
	goTree->iGridZ = 2;
	Tree* tGo = static_cast<Tree*>(goBush);
	tGo->eCurrState = Tree::FULL;
	tGo->fTimer = 0;
	tGo->iWoodAmount = 10;

	SceneData* SD = SceneData::GetInstance();
	SD->SetFood(0);
	SD->SetFoodLimit(100);
	SD->SetPopulation(0);
	SD->SetPopulationLimit(10);
	SD->SetWood(0);
	SD->SetWoodLimit(100);

	bDay = true; // day
	fTimeOfDay = 8.f;

	//go->vel.Set(1, 0, 0);
	MousePicker::GetInstance()->Init();
	MousePicker::GetInstance()->SetProjectionStack(projectionStack);
	MousePicker::GetInstance()->SetViewStack(viewStack);

	UIManager::GetInstance()->Init();
	UIManager::GetInstance()->AddUI(new UIReligionBar());
}


bool SceneSP::Handle(Message* message)
{

	MessageWRU* messageWRU = dynamic_cast<MessageWRU*>(message);
	if (messageWRU)
	{
		switch (messageWRU->type)
		{
		case MessageWRU::FIND_CHIEFHUT:
			messageWRU->go->goTarget = goChiefHut;
			break;
		case MessageWRU::PATH_TO_TARGET:
			AStarGrid(messageWRU->go, GetPoint(messageWRU->go->goTarget->pos));
			break;
		case MessageWRU::PATH_TO_POINT:
			AStarGrid(messageWRU->go, GetPoint(messageWRU->go->target));
			break;
		default:
			break;
		}
		delete message;
		return true;
	}

	delete message;
	return false;
}


GameObject* SceneSP::FetchGO(GameObject::GAMEOBJECT_TYPE type)
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (!go->active && go->type == type)
		{
			go->active = true;
			++m_objectCount;
			switch (type)
			{
			case GameObject::GO_VILLAGER:
				go->scale.Set(SceneData::GetInstance()->GetGridSize() * 0.5f, 0.25f, SceneData::GetInstance()->GetGridSize() * 0.5f);
				break;
			case GameObject::GO_BUSH:
				go->scale.Set(SceneData::GetInstance()->GetGridSize() * 0.75f, 1.f, SceneData::GetInstance()->GetGridSize() * 0.75f);
				break;
			case GameObject::GO_CHIEFHUT:
				go->scale.Set(SceneData::GetInstance()->GetGridSize() * 1.f, 0.5f, SceneData::GetInstance()->GetGridSize() * 1.f);
				break;
			case GameObject::GO_TREE:
				go->scale.Set(SceneData::GetInstance()->GetGridSize() * 1.f, 1.2f, SceneData::GetInstance()->GetGridSize() * 1.f);
				break;
			}

			go->goTarget = NULL;
			return go;
		}
	}
	for (unsigned i = 0; i < 5; ++i)
	{
		GameObject *go = nullptr;
		switch (type)
		{
		case GameObject::GO_VILLAGER:
			go = new Villager(type);
			go->smID = "VillagerSM";
			go->m_currState = go->m_nextState = SMManager::GetInstance()->GetSM(go->smID)->GetState("Idle");
			break;
		case GameObject::GO_BUILDING:
			go = new Building(type);
			break;
		case GameObject::GO_CHIEFHUT:
			go = new ChiefHut(type);
			break;
		case GameObject::GO_BUSH:
			go = new Bush(type);
			break;
		case GameObject::GO_TREE:
			go = new Tree(type);
			break;
		default:
			go = new GameObject(type);
			break;
		}
		if (go != nullptr)
			m_goList.push_back(go);
	}
	return FetchGO(type);
}

struct Compare2
{
	bool operator()(std::pair<GridPt, std::pair<int, int>> pair1, std::pair<GridPt, std::pair<int, int>> pair2)
	{
		return pair1.second.second < pair2.second.second;
	}
};

void SceneSP::AStarGrid(GameObject * go, GridPt target)
{

	//first = curr point, second.first = tile cost, second.second = total cost(tile cost + distance to final destination)
	if (go->currentPt == target)
		return;
	std::vector<std::pair<GridPt, std::pair<int, int>>>priority_Queue;
	std::sort(priority_Queue.begin(), priority_Queue.end(), Compare2());
	while (!m_shortestPath.empty())
	{
		m_shortestPath.pop_back();
	}
	SceneData* SD = SceneData::GetInstance();
	go->m_visited.resize(SD->GetNoGrid() * SD->GetNoGrid());
	std::fill(go->m_visited.begin(), go->m_visited.end(), false);
	//keeping track of the parent node
	m_previous.resize(SD->GetNoGrid() * SD->GetNoGrid());
	std::fill(m_previous.begin(), m_previous.end(), NULL);

	GridPt curr = go->currentPt;
	if (!isPointInGrid(curr))
		return;

	GridPt bestStart = curr; //Closest gridPt to start from
	float fDistanceToTarget = (target.x - curr.x) * (target.x - curr.x) + (target.z - curr.z) * (target.z - curr.z);
	Vector3 ptPos = GetGridPos(curr); //Position of gridPt in world space

	//Check if goPos is left of or right of gridPt
	if (go->pos.x < ptPos.x)
	{
		//Check left of gridPt
		GridPt temp = GridPt(curr.x - 1, curr.z);
		if (isPointInGrid(temp))
		{
			if (isTheCoastClear(go, temp, Grid::DIR_LEFT))
			{
				float distance = (target.x - temp.x) * (target.x - temp.x) + (target.z - temp.z) * (target.z - temp.z);
				if (distance < fDistanceToTarget)
				{
					fDistanceToTarget = distance;
					bestStart = temp;
				}
			}
		}
		//Check if goPos is above or below center of gridPt
		if (go->pos.z < ptPos.z)
		{
			//Check above of gridPt
			temp = GridPt(curr.x, curr.z - 1);
			if (isPointInGrid(temp))
			{
				if (isTheCoastClear(go, temp, Grid::DIR_UP))
				{
					float distance = (target.x - temp.x) * (target.x - temp.x) + (target.z - temp.z) * (target.z - temp.z);
					if (distance < fDistanceToTarget)
					{
						fDistanceToTarget = distance;
						bestStart = temp;
					}
				}
			}
			//Check diagonal
			temp = GridPt(curr.x - 1, curr.z - 1);
			if (isPointInGrid(temp))
			{
				if (isTheCoastClear(go, temp, Grid::DIR_LEFTUP))
				{
					float distance = (target.x - temp.x) * (target.x - temp.x) + (target.z - temp.z) * (target.z - temp.z);
					if (distance < fDistanceToTarget)
					{
						fDistanceToTarget = distance;
						bestStart = temp;
					}
				}
			}
		}
		else
		{
			//Check below of gridPt
			temp = GridPt(curr.x, curr.z + 1);
			if (isPointInGrid(temp))
			{
				if (isTheCoastClear(go, temp, Grid::DIR_DOWN))
				{
					float distance = (target.x - temp.x) * (target.x - temp.x) + (target.z - temp.z) * (target.z - temp.z);
					if (distance < fDistanceToTarget)
					{
						fDistanceToTarget = distance;
						bestStart = temp;
					}
				}
			}
			//Check diagonal
			temp = GridPt(curr.x - 1, curr.z + 1);
			if (isPointInGrid(temp))
			{
				if (isTheCoastClear(go, temp, Grid::DIR_LEFTDOWN))
				{
					float distance = (target.x - temp.x) * (target.x - temp.x) + (target.z - temp.z) * (target.z - temp.z);
					if (distance < fDistanceToTarget)
					{
						fDistanceToTarget = distance;
						bestStart = temp;
					}
				}
			}
		}
	}
	else
	{
		GridPt temp;
		//Check right of gridPt
		if (go->pos.x > ptPos.x)
		{
			temp = GridPt(curr.x + 1, curr.z);
			if (isPointInGrid(temp))
			{
				if (isTheCoastClear(go, temp, Grid::DIR_RIGHT))
				{
					float distance = (target.x - temp.x) * (target.x - temp.x) + (target.z - temp.z) * (target.z - temp.z);
					if (distance < fDistanceToTarget)
					{
						fDistanceToTarget = distance;
						bestStart = temp;
					}
				}
			}
		}
		//Check if goPos is above or below center of gridPt
		if (go->pos.z < ptPos.z)
		{
			//Check above of gridPt
			temp = GridPt(curr.x, curr.z - 1);
			if (isPointInGrid(temp))
			{
				if (isTheCoastClear(go, temp, Grid::DIR_UP))
				{
					float distance = (target.x - temp.x) * (target.x - temp.x) + (target.z - temp.z) * (target.z - temp.z);
					if (distance < fDistanceToTarget)
					{
						fDistanceToTarget = distance;
						bestStart = temp;
					}
				}
			}
			//Check diagonal
			if (go->pos.x > ptPos.x)
			{
				temp = GridPt(curr.x + 1, curr.z - 1);
				if (isPointInGrid(temp))
				{
					if (isTheCoastClear(go, temp, Grid::DIR_RIGHTUP))
					{
						float distance = (target.x - temp.x) * (target.x - temp.x) + (target.z - temp.z) * (target.z - temp.z);
						if (distance < fDistanceToTarget)
						{
							fDistanceToTarget = distance;
							bestStart = temp;
						}
					}
				}
			}
		}
		else if (go->pos.z > ptPos.z)
		{
			//Check below of gridPt
			temp = GridPt(curr.x, curr.z + 1);
			if (isPointInGrid(temp))
			{
				if (isTheCoastClear(go, temp, Grid::DIR_DOWN))
				{
					float distance = (target.x - temp.x) * (target.x - temp.x) + (target.z - temp.z) * (target.z - temp.z);
					if (distance < fDistanceToTarget)
					{
						fDistanceToTarget = distance;
						bestStart = temp;
					}
				}
			}
			//Check diagonal
			temp = GridPt(curr.x + 1, curr.z + 1);
			if (isPointInGrid(temp))
			{
				if (isTheCoastClear(go, temp, Grid::DIR_RIGHTDOWN))
				{
					float distance = (target.x - temp.x) * (target.x - temp.x) + (target.z - temp.z) * (target.z - temp.z);
					if (distance < fDistanceToTarget)
					{
						fDistanceToTarget = distance;
						bestStart = temp;
					}
				}
			}
		}
	}

	int G = 0;
	priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(bestStart, std::pair<int, int>(G, 0)));
	go->m_visited[GetGridIndex(bestStart)] = true;
	float nearestDistance = FLT_MAX;
	GridPt nearestTile = bestStart;
	GridPt next = bestStart;
	int currIndex = 0;

	//Since this value is rounded down, this value is for the closer side of GridPt, refer to gridImage in beside solution file
	int iHalfGridX = go->iGridX * 0.5f;
	int iHalfGridZ = go->iGridZ * 0.5f;


	for (int loop = 0; loop < SD->GetNoGrid() * SD->GetNoGrid() && !priority_Queue.empty(); ++loop)
	{
		//std::cout << "One Round of Loop" << std::endl;
 		curr = priority_Queue.begin()->first;
		//m_queue.pop();


		if (go->iGridX > 0 && go->iGridZ > 0)
		{
			if ((target.x - curr.x) * (target.x - curr.x) <= (go->iGridX - iHalfGridX + 1) * (go->iGridX - iHalfGridX + 1) && (target.z - curr.z) * (target.z - curr.z) <= (go->iGridZ - iHalfGridZ + 1) * (go->iGridZ - iHalfGridZ + 1))
			{
				if(target != curr)
					m_previous[GetGridIndex(target)] = curr;
				priority_Queue.begin()->first = target;
				break;
			}
		}
		else
		{
			if (curr == target)
			{
				break;
			}
		}

		//Check Up
		G = priority_Queue.begin()->second.first;
		next.Set(curr.x, curr.z - 1);
		currIndex = GetGridIndex(next);
		if (isPointInGrid(next))
		{
			float distanceSquared = NULL;
			//Cost of Empty Tile
			G += 1;
			//Calculate distance to end
			distanceSquared = (int)Math::FAbs(target.x - next.x) + (int)Math::FAbs(target.z - next.z);
			if (isTheCoastClear(go, next, Grid::DIR_UP))
			{
				if (!go->m_visited[currIndex])
				{
					//Update node cost
					m_previous[currIndex] = curr;
					priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
					go->m_visited[currIndex] = true;

					//Check if it is the nearest Tile
					if (distanceSquared < nearestDistance)
					{
						nearestDistance = distanceSquared;
						nearestTile = next;
					}
				}
				else if (distanceSquared != NULL)
				{
					//Checks if visited node is in queue
					for (std::vector<std::pair<GridPt, std::pair<int, int>>>::iterator it = priority_Queue.begin(); it != priority_Queue.end(); ++it)
					{
						std::pair<GridPt, std::pair<int, int>> path = *it;
						if (path.first == next)
						{
							//If in queue, check if new path is shorter thn old path
							if (path.second.second > G + distanceSquared)
							{
								//Update if new path is shorter
								priority_Queue.erase(it);
								priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
								m_previous[currIndex] = curr;
							}
							break;
						}
					}
					//If not in queue, node is already in optimal path
				}
			}
		}

		//Check Down
		G = priority_Queue.begin()->second.first;
		next.Set(curr.x, curr.z + 1);
		currIndex = GetGridIndex(next);
		if (isPointInGrid(next))
		{
			float distanceSquared = NULL;
			//Cost of Empty Tile
			G += 1;
			//Calculate distance to end
			distanceSquared = (int)Math::FAbs(target.x - next.x) + (int)Math::FAbs(target.z - next.z);
			if (isTheCoastClear(go, next, Grid::DIR_DOWN))
			{
				if (!go->m_visited[currIndex])
				{
					//Update node cost
					m_previous[currIndex] = curr;
					priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
					go->m_visited[currIndex] = true;

					//Check if it is the nearest Tile
					if (distanceSquared < nearestDistance)
					{
						nearestDistance = distanceSquared;
						nearestTile = next;
					}
				}
				else if (distanceSquared != NULL)
				{
					//Checks if visited node is in queue
					for (std::vector<std::pair<GridPt, std::pair<int, int>>>::iterator it = priority_Queue.begin(); it != priority_Queue.end(); ++it)
					{
						std::pair<GridPt, std::pair<int, int>> path = *it;
						if (path.first == next)
						{
							//If in queue, check if new path is shorter thn old path
							if (path.second.second > G + distanceSquared)
							{
								//Update if new path is shorter
								priority_Queue.erase(it);
								priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
								m_previous[currIndex] = curr;
							}
							break;
						}
					}
					//If not in queue, node is already in optimal path
				}
			}
		}

		//Check Left
		G = priority_Queue.begin()->second.first;
		next.Set(curr.x - 1, curr.z);
		currIndex = GetGridIndex(next);
		if (isPointInGrid(next))
		{
			float distanceSquared = NULL;
			//Cost of Empty Tile
			G += 1;
			//Calculate distance to end
			distanceSquared = (int)Math::FAbs(target.x - next.x) + (int)Math::FAbs(target.z - next.z);
			if (isTheCoastClear(go, next, Grid::DIR_LEFT))
			{
				if (!go->m_visited[currIndex])
				{
					//Update node cost
					m_previous[currIndex] = curr;
					priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
					go->m_visited[currIndex] = true;

					//Check if it is the nearest Tile
					if (distanceSquared < nearestDistance)
					{
						nearestDistance = distanceSquared;
						nearestTile = next;
					}
				}
				else if (distanceSquared != NULL)
				{
					//Checks if visited node is in queue
					for (std::vector<std::pair<GridPt, std::pair<int, int>>>::iterator it = priority_Queue.begin(); it != priority_Queue.end(); ++it)
					{
						std::pair<GridPt, std::pair<int, int>> path = *it;
						if (path.first == next)
						{
							//If in queue, check if new path is shorter thn old path
							if (path.second.second > G + distanceSquared)
							{
								//Update if new path is shorter
								priority_Queue.erase(it);
								priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
								m_previous[currIndex] = curr;
							}
							break;
						}
					}
					//If not in queue, node is already in optimal path
				}
			}
		}

		//Check Right
		G = priority_Queue.begin()->second.first;
		next.Set(curr.x + 1, curr.z);
		currIndex = GetGridIndex(next);
		if (isPointInGrid(next))
		{
			float distanceSquared = NULL;
			//Cost of Empty Tile
			G += 1;
			//Calculate distance to end
			distanceSquared = (int)Math::FAbs(target.x - next.x) + (int)Math::FAbs(target.z - next.z);
			if (isTheCoastClear(go, next, Grid::DIR_RIGHT))
			{
				if (!go->m_visited[currIndex])
				{
					//Update node cost
					m_previous[currIndex] = curr;
					priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
					go->m_visited[currIndex] = true;

					//Check if it is the nearest Tile
					if (distanceSquared < nearestDistance)
					{
						nearestDistance = distanceSquared;
						nearestTile = next;
					}
				}
				else if (distanceSquared != NULL)
				{
					//Checks if visited node is in queue
					for (std::vector<std::pair<GridPt, std::pair<int, int>>>::iterator it = priority_Queue.begin(); it != priority_Queue.end(); ++it)
					{
						std::pair<GridPt, std::pair<int, int>> path = *it;
						if (path.first == next)
						{
							//If in queue, check if new path is shorter thn old path
							if (path.second.second > G + distanceSquared)
							{
								//Update if new path is shorter
								priority_Queue.erase(it);
								priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
								m_previous[currIndex] = curr;
							}
							break;
						}
					}
					//If not in queue, node is already in optimal path
				}
			}
		}

		//Check Up Left
		G = priority_Queue.begin()->second.first;
		next.Set(curr.x - 1, curr.z - 1);
		currIndex = GetGridIndex(next);
		if (isPointInGrid(next))
		{
			float distanceSquared = NULL;
			//Cost of Empty Tile
			G += 1;
			//Calculate distance to end
			distanceSquared = (int)Math::FAbs(target.x - next.x) + (int)Math::FAbs(target.z - next.z);
			if (isTheCoastClear(go, next, Grid::DIR_LEFTUP))
			{
				if (!go->m_visited[currIndex])
				{
					//Update node cost
					m_previous[currIndex] = curr;
					priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
					go->m_visited[currIndex] = true;

					//Check if it is the nearest Tile
					if (distanceSquared < nearestDistance)
					{
						nearestDistance = distanceSquared;
						nearestTile = next;
					}
				}
				else if (distanceSquared != NULL)
				{
					//Checks if visited node is in queue
					for (std::vector<std::pair<GridPt, std::pair<int, int>>>::iterator it = priority_Queue.begin(); it != priority_Queue.end(); ++it)
					{
						std::pair<GridPt, std::pair<int, int>> path = *it;
						if (path.first == next)
						{
							//If in queue, check if new path is shorter thn old path
							if (path.second.second > G + distanceSquared)
							{
								//Update if new path is shorter
								priority_Queue.erase(it);
								priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
								m_previous[currIndex] = curr;
							}
							break;
						}
					}
					//If not in queue, node is already in optimal path
				}
			}
		}

		//Check Up Right
		G = priority_Queue.begin()->second.first;
		next.Set(curr.x + 1, curr.z - 1);
		currIndex = GetGridIndex(next);
		if (isPointInGrid(next))
		{
			float distanceSquared = NULL;
			//Cost of Empty Tile
			G += 1;
			//Calculate distance to end
			distanceSquared = (int)Math::FAbs(target.x - next.x) + (int)Math::FAbs(target.z - next.z);
			if (isTheCoastClear(go, next, Grid::DIR_RIGHTUP))
			{
				if (!go->m_visited[currIndex])
				{
					//Update node cost
					m_previous[currIndex] = curr;
					priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
					go->m_visited[currIndex] = true;

					//Check if it is the nearest Tile
					if (distanceSquared < nearestDistance)
					{
						nearestDistance = distanceSquared;
						nearestTile = next;
					}
				}
				else if (distanceSquared != NULL)
				{
					//Checks if visited node is in queue
					for (std::vector<std::pair<GridPt, std::pair<int, int>>>::iterator it = priority_Queue.begin(); it != priority_Queue.end(); ++it)
					{
						std::pair<GridPt, std::pair<int, int>> path = *it;
						if (path.first == next)
						{
							//If in queue, check if new path is shorter thn old path
							if (path.second.second > G + distanceSquared)
							{
								//Update if new path is shorter
								priority_Queue.erase(it);
								priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
								m_previous[currIndex] = curr;
							}
							break;
						}
					}
					//If not in queue, node is already in optimal path
				}
			}
		}

		//Check Down Left
		G = priority_Queue.begin()->second.first;
		next.Set(curr.x - 1, curr.z + 1);
		currIndex = GetGridIndex(next);
		if (isPointInGrid(next))
		{
			float distanceSquared = NULL;
			//Cost of Empty Tile
			G += 1;
			//Calculate distance to end
			distanceSquared = (int)Math::FAbs(target.x - next.x) + (int)Math::FAbs(target.z - next.z);
			if (isTheCoastClear(go, next, Grid::DIR_LEFTDOWN))
			{
				if (!go->m_visited[currIndex])
				{
					//Update node cost
					m_previous[currIndex] = curr;
					priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
					go->m_visited[currIndex] = true;

					//Check if it is the nearest Tile
					if (distanceSquared < nearestDistance)
					{
						nearestDistance = distanceSquared;
						nearestTile = next;
					}
				}
				else if (distanceSquared != NULL)
				{
					//Checks if visited node is in queue
					for (std::vector<std::pair<GridPt, std::pair<int, int>>>::iterator it = priority_Queue.begin(); it != priority_Queue.end(); ++it)
					{
						std::pair<GridPt, std::pair<int, int>> path = *it;
						if (path.first == next)
						{
							//If in queue, check if new path is shorter thn old path
							if (path.second.second > G + distanceSquared)
							{
								//Update if new path is shorter
								priority_Queue.erase(it);
								priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
								m_previous[currIndex] = curr;
							}
							break;
						}
					}
					//If not in queue, node is already in optimal path
				}
			}
		}

		//Check Down Right
		G = priority_Queue.begin()->second.first;
		next.Set(curr.x + 1, curr.z + 1);
		currIndex = GetGridIndex(next);
		if (isPointInGrid(next))
		{
			float distanceSquared = NULL;
			//Cost of Empty Tile
			G += 1;
			//Calculate distance to end
			distanceSquared = (int)Math::FAbs(target.x - next.x) + (int)Math::FAbs(target.z - next.z);
			if (isTheCoastClear(go, next, Grid::DIR_RIGHTDOWN))
			{
				if (!go->m_visited[currIndex])
				{
					//Update node cost
					m_previous[currIndex] = curr;
					priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
					go->m_visited[currIndex] = true;

					//Check if it is the nearest Tile
					if (distanceSquared < nearestDistance)
					{
						nearestDistance = distanceSquared;
						nearestTile = next;
					}
				}
				else if (distanceSquared != NULL)
				{
					//Checks if visited node is in queue
					for (std::vector<std::pair<GridPt, std::pair<int, int>>>::iterator it = priority_Queue.begin(); it != priority_Queue.end(); ++it)
					{
						std::pair<GridPt, std::pair<int, int>> path = *it;
						if (path.first == next)
						{
							//If in queue, check if new path is shorter thn old path
							if (path.second.second > G + distanceSquared)
							{
								//Update if new path is shorter
								priority_Queue.erase(it);
								priority_Queue.push_back(std::pair<GridPt, std::pair<int, int>>(next, std::pair<int, int>(G, G + distanceSquared)));
								m_previous[currIndex] = curr;
							}
							break;
						}
					}
					//If not in queue, node is already in optimal path
				}
			}
		}

		priority_Queue.erase(priority_Queue.begin());
		std::sort(priority_Queue.begin(), priority_Queue.end(), Compare2());
	}

	if (priority_Queue.size() > 0)
	{
		if (priority_Queue.begin()->first == target)
		{
			//If manage to reach target
			curr = target;
			m_shortestPath.push_back(curr);
			curr = m_previous[GetGridIndex(curr)];
			while (curr != NULL)
			{
				m_shortestPath.push_back(curr);
				curr = m_previous[GetGridIndex(curr)];
				std::cout << "hi" << std::endl;
			}
		}
		else
		{
			//If unable to reach target
			curr = nearestTile;
			m_shortestPath.push_back(curr);
			curr = m_previous[GetGridIndex(curr)];
			while (curr != NULL)
			{
				m_shortestPath.push_back(curr);
				curr = m_previous[GetGridIndex(curr)];
				std::cout << "hi" << std::endl;
			}
		}
	}
	else
	{
		//If something happened
		curr = nearestTile;
		m_shortestPath.push_back(curr);
		curr = m_previous[GetGridIndex(curr)];
		while (curr != NULL)
		{
			m_shortestPath.push_back(curr);
			curr = m_previous[GetGridIndex(curr)];
			std::cout << "hi" << std::endl;
		}
	}

	//Just take based on range of movement 
	while (!m_shortestPath.empty())
	{
		go->path.push_back(m_shortestPath.back());
		m_shortestPath.pop_back();
	}
	if (go->path.size() > 1)
	{
		std::reverse(go->path.begin(), go->path.end());
	}
	//std::cout << priority_Queue.begin()->second.first << std::endl;
	//return priority_Queue.begin()->second.first;
}

//void SceneSP::AStar(GameObject * go, Vector3 target)
//{
//	go->m_visited.resize(m_graph.nodeID);
//	std::fill(go->m_visited.begin(), go->m_visited.end(), false);
//	go->gPath.clear();
//	node* nearestToTarget = m_graph.NearestNode(target);
//
//	//node* is the current node, first float is cost to node, second float is cost to node + distance to end
//	std::vector<std::pair<node*, std::pair<float, float>>> m_queue;
//	m_queue.push_back(std::pair<node*, std::pair<float, float>>(go->currNode, std::pair<float, float>(0.f, (nearestToTarget->pos - go->currNode->pos).LengthSquared())));
//	while (m_queue.front().first != nearestToTarget && !m_queue.empty())
//	{
//
//		std::pair<node*, std::pair<float, float>> curr = m_queue.front();
//		node* currNode = curr.first;
//
//		for (auto edges : currNode->edges)
//		{
//			float cost = curr.second.first + edges->length;
//			float costToEnd = cost + (nearestToTarget->pos - edges->dst->pos).LengthSquared();
//			std::pair<node*, std::pair<float, float>> value(edges->dst, std::pair<float, float>(cost, costToEnd));
//			if (!go->m_visited[edges->dst->ID - 1])
//			{
//				edges->dst->previous = currNode;
//				go->m_visited[edges->dst->ID - 1] = true;
//				bool inserted = false;
//				for (std::vector<std::pair<node*, std::pair<float, float>>>::iterator it = m_queue.begin(); it != m_queue.end(); ++it)
//				{
//					std::pair<node*, std::pair<float, float>> temp = *it;
//					if (value.second.second < temp.second.second)
//					{
//						m_queue.insert(it,value);
//						inserted = true;
//						break;
//					}
//				}
//				if (!inserted)
//				{
//					m_queue.push_back(value);
//				}
//			}
//			else
//			{
//				for (auto go : m_queue)
//				{
//					if (go.first == value.first)
//					{
//						edges->dst->previous = currNode;
//						go = value;
//						break;
//					}
//				}
//			}
//		}
//		std::vector<std::pair<node*, std::pair<float, float>>>::iterator tempit;
//		tempit = std::find(m_queue.begin(), m_queue.end(), curr);
//		m_queue.erase(tempit);
//	}
//
//	node* curr = nearestToTarget;
//	while (curr != go->currNode)
//	{
//		go->gPath.push_back(curr->pos);
//		curr = curr->previous;
//	}
//}
//
//void SceneSP::DFSOnce(GameObject * go)
//{
//	go->gStack.push_back(go->currNode);
//	go->m_visited[go->currNode->ID - 1] = true;
//	for (auto edge : go->currNode->edges)
//	{
//		if (!go->m_visited[edge->dst->ID - 1])
//		{
//			go->currNode = edge->dst;
//			return;
//		}
//	}
//	go->gStack.pop_back();
//	if (!go->gStack.empty())
//	{
//		go->currNode = go->gStack.back();
//		go->gStack.pop_back();
//	}
//	return;
//}

void SceneSP::Reset()
{
	//Cleanup GameObjects
	while (m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}

	m_speed = 1.f;

	//game_state = NEUTRAL;
}

void SceneSP::ChangeTimeOfDay()
{
	bDay = !bDay;
	if (bDay) // daytime reset
	{
		bGodlights = false;
		for (auto go : m_goList)
		{
			if (!go->active)
				continue;
			if (go->type == GameObject::GO_BUSH)
			{
				if (static_cast<Bush*>(go)->eCurrState == Bush::DEPLETED)
					static_cast<Bush*>(go)->eCurrState = Bush::LUSH;
			}
		}
	}
	else // nighttime reset
	{
		bGodlights = true;
		SceneData* SD = SceneData::GetInstance();
		SD->SetFood(Math::Max(0, SD->GetFood() - SD->GetPopulation() * 5));// 5 food is eaten per Villager
	}
}

void SceneSP::Update(double dt)
{
	if (Application::IsKeyPressed('R'))
	{
		Reset();
		Sleep(100);
		return;
	}
	SceneData* SD = SceneData::GetInstance();
	MousePicker* MP = MousePicker::GetInstance();
	MouseController* MC = MouseController::GetInstance();
	KeyboardController* KC = KeyboardController::GetInstance();
	UIManager* UIM = UIManager::GetInstance();

	SceneBase::Update(dt);
	MP->Update(dt);
	camera.Update(dt);
	UIM->Update(dt);

	if (KC->IsKeyPressed('P')) {//A TEST TO CHANGE RELIGION VALUE DIS WONT BE IN DA FNIAL GAME
		SD->SetReligionValue(((int)SD->GetReligionValue() % 100) + 25);
	}

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	SD->SetWorldHeight(m_worldHeight);
	SD->SetWorldWidth(m_worldWidth);
	SD->SetElapsedTime(SD->GetElapsedTime() + (float)dt);

	mousePos = MP->GetIntersectionWithPlane(camera.position, Vector3(0, 0, 0), Vector3(0, 1, 0));

	if (Application::IsKeyPressed(VK_OEM_MINUS))
	{
		m_speed = Math::Max(0.f, m_speed - 0.1f);
	}
	if (Application::IsKeyPressed(VK_OEM_PLUS))
	{
		m_speed += 0.1f;
	}
	if (Application::IsKeyPressed('N'))
	{
	}
	if (Application::IsKeyPressed('M'))
	{
	}
	if (Application::IsKeyPressed(VK_RETURN))
	{
	}
	if (Application::IsKeyPressed('5'))
		bGodlights = true; // lights off
	if (Application::IsKeyPressed('6'))
		bGodlights = false; // lights on
	//if (MC->IsButtonPressed(MouseController::LMB))
		//std::cout << "asd" << std::endl;

	//Input Section
	static bool bPState = false;
	if (!bPState && Application::IsKeyPressed('P'))
	{
		bPState = true;
	}
	else if (bPState && !Application::IsKeyPressed('P'))
	{
		bPState = false;
		std::cout << "P UP" << std::endl;
	}

	static bool bFState = false;
	if (KC->IsKeyPressed('F'))
	{
		bFState = true;
		goVillager->goTarget = goBush;
	}
	else if (bFState && !Application::IsKeyPressed('F'))
	{
		bFState = false;
		std::cout << "F UP" << std::endl;
	}

	if (KC->IsKeyPressed('G'))
	{
		bShowGrid = !bShowGrid;
	}


	//Temporary Movement
	GridPt currPos = goVillager->currentPt;
	if (KC->IsKeyDown('W'))
	{
		if (goVillager->m_currState == SMManager::GetInstance()->GetSM(goVillager->smID)->GetState("Idle"))
		{
			GridPt UP(currPos.x, currPos.z - 1);
			if (isPointInGrid(UP))
			{
				float y = goVillager->pos.y;
				goVillager->target = GetGridPos(UP);
				goVillager->target.y = y;
			}
		}
	}
	if (KC->IsKeyDown('S'))
	{
		if (goVillager->m_currState == SMManager::GetInstance()->GetSM(goVillager->smID)->GetState("Idle"))
		{
			GridPt DOWN(currPos.x, currPos.z + 1);
			if (isPointInGrid(DOWN))
			{
				float y = goVillager->pos.y;
				goVillager->target = GetGridPos(DOWN);
				goVillager->target.y = y;
			}
		}
	}
	if (KC->IsKeyDown('A'))
	{
		if (goVillager->m_currState == SMManager::GetInstance()->GetSM(goVillager->smID)->GetState("Idle"))
		{
			GridPt LEFT(currPos.x - 1, currPos.z);
			if (isPointInGrid(LEFT))
			{
				float y = goVillager->pos.y;
				goVillager->target = GetGridPos(LEFT);
				goVillager->target.y = y;
			}
		}
	}
	if (KC->IsKeyDown('D'))
	{
		if (goVillager->m_currState == SMManager::GetInstance()->GetSM(goVillager->smID)->GetState("Idle"))
		{
			GridPt RIGHT(currPos.x + 1, currPos.z);
			if (isPointInGrid(RIGHT))
			{
				float y = goVillager->pos.y;
				goVillager->target = GetGridPos(RIGHT);
				goVillager->target.y = y;
			}
		}
	}
	
	Vector3 clickTarget = NULL;
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		//std::cout << "LBUTTON DOWN" << std::endl;

		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = static_cast<float>(x) / w * m_worldWidth;
		float posY = (h - static_cast<float>(y)) / h * m_worldHeight;
		//std::cout << mousePos << std::endl;
		GridPt selectedPt = GetPoint(mousePos);
		//std::cout << "Selected Grid: " << selectedPt.x << ", " << selectedPt.z << std::endl;
		bool objectFound = false;
		for (auto go : m_goList)
		{
			if (!go->active)
				continue;
			if (selectedPt == go->currentPt)
			{
				selected = go;
				if (selected != goVillager)
				{
					objectFound = true;
					goVillager->m_nextState = SMManager::GetInstance()->GetSM(goVillager->smID)->GetState("Idle");
					goVillager->goTarget = selected;
				}
			}
		}
		if (!objectFound)
		{
			goVillager->goTarget = NULL;
			if (m_grid[GetGridIndex(selectedPt)] == Grid::TILE_EMPTY)
			{
				goVillager->target = GetGridPos(selectedPt);
				goVillager->m_nextState = SMManager::GetInstance()->GetSM(goVillager->smID)->GetState("Idle");
			}
		}
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		//std::cout << "LBUTTON UP" << std::endl;
	}

	/*static bool bRButtonState = false;
	if (!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;

		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = static_cast<float>(x) / w * m_worldWidth;
		float posY = (h - static_cast<float>(y)) / h * m_worldHeight;
		if (posX < m_worldHeight && posY < m_worldHeight)
		{
			
		}

	}
	else if (bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;
	}*/

	/*static bool bSpaceState = false;
	if (!bSpaceState && Application::IsKeyPressed(VK_SPACE))
	{
		bSpaceState = true;

		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = static_cast<float>(x) / w * m_worldWidth;
		float posY = (h - static_cast<float>(y)) / h * m_worldHeight;
		if (posX < m_worldHeight && posY < m_worldHeight)
		{
			GameObject* go = FetchGO(GameObject::GO_NPC);
			go->pos.Set(posX, posY);
		}
	}
	else if (bSpaceState && !Application::IsKeyPressed(VK_SPACE))
	{
		bSpaceState = false;
	}*/

	// day/night cycle
	fTimeOfDay += dt ;
	if (fTimeOfDay >= 24.f)
	{
		fTimeOfDay = 0;
	}
	else if (fTimeOfDay >= 8.f && fTimeOfDay <= 20.f && !bDay) // 0800 to 2000 day
	{
		ChangeTimeOfDay();
	}
	else if ((fTimeOfDay <= 8.f || fTimeOfDay >= 20.f) && bDay) // 2000 to 0800 night
	{
		ChangeTimeOfDay();
	}

	// sea movement
	if (fSeaDeltaX >= SEA_WIDTH / 4)
		fSeaDeltaX = -SEA_WIDTH / 4;
	fSeaDeltaX += dt;
	if (fSeaDeltaZ >= SEA_HEIGHT / 4)
		fSeaDeltaZ = -SEA_HEIGHT / 4;
	fSeaDeltaZ += dt;

	fSeaDeltaY = 0.25f + 0.25f * cosf(SD->GetElapsedTime());

	ProjectileManager::GetInstance()->Update(dt * m_speed);
	static const float NPC_VELOCITY = 10.f;

	SD->SetPopulation(0);
	SD->SetPopulationLimit(0);

	//Update the Grid
	std::fill(m_grid.begin(), m_grid.end(), Grid::TILE_EMPTY);
	m_grid[5] = Grid::TILE_USED;
	m_grid[15] = Grid::TILE_USED;
	m_grid[25] = Grid::TILE_USED;
	m_grid[35] = Grid::TILE_USED;
	m_grid[4] = Grid::TILE_USED;
	m_grid[14] = Grid::TILE_USED;
	m_grid[24] = Grid::TILE_USED;
	m_grid[34] = Grid::TILE_USED;
	for (auto go : m_goList)
	{
		if (!go->active)
			continue;
		GridPt gridPt = go->currentPt;
		if (isPointInGrid(gridPt))
		{
			Vector3 ptPos = GetGridPos(gridPt); //Position of gridPt in world space

			//Check if this GameObject takes up a GridPt
			if (go->iGridX > 0 && go->iGridZ > 0)
			{
				//Since this value is rounded down, this value is for the closer side of GridPt, refer to gridImage in beside solution file
				int iHalfGridX = go->iGridX * 0.5f;
				int iHalfGridZ = go->iGridZ * 0.5f;

				//Check which side
				bool bLeftSide = false;
				if (go->pos.x < ptPos.x)
				{
					bLeftSide = true;
				}
				//Check which side
				bool bUpSide = false;
				if (go->pos.z < ptPos.z)
				{
					bUpSide = true;
				}

				//x-axis
				for (int i = 1; i <= iHalfGridX; ++i)
				{
					for (int j = 1; j <= iHalfGridZ; ++j)
					{
						if (bLeftSide)
						{
							if (bUpSide)
							{
								GridPt pointToChange(gridPt.x - i, gridPt.z - j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
							else
							{
								GridPt pointToChange(gridPt.x - i, gridPt.z + j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
						}
						else
						{
							if (bUpSide)
							{
								GridPt pointToChange(gridPt.x + i, gridPt.z - j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
							else
							{
								GridPt pointToChange(gridPt.x + i, gridPt.z + j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
						}
					}
					for (int j = 0; j < (go->iGridZ - iHalfGridZ); ++j)
					{
						if (bLeftSide)
						{
							if (bUpSide)
							{
								GridPt pointToChange(gridPt.x - i, gridPt.z + j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
							else
							{
								GridPt pointToChange(gridPt.x - i, gridPt.z - j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
						}
						else
						{
							if (bUpSide)
							{
								GridPt pointToChange(gridPt.x + i, gridPt.z + j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
							else
							{
								GridPt pointToChange(gridPt.x + i, gridPt.z - j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
						}
					}
				}
				for (int i = 0; i < (go->iGridX - iHalfGridX); ++i)
				{
					for (int j = 1; j <= iHalfGridZ; ++j)
					{
						if (bLeftSide)
						{
							if (bUpSide)
							{
								GridPt pointToChange(gridPt.x + i, gridPt.z - j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
							else
							{
								GridPt pointToChange(gridPt.x + i, gridPt.z + j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
						}
						else
						{
							if (bUpSide)
							{
								GridPt pointToChange(gridPt.x - i, gridPt.z - j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
							else
							{
								GridPt pointToChange(gridPt.x - i, gridPt.z + j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
						}
					}
					for (int j = 0; j < (go->iGridZ - iHalfGridZ); ++j)
					{
						if (bLeftSide)
						{
							if (bUpSide)
							{
								GridPt pointToChange(gridPt.x + i, gridPt.z + j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
							else
							{
								GridPt pointToChange(gridPt.x + i, gridPt.z - j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
						}
						else
						{
							if (bUpSide)
							{
								GridPt pointToChange(gridPt.x - i, gridPt.z + j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
							else
							{
								GridPt pointToChange(gridPt.x - i, gridPt.z - j);
								if (isPointInGrid(pointToChange))
								{
									if (m_grid[GetGridIndex(pointToChange)] == Grid::TILE_EMPTY)
									{
										m_grid[GetGridIndex(pointToChange)] = Grid::TILE_USED;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	//Update the GameObjects
	for (auto go : m_goList)
	{
		if (!go->active)
			continue;
		go->currentPt = GetPoint(go->pos);
		// updating GameObjects
		switch (go->type)
		{
		case GameObject::GO_VILLAGER:
			SD->SetPopulation(SD->GetPopulation() + 1);
			break;
		case GameObject::GO_CHIEFHUT:
			SD->SetPopulationLimit(SD->GetPopulationLimit() + 10);
			break;
		case GameObject::GO_BUSH:
			break;
		default:
			break;
		}


		/*if (go->type == GameObject::GO_NPC)
		{
			if (go->target == NULL)
			{
			}
			if (go->target != NULL)
			{
				if ((go->pos - go->target).LengthSquared() < 1.f)
				{
					go->pos = go->target;
				}
				else
				{
					try
					{
						go->pos += (go->target - go->pos).Normalized() * NPC_VELOCITY * m_speed * static_cast<float>(dt);
					}
					catch (DivideByZero)
					{
						//Do nothing
					}
				}
			}
		}
		else if (go->type == GameObject::GO_CREEP_MELEE || go->type == GameObject::GO_CREEP_RANGE)
		{
			if (go->smID != "")
			{
				SMManager::GetInstance()->GetSM(go->smID)->Update(dt * m_speed, go);
			}
		}*/
		//go->pos += go->vel * dt * m_speed;
		if (go->smID != "")
		{
			SMManager::GetInstance()->GetSM(go->smID)->Update(dt * m_speed, go);
		}
	}
}


void SceneSP::RenderGO(GameObject *go)
{
	switch (go->type)
	{
	case GameObject::GO_VILLAGER:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		//Offset to center to middle of used grids
		if (go->iGridX % 2 == 0)
		{
			modelStack.Translate(SceneData::GetInstance()->GetGridSize() * 0.5f, 0, 0);
		}
		if (go->iGridZ % 2 == 0)
		{
			modelStack.Translate(0, 0, SceneData::GetInstance()->GetGridSize() * 0.5f);
		}
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		//RenderMesh(meshList[GEO_VILLAGER], false, 1.f);
		//RenderMesh(meshList[GEO_TREE], false, 1.f);
		//RenderMesh(meshList[GEO_BERRIES], false, 1.f);
		//RenderMesh(meshList[GEO_BUSH], false, 1.f);
		RenderMesh(meshList[GEO_VILLAGER], bGodlights, 1.f);
		modelStack.PopMatrix();
	}
	break;
	case GameObject::GO_BUILDING:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BUILDING], bGodlights, 1.f);
		modelStack.PopMatrix();
	}
	break;
	case GameObject::GO_CHIEFHUT:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BUILDING], bGodlights, 1.f);
		modelStack.PopMatrix();
	}
	break;
	case GameObject::GO_BUSH:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BUSH], bGodlights, 1.f);
		if (static_cast<Bush*>(go)->eCurrState == Bush::LUSH)
			RenderMesh(meshList[GEO_BERRIES], bGodlights, 1.f);
		modelStack.PopMatrix();
	}
	break;
	case GameObject::GO_TREE:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		//Offset to center to middle of used grids
		if (go->iGridX % 2 == 0)
		{
			modelStack.Translate(SceneData::GetInstance()->GetGridSize() * 0.5f, 0, 0);
		}
		if (go->iGridZ % 2 == 0)
		{
			modelStack.Translate(0, 0, SceneData::GetInstance()->GetGridSize() * 0.5f);
		}
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		Tree* goTree = static_cast<Tree*>(go);
		switch (goTree->eCurrState)
		{
		case Tree::FULL:
			RenderMesh(meshList[GEO_TREE], bGodlights, 1.f);
			break;
		case Tree::HALFCHOPPED:
			RenderMesh(meshList[GEO_HALFTREE], bGodlights, 1.f);
			break;
		default:
			RenderMesh(meshList[GEO_TREE], bGodlights, 1.f);
			break;
		}
		modelStack.PopMatrix();
	}
	break;
	default:
		break;
	}
}

void SceneSP::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	//projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -1000, 1000);
	float aspect = (float)Application::GetInstance().GetWindowWidth() / (float)Application::GetInstance().GetWindowHeight();
	projection.SetToPerspective(70.f, aspect, 0.01f, 2000);
	projectionStack.LoadMatrix(projection);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	modelStack.PushMatrix(); 
	modelStack.Translate(mousePos.x, mousePos.y, mousePos.z);
	modelStack.Scale(0.1, 0.1, 0.1);
	RenderMesh(meshList[GEO_VILLAGER], false);
	modelStack.PopMatrix();

	RenderMesh(meshList[GEO_AXES], false);

	static float asd = 0;
	asd += 0.01;
	modelStack.PushMatrix();
	//modelStack.Translate(0, 0.5f + cosf(asd) * 0.15f, 0);
	modelStack.Translate(0, -0.5f, 0);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(15, 1, 15);
	RenderMesh(meshList[GEO_GRASS], bGodlights);
	modelStack.PopMatrix();

	SceneData* SD = SceneData::GetInstance();

	if (bShowGrid)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.5f * SD->GetNoGrid() * SD->GetGridSize(), 0.001f, -0.5f * SD->GetNoGrid() * SD->GetGridSize());
		modelStack.Scale(1, 1, 1);
		glLineWidth(2.f);
		RenderMesh(meshList[GEO_GRID], false);
		glLineWidth(1.f);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-0.5f * SD->GetNoGrid() * SD->GetGridSize(), 0.001f, -0.5f * SD->GetNoGrid() * SD->GetGridSize());
		for (int i = 0; i < SD->GetNoGrid() * SD->GetNoGrid(); ++i)
		{
			std::pair<int, int> pt = GetPoint(i);
			modelStack.PushMatrix();
			modelStack.Translate(pt.first * SD->GetGridSize() + SD->GetGridOffset(), 0, pt.second * SD->GetGridSize() + SD->GetGridOffset());
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(SD->GetGridSize(), SD->GetGridSize(), SD->GetGridSize());
			switch (m_grid[i])
			{
			case Grid::TILE_EMPTY:
				RenderMesh(meshList[GEO_GREENQUAD], false, 0.3f);
				break;
			case Grid::TILE_USED:
				RenderMesh(meshList[GEO_REDQUAD], false, 0.3f);
				break;
			}
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(fSeaDeltaX, fSeaDeltaY - 0.51f, fSeaDeltaZ);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(SEA_WIDTH, SEA_HEIGHT, SEA_HEIGHT);
	RenderMesh(meshList[GEO_SEA], bGodlights);
	modelStack.PopMatrix();

	//On screen text
	std::ostringstream ss;

	if (selected != NULL)
	{
		modelStack.PushMatrix();
		modelStack.Translate(selected->pos.x, selected->pos.y + 1.0f, selected->pos.z);
		modelStack.Scale(0.1, 0.1, 0.1);
		RenderMesh(meshList[GEO_VILLAGER], false); // renders a red cube above GO if it is currently selected
		modelStack.PopMatrix();
	}
	for (auto go : m_goList)
	{
		if (!go->active)
			continue;
		RenderGO(go);
	}

	UIManager::GetInstance()->Render(this);

	ss.str("");
	ss.precision(3);
	ss << "Speed:" << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 6);

	ss.str("");
	ss.precision(5);
	ss << "FPS:" << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 3);

	ss.str("");
	ss << "Graph " << 0;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 0);

	// resources
	ss.str("");
	//ss.precision(5);
	ss << "Food:" << SD->GetFood() << "/" << SD->GetFoodLimit();
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 10, 3);

	ss.str("");
	ss << "Population:" << SD->GetPopulation() << "/" << SD->GetPopulationLimit();
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 10, 0);

	ss.str("");
	ss << "Time: ";
	float fractpart, intpart;
	fractpart = modf(fTimeOfDay, &intpart);
	if (intpart < 10)
		ss << "0" << intpart;
	else
		ss << intpart;
	ss << ":"; 
	if ((int)(60 * fractpart) < 10)
		ss << "0" << (int)(60 * fractpart);
	else
		ss << (int)(60 * fractpart);
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 30, 0);
}

void SceneSP::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while (m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
}
