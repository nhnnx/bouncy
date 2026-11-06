#pragma once

#include "bouncy.h"

// Initialize and clean the game
bool Initialize(const char* title, int width, int height);
void Clean();

class MainMenu
{
public:
	MainMenu();
	~MainMenu();
	void run();
	void AskForPassword();

private:
	void handleEvents();
	void update();
	void render();
	bool Quit;
	bool Play;
	int StartWorld;
	bool Test;
	bool ShowInfo;
	LTexture tMenu[7];
	LTexture tInfo[6];
	int HighlightedItem;
	int nItems;
	char InPassword[256];
};

class cEditor {
public:
	cEditor();
	~cEditor();
	void Run();
private:
	void handleEvents();
	void update();
	void render();

	cLevel* Level;
	bool Quit;

	int SelObject;
	SDL_FRect lighter;
	SDL_FRect lightest;
};