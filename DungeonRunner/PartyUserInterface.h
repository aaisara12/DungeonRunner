#pragma once
#include "UserInterface.h"
#include "Observer.h"
#include "Character.h"
#include "Event.h"
#include "Party.h"

class PartyUserInterface : public UserInterface, public Observer<ContainerUpdateEventData>
{
public:

	PartyUserInterface(Party& party);
	virtual ~PartyUserInterface();

	// Inherited via Observer
	virtual void onNotify(ContainerUpdateEventData eventData);

private:

	struct CharacterHealthStat
	{
		int currentHealth;
		int maxHealth;
	};

	Party& party;

	std::unordered_map<Character*, CharacterHealthStat> characterHealthStats;
};