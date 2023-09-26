#pragma once
#include <string>

struct TruncatedSentence
{
	std::string truncated;
	std::string remainder;
};

/// <summary>
/// Truncates the given sentence at the last completed word before maxCharactersAllowed reached,
/// or simply upon reaching maxCharactersAllowed, whichever is shorter.
/// </summary>
/// <param name="sentence"></param>
/// <param name="maxCharactersAllowed"></param>
/// <returns></returns>
TruncatedSentence truncateSentence(std::string sentence, int maxCharactersAllowed);


