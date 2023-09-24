#pragma once
#include <string>
#include "Observer.h"
#include "Event.h"
#include <vector>
#include <unordered_map>
#include "ObservableCollection.h"

struct DisplayLine;

/// <summary>
/// This is a base class that contains functionality for displaying text on the screen. 
/// </summary>
class UserInterface : public Observer<const std::vector<DisplayLine>&>
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

	ObservableCollection<std::vector<DisplayLine>>& getDisplayLines();

private:

	// Flag to keep track of whether there is a change that has not been
	// seen by the user of this object. It relies on the assumption that
	// the owner sees the update when getDisplay() is called and that
	// an update has occurred when getDisplayLines() is called by a
	// derived class.
	bool _isDirty;

	ObservableCollection<std::vector<DisplayLine>> displayLines;

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

	// Inherited via Observer
	virtual void onNotify(const std::vector<DisplayLine, std::allocator<DisplayLine>>& modifiedDisplayLines);

};


// Wrapper around a line to display that includes alignment information 
// that UserInterface uses to "style" each line specifically
struct DisplayLine
{
	std::string content;
	UserInterface::ContentAlignmentType alignment;

	DisplayLine(std::string content, UserInterface::ContentAlignmentType alignment)
		:content(content), alignment(alignment)
	{}
};
