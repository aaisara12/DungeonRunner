#pragma once
#include "Event.h"
#include "Character.h"
#include <unordered_set>
#include "Observer.h"

/// <summary>
/// Separate data structure for keeping track of party details. While currently it's just a wrapper around
/// a list of Characters, I foresee in the future a need for party-wide effects/buffs that should be kept
/// track of, among other things.
/// </summary>
class Party : public Observer<ContainerUpdateEventData>
{
public:
	Party() {}
	Party(std::vector<Character*> party);

	virtual ~Party();

	Event<ContainerUpdateEventData>& getPartyHealthChangedEvent();

	void addMemberToParty(Character* member);

private:
	std::unordered_set<Character*> partyMembers;

	Event<ContainerUpdateEventData> partyHealthChangedEvent;


	// Inherited via Observer
	virtual void onNotify(ContainerUpdateEventData eventData);

};