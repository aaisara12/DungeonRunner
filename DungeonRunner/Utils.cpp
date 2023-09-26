#include "Utils.h"

TruncatedSentence truncateSentence(std::string sentence, int maxCharactersAllowed)
{
	TruncatedSentence data;

	// We want this to keep track of where to truncate when reaching sentence max
	size_t indexOfLastWhitespaceString = std::string::npos;

	for (size_t i = 0; i < maxCharactersAllowed; i++)
	{
		if (i >= sentence.length())
		{
			data.truncated = sentence;
			return data;
		}

		if (i > 0 && isspace(sentence[i]) && !isspace(sentence[i - 1]))
		{
			indexOfLastWhitespaceString = i;
		}
	}

	// If we reach this point, that means the given sentence is longer than the max chars allowed
	size_t indexToTruncateFrom = maxCharactersAllowed;
	if (indexOfLastWhitespaceString != std::string::npos)
	{
		indexToTruncateFrom = indexOfLastWhitespaceString;
	}

	std::string rawRemainder = sentence.substr(indexToTruncateFrom);

	// If first char is a non-whitespace, that's an indication that this is a really long word
	// and needs a dash
	char firstCharOfRemainder = rawRemainder[0];
	if (!isspace(firstCharOfRemainder))
	{
		rawRemainder = *rawRemainder.insert(rawRemainder.begin(), '-');
	}

	// Clean up any leading whitespace
	size_t firstNonWhitespace = rawRemainder.find_first_not_of(" \t");
	if (firstNonWhitespace != std::string::npos)
	{
		rawRemainder = rawRemainder.substr(firstNonWhitespace);
	}

	data.remainder = rawRemainder;
	data.truncated = sentence.substr(0, indexToTruncateFrom);

	return data;
}