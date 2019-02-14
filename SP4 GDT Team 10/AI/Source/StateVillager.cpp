#include "StateVillager.h"

#include "PostOffice.h"
#include "ConcreteMessages.h"
#include "SceneData.h"
#include "SMManager.h"
#include "ProjectileManager.h"
#include <iostream>

#include "Villager.h"
#include "Building.h"
#include "Bush.h"
#include "Tree.h"
//State::State(const std::string & stateID)
//	: m_stateID(stateID)
//{
//}
//
//State::~State()
//{
//}
//
//const std::string & State::GetStateID()
//{
//	return m_stateID;
//}

static float MOVE_SPEED = 5.f;

//StateIdle
StateIdle::StateIdle(const std::string & stateID)
	: State(stateID)
{
}

StateIdle::~StateIdle()
{
}


void StateIdle::Enter(GameObject* m_go)
{
	std::cout << "Enter Idle State" << std::endl;

	std::cout << "Clearing existing m_go path" << std::endl;

	while (!m_go->path.empty())
	{
		m_go->path.pop_back();
	}
}

void StateIdle::Update(double dt, GameObject* m_go)
{
	if (m_go->goTarget != NULL || m_go->target != NULL)
	{
		m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Path");
		if (m_go->goTarget != NULL && m_go->active)
		{
			MessageWRU* messagewru = new MessageWRU(m_go, MessageWRU::PATH_TO_TARGET, 1);
			PostOffice::GetInstance()->Send("Scene", messagewru);
		}
		else if (m_go->target != NULL)
		{
			MessageWRU* messagewru = new MessageWRU(m_go, MessageWRU::PATH_TO_POINT, 1);
			PostOffice::GetInstance()->Send("Scene", messagewru);
		}
		return;
	}
}

void StateIdle::Exit(GameObject* m_go)
{
}

//StatePath
StatePath::StatePath(const std::string & stateID)
	: State(stateID)
{
}

StatePath::~StatePath()
{
}

void StatePath::Enter(GameObject * m_go)
{
	std::cout << "Enter Path State" << std::endl;
}

void StatePath::Update(double dt, GameObject * m_go)
{
	SceneData* SD = SceneData::GetInstance();
	if (m_go->target != NULL || m_go->goTarget != NULL)
	{
		
		if (m_go->target != NULL)
		{
			if (!m_go->path.empty())
			{
				Vector3 ptPos = GetGridPos(m_go->path.back()); //Position of gridPt in world space
				Vector3 direction = ptPos - m_go->pos;
				direction.y = 0;
				if (direction.LengthSquared() < 0.05f)
				{
					m_go->pos += direction;
					m_go->path.pop_back();
				}
				else
				{
					m_go->pos += (direction).Normalized() * dt * MOVE_SPEED;
				}
			}
			else
			{
				m_go->target = NULL;
				m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
				return;
			}
		}
		else if (m_go->goTarget != NULL)
		{
			if (!m_go->goTarget->active)
			{
				m_go->goTarget = NULL;
				m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
			}
			//Movement
			if (!m_go->path.empty())
			{
				Vector3 ptPos = GetGridPos(m_go->path.back()); //Position of gridPt in world space
				Vector3 direction = ptPos - m_go->pos;
				direction.y = 0;
				if (direction.LengthSquared() < 0.05f)
				{
					m_go->pos += direction;
					m_go->path.pop_back();
				}
				else
				{
					m_go->pos += (direction).Normalized() * dt * MOVE_SPEED;
				}
			}
			else //Reached Destination
			{
				Villager* goVillager = dynamic_cast<Villager*>(m_go->goTarget);
				if (goVillager)
				{
					//If its another villager
					return;
				}
				Building* goBuilding = dynamic_cast<Building*>(m_go->goTarget);
				if (goBuilding)
				{
					//If its a building class
					switch (goBuilding->eCurrState)
					{
					case Building::COMPLETED:
					{
						switch (goBuilding->type)
						{
						case GameObject::GO_BUILDING:
							m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("InHut");
							break;
						case GameObject::GO_CHIEFHUT:
							//m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("InHut");
							SD->SetFood(Math::Min(SD->GetFoodLimit(), SD->GetFood() + static_cast<Villager*>(m_go)->iFoodStored));
							SD->SetWood(Math::Min(SD->GetWoodLimit(), SD->GetWood() + static_cast<Villager*>(m_go)->iWoodStored));

							static_cast<Villager*>(m_go)->iWoodStored = 0;
							static_cast<Villager*>(m_go)->iFoodStored = 0;

							m_go->goTarget = NULL;
							m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
							break;
						case GameObject::GO_HOUSE:
							m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("InHut");
							break;
						}
					}
					break;
					case Building::CONSTRUCTING:
					{
						m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Constructing");
					}
					break;
					case Building::BROKEN:
					{
						m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Constructing");
					}
					break;
					}
					return;
				}
				Environment* goEnvironment = dynamic_cast<Environment*>(m_go->goTarget);
				if (goEnvironment)
				{
					switch (goEnvironment->type)
					{
					case GameObject::GO_BUSH:
						m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Foraging");
						break;
					case GameObject::GO_TREE:
						m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("ChopTree");
						break;
					case GameObject::GO_ROCK:
						m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Mining");
						break;
					}
					return;
				}
				/* //For Enemies
				case GameObject::GO_ENEMY:
					m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Attack");
					break;
				*/
				m_go->goTarget = NULL;
				m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
				return;
			}
		}
	}
	else
	{
		m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
	}
}

