//------------------------------------------
// The return of Bumpy - by Nanni 2025
//------------------------------------------

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "main.h"

// Global windows and renderers
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindowE = NULL;
SDL_Renderer* gRendererE = NULL;
cEditor gEditor;
MIX_Mixer* gMixer = NULL;

//---------------------------------
// Main
//---------------------------------

int main(int argc, char* argv[]) {

	bool ok = Initialize("Bouncy's Arcade Fantasy", SCREEN_WIDTH, SCREEN_HEIGHT);
	if (ok) {
		MainMenu menu;
		menu.run();
	}
	Clean();
	return 0;
}

bool Initialize(const char* title, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0) {
		// Error message
		//std::cerr << "SDL Init Failed\n";
		return false;
	}

	//Create window and renderer
	if (!SDL_CreateWindowAndRenderer(title, width, height, 0, &gWindow, &gRenderer))
	{
		// Error message
		SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		// Add icon, hide the mouse...
		SDL_Surface* icon = IMG_Load("images/bumpy.png");
		bool ok = SDL_SetWindowIcon(gWindow, icon);
		if (!ok) SDL_Log("Cannot set window icon! SDL Error: %s\n", SDL_GetError());

		//Enable vsync
		SDL_SetRenderVSync(gRenderer, 1);

		//Initialize renderer color
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

		//Initialize SDL_ttf
		if (TTF_Init() == false)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", SDL_GetError());
			return false;
		}

		////Initialize SDL_mixer
		//SDL_AudioSpec audio_spec;
		//SDL_zero(audio_spec);
		//audio_spec.format = MIX_DEFAULT_FORMAT;
		//audio_spec.channels = 2;
		//audio_spec.freq = 44100;
		//if (!Mix_OpenAudio(0, &audio_spec))
		//{
		//	SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", SDL_GetError());
		//	return false;
		//}
		
		// Inizializza SDL_mixer
		if (!MIX_Init()) {
			SDL_Log("Error init SDL_mixer: %s", SDL_GetError());
		}
		else {
			// Crea il dispositivo mixer (sostituisce la vecchia Mix_OpenAudio)
			gMixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
			if (gMixer == NULL) {
				SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", SDL_GetError());
				return false;
			}
		}

		// Create editor window and renderer
		int ww = 80 * 4;
		int hh = 80 + 80 + 40 * 5 + 80 * 2;
		if (!SDL_CreateWindowAndRenderer("Editor", ww, hh, SDL_WINDOW_UTILITY | SDL_WINDOW_HIDDEN, &gWindowE, &gRendererE))
		{
			// Error message
			SDL_Log("Editor renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}
		//Enable vsync
		SDL_SetRenderVSync(gRendererE, 1);
		//Initialize renderer color
		SDL_SetRenderDrawColor(gRendererE, 0xFF, 0xFF, 0xFF, 0xFF);


		if (!loadMedia()) return false;

	}

	return true;
}

void Clean()
{
	//Free loaded images
	FreeMedia();

	//Destroy windows
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRendererE);
	SDL_DestroyWindow(gWindowE);
	gRenderer = NULL;
	gWindow = NULL;
	gRendererE = NULL;
	gWindowE = NULL;

	//Destroy mixer
	MIX_DestroyMixer(gMixer);

	//Quit SDL subsystems
	TTF_Quit();
	MIX_Quit();
	SDL_Quit();
}

//---------------------------------
// class MainMenu
//---------------------------------

