#include "Party.h"

Party::Party(std::vector<Character*> party)
{
    for (Character* member : party)
    {
        addMemberToParty(member);
    }
}

Party::~Party()
{
    for (Character* member : partyMembers)
    {
        member->getHealthDataChangedEvent().removeListener(this);
    }
}

Event<ContainerUpdateEventData>& Party::getPartyHealthChangedEvent()
{
    return partyHealthChangedEvent;
}

void Party::addMemberToParty(Character* member)
{
    member->getHealthDataChangedEvent().addListener(this);
    partyMembers.insert(member);
    partyHealthChangedEvent.Invoke(ContainerUpdateEventData(member->getStats()[Character::CUR_HP], member->getStats()[Character::MAX_HP], member));
}

void Party::onNotify(ContainerUpdateEventData eventData)
{
    // Effectively just relays all party members' events 
    partyHealthChangedEvent.Invoke(ContainerUpdateEventData(eventData));
}
