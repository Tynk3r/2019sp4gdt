#include "Building.h"
#include "ConcreteMessages.h"

Building::Building(GAMEOBJECT_TYPE typeValue) : GameObject(typeValue)
{
	//GameObject(typeValue);
	this->type;
	std::cout << "Building Constructor" << std::endl;
}

Building::~Building()
{
}

bool Building::Handle(Message* msg)
{
	MessageObject* messageObject = dynamic_cast<MessageObject*>(msg);
	switch (messageObject->type)
	{
	case MessageObject::ACTIVE_OBJECT:
		if (this->active)
		{
			delete msg;
			return true;
		}
		break;
	}
	delete msg;
	return false;
}