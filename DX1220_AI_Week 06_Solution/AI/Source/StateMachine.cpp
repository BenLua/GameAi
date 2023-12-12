#include "StateMachine.h"
#include "GameObject.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
	for (std::map<std::string, State*>::iterator it = m_stateMap.begin(); it != m_stateMap.end(); ++it)
	{
		delete it->second;
	}
	m_stateMap.clear();
}

void StateMachine::AddState(State *newState)
{
	if (!newState)
		return;
	if (m_stateMap.find(newState->GetStateID()) != m_stateMap.end())
		return;
	m_stateMap.insert(std::pair<std::string, State*>(newState->GetStateID(), newState));

	std::cout << "Added state \n";
}

void StateMachine::SetNextState(const std::string &nextStateID, GameObject* go)
{
	std::map<std::string, State*>::iterator it = m_stateMap.find(nextStateID);
	if (it != m_stateMap.end())
	{
		go->nextState = (State *)it->second;
	}
}

const std::string & StateMachine::GetCurrentState(GameObject* go)
{
	static std::string errorMsg{ "<No states>" };
	if (go->currState)
		return go->currState->GetStateID();
	return errorMsg;
}

void StateMachine::Update(double dt, GameObject* go)
{
	if (go->nextState != go->currState)
	{
		if (go->currState != nullptr)
			go->currState->Exit(go);
		go->currState = go->nextState;
		go->currState->Enter(go);
	}

	if (go->currState != nullptr)
		go->currState->Update(dt, go);
}