MainMenu::MainMenu()
{
	Quit = false;
	Test = false;
	Play = false;
	ShowInfo = false;
	StartWorld = 1;
	InPassword[0] = '\0';

	//Render text
	SDL_Color col = { 0, 0, 0 };
	int i = 0;
	tMenu[i++].loadFromRenderedText("Bouncy's Arcade Fantasy", col);
	tMenu[i++].loadFromRenderedText("Test", col);
	tMenu[i++].loadFromRenderedText("Play", col);
	tMenu[i++].loadFromRenderedText("Password", col);
	tMenu[i++].loadFromRenderedText("Editor", col);
	tMenu[i++].loadFromRenderedText("About", col);
	tMenu[i++].loadFromRenderedText("Exit", col);

	HighlightedItem = 0;
	nItems = 6;

	i = 0;
	tInfo[i++].loadFromRenderedText("About", col);
	tInfo[i++].loadFromRenderedText("Bouncy's Arcade Fantasy is a tribute to", col);
	tInfo[i++].loadFromRenderedText("Bumpy's Arcade Fantasy by Loriciel (1992)", col);
	tInfo[i++].loadFromRenderedText("Developed in C++ with SDL3 by Nanni (2025)", col);
	tInfo[i++].loadFromRenderedText("email: signornanni@hotmail.it", col);
	tInfo[i++].loadFromRenderedText("version 1.0", col);

}

MainMenu::~MainMenu()
{
	for (int i = 0; i < 7; i++)
		tMenu[i].free();
	for (int i = 0; i < 5; i++)
		tInfo[i].free();
}

void MainMenu::handleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			Quit = true;
		}
		if (e.type == SDL_EVENT_KEY_DOWN) {
			switch (e.key.key) {
			case SDLK_RETURN:
				if (ShowInfo) ShowInfo = false;
				else switch (HighlightedItem) {
				case 0: // TEST
					Test = true;
					break;
				case 1: // WORLDS
					Play = true;
					break;
				case 2: {// PASSWORD
					// Ask for password...
					AskForPassword();
					// Find world...
					char* input = InPassword;
					int idx = 1;
					if (SDL_strcmp(Passworld2, input) == 0) idx = 2;
					else if (SDL_strcmp(Passworld3, input) == 0) idx = 3;
					else if (SDL_strcmp(Passworld4, input) == 0) idx = 4;
					else if (SDL_strcmp(Passworld5, input) == 0) idx = 5;
					else if (SDL_strcmp(Passworld6, input) == 0) idx = 6;
					else if (SDL_strcmp(Passworld7, input) == 0) idx = 7;
					else if (SDL_strcmp(Passworld8, input) == 0) idx = 8;
					else if (SDL_strcmp(Passworld9, input) == 0) idx = 9;
					else if (SDL_strcmp(PassEditor, input) == 0) idx = 0;
					// Run
					if (idx >= 1) {
						StartWorld = idx;
						Play = true;
					}
					else if (idx == 0)
						gEditor.Run();
				} break;
				case 3: { // EDITOR
					gEditor.Run();
				} break;
				case 4: // INFO
					ShowInfo = true;
					break;
				case 5: // EXIT
					Quit = true;
					break;
				default:
					break;
				}
				break;
			case SDLK_DOWN:
				HighlightedItem = (HighlightedItem + 1) % nItems;
				break;
			case SDLK_UP:
				if (HighlightedItem > 0) HighlightedItem--;
				else HighlightedItem = nItems - 1;
				break;
			}
		}
	}
}

void MainMenu::update()
{
}

