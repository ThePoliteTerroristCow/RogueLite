#pragma once

class Gui {
public:
	Gui();
	~Gui();

	struct uiData {
		struct uiCheats {
			int CHEAT_TOP = 7; // Where the top-most part of the UI starts
			int CHEAT_HEIGHT = 6; // The total height of the UI Element 
			int CHEAT_WIDTH = 20; // The total width of the UI Element 
			const char *CHEAT_NAME = "-- Cheats Enabled --";
		}cheats;

		struct uiHealth {
			int HEALTH_TOP = 7;
			int HEALTH_WIDTH = 20;
			const char *HEALTH_NAME = "HP";
		}health;

		struct uiMsgFrame {
			int MSG_HEIGHT;
			int MSG_LEFTX;
			int MSG_TOP;
			int MSG_WIDTH;
		}msgFrame;

		struct msgVarsStruct {
		public:
			// Without 'turnCount' the clearing of our MsgCon happens 2 moves after we first receive a message, 
			// whereas we want the console to be cleared the move immediately after we first receive the message. 
		
			// I think its bc of the ordering of moves. 'moveOrAttack' is run (Ai.cpp) & prints a 'corpse is here' 
			// message and then I think the engine refreshes and clears the message before we ever get to see it. 
			// Whatever the case, its fixed for now by using 'turnCount'. I'll fix it properly later :)
			int turnCount = 0;
			bool bClearOnTurn;
			bool bRenderMouseInfo = false;
		}msgVars;
	}ui;

	void clearMsgCon();
	void message(const TCODColor &col, bool clearOnTurn, const char *text ...);
	void render();
	void renderMouseLook();

protected:
	struct Message {
		char *text;
		TCODColor col;
		Message(const char *text, const TCODColor &col);
		~Message();
	};
	TCODList<Message *> log;

	TCODConsole *msgCon;
	TCODConsole *healthCon;
	TCODConsole *cheatsCon;
	void renderCheatBar(int x, int y, int width, const char *name, const TCODColor &backColor);
	void renderHealthBar(int x, int y, int width, const char *name, float value, float maxValue, const TCODColor &barColor, const TCODColor &backColor);
	void renderMsgBox(int x, int y, int width, int height);
	
	bool bSetMsgBoxXY = false; // used to prevent repeated calling of 'setMsgBoxXY()'
	void setMsgBoxXY();
};
