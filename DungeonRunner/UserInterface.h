#pragma once
#include <string>
#include "Observer.h"
#include "Event.h"
#include <vector>
#include <unordered_map>

/// <summary>
/// This is a base class that contains functionality for displaying text on the screen. 
/// </summary>
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
	virtual ~UserInterface();

	// Returns a framed visual representation of the UI
	std::string getDisplay();

	// Check whether there has been an update to the UI
	bool isDirty();

	Event<UserInterface*>& getOnDirtyEvent();

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


	// DESIGN CHOICE: A dedicated accessor function automatically raises
	// the isDirty flag to notify users of this object that a change to
	// the UI has LIKELY occurred (you probably wouldn't call the accessor
	// as a derived class unless you were changing it). The reason I didn't
	// use a setter to ensure the display lines are actually changing when
	// the flag is raised is because it would require changing a good amount
	// of code and make implementations more complex with having to create
	// local vectors then copying them over. I figured this implementation's
	// weakness of not guaranteeing a change is only fully exposed if there
	// are tons of calls to it that don't actually make changes, of which 
	// there are none at the moment.
	std::vector<DisplayLine>& getDisplayLines();

private:

	// Flag to keep track of whether there is a change that has not been
	// seen by the user of this object. It relies on the assumption that
	// the owner sees the update when getDisplay() is called and that
	// an update has occurred when getDisplayLines() is called by a
	// derived class.
	bool _isDirty;

	std::vector<DisplayLine> displayLines;

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


	Event<UserInterface*> onDirty;


};


