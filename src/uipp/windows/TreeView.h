/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#ifndef _TreeView_h
#define _TreeView_h


#include "UIComponent.h"
#include "List.h"
#include "TreeNode.h"

class Marker;


//
// Class name definition:
//
#define ClassTreeView	"TreeView"

//extern "C" void TreeView_InputCB(Widget, XtPointer, XtPointer);
//extern "C" void TreeView_ResizeCB(Widget, XtPointer, XtPointer);
//extern "C" void TreeView_ExposeCB(Widget, XtPointer, XtPointer);
//extern "C" void TreeView_RolloverEH (Widget , XtPointer , XEvent* , Boolean* );
//extern "C" void TreeView_MotionEH (Widget , XtPointer , XEvent* , Boolean* );
//extern "C" void TreeView_IBeamTO(XtPointer, XtIntervalId*);

//
// TreeView class definition:
//
namespace dxui {
	class TreeView : public UIComponent
	{
	private:
		static bool ClassInitialized;

		//Pixmap buffer;
		//Pixmap cursor_backing;
		//static Pixmap Plus;
		//static Pixmap Minus;
		//static Cursor Hand;
		//static Cursor Typing;
		//GC gc;
		//Pixel highlight_color;
		//Pixel foreground_color;
		//Pixel line_color;
		//Pixel type_ahead_color;

		dxui::TreeNode* data_model;

		unsigned int single_click_time;
		int multi_click_time;

		bool dirty;
		bool initialized;

		dxui::TreeNode* selection;
		List markers;
		List items;
		Marker* containing_marker;

		void clearMarkers();

		Marker *selection_marker;
		Marker *match_marker;

		List searchable_nodes;
		bool typing_ahead;
		dxui::TreeNode* matched;
		char typing[32];
		int typing_count;
		bool ibeam_showing;
		//XtIntervalId ibeam_timer;

		void toggleIBeam(bool restart=true);

		List auto_expanded;

	protected:

		//static const String DefaultResources[];
		//static XmFontList FontList;

		//friend void TreeView_ExposeCB(Widget , XtPointer , XtPointer );
		//friend void TreeView_InputCB(Widget , XtPointer , XtPointer );
		//friend void TreeView_ResizeCB(Widget , XtPointer , XtPointer );
		//friend void TreeView_RolloverEH (Widget , XtPointer , XEvent* , Boolean* );
		//friend void TreeView_MotionEH (Widget , XtPointer , XEvent* , Boolean* );
		//friend void TreeView_IBeamTO(XtPointer, XtIntervalId*);

		virtual void enter(){}
		virtual void leave(){}
		virtual void focusIn(){}
		virtual void focusOut(){}

		void paint();
		void redisplay();
		void setDirty(bool d=true, bool repaint=false); 
		//void paintNode(dxui::TreeNode* , int& , int , int , Dimension&, bool, bool, bool& );

		virtual const char* getFont() { return "bold"; }

		bool isRootVisible() { return false; }

		bool isDirty() { return this->dirty; }

		//virtual void buttonPress(XEvent*);
		//virtual void keyPress(XEvent*);
		//virtual void motion(int x, int y);
		//virtual void resize(int width, int height);
		//virtual void select(dxui::TreeNode* node, bool repaint=true);
		//virtual void multiClick(dxui::TreeNode* node);

		//void setDefaultCursor();
		//void setHandCursor();
		//void setTypeAheadCursor();

		Marker* pick(int x, int y);

		virtual dxui::TreeNode* getSelection() { return this->selection; }

		//
		// When type-ahead starts, we fetch a list of leaf nodes against
		// which we'll perform string matching.  By default we return
		// leaf nodes that are displayed.
		//
		virtual void getSearchableNodes(dxui::TreeNode* subtree, List& nodes_to_search);
		virtual void getSearchableNodes(List& nodes_to_search);

		//virtual void typeAhead (KeySym);
		virtual bool isTyping() { return this->typing_ahead; }
		virtual void beginTyping();
		virtual void endTyping();
		virtual void adjustVisibility(int, int, int, int){};

		List* getAutoExpanded() { return &this->auto_expanded; }

	public:
		//
		// Constructor:
		//
		TreeView(const char* bubbleHelp=NUL(const char*));

		//
		// Destructor:
		//
		~TreeView();

		virtual void initialize (dxui::TreeNode* model, bool repaint=false);

		//void setHighlightColor(Pixel p) { this->highlight_color = p; }

		virtual void clear(bool repaint=true);

		//
		// The location of the selection must be recorded so that the owner
		// who might have us stuck into a scrolled window can move its
		// scrollbars to ensure that the selection is visible to the user. 
		// Return true if there is a selection and the selection was drawn.
		//
		virtual bool getSelectionLocation(int& x1, int& y1, int& x2, int& y2);
		virtual bool getMatchLocation(int& x1, int& y1, int& x2, int& y2);

		virtual dxui::TreeNode* getDataModel() { return this->data_model; }

		//
		// Returns a pointer to the class name.
		//
		const char* getClassName()
		{
			return ClassTreeView;
		}
	};
}

#if defined(TREE_VIEW_PRIVATES)
class Marker {
    private:
	int x1,y1,x2,y2;
	dxui::TreeNode* node;
    protected:
    public:
	Marker(int x, int y, int width, int height, dxui::TreeNode* node) {
	    this->x1 = x;
	    this->y1 = y;
	    this->x2 = x+width;
	    this->y2 = y+height;
	    this->node = node;
	}
	virtual ~Marker(){}
	bool contains(int x, int y) {
	    if ((x > this->x1) &&
		(x < this->x2) &&
		(y > this->y1) &&
		(y < this->y2)) return true;
	    return false;
	}
	dxui::TreeNode* getNode() { return this->node; }
	void getLocation(int& x1, int& y1, int& x2, int& y2) {
	    x1 = this->x1;
	    y1 = this->y1;
	    x2 = this->x2;
	    y2 = this->y2;
	}
};
#endif

#endif // _TreeView_h
