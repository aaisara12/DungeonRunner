#include "UserInterface.h"

UserInterface::UserInterface(int frameWidthInCharacters, int framePaddingInCharacters)
    :frameWidthInCharacters(frameWidthInCharacters), framePaddingInCharacters(framePaddingInCharacters)
{
}

std::string UserInterface::getDisplay()
{
    std::string finalDisplay = "";

    // Upper border
    finalDisplay.append(std::string(frameWidthInCharacters + 4, '/') + '\n');

    // Upper padding
    for (int i = 0; i < framePaddingInCharacters; i++)
        finalDisplay.append("//" + std::string(frameWidthInCharacters, ' ') + "//\n");

    // Content
    const std::vector<DisplayLine>& displayLines = display();
    for (DisplayLine displayLine : displayLines)
    {
        // Grab the corresponding format function based on the specified alignment
        FormatFunction f = alignmentTypeToAlignmentFunction[displayLine.alignment];
        std::string formattedLine = (this->*f)(displayLine.content, frameWidthInCharacters - 2 * framePaddingInCharacters);
        finalDisplay.append("//" + std::string(framePaddingInCharacters, ' ') + formattedLine + std::string(framePaddingInCharacters, ' ') + "//\n");
    }

    // Lower padding
    for (int i = 0; i < framePaddingInCharacters; i++)
        finalDisplay.append("//" + std::string(frameWidthInCharacters, ' ') + "//\n");

    // Lower border
    finalDisplay.append(std::string(frameWidthInCharacters + 4, '/') + '\n');

    return finalDisplay;
}

std::string UserInterface::getFormattedLineLeftAlign(const std::string& line, int maximumCharactersAllowed)
{
    if (line.size() > maximumCharactersAllowed)
        return line.substr(maximumCharactersAllowed);
    else
        return line + std::string(maximumCharactersAllowed - line.size(), ' ');
}

std::string UserInterface::getFormattedLineCenterAlign(const std::string& line, int maximumCharactersAllowed)
{
    return std::string();
}

std::string UserInterface::getFormattedLineRightAlign(const std::string& line, int maximumCharactersAllowed)
{
    return std::string();
}

UserInterface::AlignmentToFunctionMap UserInterface::alignmentTypeToAlignmentFunction =
{
    {UserInterface::ContentAlignmentType::LEFT, &UserInterface::getFormattedLineLeftAlign},
    {UserInterface::ContentAlignmentType::CENTER, &UserInterface::getFormattedLineCenterAlign},
    {UserInterface::ContentAlignmentType::RIGHT, &UserInterface::getFormattedLineRightAlign}
};