void StatePath::Exit(GameObject * m_go)
{
}

//StateChopTree
StateChopTree::StateChopTree(const std::string & stateID)
	: State(stateID)
{
}

StateChopTree::~StateChopTree()
{
}

void StateChopTree::Enter(GameObject * m_go)
{
	std::cout << "Enter Chop Tree State" << std::endl;
}

void StateChopTree::Update(double dt, GameObject * m_go)
{
	//In StateChopTree, the goTarget must be a Tree class
	if (m_go->goTarget->type != GameObject::GO_TREE)
	{
		std::cout << "Wrong State : ChopTree" << std::endl;
		return;
	}
	if (!m_go->goTarget->active)
	{
		m_go->goTarget = NULL;
		m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
	}
	Tree* treeGo = static_cast<Tree*>(m_go->goTarget);
	Villager* vGo = static_cast<Villager*>(m_go);
	if (treeGo->eCurrState == Tree::FULL)
	{
		//Insert gathering time here
		vGo->iWoodStored = treeGo->iWoodAmount;
		treeGo->eCurrState = Tree::HALFCHOPPED;

		MessageWRU* messagewru = new MessageWRU(m_go, MessageWRU::FIND_CHIEFHUT, 1);
		PostOffice::GetInstance()->Send("Scene", messagewru);
		m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
		return;
	}
	if (treeGo->eCurrState == Tree::HALFCHOPPED)
	{
		//Insert gathering time here
		vGo->iWoodStored = treeGo->iWoodAmount;
		treeGo->active = false;

		MessageWRU* messagewru = new MessageWRU(m_go, MessageWRU::FIND_CHIEFHUT, 1);
		PostOffice::GetInstance()->Send("Scene", messagewru);
		m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
		return;
	}
	m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
}

void StateChopTree::Exit(GameObject * m_go)
{
}

//StateForaging
StateForaging::StateForaging(const std::string & stateID)
	: State(stateID)
{
}

StateForaging::~StateForaging()
{
}

void StateForaging::Enter(GameObject * m_go)
{
	std::cout << "Enter Foraging State" << std::endl;
}

void StateForaging::Update(double dt, GameObject * m_go)
{
	//In StateForaging, the goTarget must be a Bush class
	if (m_go->goTarget->type != GameObject::GO_BUSH)
	{
		std::cout << "Wrong State : Foraging" << std::endl;
		return;
	}
	if (!m_go->goTarget->active)
	{
		m_go->goTarget = NULL;
		m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
	}
	Bush* bushGo = static_cast<Bush*>(m_go->goTarget);
	Villager* vGo = static_cast<Villager*>(m_go);
	if (bushGo->eCurrState == Bush::LUSH)
	{
		//Insert gathering time here
		vGo->iFoodStored = bushGo->iFoodAmount;
		bushGo->eCurrState = Bush::DEPLETED;
		m_go->goTarget = NULL;

		MessageWRU* messagewru = new MessageWRU(m_go, MessageWRU::FIND_CHIEFHUT, 1);
		PostOffice::GetInstance()->Send("Scene", messagewru);
		m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
		return;
	}
	m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
}

