#include "UserInterface.h"
#include "Utils.h"

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

    this->displayLines.getOnCollectionChangedEvent().addListener(this);
}

UserInterface::~UserInterface() {}

std::string UserInterface::getDisplay()
{
    std::string finalDisplay = "";

    // Upper border
    finalDisplay.append(std::string(frameWidthInCharacters + 4, '/') + '\n');

    // Upper padding
    for (int i = 0; i < verticalFramePaddingInCharacters; i++)
        finalDisplay.append("//" + std::string(frameWidthInCharacters, ' ') + "//\n");

    int maxCharactersThatCanFitOnLine = frameWidthInCharacters - 2 * horizontalFramePaddingInCharacters;

    // Copy construct since modifying directly triggers UI update and signals change to UI, which might end up calling this
    // Admittedly, this is pretty expensive to do every time we call getDisplay, so it might be worth looking into caching
    std::vector<DisplayLine> processedDisplayLines = displayLines.get();

    // Apply line wrapping to any lines that exceed max characters
    for (auto p = processedDisplayLines.begin(); p != processedDisplayLines.end();)
    {
        std::string remainingSentence = p->content;
        std::vector<DisplayLine> additionalLinesGenerated;
        while (!remainingSentence.empty())
        {
            TruncatedSentence res = truncateSentence(remainingSentence, maxCharactersThatCanFitOnLine);
            remainingSentence = res.remainder;
            additionalLinesGenerated.push_back(DisplayLine(res.truncated, p->alignment));
        }

        if (additionalLinesGenerated.size() > 0)
        {
            auto ptrToStartOfInsertion = processedDisplayLines.erase(p);
            ptrToStartOfInsertion = processedDisplayLines.insert(ptrToStartOfInsertion, additionalLinesGenerated.begin(), additionalLinesGenerated.end());
            
            // Fast-forward pointer to the next line it hasn't processed
            ptrToStartOfInsertion += additionalLinesGenerated.size();
            p = ptrToStartOfInsertion;
        }
        else
        {
            p++;
        }
    }


    for (DisplayLine displayLine : processedDisplayLines)
    {
        // Grab the corresponding format function based on the specified alignment
        FormatFunction f = alignmentTypeToAlignmentFunction[displayLine.alignment];
        std::string formattedLine = (this->*f)(displayLine.content, maxCharactersThatCanFitOnLine);

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


Event<UserInterface*>& UserInterface::getOnDirtyEvent()
{
    return onDirty;
}



ObservableCollection<std::vector<DisplayLine>>& UserInterface::getDisplayLines()
{
    return displayLines;
}

std::string UserInterface::getFormattedLineLeftAlign(const std::string& line, int maximumCharactersAllowed)
{
    if (line.size() > maximumCharactersAllowed)
        return line.substr(0, maximumCharactersAllowed);
    else
        return line + std::string(maximumCharactersAllowed - line.size(), ' ');
}


// DESIGN CHOICE: Why not extract out if(line.size() > maximumCharactersAllowed) return ... into
// a check before calling one of these functions? I wanted these functions to be self-contained
// so that the caller doesn't have to worry about needing to check.
std::string UserInterface::getFormattedLineCenterAlign(const std::string& line, int maximumCharactersAllowed)
{
    if (line.size() > maximumCharactersAllowed)
        return line.substr(0, maximumCharactersAllowed);
    else
    {
        std::string formattedLine = std::string(maximumCharactersAllowed, ' ');

        // Initialize at location on formatted line where content should start
        int formattedLineIndex = (maximumCharactersAllowed / 2) - (line.size() / 2);

        // Fill in the formatted line
        for (char c : line)
        {
            formattedLine[formattedLineIndex] = c;
            formattedLineIndex++;
        }

        return formattedLine;
    }
}

std::string UserInterface::getFormattedLineRightAlign(const std::string& line, int maximumCharactersAllowed)
{
    if (line.size() > maximumCharactersAllowed)
        return line.substr(0, maximumCharactersAllowed);
    else
        return std::string(maximumCharactersAllowed - line.size(), ' ') + line;
}

void UserInterface::onNotify(const std::vector<DisplayLine, std::allocator<DisplayLine>>& modifiedDisplayLines)
{
    onDirty.Invoke(this);
}

UserInterface::AlignmentToFunctionMap UserInterface::alignmentTypeToAlignmentFunction =
{
    {UserInterface::ContentAlignmentType::LEFT, &UserInterface::getFormattedLineLeftAlign},
    {UserInterface::ContentAlignmentType::CENTER, &UserInterface::getFormattedLineCenterAlign},
    {UserInterface::ContentAlignmentType::RIGHT, &UserInterface::getFormattedLineRightAlign}
};