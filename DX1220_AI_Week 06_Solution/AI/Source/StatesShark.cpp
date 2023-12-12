#include "StatesShark.h"
#include "SceneData.h"
#include "PostOffice.h"
#include "ConcreteMessages.h"

static const float MESSAGE_INTERVAL = 1.f;
static const float CRAZY_SPEED = 16.f;
static const float NAUGHTY_SPEED = 12.f;
static const float HAPPY_SPEED = 8.f;

StateCrazy::StateCrazy(const std::string & stateID)
	: State(stateID)
{
}

StateCrazy::~StateCrazy()
{
}

void StateCrazy::Enter(GameObject* go)
{
	go->moveSpeed = CRAZY_SPEED;
	go->nearest = NULL;
	go->countDown = MESSAGE_INTERVAL;
}

void StateCrazy::Update(double dt, GameObject* go)
{
	if (go->type == GameObject::GO_PAPER)
	{
		if (SceneData::GetInstance()->GetRockCount() <= 12)
			go->sm->SetNextState("Naughty", go);
	}
	else if (go->type == GameObject::GO_ROCK)
	{
		if (SceneData::GetInstance()->GetScissorsCount() <= 12)
			go->sm->SetNextState("Naughty", go);
	}
	else if (go->type == GameObject::GO_SCISSORS)
	{
		if (SceneData::GetInstance()->GetPaperCount() <= 12)
			go->sm->SetNextState("Naughty", go);
	}
	else
		std::cout << "State Crazy not working";



	go->moveLeft = go->moveRight = go->moveUp = go->moveDown = true;
	if (go->nearest)
	{
		if (go->nearest->pos.x > go->pos.x)
			go->moveLeft = false;
		else
			go->moveRight = false;
		if (go->nearest->pos.y > go->pos.y)
			go->moveDown = false;
		else
			go->moveUp = false;
	}
	else //nearest is nullptr
	{
		if (go->countDown >= MESSAGE_INTERVAL) //ensure at least 1 second interval between messages
		{
			go->countDown -= MESSAGE_INTERVAL;

			//week 4
			//send message to Scene requesting for nearest to be updated
			//message is allocated on the heap (WARNING: expensive. 
			//either refactor PostOffice to not assume heap-allocated messages,
			//or pool messages to avoid real-time heap allocation)
			if (go->type == GameObject::GO_PAPER)
			{
				PostOffice::GetInstance()->Send("Scene", new MessageWRU(go, MessageWRU::NEAREST_ROCK, 0)); //no need for threshold here

			}

			if (go->type == GameObject::GO_ROCK)
			{
				PostOffice::GetInstance()->Send("Scene", new MessageWRU(go, MessageWRU::NEAREST_SCISSORS, 0)); //no need for threshold here

			}

			if (go->type == GameObject::GO_SCISSORS)
			{
				PostOffice::GetInstance()->Send("Scene", new MessageWRU(go, MessageWRU::NEAREST_PAPER, 0)); //no need for threshold here

			}
		}
	}
}

void StateCrazy::Exit(GameObject* go)
{
}

StateNaughty::StateNaughty(const std::string & stateID)
	: State(stateID)
{
}

StateNaughty::~StateNaughty()
{
}

void StateNaughty::Enter(GameObject* go)
{
	go->moveSpeed = NAUGHTY_SPEED;
	go->nearest = NULL;
	go->countDown = MESSAGE_INTERVAL;
}

