#include "UserInterface.h"

// DESIGN CHOICE: Derive vertical and horizontal padding from abstract "units"
// to make it easier for the implementor of a derived class to get their intended
// look. In most cases, the horizontal frame padding will look best if it's twice
// that of the vertical frame padding since the vertical height of one character
// is about twice its width.
UserInterface::UserInterface(int frameWidthInCharacters, int framePaddingInUnits)
    :verticalFramePaddingInCharacters(framePaddingInUnits), 
    horizontalFramePaddingInCharacters(framePaddingInUnits * 2)
{
    // Prevent width from being too small to accommodate horizontal padding (left and right)
    this->frameWidthInCharacters = std::max(frameWidthInCharacters, 2 * horizontalFramePaddingInCharacters);
}

std::string UserInterface::getDisplay()
{
    std::string finalDisplay = "";

    // Upper border
    finalDisplay.append(std::string(frameWidthInCharacters + 4, '/') + '\n');

    // Upper padding
    for (int i = 0; i < verticalFramePaddingInCharacters; i++)
        finalDisplay.append("//" + std::string(frameWidthInCharacters, ' ') + "//\n");

    // Content
    const std::vector<DisplayLine>& displayLines = display();
    for (DisplayLine displayLine : displayLines)
    {
        // Grab the corresponding format function based on the specified alignment
        FormatFunction f = alignmentTypeToAlignmentFunction[displayLine.alignment];
        std::string formattedLine = (this->*f)(displayLine.content, frameWidthInCharacters - 2 * horizontalFramePaddingInCharacters);

        // Construct and add a row of the UI (including border)
        finalDisplay.append("//" + std::string(horizontalFramePaddingInCharacters, ' ') + formattedLine + std::string(horizontalFramePaddingInCharacters, ' ') + "//\n");
    }

    // Lower padding
    for (int i = 0; i < verticalFramePaddingInCharacters; i++)
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
    std::string formattedLine = std::string(maximumCharactersAllowed, ' ');
    // Case 1: Line has fewer characters than maximum
    if (line.size() <= maximumCharactersAllowed)
    {
        // Initialize at location on formatted line where content should start
        int formattedLineIndex = (maximumCharactersAllowed / 2) - (line.size() / 2);

        // Fill in the formatted line
        for (char c : line)
        {
            formattedLine[formattedLineIndex] = c;
            formattedLineIndex++;
        }
    }
    else
    {
        // Fill in the formatted line
        for (int i = 0; i < maximumCharactersAllowed; i++)
        {
            // This is guaranteed to always be in range since maxCharsAllowed + lineIndex < line.size()
            formattedLine[i] = line[i];
        }
    }
    return formattedLine;
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