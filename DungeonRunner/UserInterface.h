#pragma once
#include <string>
#include "Observer.h"
#include <vector>
#include <unordered_map>

class UserInterface
{
public:
	enum ContentAlignmentType
	{
		LEFT,
		RIGHT,
		CENTER
	};

	UserInterface(int frameWidthInCharacters, int framePaddingInUnits);

	// Returns a framed visual representation of the UI
	std::string getDisplay();


protected:

	// Wrapper around a line to display that includes alignment information 
	// that UserInterface uses to "style" each line specifically
	struct DisplayLine
	{
		std::string content;
		ContentAlignmentType alignment;

		DisplayLine(std::string content, ContentAlignmentType alignment)
			:content(content), alignment(alignment)
		{}
	};

	// Returns a visual representation of the UI
	// 
	// DESIGN CHOICE: Could have just used a vector<string>, which would be
	// more direct and simpler to implement, but I thought it was important
	// to have this fine-grain adjustment of the text on each line so that
	// derived classes don't need to worry about making sure the content
	// looks right on the screen.
	virtual const std::vector<DisplayLine>& display() = 0;

private:

	// Frame width is defined by number of characters between first "//" and last "//"
	// so that a border of thickness 2 = "//" is always guaranteed
	int frameWidthInCharacters;
	int horizontalFramePaddingInCharacters;
	int verticalFramePaddingInCharacters;

	// DESIGN CHOICE: Don't specify frame height since we almost always want
	// to make the frame as large as tall as the content for the frame.
	// There's no scrolling mechanic, so we wouldn't ever be able to see
	// the additional content that would be cut off by a fixed border height anyways

	std::string getFormattedLineLeftAlign(const std::string& line, int maximumCharactersAllowed);
	std::string getFormattedLineCenterAlign(const std::string& line, int maximumCharactersAllowed);
	std::string getFormattedLineRightAlign(const std::string& line, int maximumCharactersAllowed);

	// Use typedef to make it easier to understand structure of alignment to function mapping
	typedef std::string(UserInterface::* FormatFunction)(const std::string&, int);
	typedef std::unordered_map<UserInterface::ContentAlignmentType, FormatFunction> AlignmentToFunctionMap;

	// Maps a specified content alignment type to its corresponding formatting function
	//
	// DESIGN CHOICE: Could have just used a simple switch statement based on a ContentAlignmentType
	// value. Using a mapping makes the code more generic and flexible to changes to the set of
	// formatting functions. Admittedly, these are not too likely to change, and the main reason
	// I used a mapping was to get practice using function pointers :O
	static AlignmentToFunctionMap alignmentTypeToAlignmentFunction;


};