void MainMenu::render()
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x80, 0xC0, 255);
	SDL_RenderClear(gRenderer);
	int hh = 24;
	int xx = 0;
	int y0 = 0;
	int yy = y0;

	if (ShowInfo) {
		hh = tInfo[1].getHeight();
		y0 = (SCREEN_HEIGHT - hh) / 2;
		tInfo[0].render((SCREEN_WIDTH - tInfo[0].getWidth()) / 2, (y0 - hh) / 2);

		xx = (SCREEN_WIDTH - tInfo[2].getWidth()) / 2;
		yy = y0;
		tInfo[1].render(xx, yy);
		tInfo[2].render(xx, yy += hh);
		tInfo[3].render(xx, yy += hh + hh);
		tInfo[4].render(xx, yy += hh);
		tInfo[5].render(SCREEN_WIDTH - tInfo[5].getWidth(), yy += hh);
	}
	else {
		//Render menu items
		hh = tMenu[1].getHeight();
		xx = (SCREEN_WIDTH - tMenu[1].getWidth()) / 2;
		y0 = (SCREEN_HEIGHT - hh) / 2;
		yy = y0;
		tMenu[1].render(xx, yy);
		tMenu[2].render(xx, yy += hh);
		tMenu[3].render(xx, yy += hh);
		tMenu[4].render(xx, yy += hh);
		tMenu[5].render(xx, yy += hh);
		tMenu[6].render(xx, yy += hh);

		yy = (y0 - tMenu[0].getHeight()) * 2 / 3;
		tMenu[0].render((SCREEN_WIDTH - tMenu[0].getWidth()) / 2, yy);

		// Big Bumpy
		//SDL_FRect clip = { 0, 0, (float)(txBumpy.getWidth()), txBumpy.getHeight() / 2.f };
		//SDL_FPoint origin = { (SCREEN_WIDTH - txBumpy.getWidth()) / 2.f, yy - txBumpy.getHeight() * 2.f };
		//SDL_FPoint right = {origin.x + 100, origin.y};
		//SDL_FPoint down = {origin.x, origin.y + 100};
		//SDL_RenderTextureAffine(gRenderer, txBumpy.GetTexture(), &clip, &origin, &right, &down);

		// Highlight
		//float hf = (float)(hh >> 1);
		//float xf = xx - hf - hf;
		//float yf = y0 + hh * (HighlightedItem + 0.25);
		//SDL_SetRenderDrawColor(gRenderer, 0xC0, 0xC0, 0x00, 255);
		//SDL_RenderLine(gRenderer, xf, yf, xf, yf + hf);
		//SDL_RenderLine(gRenderer, xf, yf, xf + hf, yf + hf / 2);
		//SDL_RenderLine(gRenderer, xf + hf, yf + hf / 2, xf, yf + hf);

		txBumpy.render(xx - txBumpy.getWidth() * 2,
			(int)(y0 + hh * (HighlightedItem + 0.5) - txBumpy.getHeight() / 2.f));
	}

	SDL_RenderPresent(gRenderer);
}

void MainMenu::run()
{
	while (!Quit) {
		handleEvents();
		if (Quit) break;
		if (Test) {
			cWorld* world = new cWorld(WORLD_TEST, 5, 0);
			int ret = world->Run();
			//cLevel* level = new cLevel(0);
			//int ret = level->Run();
			// Handle ret...
			delete world;
			Test = false;
		}
		else if (Play) {
			// Run all Worlds
			int lives = 5; // Starting number of lives
			int score = 0;
			int success = 1;
			for (int i = StartWorld; i <= nWorlds; i++) {
				int worldid = i << 8;
				cWorld* world = new cWorld(worldid, lives, score);
				success = world->Run();
				lives = world->Lives;
				score = world->Score;
				delete world;
				// Handle success
				if (success == 0) break;
			}
			// Show high scores?
			//...

			// Back to main menu
			StartWorld = 1;
			Play = false;
		}
		update();
		render();
	}
}

void MainMenu::AskForPassword()
{
	bool stop = false;
	bool redraw = true;
	int passIdx = 0;
	char pchar = '\0';
	while (!stop) {
		// Render
		if (redraw) {
			SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
			SDL_RenderClear(gRenderer);
			LTexture txpassw;
			txpassw.loadFromRenderedText("ENTER PASSWORD:", {255, 255, 255, 255});
			txpassw.render((SCREEN_WIDTH - txpassw.getWidth()) / 2, (SCREEN_HEIGHT - txpassw.getHeight()) / 2 - txpassw.getHeight());
			txpassw.loadFromRenderedText(InPassword, { 255, 255, 128, 255 });
			txpassw.render((SCREEN_WIDTH - txpassw.getWidth()) / 2, (SCREEN_HEIGHT - txpassw.getHeight()) / 2 + txpassw.getHeight());
			SDL_RenderPresent(gRenderer);
			redraw = false;
		}
		// Message pump
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			// Press any key
			if (e.type == SDL_EVENT_KEY_DOWN) {
				if (e.key.key >= SDLK_A && e.key.key <= SDLK_Z) {
					if (passIdx < 15) {
						pchar = 'A' + (e.key.key - SDLK_A);
						InPassword[passIdx] = pchar;
						InPassword[++passIdx] = '\0';
						redraw = true;
					}
				}
				else if (e.key.key >= SDLK_0 && e.key.key <= SDLK_9) {
					if (passIdx < 15) {
						pchar = '0' + (e.key.key - SDLK_0);
						InPassword[passIdx] = pchar;
						InPassword[++passIdx] = '\0';
						redraw = true;
					}
				}
				else if (e.key.key == SDLK_BACKSPACE) {
					if (passIdx > 0) {
						passIdx--;
						InPassword[passIdx] = '\0';
						redraw = true;
					}
				}
				else if (e.key.key == SDLK_RETURN) {
					stop = true;
					break;
				}
			}
		}
	}
}

