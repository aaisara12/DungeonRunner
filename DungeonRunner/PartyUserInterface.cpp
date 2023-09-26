#include "PartyUserInterface.h"
#include <format>

PartyUserInterface::PartyUserInterface(Party& party)
	:party(party), UserInterface(30, 1)
{
	party.getPartyHealthChangedEvent().addListener(this);
}

PartyUserInterface::~PartyUserInterface()
{
	party.getPartyHealthChangedEvent().removeListener(this);
}

void PartyUserInterface::onNotify(ContainerUpdateEventData eventData)
{
	CharacterHealthStat& healthStat = characterHealthStats[eventData.owner];
	healthStat.currentHealth = eventData.newContainerCurrent;
	healthStat.maxHealth = eventData.newContainerMax;

	std::vector<DisplayLine> newHealthTexts;
	newHealthTexts.push_back(DisplayLine("YOUR PARTY", CENTER));
	newHealthTexts.push_back(DisplayLine(" ", CENTER));

	for (const auto& characterHealthInfo : characterHealthStats)
	{
		const Character* character = characterHealthInfo.first;
		const CharacterHealthStat& characterHealthStat = characterHealthInfo.second;

		std::string characterHealthText = std::format(
			"{} ({}/{} HP)",
			character->getName(),
			characterHealthStat.currentHealth,
			characterHealthStat.maxHealth);

		newHealthTexts.push_back(DisplayLine(characterHealthText, LEFT));
	}

	getDisplayLines().clear();
	getDisplayLines().insert(getDisplayLines().get().begin(), newHealthTexts.begin(), newHealthTexts.end());

}