void StateNaughty::Update(double dt, GameObject* go)
{
	go->countDown += static_cast<float>(dt);

	if (go->type == GameObject::GO_PAPER)
	{
		if (SceneData::GetInstance()->GetRockCount() > 12)
			go->sm->SetNextState("Crazy", go);
		else if (SceneData::GetInstance()->GetRockCount() < 6)
			go->sm->SetNextState("Happy", go);
	}
	else if (go->type == GameObject::GO_ROCK)
	{
		if (SceneData::GetInstance()->GetScissorsCount() > 12)
			go->sm->SetNextState("Crazy", go);
		else if (SceneData::GetInstance()->GetScissorsCount() < 6)
			go->sm->SetNextState("Happy", go);
	}
	else if (go->type == GameObject::GO_SCISSORS)
	{
		if (SceneData::GetInstance()->GetPaperCount() > 12)
			go->sm->SetNextState("Crazy", go);
		else if (SceneData::GetInstance()->GetPaperCount() < 6)
			go->sm->SetNextState("Happy", go);
	}
	else
		std::cout << "State naughty not working";



	go->moveLeft = go->moveRight = go->moveUp = go->moveDown = true;
	if (go->nearest)
	{
		if (go->nearest->pos.x > go->pos.x)
			go->moveLeft = false;
		else
			go->moveRight = false;
		if (go->nearest->pos.y > go->pos.y)
			go->moveDown = false;
		else
			go->moveUp = false;
	}
	else //nearest is nullptr
	{
		if (go->countDown >= MESSAGE_INTERVAL) //ensure at least 1 second interval between messages
		{
			go->countDown -= MESSAGE_INTERVAL;

			//week 4
			//send message to Scene requesting for nearest to be updated
			//message is allocated on the heap (WARNING: expensive. 
			//either refactor PostOffice to not assume heap-allocated messages,
			//or pool messages to avoid real-time heap allocation)
			if (go->type == GameObject::GO_PAPER)
			{
				PostOffice::GetInstance()->Send("Scene", new MessageWRU(go, MessageWRU::NEAREST_ROCK, 0)); //no need for threshold here

			}
			else if (go->type == GameObject::GO_ROCK)
			{
				PostOffice::GetInstance()->Send("Scene", new MessageWRU(go, MessageWRU::NEAREST_SCISSORS, 0)); //no need for threshold here

			}	
			else if (go->type == GameObject::GO_SCISSORS)
			{
				PostOffice::GetInstance()->Send("Scene", new MessageWRU(go, MessageWRU::NEAREST_PAPER, 0)); //no need for threshold here

			}
		}
	}
}

void StateNaughty::Exit(GameObject* go)
{
}

StateHappy::StateHappy(const std::string & stateID)
	: State(stateID)
{
}

StateHappy::~StateHappy()
{
}

void StateHappy::Enter(GameObject* go)
{
	go->moveSpeed = HAPPY_SPEED;
	go->moveLeft = go->moveRight = go->moveUp = go->moveDown = true;

	int range[] = { 10, 15 };

	if (go->type == GameObject::GO_PAPER)
	{
		PostOffice::GetInstance()->Send("Scene", new MessageSpawn(go, GameObject::GO_ROCK, 1, range));
	}
	else if (go->type == GameObject::GO_ROCK)
	{
		PostOffice::GetInstance()->Send("Scene", new MessageSpawn(go, GameObject::GO_SCISSORS, 1, range));

	}
	else if (go->type == GameObject::GO_SCISSORS)
	{
		PostOffice::GetInstance()->Send("Scene", new MessageSpawn(go, GameObject::GO_PAPER, 1, range));
	}
}

void StateHappy::Update(double dt, GameObject* go)
{
	if (go->type == GameObject::GO_PAPER)
	{
		if (SceneData::GetInstance()->GetRockCount() >= 6)
			go->sm->SetNextState("Naughty", go);
	}
	else if (go->type == GameObject::GO_ROCK)
	{
		if (SceneData::GetInstance()->GetScissorsCount() >= 6)
			go->sm->SetNextState("Naughty", go);
	}
	else if (go->type == GameObject::GO_SCISSORS)
	{
		if (SceneData::GetInstance()->GetPaperCount() >= 6)
			go->sm->SetNextState("Naughty", go);
	}
	else
		std::cout << "StateHappy Not working";
}

void StateHappy::Exit(GameObject* go)
{
}