//---------------------------------
// class cEditor
//---------------------------------

cEditor::cEditor()
{
	Level = new cLevel(WORLD_EDITOR);
	SelObject = OBJ_None;
	lighter = { 0,0,0,0 };
	lightest = { 0,0,0,0 };
	Quit = false;
}

cEditor::~cEditor()
{
	delete Level;
}

void cEditor::handleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		SDL_Window* win = SDL_GetWindowFromEvent(&e);
		if (e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
			Quit = true;
		}

		// Editor Tool Window
		else if (win == gWindowE) {
			int ci = 0, ri = 0; // index of texture
			if (e.type == SDL_EVENT_MOUSE_MOTION ||
				e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				SDL_RaiseWindow(win);
				if (e.motion.y < 80) {
					// command
					float c = SDL_floorf(e.motion.x / 80);
					//if (c < 3) {
						lighter = { c * 80, 0, 80, 80 };
						ri = 0;
						ci = (int)c;
					//}
				}
				else if (e.motion.y < 160) {
					// central
					float c = SDL_floorf(e.motion.x / 80);
					lighter = { c * 80, 80, 80, 80 };
					ri = 0;
					ci = (int)c;
				}
				else if (e.motion.y < 160 + 40 * 5) {
					// floor
					float c = SDL_floorf(e.motion.x / 80);
					float r = SDL_floorf((e.button.y - 160) / 40);
					lighter = { c * 80, 160 + r * 40, 80, 40 };
					ri = (int)r + 1;
					ci = (int)c;
				}
				else {
					// side
					float c = SDL_floorf(e.motion.x / 40);
					float r = SDL_floorf((e.button.y - (160 + 40 * 5)) / 80);
					lighter = { c * 40, (160 + 40 * 5) + r * 80, 40, 80 };
					ri = 1 + 5 + (int)r * 2 + (int)c / 4;
					ci = (int)c % 4;
				}
			}
			if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				if (e.motion.y >= 80) {
					// Highlight the rectangle
					lightest = lighter;
					// Set the correspondent object type
					SelObject = (ci + ri * 4 < nTextures) ? ObjTypesE[ci + ri * 4] : OBJ_None;
				}
				else {
					// y < 80: Run the commands
					if (e.motion.x < 80) {
						// Clear level
						Level->ClearAllObjects();
					}
					else if (e.motion.x < 160) {
						// Export initialization code
						Level->ExportCode();
					}
					else if (e.motion.x < 240) {
						// Test level
						cLevel* testlevel = new cLevel(Level);
						testlevel->Run();
						delete testlevel;
					}
					else if (e.motion.x >= 240) {
						// Toggle grid
						if (Level->ShowGrid) Level->ShowGrid = false;
						else Level->ShowGrid = true;
					}
				}
			}
			if (e.type == SDL_EVENT_KEY_DOWN) {
				if (e.key.key == SDL_SCANCODE_RETURN) {
					// Test level
					cLevel* testlevel = new cLevel(Level);
					testlevel->Run();
					delete testlevel;
				}
			}
		}

		// Level window
		else if (win == gWindow) {
			if (e.type == SDL_EVENT_MOUSE_MOTION)
				SDL_RaiseWindow(win);
			if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				SDL_RaiseWindow(win);
				// Find the correspondent cell
				float c = SDL_floorf(e.button.x / 80);
				float r = SDL_floorf(e.button.y / 80);
				int col = (int)c;
				int row = (int)r;
				// Left button
				if (e.button.button == 1) {
					cCell* cell = Level->grid(col, row);
					bool done = false;
					// Check for other objects already present
					for (int i = 0; i < cell->nObj; i++) {
						// Same object
						if (cell->Objects[i]->type == SelObject) {
							// Just change the object status, if possible
							switch (SelObject) {
							case OBJ_FLOOR_Forced:
							case OBJ_FLOOR_Catapult:
							case OBJ_FLOOR_SpineUD:
								cell->Objects[i]->Status = (cell->Objects[i]->Status + 1) % 2;
								break;
							case OBJ_FLOOR_Reducing:
							case OBJ_FLOOR_Wall:
							case OBJ_SIDE_Wall:
								cell->Objects[i]->Status = (cell->Objects[i]->Status + 1) % 3;
								break;
							case OBJ_Food:
							case OBJ_Enemy:
							case OBJ_SIDE_Nways:
							case OBJ_SIDE_Face:
								cell->Objects[i]->Status = (cell->Objects[i]->Status + 1) % 4;
								break;
							default: break;
							}
							//cell->Objects[i]->update(); // Wrong: must not update game logic, just rendering
							done = true;
							break;
						}
						else {
							if ((SelObject != OBJ_FLOOR_Exit) && (cell->Objects[i]->type != OBJ_FLOOR_Exit))
							{
								if ((mIsCentered(SelObject) && mIsCentered(cell->Objects[i]->type)) ||
									(mIsFloor(SelObject) && mIsFloor(cell->Objects[i]->type)) ||
									(mIsSide(SelObject) && mIsSide(cell->Objects[i]->type)))
								{
									// Substitute the object
									Level->DeleteObject(cell->Objects[i]->type, col, row);
									Level->NewObject(SelObject, col, row);
									done = true;
									break;
								}
							}
						}
					}
					if (!done) {
						// No objects already present
						if (!(mIsSide(SelObject) && (col == (Level->Cols - 1))))
						{
							// Add the new object
							bool ok = Level->NewObject(SelObject, col, row);
							if (ok && SelObject == OBJ_FLOOR_Exit)
								Level->Exit->Status = 0; // Set exit visible
						}
					}
				}
				else if (e.button.button == 3) {
					// Remove the object, if any
					Level->DeleteObject(SelObject, col, row);
				}
			}
			if (e.type == SDL_EVENT_MOUSE_WHEEL) {
				// Find the correspondent cell
				float c = SDL_floorf(e.wheel.mouse_x / 80);
				float r = SDL_floorf(e.wheel.mouse_y / 80);
				int col = (int)c;
				int row = (int)r;
				cCell* cell = Level->grid(col, row);
				// Change the enemy's direction
				for (int i = 0; i < cell->nObj; i++) {
					if (cell->Objects[i]->type == OBJ_Enemy) {
						auto enemy = static_cast<cEnemy*>(cell->Objects[i]);
						enemy->SetDirection((enemy->GetDirection() + 4 - static_cast<int>(e.wheel.y)) % 4);
					}
				}
			}
		}
	}
}