void StateForaging::Exit(GameObject * m_go)
{
}

//StateAttack
StateAttack::StateAttack(const std::string & stateID)
	: State(stateID)
{
}

StateAttack::~StateAttack()
{
}

void StateAttack::Enter(GameObject* m_go)
{
	std::cout << "Enter Attack State" << std::endl;
}

void StateAttack::Update(double dt, GameObject* m_go)
{
}

void StateAttack::Exit(GameObject* m_go)
{
}

//StatePickedUp
StatePickedUp::StatePickedUp(const std::string & stateID)
	: State(stateID)
{
}

StatePickedUp::~StatePickedUp()
{
}

void StatePickedUp::Enter(GameObject* m_go)
{
	std::cout << "Enter PickedUp State" << std::endl;
}

void StatePickedUp::Update(double dt, GameObject* m_go)
{
}

void StatePickedUp::Exit(GameObject* m_go)
{
}

//StateDead
StateDead::StateDead(const std::string & stateID)
	: State(stateID)
{
}

StateDead::~StateDead()
{
}

void StateDead::Enter(GameObject* m_go)
{
	std::cout << "Enter Dead State" << std::endl;
}

void StateDead::Update(double dt, GameObject* m_go)
{
}

void StateDead::Exit(GameObject* m_go)
{
}

//StateInHut
StateInHut::StateInHut(const std::string & stateID)
	: State(stateID)
{
}

StateInHut::~StateInHut()
{
}


void StateInHut::Enter(GameObject* m_go)
{
	std::cout << "Enter InHut State" << std::endl;
}

void StateInHut::Update(double dt, GameObject* m_go)
{
	//In StateInHut, the goTarget must be a Building class
	Building* goBuilding = dynamic_cast<Building*>(m_go->goTarget);
	Villager* vGo = static_cast<Villager*>(m_go);
	if (goBuilding)
	{
		//IMPORTANT!! MUST BE CHANGED, TEMPORARY CODE FOR CHANING BUILDING'S STATE
		if (!goBuilding->active)
		{
			m_go->goTarget = NULL;
			m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
			return;
		}
		m_go->goTarget = NULL;
		goBuilding->eCurrState = Building::BROKEN;
		m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
	}
	else
	{
		std::cout << "Wrong State : InHut" << std::endl;
		return;
	}
}

void StateInHut::Exit(GameObject* m_go)
{
}

//StateConstructing
StateConstructing::StateConstructing(const std::string & stateID)
	: State(stateID)
{
}

StateConstructing::~StateConstructing()
{
}


void StateConstructing::Enter(GameObject* m_go)
{
	std::cout << "Enter Constructing State" << std::endl;
}

void StateConstructing::Update(double dt, GameObject* m_go)
{
	//In StateConstructing, the goTarget must be a Building class
	Building* goBuilding = dynamic_cast<Building*>(m_go->goTarget);
	Villager* vGo = static_cast<Villager*>(m_go);
	if (goBuilding)
	{
		if (!goBuilding->active)
		{
			m_go->goTarget = NULL;
			m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
			return;
		}
		//Construction and Repair code here, maybe some timer idk
		m_go->goTarget = NULL;
		goBuilding->eCurrState = Building::COMPLETED;
		m_go->m_nextState = SMManager::GetInstance()->GetSM(m_go->smID)->GetState("Idle");
	}
	else
	{
		std::cout << "Wrong State : Constructing" << std::endl;
		return;
	}
}

void StateConstructing::Exit(GameObject* m_go)
{
}

//StateMining
StateMining::StateMining(const std::string & stateID)
	: State(stateID)
{
}

StateMining::~StateMining()
{
}


void StateMining::Enter(GameObject* m_go)
{
	std::cout << "Enter Mining State" << std::endl;
}

void StateMining::Update(double dt, GameObject* m_go)
{
}

void StateMining::Exit(GameObject* m_go)
{
}