void cEditor::update()
{
}

void cEditor::render()
{
	// Main window
	Level->render();

	// Tool window
	SDL_SetRenderDrawColor(gRendererE, 0x10, 0x10, 0x10, 255);
	SDL_RenderClear(gRendererE);
	SDL_SetRenderDrawColor(gRendererE, 0x20, 0x10, 0x20, 255);
	SDL_RenderFillRect(gRendererE, &lighter);
	SDL_SetRenderDrawColor(gRendererE, 0x30, 0x10, 0x30, 255);
	SDL_RenderFillRect(gRendererE, &lightest);

	// Command buttons
	SDL_SetRenderDrawColor(gRendererE, 0xff, 0xff, 0xff, 255);
	// Erase
	RenderDrawCircle(gRendererE, 40, 40, 15);
	SDL_RenderLine(gRendererE, 40 - 5, 25, 40 + 5, 25 - 5);
	SDL_RenderLine(gRendererE, 40 - 5, 25, 40 + 5, 25 + 5);
	
	// Export
	SDL_RenderLine(gRendererE, 80 + 40, 40 + 20, 80 + 40, 40 - 20);
	SDL_RenderLine(gRendererE, 80 + 40, 40 - 20, 80 + 40 - 10, 40 - 20 + 10);
	SDL_RenderLine(gRendererE, 80 + 40, 40 - 20, 80 + 40 + 10, 40 - 20 + 10);
	// Test
	SDL_RenderLine(gRendererE, 160 + 40 + 10, 40, 160 + 40 - 10, 40 - 8);
	SDL_RenderLine(gRendererE, 160 + 40 + 10, 40, 160 + 40 - 10, 40 + 8);
	SDL_RenderLine(gRendererE, 160 + 40 - 10, 40 - 8, 160 + 40 - 10, 40 + 8);
	// Grid view
	SDL_RenderLine(gRendererE, 240 + 40 - 20, 40 - 10, 240 + 40 + 20, 40 - 10);
	SDL_RenderLine(gRendererE, 240 + 40 - 20, 40 + 10, 240 + 40 + 20, 40 + 10);
	SDL_RenderLine(gRendererE, 240 + 40 - 10, 40 - 20, 240 + 40 - 10, 40 + 20);
	SDL_RenderLine(gRendererE, 240 + 40 + 10, 40 - 20, 240 + 40 + 10, 40 + 20);

	// Object buttons
	LTexture* text = NULL;
	int i = 0;
	// Central
	for (int c = 0; c < 4; c++) {
		text = TexturesE[i];
		if (text->getWidth())
			text->render(c * 80 + (80 - text->getWidth()) / 2, 80 + (80 - text->getHeight()) / 2);
		else
			RenderObjectDefault(gRendererE, ObjTypesE[i], c * 80 + 40.f, 80 + 40.f);
		i++;
	}
	// Floor
	for (int r = 0; r < 5; r++) {
		for (int c = 0; c < 4; c++) {
			text = TexturesE[i];
			if (text->getWidth())
				text->render(c * 80 + (80 - text->getWidth()) / 2, 160 + r * 40 + (40 - text->getHeight()) / 2);
			else
				RenderObjectDefault(gRendererE, ObjTypesE[i], c * 80 + 5.f, 160 + r * 40 + 15.f, FLOOR_WIDTH, FLOOR_HEIGHT);
			i++;
			if (i == nTextures) break;
		}
		if (i == nTextures) break;
	}
	// Side
	for (int r = 0; r < 2; r++) {
		for (int c = 0; c < 8; c++) {
			text = TexturesE[i];
			if (text->getWidth()) {
				switch (ObjTypesE[i]) {
				case OBJ_SIDE_Fake:
				case OBJ_SIDE_Plain:
				case OBJ_SIDE_Ice:
				case OBJ_SIDE_Glue:
					// Rotate texture
					text->render(c * 40 + 40 / 2 - text->getWidth() / 2,
						160 + 40 * 5 + r * 80 + 80 / 2 + - text->getHeight() / 2, NULL, 90);
					//text->render((int)(X + (W - H) / 2), (int)(Y + (H - W) / 2), NULL, 90);
					break;
				default:
					text->render(c * 40 + (40 - text->getWidth()) / 2, 160 + 40 * 5 + r * 80 + (80 - text->getHeight()) / 2);
					break;
				}
			}
			else
				RenderObjectDefault(gRendererE, ObjTypesE[i], c * 40 + 15.f, 160 + 5 * 40 + r * 80 + 5.f, FLOOR_HEIGHT, FLOOR_WIDTH);
			i++;
			if (i == nTextures) break;
		}
		if (i == nTextures) break;
	}

	//Update screen
	SDL_RenderPresent(gRendererE);
}

void cEditor::Run()
{
	SDL_ShowWindow(gWindowE);
	while (!Quit) {
		handleEvents();
		update();
		render();
	}
	SDL_HideWindow(gWindowE);
	Quit = false;
}
