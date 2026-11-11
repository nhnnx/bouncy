
#include "bouncy.h"
#include <cmath>

// Global window and renderer
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern MIX_Mixer* gMixer;

//------------------------------------------
// class cWorld
//------------------------------------------

cWorld::cWorld(int id, int lives, int score)
{
	WorldID = id;
	Lives = lives;
	Score = score;
	bfrScore[0] = '\0';
	Password = NULL;
	Rows = 0;
	Cols = 0;
	Grid = NULL;
	nLevels = 0;
	Background = NULL;
	nLevels = 0;
	nCompleted = 0;
	nObj = 0;
	Objects = NULL;
	CellX = 0;
	CellY = 0;
	Quit = false;

	Bumpy = NULL;
	Cloud = NULL;

	switch (id) {
	case WORLD_TEST: {
		//Background = ...;
		SetGrid(4, 4);
		// Add objects
		NewObject(OBJ_LevelEntrance, 0, 0, id | 0);
		NewObject(OBJ_LevelEntrance, 1, 0, id | 1);
		NewObject(OBJ_LevelEntrance, 2, 0, id | 2);
		NewObject(OBJ_LevelEntrance, 3, 0, id | 3);
		NewObject(OBJ_LevelEntrance, 1, 1, id | 4);
		NewObject(OBJ_LevelEntrance, 2, 1, id | 5);
		NewObject(OBJ_LevelEntrance, 2, 2, id | 6);
		NewObject(OBJ_LevelEntrance, 2, 3, id | 7);
		NewObject(OBJ_LevelEntrance, 0, 3, id | 8);
		NewObject(OBJ_LevelEntrance, 0, 1, id | 9);
		NewObject(OBJ_LevelEntrance, 3, 3, id | 10);
		NewObject(OBJ_LevelEntrance, 3, 2, id | 11);

		NewObject(OBJ_PathHor, 0, 0);
		NewObject(OBJ_PathHor, 1, 0);
		NewObject(OBJ_PathHor, 2, 0);
		NewObject(OBJ_PathVer, 1, 0);
		NewObject(OBJ_PathHor, 1, 1);
		NewObject(OBJ_PathVer, 2, 1);
		NewObject(OBJ_PathVer, 2, 2);
		NewObject(OBJ_PathHor, 0, 3);
		NewObject(OBJ_PathHor, 1, 3);
		NewObject(OBJ_PathHor, 2, 3);
		NewObject(OBJ_PathVer, 3, 2);
		NewObject(OBJ_PathVer, 0, 1);
		NewObject(OBJ_PathVer, 0, 2);

		NewObject(OBJ_Bumpy, 0, 0);
		NewObject(OBJ_FLOOR_Cloud, 0, 0);
	} break;

	case WORLD_1: {
		Password = Passworld1;
		//Background = ...;
		SetGrid(4, 4);
		NewObject(OBJ_Bumpy, 0, 0);
		NewObject(OBJ_FLOOR_Cloud, 0, 0);
		// Add objects
		NewObject(OBJ_LevelEntrance, 0, 0, id | 0);
		NewObject(OBJ_LevelEntrance, 1, 0, id | 1);
		NewObject(OBJ_LevelEntrance, 1, 2, id | 2);
		NewObject(OBJ_LevelEntrance, 0, 2, id | 3);
		NewObject(OBJ_LevelEntrance, 0, 1, id | 4);
		NewObject(OBJ_LevelEntrance, 0, 3, id | 5);
		NewObject(OBJ_LevelEntrance, 1, 3, id | 6);
		NewObject(OBJ_LevelEntrance, 2, 3, id | 7);
		NewObject(OBJ_LevelEntrance, 3, 3, id | 8);
		NewObject(OBJ_LevelEntrance, 3, 2, id | 9);
		NewObject(OBJ_LevelEntrance, 2, 2, id | 10);
		NewObject(OBJ_LevelEntrance, 2, 1, id | 11);
		NewObject(OBJ_LevelEntrance, 3, 1, id | 12);
		NewObject(OBJ_LevelEntrance, 3, 0, id | 13);
		NewObject(OBJ_LevelEntrance, 2, 0, id | 14);
		NewObject(OBJ_PathHor, 0, 0);
		NewObject(OBJ_PathVer, 1, 0);
		NewObject(OBJ_PathVer, 1, 1);
		NewObject(OBJ_PathHor, 0, 2);
		NewObject(OBJ_PathVer, 0, 1);
		NewObject(OBJ_PathVer, 0, 2);
		NewObject(OBJ_PathHor, 0, 3);
		NewObject(OBJ_PathHor, 1, 3);
		NewObject(OBJ_PathHor, 2, 3);
		NewObject(OBJ_PathVer, 3, 2);
		NewObject(OBJ_PathHor, 2, 2);
		NewObject(OBJ_PathVer, 2, 1);
		NewObject(OBJ_PathHor, 2, 1);
		NewObject(OBJ_PathVer, 3, 0);
		NewObject(OBJ_PathHor, 2, 0);
	} break;

	case WORLD_2: {
		Password = Passworld2;
		//Background = ...;
		SetGrid(4, 4);
		NewObject(OBJ_Bumpy, 1, 0);
		NewObject(OBJ_FLOOR_Cloud, 1, 0);
		// Add objects
		NewObject(OBJ_LevelEntrance, 0, 1, id | 0);
		NewObject(OBJ_PathVer, 0, 1);
		NewObject(OBJ_LevelEntrance, 0, 2, id | 1);
		NewObject(OBJ_PathVer, 0, 2);
		NewObject(OBJ_LevelEntrance, 0, 3, id | 2);
		NewObject(OBJ_PathHor, 0, 3);

		NewObject(OBJ_LevelEntrance, 1, 0, id | 3);
		NewObject(OBJ_PathVer, 1, 0);
		NewObject(OBJ_LevelEntrance, 1, 1, id | 4);
		NewObject(OBJ_PathVer, 1, 1);
		NewObject(OBJ_LevelEntrance, 1, 2, id | 5);
		NewObject(OBJ_PathVer, 1, 2);
		NewObject(OBJ_LevelEntrance, 1, 3, id | 6);
		NewObject(OBJ_PathHor, 1, 3);

		NewObject(OBJ_LevelEntrance, 2, 0, id | 7);
		NewObject(OBJ_PathVer, 2, 0);
		NewObject(OBJ_LevelEntrance, 2, 1, id | 8);
		NewObject(OBJ_PathVer, 2, 1);
		NewObject(OBJ_LevelEntrance, 2, 2, id | 9);
		NewObject(OBJ_PathVer, 2, 2);
		NewObject(OBJ_LevelEntrance, 2, 3, id | 10);
		NewObject(OBJ_PathHor, 2, 3);

		NewObject(OBJ_LevelEntrance, 3, 0, id | 11);
		NewObject(OBJ_PathVer, 3, 0);
		NewObject(OBJ_LevelEntrance, 3, 1, id | 12);
		NewObject(OBJ_PathVer, 3, 1);
		NewObject(OBJ_LevelEntrance, 3, 2, id | 13);
		NewObject(OBJ_PathVer, 3, 2);
		NewObject(OBJ_LevelEntrance, 3, 3, id | 14);
	} break;

	case WORLD_3: {
		Password = Passworld3;
		//Background = ...;
		SetGrid(4, 4);
		NewObject(OBJ_Bumpy, 0, 0);
		NewObject(OBJ_FLOOR_Cloud, 0, 0);
		// Add objects
		NewObject(OBJ_LevelEntrance, 0, 0, id | 0);
		NewObject(OBJ_LevelEntrance, 1, 0, id | 0);
		NewObject(OBJ_LevelEntrance, 2, 0, id | 1);
		NewObject(OBJ_LevelEntrance, 0, 1, id | 0);
		NewObject(OBJ_LevelEntrance, 2, 1, id | 2);
		NewObject(OBJ_LevelEntrance, 0, 2, id | 0);
		NewObject(OBJ_LevelEntrance, 0, 3, id | 0);
		NewObject(OBJ_LevelEntrance, 1, 2, id | 0);
		NewObject(OBJ_LevelEntrance, 1, 3, id | 0);
		NewObject(OBJ_LevelEntrance, 2, 2, id | 0);
		NewObject(OBJ_LevelEntrance, 2, 3, id | 0);
		NewObject(OBJ_LevelEntrance, 3, 2, id | 0);
		NewObject(OBJ_LevelEntrance, 3, 3, id | 0);
		NewObject(OBJ_LevelEntrance, 3, 1, id | 0);
		NewObject(OBJ_LevelEntrance, 3, 0, id | 0);
		NewObject(OBJ_PathHor, 0, 0);
		NewObject(OBJ_PathHor, 1, 0);
		NewObject(OBJ_PathVer, 0, 0);
		NewObject(OBJ_PathVer, 2, 0);
		NewObject(OBJ_PathVer, 2, 1);
		NewObject(OBJ_PathVer, 0, 1);
		NewObject(OBJ_PathVer, 0, 2);
		NewObject(OBJ_PathHor, 0, 2);
		NewObject(OBJ_PathHor, 1, 2);
		NewObject(OBJ_PathVer, 1, 2);
		NewObject(OBJ_PathVer, 2, 2);
		NewObject(OBJ_PathHor, 2, 2);
		NewObject(OBJ_PathVer, 3, 0);
		NewObject(OBJ_PathVer, 3, 1);
		NewObject(OBJ_PathVer, 3, 2);
	} break;

	case WORLD_EDITOR:
		Password = PassEditor;
		break;

	default:
		break;
	}
}

cWorld::~cWorld()
{
	// Delete all the objects in the level
	delete Background;
	for (int i = 0; i < nObj; i++)
		delete Objects[i];
	delete[] Objects;
	delete Bumpy;
	delete Cloud;
	delete[] Grid;
	//txScore.free();
}

void cWorld::ShowPassword() const
{
	if (!(Password && Password[0])) return;

	// Render
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	SDL_RenderClear(gRenderer);
	LTexture txpassw;
	txpassw.loadFromRenderedText(Password, { 255, 255, 255, 255 });
	txpassw.render((SCREEN_WIDTH - txpassw.getWidth()) / 2, (SCREEN_HEIGHT - txpassw.getHeight()) / 2);
	SDL_RenderPresent(gRenderer);

	// Message pump
	SDL_Event e;
	bool stop = false;
	while (!stop) {
		while (SDL_PollEvent(&e)) {
			// Press any key
			if (e.type == SDL_EVENT_KEY_DOWN) {
				stop = true;
				break;
			}
		}
	}
}

int cWorld::Run()
{
	// Show password
	ShowPassword();
	int success = false;
	while (!Quit) {
		HandleEvents();
		if (Lives == 0) {
			success = false;
			break;
		}
		if (nCompleted >= nLevels) {
			success = true;
			break;
		}
		if (Quit) break;
		Render();
	}
	return success; // specify if the world is completed, failed...
}

void cWorld::HandleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT ||
			(e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE)) {
			// Back to menu
			Quit = true;
		}

		if (e.type == SDL_EVENT_KEY_DOWN) {
			switch (e.key.key) {
			// Move Bumpy
			case SDLK_UP: 
			case SDLK_DOWN:
			case SDLK_LEFT:
			case SDLK_RIGHT:
			{
				float signx = 0.f;
				float signy = 0.f;
				if (e.key.key == SDLK_LEFT) signx = -1.f;
				else if (e.key.key == SDLK_RIGHT) signx = 1.f;
				else if (e.key.key == SDLK_UP) signy = -1.f;
				else if (e.key.key == SDLK_DOWN) signy = 1.f;
				while (true) {
					// Check if there is a Path
					bool canmove = false;
					cCell* cell = Bumpy->myCell;
					if (e.key.key == SDLK_LEFT) cell = grid(cell->col - 1, cell->row);
					else if (e.key.key == SDLK_UP) cell = grid(cell->col, cell->row - 1);
					if (!cell) break;
					int objtype = OBJ_PathHor;
					if ((e.key.key == SDLK_UP) || (e.key.key == SDLK_DOWN))
						objtype = OBJ_PathVer;
					int nobj = cell->nObj;
					for (int i = 0; i < nobj; i++) {
						if (cell->Objects[i]->type == objtype) {
							canmove = true;
							break;
						}
					}
					if (!canmove) break;

					// Move Bumpy (animation)
					float dist = 0;
					float deltax = signx * MaxVelX * 2;
					float deltay = signy * MaxVelX * 2;
					float finalxb = Bumpy->X + signx * CellX;
					float finalyb = Bumpy->Y + signy * CellY;
					float finalxc = Cloud->X + signx * CellX;
					float finalyc = Cloud->Y + signy * CellY;
					int maxdist = CellX;
					if ((e.key.key == SDLK_UP) || (e.key.key == SDLK_DOWN))
						maxdist = CellY;
					while (fabs(dist) < maxdist) {
						Bumpy->X += deltax;
						Bumpy->Y += deltay;
						Cloud->X += deltax;
						Cloud->Y += deltay;
						dist += deltax + deltay;
						// Update the screen
						Render();
						// Remove events during this animation
						SDL_PumpEvents();
						SDL_FlushEvent(SDL_EVENT_KEY_DOWN);
					}
					Bumpy->X = finalxb;
					Bumpy->Y = finalyb;
					Cloud->X = finalxc;
					Cloud->Y = finalyc;
					int col = Bumpy->myCell->col;
					int row = Bumpy->myCell->row;
					Bumpy->myCell = grid(col + (int)signx, row + (int)signy);
					Cloud->myCell = grid(col + (int)signx, row + (int)signy);

					// Did we found a new level entrance?
					bool stop = false;
					nobj = Bumpy->myCell->nObj;
					for (int i = 0; i < nobj; i++) {
						if (Bumpy->myCell->Objects[i]->type == OBJ_LevelEntrance) {
							stop = true;
							break;
						}
					}
					if (stop) break;
				}
			} break;

			// Enter a level
			case SDLK_RETURN:
			case SDLK_SPACE: {
				// Get the level
				cCell* cell = Bumpy->myCell;
				cLevelEntrance* entr = NULL;
				int nobj = cell->nObj;
				for (int i = 0; i < nobj; i++) {
					if (cell->Objects[i]->type == OBJ_LevelEntrance) {
						entr = static_cast<cLevelEntrance*>(cell->Objects[i]);
						break;
					}
				}
				// Run the level
				if (entr && entr->Status == 0) {
					cLevel* level = new cLevel(entr->LevelID);
					bool success = level->Run();
					if (!success) Lives--; // Lose 1 life
					else {
						entr->Status = 1; // Mark as completed
						nCompleted++;
						Score += level->nEaten + 10; // Add score
					}
					delete level;
				}
			} break;

			default:;
			}
		}
	}
}

void cWorld::Update()
{
}

void cWorld::Render()
{
	// Background
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	SDL_RenderClear(gRenderer);
	// Add background picture...

	// Show extra lives and points
	int xoff = 10, yoff = 10;
	for (int i = 0; i < Lives - 1; i++) {
		if (txLife.getWidth()) txLife.render(xoff, yoff);
		else RenderObjectDefault(gRenderer, OBJ_Life, (float)xoff, (float)yoff);
		xoff += 20;
	}
	LTexture txScore;
	char bfrScore[100];
	SDL_snprintf(bfrScore, 10, "%i", Score);
	txScore.loadFromRenderedText(bfrScore, { 255, 255, 255, 255 });
	txScore.render(SCREEN_WIDTH - txScore.getWidth(), 0);

	// Render all the objects
	for (int i = 0; i < nObj; i++)
		if (Objects[i]->type != OBJ_LevelEntrance)
			Objects[i]->render(gRenderer);
	for (int i = 0; i < nObj; i++)
		if (Objects[i]->type == OBJ_LevelEntrance)
			Objects[i]->render(gRenderer);
	if (Cloud) Cloud->render(gRenderer);
	if (Bumpy) Bumpy->render(gRenderer);

	SDL_RenderPresent(gRenderer);
}

cCell* cWorld::SetGrid(int cols, int rows)
{
	if (Grid) delete[] Grid;
	Rows = rows;
	Cols = cols;
	Grid = new cCell[Rows * Cols];
	for (int r = 0; r < Rows; r++) {
		for (int c = 0; c < Cols; c++) {
			Grid[r + c * Rows].row = r; // why there's a warning?!
			Grid[r + c * Rows].col = c;
		}
	}
	CellX = SCREEN_WIDTH / Cols;
	CellY = SCREEN_HEIGHT / Rows;
	return Grid;
}

cCell* cWorld::grid(int col, int row)
{
	if (col < 0 || col >= Cols) return NULL;
	if (row < 0 || row >= Rows) return NULL;
	return Grid + row + col * Rows;
}

bool cWorld::NewObject(int type, int col, int row, int id)
{
	bool success = false;
	int x0 = CellX * col;
	int y0 = CellY * row;
	cObject* obj = NULL;

	switch (type) {
	case OBJ_LevelEntrance: {
		obj = new cLevelEntrance(id);
		nLevels++;
		obj->type = type;
		// Position obj into the cell
		obj->X = x0 + (CellX - obj->W) / 2;
		obj->Y = y0 + (CellY - obj->H) / 2;
		obj->Collider.x = (int)obj->X;
		obj->Collider.y = (int)obj->Y;
		// Add to the object list
		AddObject(obj);
		grid(col, row)->AddObject(obj);
		success = true;
	} break;

	case OBJ_PathHor: {
		obj = new cPathHor();
		obj->type = type;
		// Position obj into the cell
		obj->X = x0 + CellX / 2.f;
		obj->Y = y0 + (CellY - obj->H) / 2;
		obj->Collider.x = (int)obj->X;
		obj->Collider.y = (int)obj->Y;
		obj->W = (float)CellX;
		// Add to the object list
		AddObject(obj);
		grid(col, row)->AddObject(obj);
		success = true;
	} break;
	
	case OBJ_PathVer: {
		obj = new cPathVer();
		obj->type = type;
		// Position obj into the cell
		obj->X = x0 + (CellX - obj->W) / 2;
		obj->Y = y0 + CellY / 2.f;
		obj->Collider.x = (int)obj->X;
		obj->Collider.y = (int)obj->Y;
		obj->H = (float)CellY;
		// Add to the object list
		AddObject(obj);
		grid(col, row)->AddObject(obj);
		success = true;
	} break;

	case OBJ_Bumpy: {
		if (Bumpy) delete Bumpy;
		Bumpy = new cBumpy();
		Bumpy->type = type;
		// Center Bumpy into the cell
		Bumpy->X = x0 + (CellX - Bumpy->W) / 2;
		Bumpy->Y = y0 + (CellY - Bumpy->H) / 2;
		Bumpy->Collider.x += (int)Bumpy->X;
		Bumpy->Collider.y += (int)Bumpy->Y;
		// Keep Bumpy outside objects list for now
		Bumpy->myCell = grid(col, row);
		Bumpy->myWorld = this;
		success = true;
	} break;

	case OBJ_FLOOR_Cloud: {
		Cloud = new cCloud();
		Cloud->type = type;
		// Position obj into the cell
		Cloud->X = x0 + (CellX - Cloud->W) / 2;
		Cloud->Y = y0 + (CellY + 20.f) / 2;
		Cloud->Collider.x += (int)Cloud->X;
		Cloud->Collider.y += (int)Cloud->Y;
		// Keep Cloud outside objects list for now
		//AddObject(Cloud);
		//grid(col, row)->AddObject(Cloud);
		Cloud->myCell = grid(col, row);
		Cloud->myWorld = this;
		success = true;
	} break;

	default:;
	}

	return success;
}

void cWorld::AddObject(cObject* obj)
// Add to the object list
{
	if (!obj) return;
	if (obj->myWorld == this) return; // already in
	//if (obj->myWorld) obj->myWorld->RemoveObject(obj);
	// Reallocate array
	cObject** newlist = new cObject * [nObj + 1];
	// Copy old list
	for (int i = 0; i < nObj; i++)
		newlist[i] = Objects[i];
	newlist[nObj] = obj;
	delete[] Objects;
	Objects = newlist;
	nObj++;
	obj->myWorld = this;
}

//------------------------------------------
// class cCell
//------------------------------------------

cCell::cCell()
{
	nObj = 0;
	Objects = NULL;
	row = 0;
	col = 0;
}

cCell::~cCell()
{
	// Delete the objects list
	if (Objects) {
		delete[] Objects;
		Objects = NULL;
	}
	nObj = 0;
}

void cCell::AddObject(cObject* obj)
{
	if (!obj) return;
	if (obj->myCell == this) return; // already in
	if (obj->myCell) obj->myCell->RemoveObject(obj);
	// Reallocate array
	cObject** newlist = new cObject*[nObj + 1];
	// Copy old list
	for (int i = 0; i < nObj; i++)
		newlist[i] = Objects[i];
	newlist[nObj] = obj;
	if (Objects) delete[] Objects;
	Objects = newlist;
	nObj++;
	obj->myCell = this;
}

void cCell::RemoveObject(cObject* obj)
{
	if (!obj) return;
	if (nObj == 0) return;
	int i = 0;
	for (i = 0; i < nObj; i++)
		if (Objects[i] == obj) break;
	if (i >= nObj) return; // not in the list
	// Reallocate array
	cObject** newlist = NULL;
	if (nObj > 1) {
		newlist = new cObject * [nObj - 1];
		// Copy old list
		for (int j = 0; j < i; j++)
			newlist[j] = Objects[j];
		for (int j = i; j + 1 < nObj; j++)
			newlist[j] = Objects[j + 1];
	}
	delete[] Objects;
	Objects = newlist;
	nObj--;
	obj->myCell = NULL;
}

//------------------------------------------
// class cLevel
//------------------------------------------

cLevel::cLevel(int levelID)
{
	LevelID = levelID;
	Rows = 0;
	Cols = 0;
	CellX = 0;
	CellY = 0;
	nFood = 0;
	nEaten = 0;
	nObj = 0;
	Objects = NULL;
	Exit = NULL;
	Enemy = NULL;
	Bumpy = NULL;
	Grid = NULL;
	Background = NULL;
	ShowGrid = false;
	QuitLevel = false;
	Started = false;
	Completed = false;

	// Initialize the level
	// Add grid, background, objects...

	switch (LevelID) {

	//-----------------------------------------
	// WORLD TEST
	//-----------------------------------------


	case WORLD_TEST | 0: {
		//Background = ...;
		SetGrid(8, 6);
		// Add objects
		NewObject(OBJ_FLOOR_Forced, 0, 1, 0);

		NewObject(OBJ_FLOOR_Spine, 3, 0);
		NewObject(OBJ_FLOOR_SpineUD, 1, 1, 1);
		NewObject(OBJ_FLOOR_SpineUD, 0, 2, 0);

		NewObject(OBJ_FLOOR_Invisible, 0, 0);
		NewObject(OBJ_FLOOR_Invisible, 1, 0);

		NewObject(OBJ_SIDE_Fake, 0, 4);
		NewObject(OBJ_SIDE_Invisible, 0, 5);
		NewObject(OBJ_Life, 0, 5);

		NewObject(OBJ_FLOOR_Plain, 1, 3);
		NewObject(OBJ_FLOOR_Up, 2, 2);
		NewObject(OBJ_FLOOR_Down, 3, 1);
		NewObject(OBJ_FLOOR_Decision, 4, 0);

		NewObject(OBJ_SIDE_Wall, 3, 2, 0);
		NewObject(OBJ_SIDE_Wall, 3, 3, 1);
		NewObject(OBJ_SIDE_Wall, 3, 4, 2);
		NewObject(OBJ_FLOOR_Fake, 4, 1);
		NewObject(OBJ_FLOOR_Wall, 4, 2, 2);

		NewObject(OBJ_FLOOR_Plain, 4, 4);
		NewObject(OBJ_FLOOR_Reducing, 5, 3, 2);
		NewObject(OBJ_FLOOR_Reducing, 6, 2, 1);
		NewObject(OBJ_FLOOR_Reducing, 7, 1, 0);
		NewObject(OBJ_FLOOR_Wall, 6, 0, 1);
		//NewObject(OBJ_FLOOR_Plain, 7, 1);
		NewObject(OBJ_Food, 4, 4);
		NewObject(OBJ_Food, 5, 3);
		NewObject(OBJ_Food, 6, 2);
		NewObject(OBJ_Food, 7, 1);

		NewObject(OBJ_FLOOR_Spring, 1, 5);
		NewObject(OBJ_SIDE_Shooter, 5, 3);

		NewObject(OBJ_FLOOR_Ice, 2, 5);
		NewObject(OBJ_FLOOR_Ice, 3, 5);
		NewObject(OBJ_FLOOR_Ice, 4, 5);
		NewObject(OBJ_FLOOR_Ice, 5, 5);
		NewObject(OBJ_FLOOR_OneBounce, 6, 5);
		NewObject(OBJ_FLOOR_Ice, 7, 5);
		NewObject(OBJ_Food, 4, 5);
		NewObject(OBJ_Food, 5, 5);
		NewObject(OBJ_Food, 6, 5);
		NewObject(OBJ_Food, 7, 5);

		NewObject(OBJ_SIDE_Plain, 1, 5);
		NewObject(OBJ_SIDE_Nways, 4, 4, 1);
		NewObject(OBJ_SIDE_Nways, 4, 5, 2);
		NewObject(OBJ_SIDE_Nways, 5, 5, 3);
		NewObject(OBJ_SIDE_RightOnly, 6, 5);
		NewObject(OBJ_SIDE_LeftOnly, 6, 4);

		NewObject(OBJ_FLOOR_Forced, 7, 3, 1);

		NewObject(OBJ_FLOOR_Cloud, 2, 4);

		// Necessary objects:
		NewObject(OBJ_Bumpy, 3, 4);
		NewObject(OBJ_FLOOR_Exit, 0, 4);
	} break;
	case WORLD_TEST | 1: {
		//Background = ...;
		SetGrid(8, 6);

		NewObject(OBJ_FLOOR_Forced, 4, 3, 1);
		NewObject(OBJ_Food, 4, 3, 0);
		NewObject(OBJ_Food, 3, 4, 0);
		NewObject(OBJ_Food, 6, 0, 0);
		NewObject(OBJ_FLOOR_Reducing, 3, 1, 0);
		NewObject(OBJ_FLOOR_Reducing, 3, 4, 0);
		NewObject(OBJ_FLOOR_Reducing, 4, 4, 0);
		NewObject(OBJ_FLOOR_Reducing, 5, 4, 0);
		NewObject(OBJ_FLOOR_Reducing, 6, 4, 0);
		NewObject(OBJ_FLOOR_Reducing, 7, 4, 1);
		NewObject(OBJ_FLOOR_Reducing, 4, 0, 0);
		NewObject(OBJ_FLOOR_Ice, 2, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 0, 3, 0);
		NewObject(OBJ_FLOOR_Ice, 1, 2, 0);
		NewObject(OBJ_Food, 4, 0, 0);
		NewObject(OBJ_Food, 3, 1, 0);
		NewObject(OBJ_Food, 2, 2, 0);
		NewObject(OBJ_Food, 4, 4, 0);
		NewObject(OBJ_Food, 5, 4, 0);
		NewObject(OBJ_Food, 6, 4, 0);
		NewObject(OBJ_Food, 7, 4, 0);
		NewObject(OBJ_Food, 6, 3, 0);
		NewObject(OBJ_Food, 7, 3, 0);
		NewObject(OBJ_FLOOR_Spring, 1, 5, 0);
		NewObject(OBJ_SIDE_Nways, 6, 1, 1);
		NewObject(OBJ_SIDE_Nways, 5, 1, 1);
		NewObject(OBJ_FLOOR_Down, 6, 1, 0);
		NewObject(OBJ_FLOOR_SpineUD, 6, 0, 0);
		NewObject(OBJ_Food, 6, 1, 0);
		NewObject(OBJ_FLOOR_Reducing, 5, 0, 1);
		NewObject(OBJ_FLOOR_Reducing, 2, 4, 0);
		NewObject(OBJ_Food, 2, 4, 0);
		NewObject(OBJ_FLOOR_Forced, 5, 3, 0);
		NewObject(OBJ_Food, 5, 3, 0);
		NewObject(OBJ_FLOOR_Exit, 6, 5, 0);
		NewObject(OBJ_Bumpy, 0, 1);
	} break;

	case WORLD_TEST | 2: {
		//Background = ...;
		SetGrid(8, 6);

		NewObject(OBJ_FLOOR_Teleport, 0, 5);
		NewObject(OBJ_FLOOR_Plain, 1, 4, 0);
		NewObject(OBJ_FLOOR_Catapult, 1, 5, 0);
		NewObject(OBJ_FLOOR_Glue, 2, 5);
		NewObject(OBJ_FLOOR_Magnetic, 3, 4, 0);
		NewObject(OBJ_FLOOR_Magnetic, 3, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 5, 4, 0);
		NewObject(OBJ_FLOOR_Catapult, 5, 5, 1);
		NewObject(OBJ_FLOOR_Teleport, 6, 5, 0);
		NewObject(OBJ_FLOOR_Exit, 7, 5, 0);

		NewObject(OBJ_Food, 3, 2, 0);
		NewObject(OBJ_Food, 3, 3, 0);
		NewObject(OBJ_Food, 3, 4, 0);

		NewObject(OBJ_FLOOR_Plain, 2, 2, 0);
		NewObject(OBJ_Bumpy, 2, 2);
	} break;
	case WORLD_TEST | 3: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_Glue, 2, 3, 0);
		NewObject(OBJ_FLOOR_Glue, 1, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 2, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 3, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 3, 0);
		NewObject(OBJ_FLOOR_Teleport, 4, 1, 0);
		NewObject(OBJ_FLOOR_Teleport, 5, 1, 0);
		NewObject(OBJ_FLOOR_Teleport, 6, 2, 0);
		NewObject(OBJ_SIDE_Glue, 0, 3, 0);
		NewObject(OBJ_SIDE_Glue, 0, 2, 0);
		NewObject(OBJ_SIDE_Glue, 2, 1, 0);
		NewObject(OBJ_SIDE_Glue, 1, 3, 0);
		NewObject(OBJ_Food, 7, 0, 0);
		NewObject(OBJ_Food, 7, 1, 0);
		NewObject(OBJ_Food, 7, 2, 0);
		NewObject(OBJ_Food, 7, 3, 0);
		NewObject(OBJ_Food, 7, 4, 0);
		NewObject(OBJ_FLOOR_Exit, 7, 5, 0);
		NewObject(OBJ_Food, 0, 3, 0);
		NewObject(OBJ_Food, 0, 2, 0);
		NewObject(OBJ_Food, 0, 1, 0);
		NewObject(OBJ_Food, 0, 0, 0);
		NewObject(OBJ_FLOOR_Teleport, 0, 5, 0);
		NewObject(OBJ_FLOOR_Teleport, 1, 5, 0);
		NewObject(OBJ_FLOOR_Teleport, 2, 5, 0);
		NewObject(OBJ_FLOOR_Teleport, 3, 5, 0);
		NewObject(OBJ_FLOOR_Teleport, 4, 5, 0);
		NewObject(OBJ_FLOOR_Teleport, 5, 5, 0);
		NewObject(OBJ_FLOOR_Teleport, 6, 5, 0);
		NewObject(OBJ_FLOOR_Teleport, 7, 5, 0);
		NewObject(OBJ_Food, 0, 4, 0);
		NewObject(OBJ_Food, 0, 5, 0);
		NewObject(OBJ_Food, 1, 0, 0);
		NewObject(OBJ_Food, 2, 0, 0);
		NewObject(OBJ_Food, 3, 0, 0);
		NewObject(OBJ_Food, 4, 0, 0);
		NewObject(OBJ_Food, 5, 0, 0);
		NewObject(OBJ_Food, 6, 0, 0);

		NewObject(OBJ_SIDE_Face, 3, 2, 0);
		NewObject(OBJ_SIDE_Ice, 6, 0, 0);
		NewObject(OBJ_SIDE_Ice, 6, 1, 0);
		NewObject(OBJ_SIDE_Ice, 6, 2, 0);
		NewObject(OBJ_SIDE_Ice, 6, 3, 0);
		NewObject(OBJ_SIDE_Ice, 6, 4, 0);
		NewObject(OBJ_SIDE_Ice, 6, 5, 0);

		NewObject(OBJ_Enemy, 0, 0);

		NewObject(OBJ_Bumpy, 3, 2);
	} break;
	
	case WORLD_TEST | 4: {
		SetGrid(8, 6);
		NewObject(OBJ_Food, 1, 1, 0);
		NewObject(OBJ_Food, 2, 1, 0);
		NewObject(OBJ_Food, 3, 1, 0);
		NewObject(OBJ_Food, 4, 1, 0);
		NewObject(OBJ_Food, 5, 1, 0);
		NewObject(OBJ_Food, 6, 1, 0);
		NewObject(OBJ_Food, 7, 1, 0);
		NewObject(OBJ_Food, 7, 4, 0);
		NewObject(OBJ_Food, 6, 4, 0);
		NewObject(OBJ_Food, 5, 4, 0);
		NewObject(OBJ_Food, 4, 4, 0);
		NewObject(OBJ_Food, 3, 4, 0);
		NewObject(OBJ_Food, 2, 4, 0);
		NewObject(OBJ_Food, 1, 4, 0);
		NewObject(OBJ_Food, 0, 4, 0);
		NewObject(OBJ_Food, 0, 1, 0);
		NewObject(OBJ_FLOOR_Cloud, 0, 3, 0);
		NewObject(OBJ_FLOOR_Exit, 3, 2, 0);
		NewObject(OBJ_Enemy, 6, 0, 11);
		NewObject(1, 0, 2);
	} break;

	case WORLD_TEST | 5: {
		SetGrid(8, 6);
		NewObject(OBJ_Food, 1, 1, 0);
		NewObject(OBJ_Food, 2, 1, 0);
		NewObject(OBJ_Food, 3, 1, 0);
		NewObject(OBJ_Food, 4, 1, 0);
		NewObject(OBJ_Food, 5, 1, 0);
		NewObject(OBJ_Food, 6, 1, 0);
		NewObject(OBJ_Food, 7, 1, 0);
		NewObject(OBJ_Food, 7, 4, 0);
		NewObject(OBJ_Food, 6, 4, 0);
		NewObject(OBJ_Food, 5, 4, 0);
		NewObject(OBJ_Food, 4, 4, 0);
		NewObject(OBJ_Food, 3, 4, 0);
		NewObject(OBJ_Food, 2, 4, 0);
		NewObject(OBJ_Food, 1, 4, 0);
		NewObject(OBJ_Food, 0, 4, 0);
		NewObject(OBJ_Food, 0, 1, 0);
		NewObject(OBJ_FLOOR_Cloud, 0, 3, 0);
		NewObject(OBJ_FLOOR_Exit, 3, 2, 0);
		NewObject(OBJ_Enemy, 6, 0, 22);
		NewObject(1, 0, 2);
	} break;

	case WORLD_TEST | 6: {
		SetGrid(8, 6);
		NewObject(OBJ_Food, 1, 1, 0);
		NewObject(OBJ_Food, 2, 1, 0);
		NewObject(OBJ_Food, 3, 1, 0);
		NewObject(OBJ_Food, 4, 1, 0);
		NewObject(OBJ_Food, 5, 1, 0);
		NewObject(OBJ_Food, 6, 1, 0);
		NewObject(OBJ_Food, 7, 1, 0);
		NewObject(OBJ_Food, 7, 4, 0);
		NewObject(OBJ_Food, 6, 4, 0);
		NewObject(OBJ_Food, 5, 4, 0);
		NewObject(OBJ_Food, 4, 4, 0);
		NewObject(OBJ_Food, 3, 4, 0);
		NewObject(OBJ_Food, 2, 4, 0);
		NewObject(OBJ_Food, 1, 4, 0);
		NewObject(OBJ_Food, 0, 4, 0);
		NewObject(OBJ_Food, 0, 1, 0);
		NewObject(OBJ_FLOOR_Cloud, 0, 3, 0);
		NewObject(OBJ_FLOOR_Exit, 3, 2, 0);
		NewObject(OBJ_Enemy, 6, 0, 33);
		NewObject(1, 0, 2);
	} break;

	case WORLD_TEST | 7: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_Magnetic, 2, 1, 0);
		NewObject(OBJ_FLOOR_Magnetic, 3, 1, 0);
		NewObject(OBJ_FLOOR_Magnetic, 4, 1, 0);
		NewObject(OBJ_FLOOR_Magnetic, 4, 3, 0);
		NewObject(OBJ_FLOOR_Magnetic, 5, 1, 0);
		NewObject(OBJ_FLOOR_Magnetic, 6, 1, 0);
		NewObject(OBJ_FLOOR_Magnetic, 7, 1, 0);
		NewObject(OBJ_FLOOR_Catapult, 7, 2, 1);
		NewObject(OBJ_SIDE_Shooter, 6, 3, 0);
		NewObject(OBJ_FLOOR_Magnetic, 3, 2, 0);
		NewObject(OBJ_FLOOR_Magnetic, 2, 2, 0);
		NewObject(OBJ_FLOOR_Magnetic, 1, 2, 0);
		NewObject(OBJ_FLOOR_Ice, 3, 3, 0);
		NewObject(OBJ_FLOOR_Spring, 0, 4, 0);
		NewObject(OBJ_FLOOR_SpineUD, 2, 3, 0);
		NewObject(OBJ_FLOOR_Wall, 1, 3, 0);
		NewObject(OBJ_FLOOR_Forced, 0, 2, 0);
		NewObject(OBJ_FLOOR_Magnetic, 0, 1, 0);
		NewObject(OBJ_FLOOR_Exit, 7, 5, 0);
		NewObject(OBJ_FLOOR_Reducing, 6, 4, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 5, 0);
		NewObject(OBJ_FLOOR_OneBounce, 5, 4, 0);
		NewObject(OBJ_FLOOR_Plain, 5, 5, 0);
		NewObject(OBJ_FLOOR_Glue, 4, 4, 0);
		NewObject(OBJ_FLOOR_Glue, 5, 2, 0);
		NewObject(OBJ_FLOOR_Invisible, 6, 2, 0);
		NewObject(OBJ_FLOOR_Cloud, 3, 5, 0);
		NewObject(OBJ_FLOOR_Magnetic, 1, 4, 0);
		NewObject(OBJ_FLOOR_Magnetic, 2, 4, 0);
		NewObject(OBJ_FLOOR_Magnetic, 4, 0, 0);
		NewObject(OBJ_FLOOR_Magnetic, 2, 0, 0);
		NewObject(OBJ_SIDE_Glue, 2, 1, 0);
		NewObject(OBJ_SIDE_RightOnly, 3, 1, 0);
		NewObject(OBJ_Bumpy, 1, 1);
	} break;

	case WORLD_TEST | 8:
	case WORLD_TEST | 9:
	case WORLD_TEST | 10:
	case WORLD_TEST | 11: {
		SetGrid(8, 6);
		NewObject(OBJ_Bumpy, 4, 1);
		NewObject(OBJ_FLOOR_Plain, 4, 1);
		NewObject(OBJ_Food, 3, 1);
		NewObject(OBJ_Food, 3, 2);
		NewObject(OBJ_Food, 3, 3);
		NewObject(OBJ_FLOOR_Exit, 3, 4);
	} break;

	//-----------------------------------------
	// WORLD 1 
	//-----------------------------------------

	case WORLD_1 | 0: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_Plain, 0, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 2, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 5, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 4, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 3, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 1, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 1, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 3, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 3, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 4, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 4, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 1, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 1, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 3, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 4, 0);
		NewObject(OBJ_FLOOR_Exit, 3, 5, 0);
		NewObject(OBJ_Food, 1, 3, 0);
		NewObject(OBJ_Food, 3, 0, 0);
		NewObject(OBJ_Food, 3, 5, 0);
		NewObject(OBJ_Food, 4, 1, 0);
		NewObject(OBJ_Food, 4, 4, 0);
		NewObject(OBJ_Food, 6, 3, 0);
		NewObject(OBJ_Bumpy, 0, 5);
	} break;

	case WORLD_1 | 1: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_Plain, 0, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 1, 0);
		NewObject(OBJ_FLOOR_Plain, 2, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 3, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 4, 0);
		NewObject(OBJ_FLOOR_Plain, 5, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 2, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 5, 0);
		NewObject(OBJ_FLOOR_Forced, 0, 5, 0);
		NewObject(OBJ_FLOOR_Forced, 7, 5, 1);
		NewObject(OBJ_FLOOR_Spine, 6, 1, 0);
		NewObject(OBJ_Food, 1, 1, 0);
		NewObject(OBJ_Food, 2, 2, 0);
		NewObject(OBJ_Food, 3, 3, 0);
		NewObject(OBJ_Food, 4, 4, 0);
		NewObject(OBJ_Food, 6, 5, 0);
		NewObject(OBJ_Food, 5, 5, 0);
		NewObject(OBJ_Food, 4, 5, 0);
		NewObject(OBJ_Food, 3, 5, 0);
		NewObject(OBJ_Food, 2, 5, 0);
		NewObject(OBJ_Food, 1, 5, 0);
		NewObject(OBJ_FLOOR_Exit, 0, 0, 0);
		NewObject(OBJ_Bumpy, 0, 0);
	} break;

	case WORLD_1 | 2: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_Plain, 0, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 1, 0);
		NewObject(OBJ_FLOOR_Plain, 0, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 3, 0);
		NewObject(OBJ_FLOOR_Plain, 0, 4, 0);
		NewObject(OBJ_FLOOR_Plain, 7, 4, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 3, 0);
		NewObject(OBJ_FLOOR_Plain, 7, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 1, 0);
		NewObject(OBJ_FLOOR_Plain, 7, 0, 0);
		NewObject(OBJ_FLOOR_Exit, 6, 1, 0);
		NewObject(OBJ_FLOOR_Spine, 3, 1, 0);
		NewObject(OBJ_FLOOR_Spine, 2, 1, 0);
		NewObject(OBJ_FLOOR_Spine, 4, 1, 0);
		NewObject(OBJ_FLOOR_Spine, 5, 1, 0);
		NewObject(OBJ_FLOOR_Spine, 2, 3, 0);
		NewObject(OBJ_FLOOR_Spine, 3, 3, 0);
		NewObject(OBJ_FLOOR_Spine, 4, 3, 0);
		NewObject(OBJ_FLOOR_Spine, 5, 3, 0);
		NewObject(OBJ_FLOOR_Ice, 5, 5, 0);
		NewObject(OBJ_FLOOR_Ice, 4, 5, 0);
		NewObject(OBJ_FLOOR_Ice, 3, 5, 0);
		NewObject(OBJ_FLOOR_Ice, 2, 5, 0);
		NewObject(OBJ_FLOOR_Ice, 1, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 5, 0);
		NewObject(OBJ_Food, 1, 1, 0);
		NewObject(OBJ_Food, 0, 2, 0);
		NewObject(OBJ_Food, 1, 3, 0);
		NewObject(OBJ_Food, 0, 4, 0);
		NewObject(OBJ_Food, 1, 5, 0);
		NewObject(OBJ_Food, 2, 5, 0);
		NewObject(OBJ_Food, 3, 5, 0);
		NewObject(OBJ_Food, 4, 5, 0);
		NewObject(OBJ_Food, 5, 5, 0);
		NewObject(OBJ_Food, 6, 5, 0);
		NewObject(OBJ_Food, 7, 4, 0);
		NewObject(OBJ_Food, 6, 3, 0);
		NewObject(OBJ_Food, 7, 2, 0);
		NewObject(OBJ_Food, 6, 1, 0);
		NewObject(OBJ_Food, 7, 0, 0);
		NewObject(OBJ_Bumpy, 0, 0);
	} break;

	case WORLD_1 | 3: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_SpineUD, 0, 0, 0);
		NewObject(OBJ_FLOOR_SpineUD, 1, 2, 0);
		NewObject(OBJ_FLOOR_SpineUD, 2, 1, 0);
		NewObject(OBJ_FLOOR_SpineUD, 3, 0, 0);
		NewObject(OBJ_FLOOR_SpineUD, 4, 0, 0);
		NewObject(OBJ_FLOOR_SpineUD, 5, 1, 0);
		NewObject(OBJ_FLOOR_SpineUD, 6, 2, 0);
		NewObject(OBJ_FLOOR_SpineUD, 7, 0, 0);
		NewObject(OBJ_Food, 0, 2, 0);
		NewObject(OBJ_Food, 1, 4, 0);
		NewObject(OBJ_Food, 2, 3, 0);
		NewObject(OBJ_Food, 3, 2, 0);
		NewObject(OBJ_Food, 4, 2, 0);
		NewObject(OBJ_Food, 5, 3, 0);
		NewObject(OBJ_Food, 6, 4, 0);
		NewObject(OBJ_Food, 7, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 0, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 2, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 5, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 7, 5, 0);
		NewObject(OBJ_FLOOR_Exit, 4, 2, 0);
		NewObject(OBJ_Bumpy, 0, 0);
	} break;

	case WORLD_1 | 4: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_SpineUD, 0, 0, 0);
		NewObject(OBJ_FLOOR_Ice, 1, 0, 0);
		NewObject(OBJ_FLOOR_Ice, 2, 0, 0);
		NewObject(OBJ_FLOOR_Ice, 3, 0, 0);
		NewObject(OBJ_FLOOR_Ice, 4, 0, 0);

		NewObject(OBJ_FLOOR_Ice, 5, 1, 0);
		NewObject(OBJ_FLOOR_Ice, 4, 1, 0);
		NewObject(OBJ_FLOOR_Ice, 3, 1, 0);
		NewObject(OBJ_SIDE_Spine, 5, 1, 0);

		NewObject(OBJ_FLOOR_SpineUD, 1, 2, 0);
		NewObject(OBJ_FLOOR_Ice, 2, 2, 0);
		NewObject(OBJ_FLOOR_Ice, 3, 2, 0);
		NewObject(OBJ_FLOOR_Ice, 4, 2, 0);

		NewObject(OBJ_FLOOR_Ice, 5, 3, 0);
		NewObject(OBJ_FLOOR_SpineUD, 6, 3, 0);

		NewObject(OBJ_SIDE_Spine, 3, 4, 0);
		NewObject(OBJ_FLOOR_Ice, 4, 4, 0);
		NewObject(OBJ_FLOOR_Ice, 5, 4, 0);

		NewObject(OBJ_FLOOR_Ice, 0, 5, 0);
		NewObject(OBJ_FLOOR_Ice, 1, 5, 0);
		NewObject(OBJ_FLOOR_Ice, 2, 5, 0);
		NewObject(OBJ_FLOOR_Ice, 3, 5, 0);
		NewObject(OBJ_FLOOR_Ice, 4, 5, 0);
		NewObject(OBJ_FLOOR_Ice, 5, 5, 0);
		NewObject(OBJ_FLOOR_Ice, 6, 5, 0);
		NewObject(OBJ_FLOOR_Spine, 7, 5, 0);

		NewObject(OBJ_Food, 5, 1, 0);
		NewObject(OBJ_Food, 2, 2, 0);
		NewObject(OBJ_Food, 5, 3, 0);
		NewObject(OBJ_Food, 4, 4, 0);
		NewObject(OBJ_Food, 6, 5, 0);
		NewObject(OBJ_Food, 0, 1, 0);

		NewObject(OBJ_FLOOR_Exit, 2, 5, 0);
		NewObject(OBJ_Bumpy, 0, 0);
	} break;

	case WORLD_1 | 5: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_Reducing, 2, 0, 0);
		NewObject(OBJ_FLOOR_Reducing, 2, 1, 1);
		NewObject(OBJ_FLOOR_Reducing, 2, 2, 0);
		NewObject(OBJ_FLOOR_Reducing, 2, 3, 1);
		NewObject(OBJ_FLOOR_Plain, 0, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 1, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 1, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 3, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 3, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 4, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 4, 0);
		NewObject(OBJ_FLOOR_Plain, 5, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 2, 5, 0);
		NewObject(OBJ_FLOOR_Reducing, 5, 1, 1);
		NewObject(OBJ_FLOOR_Reducing, 5, 0, 1);
		NewObject(OBJ_FLOOR_Reducing, 6, 1, 0);
		NewObject(OBJ_FLOOR_Reducing, 5, 2, 0);
		NewObject(OBJ_FLOOR_Reducing, 5, 3, 1);
		NewObject(OBJ_FLOOR_Reducing, 2, 4, 1);
		NewObject(OBJ_FLOOR_Reducing, 5, 4, 0);
		NewObject(OBJ_Food, 3, 0, 0);
		NewObject(OBJ_Food, 4, 0, 0);
		NewObject(OBJ_Food, 4, 1, 0);
		NewObject(OBJ_Food, 3, 1, 0);
		NewObject(OBJ_Food, 3, 2, 0);
		NewObject(OBJ_Food, 4, 2, 0);
		NewObject(OBJ_Food, 4, 3, 0);
		NewObject(OBJ_Food, 3, 3, 0);
		NewObject(OBJ_Food, 3, 4, 0);
		NewObject(OBJ_Food, 4, 4, 0);
		NewObject(OBJ_Food, 4, 5, 0);
		NewObject(OBJ_Food, 5, 5, 0);
		NewObject(OBJ_Food, 3, 5, 0);
		NewObject(OBJ_Food, 2, 5, 0);
		NewObject(OBJ_FLOOR_Exit, 7, 1, 0);
		NewObject(OBJ_Bumpy, 0, 0);
	} break;

	case WORLD_1 | 6: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_Plain, 0, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 2, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 5, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 1, 0);
		NewObject(OBJ_FLOOR_Plain, 5, 1, 0);
		NewObject(OBJ_FLOOR_Plain, 5, 2, 0);
		NewObject(OBJ_FLOOR_Reducing, 3, 0, 2);
		NewObject(OBJ_FLOOR_Reducing, 4, 1, 1);
		NewObject(OBJ_FLOOR_Reducing, 4, 2, 1);
		NewObject(OBJ_FLOOR_Reducing, 3, 2, 0);
		NewObject(OBJ_FLOOR_Spine, 6, 2, 0);
		NewObject(OBJ_FLOOR_Spine, 2, 2, 0);
		NewObject(OBJ_FLOOR_Spine, 4, 3, 0);
		NewObject(OBJ_FLOOR_Ice, 4, 4, 0);
		NewObject(OBJ_FLOOR_Ice, 3, 4, 0);
		NewObject(OBJ_FLOOR_Ice, 2, 4, 0);
		NewObject(OBJ_FLOOR_Ice, 5, 4, 0);
		NewObject(OBJ_FLOOR_Reducing, 1, 4, 1);
		NewObject(OBJ_FLOOR_Reducing, 6, 4, 1);
		NewObject(OBJ_Life, 1, 5, 0);
		NewObject(OBJ_Life, 6, 5, 0);
		NewObject(OBJ_Food, 2, 4, 0);
		NewObject(OBJ_Food, 3, 4, 0);
		NewObject(OBJ_Food, 4, 4, 0);
		NewObject(OBJ_Food, 5, 4, 0);
		NewObject(OBJ_Food, 5, 0, 0);
		NewObject(OBJ_FLOOR_Exit, 6, 4, 0);
		NewObject(OBJ_Bumpy, 0, 0);
	} break;

	case WORLD_1 | 7: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_SpineUD, 0, 0, 0);
		NewObject(OBJ_FLOOR_SpineUD, 7, 0, 0);
		NewObject(OBJ_FLOOR_Ice, 0, 3, 0);
		NewObject(OBJ_FLOOR_Ice, 7, 3, 0);
		NewObject(OBJ_Food, 0, 2, 0);
		NewObject(OBJ_Food, 1, 3, 0);
		NewObject(OBJ_Food, 2, 3, 0);
		NewObject(OBJ_Food, 3, 3, 0);
		NewObject(OBJ_Food, 4, 3, 0);
		NewObject(OBJ_Food, 5, 3, 0);
		NewObject(OBJ_Food, 6, 3, 0);
		NewObject(OBJ_Food, 7, 2, 0);
		NewObject(OBJ_FLOOR_Catapult, 1, 3, 0);
		NewObject(OBJ_FLOOR_Catapult, 3, 3, 0);
		NewObject(OBJ_FLOOR_Catapult, 5, 3, 0);
		NewObject(OBJ_FLOOR_Catapult, 6, 3, 1);
		NewObject(OBJ_FLOOR_Catapult, 4, 3, 1);
		NewObject(OBJ_FLOOR_Catapult, 2, 3, 1);
		NewObject(OBJ_FLOOR_Exit, 7, 3, 0);
		NewObject(OBJ_Bumpy, 0, 0);
	} break;

	case WORLD_1 | 8: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_Plain, 0, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 3, 0);
		NewObject(OBJ_FLOOR_Plain, 7, 5, 0);
		NewObject(OBJ_FLOOR_Reducing, 1, 0, 2);
		NewObject(OBJ_FLOOR_Catapult, 2, 0, 1);
		NewObject(OBJ_FLOOR_Catapult, 1, 1, 0);
		NewObject(OBJ_FLOOR_Catapult, 6, 3, 1);
		NewObject(OBJ_FLOOR_Catapult, 5, 5, 0);
		NewObject(OBJ_FLOOR_Catapult, 3, 5, 0);
		NewObject(OBJ_FLOOR_Fake, 3, 1, 0);
		NewObject(OBJ_FLOOR_Fake, 3, 2, 0);
		NewObject(OBJ_FLOOR_Fake, 3, 3, 0);
		NewObject(OBJ_FLOOR_Fake, 3, 4, 0);
		NewObject(OBJ_FLOOR_Fake, 4, 4, 0);
		NewObject(OBJ_FLOOR_Fake, 5, 4, 0);
		NewObject(OBJ_FLOOR_Fake, 6, 4, 0);
		NewObject(OBJ_Food, 4, 3, 0);
		NewObject(OBJ_FLOOR_Exit, 6, 5, 0);
		NewObject(OBJ_Bumpy, 0, 0);
	} break;

	case WORLD_1 | 9: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_Plain, 0, 0, 0);
		NewObject(OBJ_FLOOR_Down, 1, 0, 0);
		NewObject(OBJ_FLOOR_Down, 2, 1, 0);
		NewObject(OBJ_FLOOR_Down, 3, 2, 0);
		NewObject(OBJ_FLOOR_Down, 4, 3, 0);
		NewObject(OBJ_FLOOR_Down, 5, 4, 0);
		NewObject(OBJ_FLOOR_Reducing, 1, 1, 2);
		NewObject(OBJ_FLOOR_Reducing, 2, 2, 2);
		NewObject(OBJ_FLOOR_Reducing, 3, 3, 1);
		NewObject(OBJ_FLOOR_Reducing, 4, 4, 0);
		NewObject(OBJ_FLOOR_Reducing, 5, 5, 0);
		NewObject(OBJ_FLOOR_Reducing, 7, 5, 2);
		NewObject(OBJ_SIDE_Spine, 1, 0, 0);
		NewObject(OBJ_SIDE_Spine, 2, 1, 0);
		NewObject(OBJ_SIDE_Spine, 3, 2, 0);
		NewObject(OBJ_SIDE_Spine, 4, 3, 0);
		NewObject(OBJ_SIDE_Spine, 5, 4, 0);
		NewObject(OBJ_FLOOR_Spine, 2, 0, 0);
		NewObject(OBJ_FLOOR_Spine, 3, 1, 0);
		NewObject(OBJ_FLOOR_Spine, 4, 2, 0);
		NewObject(OBJ_FLOOR_Spine, 5, 3, 0);
		NewObject(OBJ_FLOOR_Spine, 6, 4, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 5, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 0, 0);
		NewObject(OBJ_FLOOR_Exit, 2, 0, 0);
		NewObject(OBJ_Food, 1, 0, 0);
		NewObject(OBJ_Food, 2, 1, 0);
		NewObject(OBJ_Food, 3, 2, 0);
		NewObject(OBJ_Food, 4, 3, 0);
		NewObject(OBJ_Food, 5, 4, 0);
		NewObject(OBJ_Food, 6, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 5, 0);
		NewObject(OBJ_Life, 1, 4, 0);
		NewObject(OBJ_Life, 2, 5, 0);
		NewObject(OBJ_Bumpy, 0, 0);
	} break;

	case WORLD_1 | 10: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_Plain, 0, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 2, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 1, 0);
		NewObject(OBJ_FLOOR_Plain, 0, 1, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 2, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 2, 3, 0);
		NewObject(OBJ_FLOOR_Plain, 0, 3, 0);
		NewObject(OBJ_FLOOR_Plain, 0, 4, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 4, 0);
		NewObject(OBJ_FLOOR_Plain, 5, 4, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 5, 0);
		NewObject(OBJ_FLOOR_Down, 1, 0, 0);
		NewObject(OBJ_FLOOR_Down, 2, 1, 0);
		NewObject(OBJ_FLOOR_Down, 0, 2, 0);
		NewObject(OBJ_FLOOR_Down, 1, 3, 0);
		NewObject(OBJ_FLOOR_Down, 2, 4, 0);
		NewObject(OBJ_FLOOR_Down, 4, 3, 0);
		NewObject(OBJ_FLOOR_Down, 4, 2, 0);
		NewObject(OBJ_FLOOR_Down, 4, 1, 0);
		NewObject(OBJ_FLOOR_Up, 5, 2, 0);
		NewObject(OBJ_FLOOR_Up, 5, 1, 0);
		NewObject(OBJ_FLOOR_Up, 5, 3, 0);
		NewObject(OBJ_FLOOR_Up, 4, 4, 0);
		NewObject(OBJ_FLOOR_Catapult, 2, 5, 0);
		NewObject(OBJ_FLOOR_Catapult, 3, 5, 0);
		NewObject(OBJ_FLOOR_Ice, 6, 1, 0);
		NewObject(OBJ_FLOOR_Ice, 6, 2, 0);
		NewObject(OBJ_FLOOR_Ice, 6, 3, 0);
		NewObject(OBJ_FLOOR_Ice, 6, 4, 0);
		NewObject(OBJ_Food, 2, 0, 0);
		NewObject(OBJ_Food, 0, 1, 0);
		NewObject(OBJ_Food, 2, 2, 0);
		NewObject(OBJ_Food, 0, 3, 0);
		NewObject(OBJ_Food, 2, 4, 0);
		NewObject(OBJ_Food, 6, 4, 0);
		NewObject(OBJ_Food, 6, 2, 0);
		NewObject(OBJ_Food, 6, 0, 0);
		NewObject(OBJ_FLOOR_SpineUD, 5, 0, 0);
		NewObject(OBJ_FLOOR_Exit, 5, 5, 0);
		NewObject(OBJ_Bumpy, 0, 0);
	} break;

	case WORLD_1 | 11: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_Teleport, 0, 5, 0);
		NewObject(OBJ_FLOOR_Teleport, 2, 5, 0);
		NewObject(OBJ_FLOOR_Teleport, 4, 5, 0);
		NewObject(OBJ_FLOOR_Teleport, 6, 5, 0);
		NewObject(OBJ_FLOOR_Spine, 1, 5, 0);
		NewObject(OBJ_FLOOR_Spine, 3, 5, 0);
		NewObject(OBJ_FLOOR_Spine, 5, 5, 0);
		NewObject(OBJ_FLOOR_Spine, 7, 5, 0);
		NewObject(OBJ_FLOOR_SpineUD, 0, 0, 0);
		NewObject(OBJ_FLOOR_SpineUD, 1, 0, 0);
		NewObject(OBJ_FLOOR_SpineUD, 2, 0, 0);
		NewObject(OBJ_FLOOR_SpineUD, 3, 0, 0);
		NewObject(OBJ_FLOOR_SpineUD, 4, 0, 0);
		NewObject(OBJ_FLOOR_SpineUD, 5, 0, 0);
		NewObject(OBJ_FLOOR_SpineUD, 6, 0, 0);
		NewObject(OBJ_FLOOR_SpineUD, 7, 0, 0);
		NewObject(OBJ_Life, 7, 0, 0);
		NewObject(OBJ_Life, 6, 0, 0);
		NewObject(OBJ_Life, 5, 0, 0);
		NewObject(OBJ_Life, 4, 0, 0);
		NewObject(OBJ_Life, 3, 0, 0);
		NewObject(OBJ_Life, 2, 0, 0);
		NewObject(OBJ_Life, 1, 0, 0);
		NewObject(OBJ_Life, 0, 0, 0);
		NewObject(OBJ_Food, 0, 1, 0);
		NewObject(OBJ_Food, 2, 3, 0);
		NewObject(OBJ_Food, 4, 3, 0);
		NewObject(OBJ_Food, 6, 1, 0);
		NewObject(OBJ_FLOOR_Exit, 1, 1, 0);
		NewObject(OBJ_Bumpy, 0, 3);
	} break;

	case WORLD_1 | 12: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_Plain, 0, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 2, 1, 0);
		NewObject(OBJ_FLOOR_Plain, 5, 1, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 2, 0);
		NewObject(OBJ_FLOOR_Teleport, 4, 5, 0);
		NewObject(OBJ_FLOOR_Teleport, 7, 5, 0);
		NewObject(OBJ_SIDE_RightOnly, 0, 0, 0);
		NewObject(OBJ_SIDE_RightOnly, 1, 0, 0);
		NewObject(OBJ_SIDE_RightOnly, 2, 0, 0);
		NewObject(OBJ_SIDE_LeftOnly, 3, 0, 0);
		NewObject(OBJ_SIDE_LeftOnly, 4, 0, 0);
		NewObject(OBJ_SIDE_LeftOnly, 5, 0, 0);
		NewObject(OBJ_SIDE_LeftOnly, 6, 0, 0);
		NewObject(OBJ_SIDE_Nways, 6, 1, 0);
		NewObject(OBJ_SIDE_Nways, 6, 2, 0);
		NewObject(OBJ_SIDE_Nways, 5, 2, 0);
		NewObject(OBJ_SIDE_Nways, 5, 1, 0);
		NewObject(OBJ_SIDE_Nways, 4, 1, 0);
		NewObject(OBJ_SIDE_Nways, 3, 1, 2);
		NewObject(OBJ_SIDE_Nways, 3, 2, 0);
		NewObject(OBJ_SIDE_Nways, 3, 3, 0);
		NewObject(OBJ_SIDE_Nways, 3, 4, 0);
		NewObject(OBJ_SIDE_Nways, 3, 5, 0);
		NewObject(OBJ_SIDE_Nways, 0, 1, 0);
		NewObject(OBJ_SIDE_Nways, 0, 2, 0);
		NewObject(OBJ_SIDE_Nways, 0, 3, 0);
		NewObject(OBJ_SIDE_Nways, 1, 1, 0);
		NewObject(OBJ_SIDE_Nways, 1, 2, 0);
		NewObject(OBJ_SIDE_Nways, 2, 1, 0);
		NewObject(OBJ_Food, 1, 2, 0);
		NewObject(OBJ_Food, 2, 1, 0);
		NewObject(OBJ_Food, 5, 1, 0);
		NewObject(OBJ_Food, 6, 2, 0);
		NewObject(OBJ_Food, 4, 5, 0);
		NewObject(OBJ_Food, 3, 5, 0);
		NewObject(OBJ_FLOOR_Forced, 1, 5, 1);
		NewObject(OBJ_FLOOR_Forced, 2, 5, 1);
		NewObject(OBJ_FLOOR_Exit, 0, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 5, 0);
		NewObject(OBJ_FLOOR_Forced, 4, 0, 1);
		NewObject(OBJ_Bumpy, 0, 0);
	} break;

	case WORLD_1 | 13: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_Plain, 0, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 7, 0, 0);
		NewObject(OBJ_FLOOR_Plain, 7, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 0, 2, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 2, 0);
		NewObject(OBJ_FLOOR_Reducing, 1, 0, 0);
		NewObject(OBJ_FLOOR_Reducing, 2, 0, 0);
		NewObject(OBJ_FLOOR_Reducing, 3, 0, 0);
		NewObject(OBJ_FLOOR_Reducing, 4, 0, 0);
		NewObject(OBJ_FLOOR_Reducing, 5, 0, 0);
		NewObject(OBJ_FLOOR_Reducing, 6, 0, 0);
		NewObject(OBJ_FLOOR_Reducing, 3, 1, 0);
		NewObject(OBJ_FLOOR_Reducing, 4, 1, 0);
		NewObject(OBJ_FLOOR_Reducing, 5, 4, 1);
		NewObject(OBJ_FLOOR_Reducing, 2, 4, 1);
		NewObject(OBJ_FLOOR_Forced, 1, 4, 0);
		NewObject(OBJ_FLOOR_Forced, 6, 4, 1);
		NewObject(OBJ_FLOOR_Catapult, 4, 2, 1);
		NewObject(OBJ_FLOOR_Catapult, 3, 2, 0);
		NewObject(OBJ_SIDE_RightOnly, 4, 2, 0);
		NewObject(OBJ_SIDE_LeftOnly, 2, 2, 0);
		NewObject(OBJ_FLOOR_Down, 5, 2, 0);
		NewObject(OBJ_FLOOR_Up, 2, 2, 0);
		NewObject(OBJ_FLOOR_SpineUD, 1, 1, 0);
		NewObject(OBJ_FLOOR_SpineUD, 2, 1, 0);
		NewObject(OBJ_FLOOR_SpineUD, 5, 1, 0);
		NewObject(OBJ_FLOOR_SpineUD, 6, 1, 0);
		NewObject(OBJ_FLOOR_Ice, 3, 4, 0);
		NewObject(OBJ_FLOOR_Ice, 4, 4, 0);
		NewObject(OBJ_Food, 3, 4, 0);
		NewObject(OBJ_Food, 4, 4, 0);
		NewObject(OBJ_Food, 2, 2, 0);
		NewObject(OBJ_Food, 5, 2, 0);
		NewObject(OBJ_FLOOR_Exit, 0, 2, 0);
		NewObject(OBJ_Bumpy, 0, 0);
	} break;

	case WORLD_1 | 14: {
		SetGrid(8, 6);
		NewObject(OBJ_FLOOR_Plain, 0, 4, 0);
		NewObject(OBJ_FLOOR_Plain, 0, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 1, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 2, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 3, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 4, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 5, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 6, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 7, 5, 0);
		NewObject(OBJ_FLOOR_Plain, 7, 4, 0);
		NewObject(OBJ_FLOOR_Ice, 3, 4, 0);
		NewObject(OBJ_FLOOR_Ice, 4, 4, 0);

		NewObject(OBJ_Food, 1, 5, 0);
		NewObject(OBJ_Food, 3, 5, 0);
		NewObject(OBJ_Food, 4, 5, 0);
		NewObject(OBJ_Food, 6, 5, 0);

		NewObject(OBJ_Food, 2, 1, 0);
		NewObject(OBJ_Food, 3, 2, 0);
		NewObject(OBJ_Food, 4, 2, 0);
		NewObject(OBJ_Food, 5, 1, 0);

		NewObject(OBJ_Enemy, 0, 5, 0);
		NewObject(OBJ_FLOOR_Exit, 0, 1, 0);
		NewObject(OBJ_Bumpy, 0, 1);
	} break;

	//-----------------------------------------
	// WORLD 2
	//-----------------------------------------

	case WORLD_2 | 0:
	case WORLD_2 | 1:
	case WORLD_2 | 2:
	case WORLD_2 | 3:
	case WORLD_2 | 4:
	case WORLD_2 | 5:
	case WORLD_2 | 6:
	case WORLD_2 | 7:
	case WORLD_2 | 8:
	case WORLD_2 | 9:
	case WORLD_2 | 10:
	case WORLD_2 | 11:
	case WORLD_2 | 12:
	case WORLD_2 | 13:
	case WORLD_2 | 14: {
		SetGrid(8, 6);
		NewObject(OBJ_Bumpy, 4, 1);
		NewObject(OBJ_FLOOR_Plain, 4, 1);
		NewObject(OBJ_Food, 3, 1);
		NewObject(OBJ_Food, 3, 2);
		NewObject(OBJ_Food, 3, 3);
		NewObject(OBJ_FLOOR_Exit, 3, 5);
	} break;

	//-----------------------------------------
	// WORLD 3
	//-----------------------------------------

	case WORLD_3 | 0:
	case WORLD_3 | 1:
	case WORLD_3 | 2:
	case WORLD_3 | 3:
	case WORLD_3 | 4:
	case WORLD_3 | 5:
	case WORLD_3 | 6:
	case WORLD_3 | 7:
	case WORLD_3 | 8:
	case WORLD_3 | 9:
	case WORLD_3 | 10:
	case WORLD_3 | 11:
	case WORLD_3 | 12:
	case WORLD_3 | 13:
	case WORLD_3 | 14: {
		SetGrid(8, 6);
		NewObject(OBJ_Bumpy, 4, 1);
		NewObject(OBJ_FLOOR_Plain, 4, 1);
		NewObject(OBJ_Food, 3, 1);
		NewObject(OBJ_Food, 3, 2);
		NewObject(OBJ_Food, 3, 3);
		NewObject(OBJ_FLOOR_Exit, 3, 5);
	} break;

	//-----------------------------------------
	// WORLD EDITOR
	//-----------------------------------------

	case WORLD_EDITOR | 0: {
		SetGrid(8, 6);
		ShowGrid = true;
	} break;

	default: {
		// Empty level
		SetGrid(8, 6);
	} break;
	}
}

cLevel::cLevel(cLevel* copy)
{
	LevelID = copy->LevelID;
	// Copy Grid (and set Cols, Rows, CellX, Celly)
	SetGrid(copy->Cols, copy->Rows);
	// Copy all the objects
	Exit = NULL;
	Enemy = NULL;
	Bumpy = NULL;
	nObj = 0;
	nFood = 0;
	nEaten = 0;
	nObj = 0;
	Objects = NULL;
	for (int i = 0; i < copy->nObj; i++) {
		cObject* obj = copy->Objects[i];
		NewObject(obj->type, obj->myCell->col, obj->myCell->row, obj->Status);
	}
	if (copy->Bumpy) {
		NewObject(OBJ_Bumpy, copy->Bumpy->myCell->col, copy->Bumpy->myCell->row);
	}
	Background = NULL;
	ShowGrid = false;
	QuitLevel = false;
	Started = false;
	Completed = false;
}

cLevel::~cLevel()
{
	// Delete all the objects in the level
	delete Background;
	for (int i = 0; i < nObj; i++)
		delete Objects[i];
	delete[] Objects;
	if (Bumpy) delete Bumpy;
	delete[] Grid;
}

cCell* cLevel::SetGrid(int cols, int rows)
{
	if (Grid) delete[] Grid;
	Rows = rows;
	Cols = cols;
	Grid = new cCell[Rows * Cols];
	for (int r = 0; r < Rows; r++) {
		for (int c = 0; c < Cols; c++) {
			Grid[r + c * Rows].row = r; // why there's a warning?!
			Grid[r + c * Rows].col = c;
		}
	}
	CellX = SCREEN_WIDTH / Cols;
	CellY = SCREEN_HEIGHT / Rows;
	return Grid;
}

cObject* cLevel::NewObject(int type, int col, int row, int status)
{
	int xoff = CellX * col;
	int yoff = CellY * row;
	cObject* obj = NULL;

	switch (type) {
	case OBJ_Bumpy: {
		if (Bumpy) delete Bumpy;
		Bumpy = new cBumpy();
		Bumpy->type = type;
		// Center Bumpy into the cell
		Bumpy->X = xoff + (CellX - Bumpy->W) / 2;
		Bumpy->Y = yoff + (CellY - Bumpy->H) / 2;
		Bumpy->Collider.x += (int)Bumpy->X;
		Bumpy->Collider.y += (int)Bumpy->Y;
		// Keep Bumpy outside objects list for now
		// Expand the object list
		//cObject** newlist = new cObject * [nObj + 1];
		//for (int i = 0; i < nObj; i++) newlist[i] = Objects[i];
		//delete[] Objects;
		//Objects[nObj] = Bumpy;
		//nObj++;
		//Objects = newlist;
		//grid(col, row)->AddObject(Bumpy);
		Bumpy->myCell = grid(col, row);
		Bumpy->myLevel = this;
		obj = Bumpy;
	} break;

	case OBJ_FLOOR_Exit:
		// Member Exit is just a pointer. Useful when checking collisions
		if (Exit) DeleteObject(OBJ_FLOOR_Exit, Exit->myCell->col, Exit->myCell->row);
		Exit = new cExit();
		obj = Exit;
		obj->Status = -1; // invisible by default
		goto FloorCommon;

	case OBJ_FLOOR_Plain:
		obj = new cPlainFloor();
		goto FloorCommon;

	case OBJ_FLOOR_Up:
		obj = new cFloorUp();
		goto FloorCommon;

	case OBJ_FLOOR_Down:
		obj = new cFloorDown();
		goto FloorCommon;

	case OBJ_FLOOR_Ice:
		obj = new cIceFloor();
		goto FloorCommon;

	case OBJ_FLOOR_Forced:
		obj = new cForced(status);
		goto FloorCommon;

	case OBJ_FLOOR_Decision:
		obj = new cDecision();
		goto FloorCommon;

	case OBJ_FLOOR_Fake:
		obj = new cFakeFloor();
		goto FloorCommon;

	case OBJ_FLOOR_Invisible:
		obj = new cInvisibleFloor();
		goto FloorCommon;

	case OBJ_FLOOR_Reducing:
		obj = new cReducingFloor(status);
		goto FloorCommon;

	case OBJ_FLOOR_Wall:
		obj = new cFloorWall(status);
		goto FloorCommon;

	case OBJ_FLOOR_Spine:
		obj = new cSpine();
		goto FloorCommon;

	case OBJ_FLOOR_SpineUD:
		obj = new cSpineUD(status);
		goto FloorCommon;

	case OBJ_FLOOR_Spring:
		obj = new cSpring();
		goto FloorCommon;

	case OBJ_FLOOR_Cloud:
		obj = new cCloud();
		goto FloorCommon;

	case OBJ_FLOOR_OneBounce:
		obj = new cOneBounce();
		goto FloorCommon;

	case OBJ_FLOOR_Glue:
		obj = new cGlue();
		goto FloorCommon;

	case OBJ_FLOOR_Magnetic:
		obj = new cMagnetic();
		goto FloorCommon;

	case OBJ_FLOOR_Catapult:
		obj = new cCatapult(status);
		goto FloorCommon;

	case OBJ_FLOOR_Teleport:
		obj = new cTeleport();
		goto FloorCommon;

FloorCommon:
		obj->type = type;
		// Position obj into the cell
		obj->X = xoff + (CellX - obj->W) / 2;
		obj->Y = yoff + CellY - obj->H;
		obj->Collider.x += (int)obj->X;
		obj->Collider.y += (int)obj->Y;
		// Add to the object list
		AddObject(obj);
		grid(col, row)->AddObject(obj);
		break;

	case OBJ_SIDE_Plain:
		obj = new cPlainSide();
		goto SideCommon;

	case OBJ_SIDE_LeftOnly:
		obj = new cLeftOnly();
		goto SideCommon;

	case OBJ_SIDE_RightOnly:
		obj = new cRightOnly();
		goto SideCommon;

	case OBJ_SIDE_Nways:
		obj = new cNways(status);
		goto SideCommon;

	case OBJ_SIDE_Wall:
		obj = new cSideWall(status);
		goto SideCommon;

	case OBJ_SIDE_Spine:
		obj = new cSpineSide();
		goto SideCommon;

	case OBJ_SIDE_Shooter:
		obj = new cSpringH();
		goto SideCommon;

	case OBJ_SIDE_Fake:
		obj = new cFakeSide();
		goto SideCommon;

	case OBJ_SIDE_Invisible:
		obj = new cInvisibleSide();
		goto SideCommon;

	case OBJ_SIDE_Glue:
		obj = new cGlueSide();
		goto SideCommon;

	case OBJ_SIDE_Ice:
		obj = new cIceSide();
		goto SideCommon;

	case OBJ_SIDE_Face:
		obj = new cFace(status);
		goto SideCommon;

SideCommon:
		obj->type = type;
		// Position obj into the cell
		obj->X = xoff + CellX - obj->W / 2;
		obj->Y = (float)yoff;
		obj->Collider.x += (int)obj->X;
		obj->Collider.y += (int)obj->Y;
		// Add to the object list
		AddObject(obj);
		grid(col, row)->AddObject(obj);
		break;

	case OBJ_Life:
		obj = new cLife();
		goto CenteredCommon;

	case OBJ_Food:
		nFood++;
		obj = new cFood();
		goto CenteredCommon;

	case OBJ_Enemy:
		if (Enemy) DeleteObject(OBJ_Enemy, Enemy->myCell->col, Enemy->myCell->row);
		Enemy = new cEnemy(status);
		obj = Enemy;
		goto CenteredCommon;

CenteredCommon:
		obj->type = type;
		// Position obj into the cell
		obj->X = xoff + (CellX - obj->W) / 2;
		obj->Y = yoff + (CellY - obj->H) / 2;
		obj->Collider.x += (int)obj->X;
		obj->Collider.y += (int)obj->Y;

		// Add to the object list
		AddObject(obj);
		grid(col, row)->AddObject(obj);
		break;

	default:;
	}

	return obj;
}

bool cLevel::DeleteObject(int type, int col, int row)
{
	bool success = false;
	cCell* cell = grid(col, row);
	if (!cell) return success;
	// Is the object there?
	if (type == OBJ_Bumpy) {
		if (Bumpy && (Bumpy->myCell->col == col) && (Bumpy->myCell->row == row)) {
			delete Bumpy;
			Bumpy = NULL;
		}
	}
	for (int i = 0; i < cell->nObj; i++) {
		cObject* obj = cell->Objects[i];
		if (obj->type == type) {
			RemoveObject(obj);
			cell->RemoveObject(obj);
			delete obj;
			if (type == OBJ_FLOOR_Exit) Exit = NULL;
			if (type == OBJ_Enemy) Enemy = NULL;
			success = true;
			break;
		}
	}
	return success;
}

void cLevel::ClearAllObjects()
{
	int n = nObj;
	for (int i = 0; i < n; i++) {
		cObject* obj = Objects[0];
		cCell* cell = obj->myCell;
		RemoveObject(obj);
		cell->RemoveObject(obj);
		delete obj;
	}
	if (Bumpy) delete Bumpy;
	Bumpy = NULL;
	Exit = NULL;
}

int cLevel::Run()
{
	if (Exit) {
		Exit->Status = nFood ? -1 : 0;
	}
	while (!QuitLevel) {
		handleEvents();
		update();
		render();
		//SDL_Delay(16); // ~60 FPS
	}
	return Completed; // specify if the level is completed, failed...
}

void cLevel::handleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
			// Back to menu
			QuitLevel = true;
		}
		if (e.type == SDL_EVENT_KEY_DOWN || e.type == SDL_EVENT_KEY_UP) {
			// Start
			if (e.key.key == SDLK_UP ||
				e.key.key == SDLK_DOWN ||
				e.key.key == SDLK_LEFT ||
				e.key.key == SDLK_RIGHT ||
				e.key.key == SDLK_RETURN ||
				e.key.key == SDLK_SPACE) {
				if (!Started)
				{
					if (e.type == SDL_EVENT_KEY_DOWN)
						Started = true;
				}
				if (Bumpy) Bumpy->handleEvent(e);
			}
		}
		if (e.type == SDL_EVENT_QUIT)
			QuitLevel = true;
	}
}

void cLevel::AddObject(cObject* obj)
// Add to the object list
{
	if (!obj) return;
	if (obj->myLevel == this) return; // already in
	//if (obj->myLevel) obj->myLevel->RemoveObject(obj);
	// Reallocate array
	cObject** newlist = new cObject * [nObj + 1];
	// Copy old list
	for (int i = 0; i < nObj; i++)
		newlist[i] = Objects[i];
	newlist[nObj] = obj;
	delete[] Objects;
	Objects = newlist;
	nObj++;
	obj->myLevel = this;
}

void cLevel::RemoveObject(cObject* obj)
{
	if (!obj) return;
	if (nObj == 0) return;
	int i = 0;
	for (i = 0; i < nObj; i++)
		if (Objects[i] == obj) break;
	if (i >= nObj) return; // not in the list
	// Reallocate array
	cObject** newlist = NULL;
	if (nObj > 1) {
		newlist = new cObject * [nObj - 1];
		// Copy old list
		for (int j = 0; j < i; j++)
			newlist[j] = Objects[j];
		for (int j = i; j + 1 < nObj; j++)
			newlist[j] = Objects[j + 1];
	}
	delete[] Objects;
	Objects = newlist;
	nObj--;
	obj->myLevel = NULL;
}

void cLevel::update()
{
	if (!Started) return;
	// TODO: aggiorna logica di gioco
	for (int i = 0; i < nObj; i++)
		Objects[i]->update();
	if (Bumpy) Bumpy->update();
}

void cLevel::render()
{
	// Background
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	SDL_RenderClear(gRenderer);

	// Add a background picture...

	// Render grid
	if (ShowGrid) {
		int drow = (Rows > 0) ? SCREEN_HEIGHT / Rows : 0;
		int dcol = (Cols > 0) ? SCREEN_WIDTH / Cols : 0;
		char label[5] = { 0 };
		for (int r = 1; r < Rows; r++) {
			SDL_SetRenderDrawColor(gRenderer, 0xC0, 0xC0, 0xC0, 0xC0);
			float y = (float)r * drow;
			SDL_RenderLine(gRenderer, 0, y, (float)SCREEN_WIDTH, y);
		}
		for (int c = 1; c < Cols; c++) {
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			float x = (float)c * dcol;
			SDL_RenderLine(gRenderer, x, 0, x, (float)SCREEN_HEIGHT);
		}
	}
	
	// Objects
	if (Bumpy) Bumpy->render(gRenderer);
	for (int i = 0; i < nObj; i++)
		Objects[i]->render(gRenderer);

	SDL_RenderPresent(gRenderer);
}

cCell* cLevel::grid(int col, int row)
{
	if (col < 0 || col >= Cols) return NULL;
	if (row < 0 || row >= Rows) return NULL;
	return Grid + row + col * Rows;
}

cObject* cLevel::FindNextObject(cCell* cell0, unsigned int objtype)
{
	cObject* next = NULL;

	for (int c = cell0->col + 1; c < Cols; c++) {
		cCell* cell = grid(c, cell0->row);
		for (int i = 0; i < cell->nObj; i++) {
			if (cell->Objects[i]->type == objtype) {
				next = cell->Objects[i]; // found!
				break;
			}
		}
		if (next) break;
	}
	if (!next) for (int r = cell0->row + 1; r < Rows; r++) {
		for (int c = 0; c < Cols; c++) {
			cCell* cell = grid(c, r);
			for (int i = 0; i < cell->nObj; i++) {
				if (cell->Objects[i]->type == objtype) {
					next = cell->Objects[i]; // found!
					break;
				}
			}
			if (next) break;
		}
		if (next) break;
	}
	if (!next) for (int r = 0; r <= cell0->row; r++) {
		for (int c = 0; c < Cols; c++) {
			cCell* cell = grid(c, r);
			for (int i = 0; i < cell->nObj; i++) {
				if (cell->Objects[i]->type == objtype) {
					next = cell->Objects[i]; // found!
					break;
				}
			}
			if (next) break;
		}
		if (next) break;
	}
	return next;
}

void cLevel::ExportCode()
{
	size_t size = 8192;
	size_t idx = 0;
	char* code = new char[size];
	char* buff = new char[1000];
	code[0] = '\0';
	buff[0] = '\0';

	int bidx = SDL_snprintf(buff, 1000, "SetGrid(%i, %i);\n", Cols, Rows);
	idx += SDL_strlcat(code, buff, size);

	for (int i = 0; i < nObj; i++) {
		cObject* obj = Objects[i];
		const char* otype = NULL;
		switch (obj->type) {
			// centers
		case OBJ_Bumpy: otype = "OBJ_Bumpy"; break;
		case OBJ_Food: otype = "OBJ_Food"; break;
		case OBJ_Enemy: otype = "OBJ_Enemy"; break;
		case OBJ_Life: otype = "OBJ_Life"; break;
			// floors
		case OBJ_FLOOR_Plain: otype = "OBJ_FLOOR_Plain"; break;
		case OBJ_FLOOR_Cloud: otype = "OBJ_FLOOR_Cloud"; break;
		case OBJ_FLOOR_Exit: otype = "OBJ_FLOOR_Exit"; break;
		case OBJ_FLOOR_Ice: otype = "OBJ_FLOOR_Ice"; break;
		case OBJ_FLOOR_Down: otype = "OBJ_FLOOR_Down"; break;
		case OBJ_FLOOR_Up: otype = "OBJ_FLOOR_Up"; break;
		case OBJ_FLOOR_Reducing: otype = "OBJ_FLOOR_Reducing"; break;
		case OBJ_FLOOR_Invisible: otype = "OBJ_FLOOR_Invisible"; break;
		case OBJ_FLOOR_Fake: otype = "OBJ_FLOOR_Fake"; break;
		case OBJ_FLOOR_Spring: otype = "OBJ_FLOOR_Spring"; break;
		case OBJ_FLOOR_Spine: otype = "OBJ_FLOOR_Spine"; break;
		case OBJ_FLOOR_SpineUD: otype = "OBJ_FLOOR_SpineUD"; break;
		case OBJ_FLOOR_Glue: otype = "OBJ_FLOOR_Glue"; break;
		case OBJ_FLOOR_OneBounce: otype = "OBJ_FLOOR_OneBounce"; break;
		case OBJ_FLOOR_Wall: otype = "OBJ_FLOOR_Wall"; break;
		case OBJ_FLOOR_Forced: otype = "OBJ_FLOOR_Forced"; break;
		case OBJ_FLOOR_Decision: otype = "OBJ_FLOOR_Decision"; break;
		case OBJ_FLOOR_Catapult: otype = "OBJ_FLOOR_Catapult"; break;
		case OBJ_FLOOR_Teleport: otype = "OBJ_FLOOR_Teleport"; break;
		case OBJ_FLOOR_Magnetic: otype = "OBJ_FLOOR_Magnetic"; break;
			// sides
		case OBJ_SIDE_Plain: otype = "OBJ_SIDE_Plain"; break;
		case OBJ_SIDE_LeftOnly: otype = "OBJ_SIDE_LeftOnly"; break;
		case OBJ_SIDE_RightOnly: otype = "OBJ_SIDE_RightOnly"; break;
		case OBJ_SIDE_Nways: otype = "OBJ_SIDE_Nways"; break;
		case OBJ_SIDE_Wall: otype = "OBJ_SIDE_Wall"; break;
		case OBJ_SIDE_Face: otype = "OBJ_SIDE_Face"; break;
		case OBJ_SIDE_Ice: otype = "OBJ_SIDE_Ice"; break;
		case OBJ_SIDE_Spine: otype = "OBJ_SIDE_Spine"; break;
		case OBJ_SIDE_Glue: otype = "OBJ_SIDE_Glue"; break;
		case OBJ_SIDE_Shooter: otype = "OBJ_SIDE_Shooter"; break;
		case OBJ_SIDE_Invisible: otype = "OBJ_SIDE_Invisible"; break;
		case OBJ_SIDE_Fake: otype = "OBJ_SIDE_Fake"; break;
		default:
		case OBJ_None: otype = "OBJ_None"; break;;
		}
		int status = obj->Status;
		// Set the enemy initial velocity in the status field
		if (obj->type == OBJ_Enemy) {
			int dir = static_cast<cEnemy*>(obj)->GetDirection();
			status += dir * 10;
		}
		bidx = SDL_snprintf(buff, 1000, "NewObject(%s, %i, %i, %i);\n",
			otype, obj->myCell->col, obj->myCell->row, status);
		if (size - idx <= bidx) {
			// Expand code buffer...
		}
		idx += SDL_strlcat(code, buff, size);
	}
	if (Bumpy) {
		bidx = SDL_snprintf(buff, 1000, "NewObject(OBJ_Bumpy, %i, %i);\n",
			Bumpy->myCell->col, Bumpy->myCell->row);
		if (size - idx <= bidx) {
			// Expand code buffer...
		}
		idx += SDL_strlcat(code, buff, size);
	}
	SDL_SetClipboardText(code);
	delete[] code;
	delete[] buff;
}

//------------------------------------------
// class cObject
//------------------------------------------

cObject::cObject()
{
	//Initialize the offsets
	X = 0;
	Y = 0;
	W = 0;
	H = 0;

	Texture = NULL;

	//Initialize the velocity
	VelX = 0;
	VelY = 0;

	//Set collision box dimension
	Collider.x = 0;
	Collider.y = 0;
	Collider.w = 0;
	Collider.h = 0;

	myWorld = NULL;
	myLevel = NULL;
	myCell = NULL;

	type = 0;
	Status = 0;
}

cObject::~cObject() {
	if (myCell) myCell->RemoveObject(this);
}

void cObject::render(SDL_Renderer* renderer) {
	if (Texture) Texture->render((int)X, (int)Y);
}

//------------------------------------------
// class cBumpy
//------------------------------------------

cBumpy::cBumpy() : cObject()
{
	Status = BOUNCING;
	crossingfloor = false;
	crossingside = false;

	// These should depend on grid dimensions
	W = 20;
	H = 20;
	//Collider
	Collider.w = (int)W;
	Collider.h = (int)H;

	pressedUp = false;
	pressedDown = false;
	pressedLeft = false;
	pressedRight = false;
	pressedSpace = false;

	myCloud = NULL;

	Texture = &txBumpy;
}

cBumpy::~cBumpy() {}

void cBumpy::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_EVENT_KEY_DOWN)
	{
		switch (e.key.key)
		{
		case SDLK_UP:
			pressedUp = true; break;
		case SDLK_DOWN: pressedDown = true; break;
		case SDLK_LEFT: {
			pressedLeft = true;
			pressedRight = false;
		} break;
		case SDLK_RIGHT: {
			pressedRight = true;
			pressedLeft = false;
		} break;
		case SDLK_SPACE: pressedSpace = true; break;
		default: break;
		}
	}
	else if (e.type == SDL_EVENT_KEY_UP)
	{
		switch (e.key.key)
		{
		case SDLK_UP: pressedUp = false; break;
		case SDLK_DOWN: pressedDown = false; break;
		case SDLK_LEFT: pressedLeft = false; break;
		case SDLK_RIGHT: pressedRight = false; break;
		case SDLK_SPACE: pressedSpace = false; break;
		default: break;
		}
	}
}

//------------------------------
// Update the logic of the game
//------------------------------
// Useful functions:
//  SDL_HasEvent(Uint32 type);
//  SDL_FlushEvent(Uint32 type);

void cBumpy::MoveOnCloud()
// Auxiliary for update()
// Call when Bumpy is on the cloud and the cloud is still
{
	cCell* c = NULL;
	int col = myCloud->myCell->col;
	int row = myCloud->myCell->row;
	if (pressedUp)
		c = myLevel->grid(col, row - 1);
	else if (pressedDown)
		c = myLevel->grid(col, row + 1);
	if (c) {
		cObject* floor = NULL;
		// is there a floor?
		for (int i = 0; i < c->nObj; i++) {
			if (mIsFloor(c->Objects[i]->type) && c->Objects[i]->Status >= 0)
			{
				floor = c->Objects[i];
				break;
			}
		}
		if (!floor) {
			bool dontmove = false;
			if (pressedDown) {
				// is there a enemy?
				for (int i = 0; i < c->nObj; i++) {
					if (c->Objects[i]->type == OBJ_Enemy) {
						dontmove = true;
						break;
					}
				}
			}
			if (!dontmove) {
				// Start moving
				VelY = pressedUp ? -MaxVelY : MaxVelY;
				VelX = 0;
				Y += VelY;
				myCloud->VelY = VelY;
				myCloud->VelX = 0;
				myCloud->Y = Y + H;
				myCloud->Collider.x = (int)(myCloud->X);
				myCloud->Collider.y = (int)(myCloud->Y);
			}
		}

		return;
	}

	if (pressedLeft)
		c = myLevel->grid(col - 1, row);
	else if (pressedRight)
		c = myLevel->grid(col + 1, row);
	if (c) {
		cObject* floor = NULL;
		cObject* side = NULL;
		// is there a floor?
		for (int i = 0; i < c->nObj; i++) {
			if (mIsFloor(c->Objects[i]->type) &&
				c->Objects[i]->Status >= 0)
			{
				floor = c->Objects[i];
				break;
			}
		}
		// is there a side?
		if (pressedRight) c = myLevel->grid(col, row);
		for (int i = 0; i < c->nObj; i++) {
			if (mIsSide(c->Objects[i]->type) &&
				c->Objects[i]->Status >= 0)
			{
				side = c->Objects[i];
				break;
			}
		}
		if (!floor && !side && !pressedSpace) {
			// Start moving with the cloud
			VelX = pressedLeft ? -MaxVelX : MaxVelX;
			VelY = 0;
			X += VelX;
			myCloud->VelX = VelX;
			myCloud->VelY = 0;
			myCloud->X += VelX;
			myCloud->Collider.x = (int)(myCloud->X);
			myCloud->Collider.y = (int)(myCloud->Y);
		}
		else {
			// Get off the cloud
			Status = BOUNCING;
			if (pressedRight) VelX = MaxVelX;
			else if (pressedLeft) VelX = -MaxVelX;
			VelY = -MaxVelY + AccelY;
			// Update X,Y
			Y += (-MaxVelY + VelY) / 2;
			X += VelX;
			Collider.y = (int)Y;
			Collider.x = (int)X;
			// Detach the cloud
			myCloud->VelX = 0;
			myCloud->VelY = 0;
			myCloud->Collider.x = (int)(myCloud->X);
			myCloud->Collider.y = (int)(myCloud->Y);
			myCloud = NULL;
		}

		return;
	}
}

void cBumpy::update()
{
	if (Status == CLOUD) {
		if (((((int)(Y + H + FLOOR_HEIGHT) % myLevel->CellY) == 0) && (VelY != 0)) ||
			((((int)(X - (myLevel->CellX - (int)W) / 2) % myLevel->CellX) == 0) && (VelX != 0)) ||
			(VelY == 0 && VelX == 0))
		{
			// Stop moving
			VelY = 0;
			VelX = 0;
			myCloud->Y = Y + H; // ?
			myCloud->VelY = 0;
			myCloud->VelX = 0;
			
			MoveOnCloud();
		}
		else {
			// Keep moving
			Y += VelY;
			X += VelX;
			myCloud->Y += VelY;
			myCloud->X += VelX;
			myCloud->Collider.x = (int)(myCloud->X);
			myCloud->Collider.y = (int)(myCloud->Y);
		}
	}

	if (Status == MAGNETIC) {
		if (pressedDown && (pressedLeft || pressedRight)) {
			VelY = 0;
			Status = FALLING;
		}
	}

	if (Status == GLUED) {
		long lx = SDL_lroundf(X);
		long ly = SDL_lroundf(Y);
		if (ly % myLevel->CellY > 10 && (ly % myLevel->CellY) < (myLevel->CellY - 40)) {
			// Glued on side
			if (lx % myLevel->CellX == 5) {
				// Glued right
				if (pressedDown || pressedSpace) {
					VelY = 2.f - AccelY;
					VelX = MaxVelX;
					Status = BOUNCING;
				}
			}
			else {
				// Glued left
				if (pressedDown || pressedSpace) {
					VelY = 2.f - AccelY;
					VelX = -MaxVelX;
					Status = BOUNCING;
				}
			}
		}
		else {
			if (ly % myLevel->CellY == 0) {
				// Glued up
				if (pressedDown || pressedSpace) {
					VelY = 0;
					Status = FALLING;
				}
			}
			else {
				// Glued down
				if (pressedLeft || pressedRight) {
					VelY = -MaxVelY;
					if (pressedLeft) VelX = -MaxVelX;
					else VelX = MaxVelX;
					Status = BOUNCING;
				}
			}
		}
	}

	float vy = VelY;
	if (Status != CLOUD)
	{		
		// Gravità
		if (Status != JUMPING &&
			Status != SHOT &&
			Status != GLUED &&
			Status != TELEPORTING &&
			Status != MAGNETIC)
		{
			// Is there a magnetic ceiling?
			cCell* cell = myLevel->grid(myCell->col, myCell->row - 1);
			if (cell && VelY < 0 && VelX == 0.) {
				// cycle objects in the i-th cell
				for (int o = 0; o < cell->nObj; o++) {
					cObject* obj = cell->Objects[o];
					if (obj && (obj->type == OBJ_FLOOR_Magnetic)) {
						if (!(pressedDown && (pressedLeft || pressedRight)))
						{
							Status = JUMPING;
							break;
						}
					}
				}
			}
			if (Status != JUMPING)
				VelY += AccelY;
		}
		// Limit speed
		if (VelY > MaxVelY)
		{
			VelY = MaxVelY;
		}
		vy = (vy + VelY) / 2;
		Y += vy;
		X += VelX;
	}

	if (Status == SHOT) {
		if (pressedDown || pressedSpace) {
			if (SDL_abs(((int)(X + W / 2) % myLevel->CellX) - (myLevel->CellX >> 1)) <= (ShotVelX / 2)) {
				// Stop from shooting
				Status = FALLING;
				X = myLevel->CellX * (myCell->col + 0.5f) - (W / 2);
				VelX = 0;
			}
		}
	}

	Collider.y = (int)Y;
	Collider.x = (int)X;

	// Check collision with (all) the objects!
	// Search for objects in the cells close to Bumpy:
	int r = myCell->row;
	int c = myCell->col;
	cCell* cells[9] = { NULL };
	cells[0] = myCell;
	cells[1] = myLevel->grid(c - 1, r);	cells[5] = myLevel->grid(c - 1, r - 1);
	cells[2] = myLevel->grid(c + 1, r);	cells[6] = myLevel->grid(c - 1, r + 1);
	cells[3] = myLevel->grid(c, r - 1);	cells[7] = myLevel->grid(c + 1, r - 1);
	cells[4] = myLevel->grid(c, r + 1);	cells[8] = myLevel->grid(c + 1, r + 1);

	int i = 0, o = 0;
	cObject* obj = NULL;
	bool stopcheck = false;
	bool hitfloor = false;

	// Hit the ceiling?
	if (Y <= 0) {
		Y = 0;
		goto ceiling;
	}

	// skip if no objects
	if (myLevel->Objects) {
		// cycle the cells
		for (i = 0; i < 9; i++) {
			if (cells[i]) {
				// cycle objects in the i-th cell
				for (o = 0; o < cells[i]->nObj; o++) {
					obj = cells[i]->Objects[o];
					if (obj && (obj->Status >= 0) && obj != this) { // just precaution
						// Check collision
						if (CheckCollision(Collider, obj->Collider)) {

							// Play sound related to the object
							PlaySound(obj->type);

							switch (obj->type) {

							case OBJ_Food: {
								// set invisible (instead of deleting)
								obj->Status = -1;
								myLevel->nEaten++;
								if (myLevel->nEaten >= myLevel->nFood) {
									// Show exit
									myLevel->Exit->Status = 0;
									// se c'è un oggetto floor nello stesso posto di exit, mettiamolo invisibile
									cCell* cell = myLevel->Exit->myCell;
									for (int j = 0; j < cell->nObj; j++) {
										cObject* jjj = cell->Objects[j];
										if (mIsFloor(jjj->type) && jjj != myLevel->Exit)
											jjj->Status = -1;
									}
								}
							} break;

							case OBJ_Life:
								// Add one life...
								obj->Status = -1;
								break;

							case OBJ_FLOOR_Exit: {
								Status = WON;
								myLevel->Completed = true;
								myLevel->QuitLevel = true;
								return;
							} break;

							case OBJ_FLOOR_Fake:
								obj->Status = -1;
								break;

							case OBJ_FLOOR_Invisible:
								if (obj->Status == 0) obj->Status = 1;
								goto plainfloor;

							case OBJ_FLOOR_Reducing:
								if (obj->Status == -1) break;
								if (VelY > 0) {
									obj->Status--;
								}
								goto plainfloor;

							case OBJ_FLOOR_Wall:
								if (obj->Status == -1) break;
								if (VelY < 0) obj->Status--;
								goto plainfloor;

							case OBJ_FLOOR_Up:
								if (VelY < 0) break; // ignore it
								else goto plainfloor;

							case OBJ_FLOOR_Down:
								if (VelY < 0) goto ceiling;
								else {
									if (pressedDown) {
										crossingfloor = true;
										break; // go down
									}
									else {
										if (crossingfloor) break; // ignore it
										else goto plainfloor;
									}
								}

							case OBJ_FLOOR_Decision: {
								if (obj->Status == 0) goto plainfloor;
								if (VelY > 0) {
									hitfloor = true;
									// Restore starting values
									Y = obj->Y - H;
									X = obj->X + (obj->W - W) / 2;
									VelX = 0;
									VelY = -MaxVelY;
									Status = BOUNCING;
									// Apply gravity
									VelY += AccelY;
									// Start moving left/right
									if (obj->Status == 1)
										VelX = MaxVelX; // Force right
									else if (obj->Status == 2)
										VelX = -MaxVelX; // Force left
									// Update X,Y
									Y += (-MaxVelY + VelY) / 2;
									X += VelX;
									break;
								}
								else goto ceiling;
							}

							case OBJ_Enemy:
							case OBJ_SIDE_Spine:
							case OBJ_FLOOR_Spine:
								Status = DEAD;
								break;

							case OBJ_FLOOR_SpineUD:
								if (obj->Status == 0) {
									// Spine Up
									if (VelY < 0) goto ceiling;
									else Status = DEAD;
								}
								else {
									// Spine douwn
									if (VelY > 0) goto plainfloor;
									else Status = DEAD;
								}
								break;

							case OBJ_FLOOR_Spring:
								goto plainfloor;

							case OBJ_FLOOR_Forced:
forced:							if (VelY > 0) {
									hitfloor = true;
									// Restore starting values
									Y = obj->Y - H;
									X = obj->X + (obj->W - W) / 2;
									VelX = 0;
									VelY = -MaxVelY;
									Status = BOUNCING;
									// Apply gravity
									VelY += AccelY;
									// Start moving left/right
									if (obj->Status == 0)
										VelX = MaxVelX; // Force right
									else if (obj->Status == 1)
										VelX = -MaxVelX; // Force left
									// Update X,Y
									Y += (-MaxVelY + VelY) / 2;
									X += VelX;
									break;
								}
							else goto ceiling;

							case OBJ_FLOOR_Ice:
								goto plainfloor;
							
							case OBJ_FLOOR_OneBounce:
								goto plainfloor;

							case OBJ_FLOOR_Catapult: {
								if (VelY < 0) goto ceiling;
								hitfloor = true;
								// Restore starting values
								Y = obj->Y - H;
								X = obj->X + (obj->W - W) / 2;
								VelX = 0;
								VelY = -MaxVelY;
								Status = CATAPULT;
								// Apply gravity
								VelY += AccelY;
								// Start moving left/right
								if (obj->Status == 0)
									VelX = 2 * MaxVelX; // Catapult right
								else if (obj->Status == 1)
									VelX = -2 * MaxVelX; // Catapult left
								// Update X,Y
								Y += (-MaxVelY + VelY) / 2;
								X += VelX;
							} break;

							case OBJ_FLOOR_Teleport: {

								if (Status != TELEPORTING) {
									if (VelY < 0) goto ceiling;
									if ((pressedLeft || pressedRight) && !pressedUp) goto plainfloor;
									
									// Start teleporting
									Status = TELEPORTING;
									VelY = MaxVelY / 4;
								}

								// Test for being teleported
								if (VelY > 0 && (Y >= obj->Y))
								{
									// Find the next teleport
									cTeleport* next = static_cast<cTeleport*>(myLevel->FindNextObject(obj->myCell, OBJ_FLOOR_Teleport));
									if (next) {
										// Translate Bumpy
										X += (next->myCell->col - obj->myCell->col) * myLevel->CellX;
										Y += (next->myCell->row - obj->myCell->row) * myLevel->CellY;
										// Invert the velocity
										VelY = -VelY;
										Y += VelY;
										// Set the next teleport as the colliding element
										obj = next;
									}
								}

								// Test for exit teleport
								if (VelY < 0 && (Y + H + VelY <= obj->Y)) {
									Y += VelY;
									VelY = MaxVelY; // As if it's bouncing
									Status = JUMPING;
									goto plainfloor;
								}

							} break;

							case OBJ_FLOOR_Glue:
							{
								if ((VelY > 0) && (pressedRight || pressedLeft || pressedUp || pressedSpace))
									goto plainfloor;
								else {
									// Restore starting values
									if (VelY > 0) Y = obj->Y - H;
									else Y = obj->Y + obj->H;
									X = obj->X + (obj->W - W) / 2;
									VelX = 0;
									VelY = 0;
									Status = GLUED;
								}
							} break;

							case OBJ_FLOOR_Magnetic: // To be implemented
							{
								if (VelY > 0) goto plainfloor;
								else {
									// Restore starting values
									Y = obj->Y + obj->H;
									X = obj->X + (obj->W - W) / 2;
									VelX = 0;
									VelY = 0;
									Status = MAGNETIC;
								}
							} break;

							case OBJ_FLOOR_Plain: {
plainfloor:
								// Hit the floor
								if (VelY > 0) {
									hitfloor = true;
									// Restore starting values
									Y = obj->Y - H;
									X = obj->X + (obj->W - W) / 2;
									float vx = VelX; // to use later
									VelX = 0;
									VelY = -MaxVelY;
									bool cantjump = obj->type == OBJ_FLOOR_Wall || 
										(obj->type == OBJ_FLOOR_SpineUD && obj->Status == 1);
									if (((pressedUp || pressedSpace) && !cantjump) ||
										obj->type == OBJ_FLOOR_Spring ||
										((obj->type == OBJ_FLOOR_Teleport) && !(pressedLeft || pressedRight || pressedDown))) {
										Status = JUMPING;
										Y += VelY;
									}
									else {
										Status = BOUNCING;
										// Apply gravity
										VelY += AccelY;
										// Start moving left/right
										if (pressedRight) {
											VelX = MaxVelX;
											if (obj->type == OBJ_FLOOR_Decision)
												obj->Status = 1;
										}
										else if (pressedLeft) {
											VelX = -MaxVelX;
											if (obj->type == OBJ_FLOOR_Decision)
												obj->Status = 2;
										}
										// Sliding on ice
										else if (obj->type == OBJ_FLOOR_Ice) {
											VelX = vx;
											if (VelX) Status = SLIDING;
										}
										// Update X,Y
										Y += (-MaxVelY + VelY) / 2;
										X += VelX;
									}

									if (obj->type == OBJ_FLOOR_OneBounce)
										if (!(pressedUp || pressedLeft || pressedRight || pressedSpace))
											obj->Status = -1;
								}
								// Hit the ceiling
								else {
									Y = obj->Y + obj->H;
ceiling:
								
									VelY = MaxVelY;
									Status = FALLING;
								}
							} break;

							case OBJ_FLOOR_Cloud: {
								if (VelY < 0)
									goto ceiling;
								// Restore previous values
								Y = obj->Y - H;
								X = obj->X + (obj->W - W) / 2;
								// Set velocity and status
								VelX = 0;
								VelY = 0;
								Status = CLOUD;
								myCloud = static_cast<cCloud*>(obj);

								MoveOnCloud();

							} break;

							// SIDE objects

							case OBJ_SIDE_RightOnly:
								if (VelX > 0)
									break; // ignore it
								else // bounce against it
									goto rebound;

							case OBJ_SIDE_LeftOnly:
								if (VelX < 0)
									break; // ignore it
								else // bounce against it
									goto rebound;

							case OBJ_SIDE_Nways: {
								if (!crossingside) {
									if (obj->Status == 0)
										goto rebound;
									if (Status == SLIDING) {
										obj->Status--;
										goto rebound;
									}
									else {
										// Cross the object
										crossingside = true;
										obj->Status--;
									}
								}
							} break;

							case OBJ_SIDE_Wall:
								if (obj->Status == -1) break;
								obj->Status--;
								goto rebound;

							case OBJ_SIDE_Shooter: {
								if (Status == SHOT) {
									goto rebound;
								}
								else {
									// shooting horizontally
									Status = SHOT;
									X -= VelX;
									Y -= vy;
									VelY = 0;
									VelX = (VelX > 0) ? -ShotVelX : ShotVelX;
									// Update X
									X += VelX;
								}
								break;
							}

							case OBJ_SIDE_Fake:
								obj->Status = -1;
								break;

							case OBJ_SIDE_Invisible:
								obj->Status = 1;
								goto rebound;

							case OBJ_SIDE_Face: {
								// Change status
								cFace* face = static_cast<cFace*>(obj);
								face->Status = (face->Status + 1) % 4;
								// Check all faces status
								bool dobreakice = true;
								for (int i = 0; i < myLevel->nObj; i++) {
									cObject* o = myLevel->Objects[i];
									if (o->type == OBJ_SIDE_Face) {
										if (o->Status != face->Status) {
											dobreakice = false;
											break;
										}
									}
								}
								if (dobreakice) {
									// hide all ice sides instantly
									for (int i = 0; i < myLevel->nObj; i++) {
										cObject* o = myLevel->Objects[i];
										if (o->type == OBJ_SIDE_Ice)
											o->Status = -1;
									}
									// If need to break ice in order (eg. animation) use:
									// myLevel->FindNextObject(myCell, OBJ_SIDE_ICE));

								}
								goto rebound;
							}

							case OBJ_SIDE_Ice:
								goto rebound;

							case OBJ_SIDE_Glue: {
								if ((VelX > 0) && (pressedLeft || pressedSpace)) goto rebound;
								if ((VelX < 0) && (pressedRight || pressedSpace)) goto rebound;
								else {
									// Restore starting values
									if (VelX > 0) X = obj->X - W;
									else X = obj->X + obj->W;
									//Y = obj->Y + (obj->H - H) / 2;
									Y = Y - vy;
									VelX = 0;
									VelY = 0;
									Status = GLUED;
								}
							} break;

							case OBJ_SIDE_Plain: {

rebound:						// Restore status
								if (Status == SHOT) {
									Status = FALLING;
									// Adjust X
									X = obj->X + obj->W + 1.f;
								}
								else {
									X -= VelX;
									Y -= vy;
								}
								//VelY -= AccelY;
								// Revert speed
								//VelX = -VelX;
								VelX = (VelX > 0) ? -MaxVelX : MaxVelX;
								//float oldv = -VelY;
								//VelY = oldv + AccelY;
								VelY = 2.0f;
								float oldv = 1.6f;
								// Update X,Y
								Y += (oldv + VelY) / 2;
								X += VelX;
							} break;

							default:;
							}
							// stop checking collision?!
							//stopcheck = true;
							break;
						}
					}
				}
			}
			if (stopcheck) break;
		}
	}

	if (Status == DEAD) {
		myLevel->QuitLevel = true;
		return;
	}

	// Reset flag for crossing down floor
	if (((int)Y % myLevel->CellY) <= MaxVelY)
		crossingfloor = false;

	// Reset flag for crossing side
	int auxint = (int)X % myLevel->CellX;
	if (auxint > (FLOOR_HEIGHT >> 1) && auxint < myLevel->CellX - (FLOOR_HEIGHT >> 1) - W)
		crossingside = false;

	// Hit the edge of the window
	if (X < 0 || (int)(X + W) >= SCREEN_WIDTH) {
		if (Status == SHOT) {
			X = (X < 0) ? 6.f : (float)SCREEN_WIDTH - W - 6.f;
			Status = FALLING;
			VelX = (VelX > 0) ? -MaxVelX : MaxVelX;
			VelY = 2.0f;
			float oldv = 1.6f;
			// Update X,Y
			Y += (oldv + VelY) / 2;
			X += VelX;
		}
		else {
			// Restore status
			X -= VelX;
			Y -= vy;
			VelY -= AccelY;
			// Revert speed
			VelX = -VelX;
			float oldv = -VelY;
			VelY = oldv + AccelY;
			// Update X,Y
			Y += (oldv + VelY) / 2;
			X += VelX;
		}
	}

	// Handle jumping
	r = (int)(Y + H + FLOOR_HEIGHT) / myLevel->CellY;
	c = (int)(X + W / 2) / myLevel->CellX;
	// Jumping upwards
	if (Status == JUMPING) {
		if (!hitfloor) {
			// Position over floor thickness?
			if (r < myCell->row) {
				if (pressedLeft) {
					// Stop jumping
					Y -= vy;
					VelX = -MaxVelX;
					// restore gravity
					Status = FALLING;
					VelY += AccelY;
					Y += (vy + VelY) / 2;
					X += VelX;
				}
				else if (pressedRight) {
					// Stop jumping
					Y -= vy;
					VelX = MaxVelX;
					// restore gravity
					Status = FALLING;
					VelY += AccelY;
					Y += (vy + VelY) / 2;
					X += VelX;
				}
				// Stop jumping 
				if (pressedDown) {
					Status = FALLING;
				}
			}
		}
	}
	// Falling down
	else if (r > myCell->row) {
		if (!hitfloor && Status != CLOUD) {
			bool fall = true;
			for (int i = 0; i < myCell->nObj; i++) {
				cObject* obj = myCell->Objects[i];
				if (obj->type == OBJ_FLOOR_Ice) {
				//if (mIsFloor(obj->type) && obj->Status >= 0) {
					fall = false;
					break;
				}
			}
			if (fall) VelX = 0;
		}
	}

	// Update Bumpy's collider
	Collider.x = (int)X;
	Collider.y = (int)Y;

	// Update cell
	cCell* cell = myLevel->grid(c, r);
	if (myCell != cell) {
		// Change cell
		if (r != myLevel->Rows) // ?!
			myCell = cell;
		if (Status == TELEPORTING && r == myLevel->Rows)
			myCell = myLevel->grid(c, r - 1);
	}
	if (myCloud) {
		// This could be moved into cCloud::update()
		r = (int)(myCloud->Y + (myCloud->H / 2)) / myLevel->CellY;
		cell = myLevel->grid(c, r);
		cell->AddObject(myCloud);
	}

	// Bumpy falling down outside the window
	if (Y > SCREEN_HEIGHT || !myCell) {
		Status = DEAD;
		myLevel->QuitLevel = true;
	}
}

void cBumpy::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		SDL_FRect clip = { 0, 0, W, H};
		if (Status == TELEPORTING) {
			long ch = lroundf(Y + H) % myLevel->CellY;
			if (ch < H) clip = { X, Y, W, H - ch};
		}
		Texture->render((int)X, (int)Y, &clip);
	}
	else {
		// Render default 
		float R = W / 2;
		RenderObjectDefault(renderer, type, (X + R), (Y + R));
		//SDL_SetRenderDrawColor(renderer, 0xc0, 0, 0, 255);
		//RenderFillCircle(renderer, (X + R), (Y + R), R);
	}
}

//------------------------------------------
// class cFood
//------------------------------------------

cFood::cFood() : cObject()
{
	// These should depend on grid dimensions
	W = 10;
	H = 10;
	Collider.w = (int)W;
	Collider.h = (int)H;
}

cFood::~cFood() {}

void cFood::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default 
		float R = W / 2;
		RenderObjectDefault(renderer, type, (X + R), (Y + R));
	}
}

//------------------------------------------
// class cLife
//------------------------------------------

cLife::cLife() : cObject()
{
	// These should depend on grid dimensions
	W = 20;
	H = 20;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txLife;
}

cLife::~cLife() {}

void cLife::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default 
		float R = W / 2;
		RenderObjectDefault(renderer, type, (X + R), (Y + R));
	}
}

//------------------------------------------
// class cEnemy
//------------------------------------------

cEnemy::cEnemy(int status) : cObject()
{
	// These should depend on grid dimensions
	W = 20;
	H = 20;
	Collider.w = (int)W;
	Collider.h = (int)H;
	// Initialize velocity
	VelX = VelY = 0;
	int dir = status / 10;
	SetDirection(dir % 4);
	Status = (status - dir * 10) % 4;
	Texture = &txEnemy;
}

cEnemy::~cEnemy() {}

void cEnemy::update()
{
	// Update position
	Y += VelY;
	X += VelX;
	Collider.x = (int)X;
	Collider.y = (int)Y;

	// Calculate velocity
	bool goup = false;
	bool godown = false;
	bool goleft = false;
	bool goright = false;

	// Is the enemy in the center of the cell?
	long incellx = SDL_lroundf(X + W / 2) % myLevel->CellX;
	long incelly = SDL_lroundf(Y + H / 2) % myLevel->CellY;
	bool iscenterx = incellx < ((myLevel->CellX + MaxVelX) / 2) && incellx > ((myLevel->CellX - MaxVelX) / 2);
	bool iscentery = incelly < ((myLevel->CellY + MaxVelY) / 2) && incelly > ((myLevel->CellY - MaxVelY) / 2);

	if ((VelX && iscenterx) || (VelY && iscentery))
	{
		// Yes! Check which directions are free
		bool freeup = true;
		bool freedown = true;
		bool freeleft = true;
		bool freeright = true;

		// Downwards
		cCell* cell = myCell;
		if (cell->row == myLevel->Rows - 1) freedown = false;
		else for (int i = 0; i < cell->nObj; i++) {
			if (mIsFloor(cell->Objects[i]->type) && cell->Objects[i]->Status >= 0) {
				freedown = false;
				break;
			}
		}
		// Upwards
		cell = myLevel->grid(myCell->col, myCell->row - 1);
		if (!cell) freeup = false;
		else for (int i = 0; i < cell->nObj; i++) {
			if (mIsFloor(cell->Objects[i]->type) && cell->Objects[i]->Status >= 0) {
				freeup = false;
				break;
			}
		}
		// Rightwards
		cell = myCell;
		if (cell->col == myLevel->Cols - 1) freeright = false;
		else for (int i = 0; i < cell->nObj; i++) {
			if (mIsSide(cell->Objects[i]->type) && cell->Objects[i]->Status >= 0) {
				freeright = false;
				break;
			}
		}
		// Leftwards
		cell = myLevel->grid(myCell->col - 1, myCell->row);
		if (!cell) freeleft = false;
		else for (int i = 0; i < cell->nObj; i++) {
			if (mIsSide(cell->Objects[i]->type) && cell->Objects[i]->Status >= 0) {
				freeleft = false;
				break;
			}
		}

		// Choose the direction according to the status
		switch (Status) {

		case SUPERDUMB: {
			// Just invert the direction
			if (VelX > 0 && !freeright) goleft = true;
			else if (VelX < 0 && !freeleft) goright = true;
			else if (VelY > 0 && !freedown) goup = true;
			else if (VelY < 0 && !freeup) godown = true;
		} break;

		case DUMB: {
			// Turn prefearably clockwise
			if (VelX > 0 && !freeright) {
				if (freedown) godown = true;
				else if (freeup) goup = true;
				else goleft = true;
			}
			if (VelX < 0 && !freeleft) {
				if (freeup) goup = true;
				else if (freedown) godown = true;
				else goright = true;
			}
			if (VelY > 0 && !freedown) {
				if (freeleft) goleft = true;
				else if (freeright) goright = true;
				else goup = true;
			}
			if (VelY < 0 && !freeup) {
				if (freeright) goright = true;
				else if (freeleft) goleft = true;
				else godown = true;
			}
		} break;

		case RANDOM: {
			// Randomly choose a free direction
		random:
			int nf = freeup ? 1 : 0;
			nf += freedown ? 1 : 0;
			nf += freeright ? 1 : 0;
			nf += freeleft ? 1 : 0;
			int rand = SDL_rand(nf);
			bool* goptr[4] = { 0 };
			int idx = 0;
			if (freeup) goptr[idx++] = &goup;
			if (freedown) goptr[idx++] = &godown;
			if (freeleft) goptr[idx++] = &goleft;
			if (freeright) goptr[idx++] = &goright;
			*goptr[rand] = true;
		} break;

		case NASTY: {
			// Try to follow bumpy
			cBumpy* bumpy = myLevel->Bumpy;
			float dx = bumpy->X - X;
			float dy = bumpy->Y - Y;

			// Add a 50% random component
			int rand = SDL_rand(2);
			if (rand == 1) goto random;

			if (dx >= 2 * dy && dx >= -dy) {
				// Bumpy is on the right
				if (freeright) goright = true;
				else {
					if (dy > 0) {
						if (freedown) godown = true;
						else if (freeup) goup = true;
						else if (freeleft) goleft = true;
					}
					else if (dy < 0) {
						if (freeup) goup = true;
						else if (freedown) godown = true;
						else if (freeleft) goleft = true;
					}
					else {
						if (bumpy->VelY > 0) {
							if (freedown) godown = true;
							else if (freeup) goup = true;
							else if (freeleft) goleft = true;
						}
						else {
							if (freeup) goup = true;
							else if (freedown) godown = true;
							else if (freeleft) goleft = true;
						}
					}
				}
			}
			else if (dx <= dy && dx <= -2 * dy) {
				// Bumpy is on the left
				if (freeleft) goleft = true;
				else {
					if (dy > 0) {
						if (freedown) godown = true;
						else if (freeup) goup = true;
						else if (freeright) goright = true;
					}
					else if (dy < 0) {
						if (freeup) goup = true;
						else if (freedown) godown = true;
						else if (freeright) goright = true;
					}
					else {
						if (bumpy->VelY > 0) {
							if (freedown) godown = true;
							else if (freeup) goup = true;
							else if (freeright) goright = true;
						}
						else {
							if (freeup) goup = true;
							else if (freedown) godown = true;
							else if (freeright) goright = true;
						}
					}
				}
			}
			else if (dx > 2 * dy && dx < -2 * dy) {
				// Bumpy is above
				if (freeup) goup = true;
				else {
					if (dx > 0) {
						if (freeright) goright = true;
						else if (freeleft) goleft = true;
						else if (freedown) godown = true;
					}
					else if (dx < 0) {
						if (freeleft) goleft = true;
						else if (freeright) goright = true;
						else if (freedown) godown = true;
					}
					else {
						if (bumpy->VelX >= 0) {
							if (freeright) goright = true;
							else if (freeleft) goleft = true;
							else if (freedown) godown = true;
						}
						else {
							if (freeleft) goleft = true;
							else if (freeright) goright = true;
							else if (freedown) godown = true;
						}
					}
				}
			}
			else {
				// Bumpy is below
				if (freedown) godown = true;
				else {
					if (dx > 0) {
						if (freeright) goright = true;
						else if (freeleft) goleft = true;
						else if (freeup) goup = true;
					}
					else if (dx < 0) {
						if (freeleft) goleft = true;
						else if (freeright) goright = true;
						else if (freeup) goup = true;
					}
					else {
						if (bumpy->VelX >= 0) {
							if (freeright) goright = true;
							else if (freeleft) goleft = true;
							else if (freeup) goup = true;
						}
						else {
							if (freeleft) goleft = true;
							else if (freeright) goright = true;
							else if (freeup) goup = true;
						}
					}
				}
			}
		} break;

		default: break;
		}
	}
	
	// Update the velocity
	if (goup) {
		VelX = 0;
		VelY = -EnemyVel;
	}
	else if (godown) {
		VelX = 0;
		VelY = EnemyVel;
	}
	else if (goright) {
		VelX = EnemyVel;
		VelY = 0;
	}
	else if (goleft) {
		VelX = -EnemyVel;
		VelY = 0;
	}

	// Update myCell
	int r = (int)(Y + H / 2) / myLevel->CellY;
	int c = (int)(X + W / 2) / myLevel->CellX;
	cCell* cell = myLevel->grid(c, r);
	if (cell && myCell != cell) {
		// Change cell
		cell->AddObject(this);
		myCell = cell;
	}
}

void cEnemy::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;
	if (myLevel->ShowGrid) {
		// Render direction
		int xw2 = X + W / 2;
		int yh2 = Y + H / 2;
		SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 255);
		int dir = GetDirection();
		if (dir == 0) {
			SDL_RenderLine(renderer, X - 10, yh2, X + W + 10, yh2);
			SDL_RenderLine(renderer, xw2, Y - 10, X + W + 10, yh2);
			SDL_RenderLine(renderer, xw2, Y + H + 10, X + W + 10, yh2);
		}
		else if (dir == 1) {
			SDL_RenderLine(renderer, xw2, Y - 10, xw2, Y + H + 10);
			SDL_RenderLine(renderer, X - 10, yh2, xw2, Y + H + 10);
			SDL_RenderLine(renderer, X + W + 10, yh2, xw2, Y + H + 10);
		}
		else if (dir == 2) {
			SDL_RenderLine(renderer, X - 10, yh2, X + W + 10, yh2);
			SDL_RenderLine(renderer, xw2, Y - 10, X - 10, yh2);
			SDL_RenderLine(renderer, xw2, Y + H + 10, X - 10, yh2);
		}
		else if (dir == 3) {
			SDL_RenderLine(renderer, xw2, Y - 10, xw2, Y + H + 10);
			SDL_RenderLine(renderer, X - 10, yh2, xw2, Y - 10);
			SDL_RenderLine(renderer, X + W + 10, yh2, xw2, Y - 10);
		}
	}
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default 
		float R = W / 2;
		RenderObjectDefault(renderer, type, (X + R), (Y + R), 0., 0., Status);
	}
}


void cEnemy::SetDirection(int dir)
{
	switch (dir) {
	case 0: VelX = EnemyVel; VelY = 0; break;
	case 1: VelX = 0; VelY = EnemyVel; break;
	case 2: VelX = -EnemyVel; VelY = 0; break;
	case 3: VelX = 0; VelY = -EnemyVel; break;
	default: VelX = 0; VelY = 0; break;
	}
}

int cEnemy::GetDirection()
{
	if (VelX > 0 && VelY == 0) return 0;
	if (VelX == 0 && VelY > 0) return 1;
	if (VelX < 0 && VelY == 0) return 2;
	if (VelX == 0 && VelY < 0) return 3;
	return -1;
}

//------------------------------------------
// class cPlainFloor
//------------------------------------------

cPlainFloor::cPlainFloor() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txFloor;
}

cPlainFloor::~cPlainFloor() {}

void cPlainFloor::handleEvent(SDL_Event& e) {}

void cPlainFloor::update() {
	// Some animation...
}

void cPlainFloor::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H);
	}
}

//------------------------------------------
// class cIceFloor
//------------------------------------------

cIceFloor::cIceFloor() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txIce;
}

cIceFloor::~cIceFloor() {}

void cIceFloor::handleEvent(SDL_Event& e) {}

void cIceFloor::update() {
	// Some animation...
}

void cIceFloor::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default
		RenderObjectDefault(renderer, type, X, Y, W, H);
	}
}

//------------------------------------------
// class cFakeFloor
//------------------------------------------

cFakeFloor::cFakeFloor() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txFake;
}

cFakeFloor::~cFakeFloor() {}

void cFakeFloor::handleEvent(SDL_Event& e) {}

void cFakeFloor::update() {
	// Some animation...
}

void cFakeFloor::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default
		RenderObjectDefault(renderer, type, X, Y, W, H);
	}
}

//------------------------------------------
// class cInvisibleFloor
//------------------------------------------

cInvisibleFloor::cInvisibleFloor() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txInvisible;
}

cInvisibleFloor::~cInvisibleFloor() {}

void cInvisibleFloor::handleEvent(SDL_Event& e) {}

void cInvisibleFloor::update() {
	// Some animation...
}

void cInvisibleFloor::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;

	// When hit, it become invisible
	if (Status == 1) return;

	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)(X + (W - Texture->getWidth()) / 2), (int)Y);
	}
	else {
		// Render default
		RenderObjectDefault(renderer, type, X, Y, W, H);
	}
}

//------------------------------------------
// class cReducingFloor
//------------------------------------------

cReducingFloor::cReducingFloor(int status) : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Status = status;
	if (Status == 0) Texture = &txReduce1;
	else if (Status == 1) Texture = &txReduce2;
	else if (Status == 2) Texture = &txReduce3;
	else Texture = NULL;
}

cReducingFloor::~cReducingFloor() {}

void cReducingFloor::handleEvent(SDL_Event& e) {}

void cReducingFloor::update() {}

void cReducingFloor::render(SDL_Renderer* renderer)
{
	switch (Status) {
	case 0: Texture = &txReduce1; break;
	case 1: Texture = &txReduce2; break;
	case 2: Texture = &txReduce3; break;
	default: return;
	}
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cFloorWall
//------------------------------------------

cFloorWall::cFloorWall(int status) : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Status = status;
	if (Status == 0) Texture = &txWall1;
	else if (Status == 1) Texture = &txWall2;
	else if (Status == 2) Texture = &txWall3;
	else Texture = NULL;
}

cFloorWall::~cFloorWall() {}

void cFloorWall::handleEvent(SDL_Event& e) {}

void cFloorWall::update() {
	// Some animation...
	if (Status == 0) Texture = &txWall1;
	else if (Status == 1) Texture = &txWall2;
	else if (Status == 2) Texture = &txWall3;
	else Texture = NULL;
}

void cFloorWall::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cForced
//------------------------------------------

cForced::cForced(int status) : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Status = status;
	Texture = &txForced;
}

cForced::~cForced() {}

void cForced::handleEvent(SDL_Event& e) {}

void cForced::update() {
	// Some animation...
}

void cForced::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		if (Status == 0) Texture->render((int)X, (int)Y);
		else if (Status == 1) Texture->render((int)X, (int)Y, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
	}
	else {
		// Render default
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cDecision
//------------------------------------------

cDecision::cDecision(int status) : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Status = status;
	Texture = &txDecision;
}

cDecision::~cDecision() {}

void cDecision::handleEvent(SDL_Event& e) {}

void cDecision::update() {
	// Some animation...
}

void cDecision::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		if (Status == 0)
			Texture->render((int)X, (int)Y);
		else if (Status == 1) // Force right
			Texture->render((int)X, (int)Y, NULL, 16);
		else /*if (Status == 2)*/ // Force left
			Texture->render((int)X, (int)Y, NULL, -16);
	}
	else {
		// Render default
	}
}

//------------------------------------------
// class cFloorUp
//------------------------------------------

cFloorUp::cFloorUp() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txFloorUp;
}

cFloorUp::~cFloorUp() {}

void cFloorUp::handleEvent(SDL_Event& e) {}

void cFloorUp::update() {
	// Some animation...
}

void cFloorUp::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cFloorDown
//------------------------------------------

cFloorDown::cFloorDown() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txFloorDown;
}

cFloorDown::~cFloorDown() {}

void cFloorDown::handleEvent(SDL_Event& e) {}

void cFloorDown::update() {
	// Some animation...
}

void cFloorDown::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cSpine
//------------------------------------------

cSpine::cSpine() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txSpine;
}

cSpine::~cSpine() {}

void cSpine::handleEvent(SDL_Event& e) {}

void cSpine::update() {
	// Some animation...
}

void cSpine::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cSpineUD
//------------------------------------------

cSpineUD::cSpineUD(int status) : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txSpineDown;
}

cSpineUD::~cSpineUD() {}

void cSpineUD::handleEvent(SDL_Event& e) {}

void cSpineUD::update() {
	// Some animation...
}

void cSpineUD::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		if (Status == 0) Texture->render((int)X, (int)Y, NULL, 0, NULL, SDL_FLIP_VERTICAL);
		else if (Status == 1) Texture->render((int)X, (int)Y);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cSpring
//------------------------------------------

cSpring::cSpring() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txSpring;
}

cSpring::~cSpring() {}

void cSpring::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cExit
//------------------------------------------

cExit::cExit() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
}

cExit::~cExit() {}

void cExit::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cCloud
//------------------------------------------

cCloud::cCloud() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txCloud;
}

cCloud::~cCloud() {}

void cCloud::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cOneBounce
//------------------------------------------

cOneBounce::cOneBounce() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txOneBounce;
}

cOneBounce::~cOneBounce() {}

void cOneBounce::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cGlue
//------------------------------------------

cGlue::cGlue() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txGlue;
}

cGlue::~cGlue() {}

void cGlue::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H);
	}
}

//------------------------------------------
// class cTeleport
//------------------------------------------

cTeleport::cTeleport() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txTeleport;
}

cTeleport::~cTeleport() {}

void cTeleport::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H);
	}
}

//------------------------------------------
// class cMagnetic
//------------------------------------------

cMagnetic::cMagnetic() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txMagnetic;
}

cMagnetic::~cMagnetic() {}

void cMagnetic::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H);
	}
}

//------------------------------------------
// class cCatapult
//------------------------------------------

cCatapult::cCatapult(int status) : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Status = status;
	Texture = &txCatapult;
}

cCatapult::~cCatapult() {}

void cCatapult::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cPlainSide
//------------------------------------------

cPlainSide::cPlainSide() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_HEIGHT;
	H = FLOOR_WIDTH;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txFloor;
}

cPlainSide::~cPlainSide() {}

void cPlainSide::handleEvent(SDL_Event& e) {}

void cPlainSide::update() {
	// Some animation...
}

void cPlainSide::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)(X + (W - H) / 2), (int)(Y + (H - W) / 2), NULL, 90);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H);
	}
}

//------------------------------------------
// class cLeftOnly
//------------------------------------------

cLeftOnly::cLeftOnly() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_HEIGHT;
	H = FLOOR_WIDTH;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txLeft;
}

cLeftOnly::~cLeftOnly() {}

void cLeftOnly::handleEvent(SDL_Event& e) {}

void cLeftOnly::update() {
	// Some animation...
}

void cLeftOnly::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)(X), (int)(Y), NULL, 0);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H);
	}
}

//------------------------------------------
// class cRightOnly
//------------------------------------------

cRightOnly::cRightOnly() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_HEIGHT;
	H = FLOOR_WIDTH;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txRight;
}

cRightOnly::~cRightOnly() {}

void cRightOnly::handleEvent(SDL_Event& e) {}

void cRightOnly::update() {
	// Some animation...
}

void cRightOnly::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)(X), (int)(Y), NULL, 0);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H);
	}
}

//------------------------------------------
// class cNways
//------------------------------------------

cNways::cNways(int status) : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_HEIGHT;
	H = FLOOR_WIDTH;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Status = status;
	if (Status == 0) Texture = &txNways0;
	else if (Status == 1) Texture = &txNways1;
	else if (Status == 2) Texture = &txNways2;
	else if (Status == 3) Texture = &txNways3;
	else Texture = NULL;
}

cNways::~cNways() {}

void cNways::handleEvent(SDL_Event& e) {}

void cNways::update() {
	// Some animation...
	if (Status == 0) Texture = &txNways0;
	else if (Status == 1) Texture = &txNways1;
	else if (Status == 2) Texture = &txNways2;
	else if (Status == 3) Texture = &txNways3;
	else Texture = NULL;
}

void cNways::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)(X), (int)(Y), NULL, 0);
	}
	else {
		// Render default
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cSideWall
//------------------------------------------

cSideWall::cSideWall(int status) : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_HEIGHT;
	H = FLOOR_WIDTH;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Status = status;
	if (Status == 0) Texture = &txWall1;
	else if (Status == 1) Texture = &txWall2;
	else if (Status == 2) Texture = &txWall3;
	else Texture = NULL;
}

cSideWall::~cSideWall() {}

void cSideWall::handleEvent(SDL_Event& e) {}

void cSideWall::update() {
	// Some animation...
	if (Status == 0) Texture = &txWall1;
	else if (Status == 1) Texture = &txWall2;
	else if (Status == 2) Texture = &txWall3;
	else Texture = NULL;
}

void cSideWall::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)(X + (W - H) / 2), (int)(Y + (H - W) / 2), NULL, 90);
	}
	else {
		// Render default
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cSpineSide
//------------------------------------------

cSpineSide::cSpineSide() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_HEIGHT;
	H = FLOOR_WIDTH;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txSpineV;
}

cSpineSide::~cSpineSide() {}

void cSpineSide::handleEvent(SDL_Event& e) {}

void cSpineSide::update() {
	// Some animation...
}

void cSpineSide::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)(X + (W - H) / 2), (int)(Y + (H - W) / 2), NULL, 90);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cSpringH
//------------------------------------------

cSpringH::cSpringH() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_HEIGHT;
	H = FLOOR_WIDTH;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txShooter;
}

cSpringH::~cSpringH() {}

void cSpringH::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default 
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cFakeSide
//------------------------------------------

cFakeSide::cFakeSide() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_HEIGHT;
	H = FLOOR_WIDTH;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txFake;
}

cFakeSide::~cFakeSide() {}

void cFakeSide::handleEvent(SDL_Event& e) {}

void cFakeSide::update() {
	// Some animation...
}

void cFakeSide::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)(X + (W - H) / 2), (int)(Y + (H - W) / 2), NULL, 90);
	}
	else {
		// Render default
		RenderObjectDefault(renderer, type, X, Y, W, H);
	}
}

//------------------------------------------
// class cInvisibleSide
//------------------------------------------

cInvisibleSide::cInvisibleSide() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_HEIGHT;
	H = FLOOR_WIDTH;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txInvisible;
}

cInvisibleSide::~cInvisibleSide() {}

void cInvisibleSide::handleEvent(SDL_Event& e) {}

void cInvisibleSide::update() {
	// Some animation...
}

void cInvisibleSide::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;

	// When hit, it become invisible
	if (Status == 1) return;

	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)(X + (W - Texture->getWidth()) / 2), (int)(Y + (H - Texture->getHeight()) / 2), NULL, 90);
	}
	else {
		// Render default
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cIceSide
//------------------------------------------

cIceSide::cIceSide() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_HEIGHT;
	H = FLOOR_WIDTH;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txIce;
}

cIceSide::~cIceSide() {}

void cIceSide::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;

	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)(X + (W - Texture->getWidth()) / 2), (int)(Y + (H - Texture->getHeight()) / 2), NULL, 90);
	}
	else {
		// Render default
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cFace
//------------------------------------------

cFace::cFace(int status) : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_HEIGHT;
	H = FLOOR_WIDTH;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Status = status;
	Texture = &txFace1;
}

cFace::~cFace() {}

void cFace::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;

	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)(X + (W - Texture->getWidth()) / 2), (int)(Y + (H - Texture->getHeight()) / 2), NULL, 90);
	}
	else {
		// Render default
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------------
// class cGlueSide
//------------------------------------------

cGlueSide::cGlueSide() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_HEIGHT;
	H = FLOOR_WIDTH;
	Collider.w = (int)W;
	Collider.h = (int)H;
	Texture = &txGlue;
}

cGlueSide::~cGlueSide() {}

void cGlueSide::render(SDL_Renderer* renderer)
{
	if (Status < 0) return;

	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)(X + (W - Texture->getWidth()) / 2), (int)(Y + (H - Texture->getHeight()) / 2), NULL, 90);
	}
	else {
		// Render default
		RenderObjectDefault(renderer, type, X, Y, W, H, Status);
	}
}

//------------------------------------
// World objects
//------------------------------------

//------------------------------------------
// class cLevelEntrance
//------------------------------------------

cLevelEntrance::cLevelEntrance(int levelid) : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_WIDTH;
	LevelID = levelid;
}

cLevelEntrance::~cLevelEntrance() {}

void cLevelEntrance::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;

	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default
		SDL_SetRenderDrawColor(renderer, 0x40, 0x40, 0x40, 255);
		RenderFillCircle(renderer, X + W / 2, Y + H / 2, H / 2);
		SDL_SetRenderDrawColor(renderer, 0xc0, 0xc0, 0xc0, 255);
		RenderDrawCircle(renderer, X + W / 2, Y + H / 2, H / 2);
#ifdef _DEBUG
		LTexture txIdx;
		char buff[10] = { 0 };
		SDL_Color col = { 0xFF, 0xFF, 0xFF, 0xFF };
		SDL_snprintf(buff, 9, "%i", LevelID & 0xFF);
		txIdx.loadFromRenderedText(buff, col);
		txIdx.render((int)(X + (W - txIdx.getWidth()) / 2), (int)(Y + (H - txIdx.getHeight()) / 2));
#endif
		if (Status == 1) {
			SDL_SetRenderDrawColor(renderer, 0xE0, 0x40, 0x00, 255);
			SDL_RenderLine(renderer, X, Y, X + W, Y + H);
			SDL_RenderLine(renderer, X, Y + H, X + W, Y);
		}
	}
}

//------------------------------------------
// class cPathHor
//------------------------------------------

cPathHor::cPathHor() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_WIDTH;
	H = FLOOR_HEIGHT >> 1;
}

cPathHor::~cPathHor() {}

void cPathHor::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default
		SDL_SetRenderDrawColor(renderer, 0x00, 0x80, 0xc0, 255);
		SDL_FRect rect = { X, Y, W, H };
		SDL_RenderFillRect(renderer, &rect);
	}
}

//------------------------------------------
// class cPathVer
//------------------------------------------

cPathVer::cPathVer() : cObject()
{
	// These should depend on grid dimensions
	W = FLOOR_HEIGHT >> 1;
	H = FLOOR_WIDTH;
}

cPathVer::~cPathVer() {}

void cPathVer::render(SDL_Renderer* renderer)
{
	if (Status == -1) return;
	if (Texture && Texture->getWidth() != 0) {
		// Render the texture
		Texture->render((int)X, (int)Y);
	}
	else {
		// Render default
		SDL_SetRenderDrawColor(renderer, 0x00, 0x80, 0xc0, 255);
		SDL_FRect rect = { X, Y, W, H };
		SDL_RenderFillRect(renderer, &rect);
	}
}

//------------------------------------------
// Support functions
//------------------------------------------

void RenderObjectDefault(SDL_Renderer* renderer, int objtype, float x, float y, float w, float h, int status)
{
	SDL_FRect rect = { x, y, w, h };
	switch (objtype) {
	
		// Central objects

	case OBJ_Bumpy:
		SDL_SetRenderDrawColor(renderer, 0xc0, 0, 0, 255);
		RenderFillCircle(renderer, x, y, 10);
		break;
	case OBJ_Food:
		SDL_SetRenderDrawColor(renderer, 0xc0, 0xc0, 0, 255);
		RenderFillCircle(renderer, x, y, 3);
		break;
	case OBJ_Enemy:
		SDL_SetRenderDrawColor(renderer, 0xff, 0xd0, 0xd0, 255);
		if (status == cEnemy::DUMB) SDL_SetRenderDrawColor(renderer, 0xf0, 0xa0, 0xa0, 255);
		else if (status == cEnemy::RANDOM) SDL_SetRenderDrawColor(renderer, 0xd0, 0x60, 0x60, 255);
		else if (status == cEnemy::NASTY) SDL_SetRenderDrawColor(renderer, 0xc0, 0x20, 0x20, 255);
		RenderFillCircle(renderer, x, y, 10);

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
		RenderDrawCircle(renderer, x - 4, y - 2, 4);
		RenderDrawCircle(renderer, x + 4, y - 2, 4);
		SDL_RenderLine(renderer, x - 4, y + 7, x - 2, y + 5);
		SDL_RenderLine(renderer, x - 2, y + 5, x + 2, y + 5);
		SDL_RenderLine(renderer, x + 2, y + 5, x + 4, y + 7);
		break;
	case OBJ_Life:
		SDL_SetRenderDrawColor(renderer, 0x00, 0x80, 0xC0, 255);
		RenderFillCircle(renderer, x, y, 10);

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
		RenderDrawCircle(renderer, x - 4, y - 2, 3);
		RenderDrawCircle(renderer, x + 4, y - 2, 3);
		SDL_RenderLine(renderer, x - 4, y + 5, x - 2, y + 7);
		SDL_RenderLine(renderer, x - 2, y + 7, x + 2, y + 7);
		SDL_RenderLine(renderer, x + 2, y + 7, x + 4, y + 5);
		break;

		// Floor objects

	case OBJ_FLOOR_Plain:
		SDL_SetRenderDrawColor(renderer, 0x80, 0x40, 0xC0, 255);
		SDL_RenderFillRect(renderer, &rect);
		break;
	case OBJ_FLOOR_Cloud:
		SDL_SetRenderDrawColor(renderer, 0x00, 0x80, 0xC0, 255);
		rect = { x, y - 5, w / 3, h + 5 };
		SDL_RenderFillRect(renderer, &rect);
		rect = { x + w / 3, y, w / 3, h + 5 };
		SDL_RenderFillRect(renderer, &rect);
		rect = { x + 2 * w / 3, y - 5, w / 3, h + 5 };
		SDL_RenderFillRect(renderer, &rect);
		break;
	case OBJ_FLOOR_Exit:
		SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0, 255);
		SDL_RenderRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0xF0, 0xF0, 0xc0, 255);
		SDL_RenderLine(renderer, x + w / 2, y, x + w / 2 - 10, y - 10);
		SDL_RenderLine(renderer, x + w / 2, y, x + w / 2 + 10, y - 10);
		SDL_RenderLine(renderer, x + w / 2 - 10, y - 10, x + w / 2 + 10, y - 10);
		break;
	case OBJ_FLOOR_Ice:
		SDL_SetRenderDrawColor(renderer, 0x00, 0xC0, 0xC0, 255);
		SDL_RenderFillRect(renderer, &rect);
		break;
	case OBJ_FLOOR_Down: {
		SDL_SetRenderDrawColor(renderer, 0x40, 0x40, 0x00, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x80, 0xc0, 255);
		float w5 = w / 5;
		SDL_RenderLine(renderer, x + w5, y, x + w5 + w5 / 2, y + h - 1);
		SDL_RenderLine(renderer, x + w5 + w5 / 2, y + h - 1, x + 2 * w5, y);
		SDL_RenderLine(renderer, x + 3 * w5, y, x + 3 * w5 + w5 / 2, y + h - 1);
		SDL_RenderLine(renderer, x + 3 * w5 + w5 / 2, y + h - 1, x + 4 * w5, y);
	} break;
	case OBJ_FLOOR_Up: {
		SDL_SetRenderDrawColor(renderer, 0x40, 0x40, 0x00, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x80, 0x00, 255);
		float w5 = w / 5;
		SDL_RenderLine(renderer, x + w5, y + h - 1, x + w5 + w5 / 2, y);
		SDL_RenderLine(renderer, x + w5 + w5 / 2, y, x + 2 * w5, y + h - 1);
		SDL_RenderLine(renderer, x + 3 * w5, y + h - 1, x + 3 * w5 + w5 / 2, y);
		SDL_RenderLine(renderer, x + 3 * w5 + w5 / 2, y, x + 4 * w5, y + h - 1);
	} break;
	case OBJ_FLOOR_Reducing:
		SDL_SetRenderDrawColor(renderer, 0x00, 0xC0, 0x40, 255);
		if (status == 0) rect = { x + w / 2 - 5, y, 10, h};
		if (status == 1) rect = { x + w / 2 - 20, y, 40, h };
		SDL_RenderFillRect(renderer, &rect);
		break;
	case OBJ_FLOOR_Invisible:
		if (status == 1) break;
		SDL_SetRenderDrawColor(renderer, 0x00, 0xE0, 0x00, 255);
		//SDL_RenderFillRect(renderer, &rect); // ??
		RenderFillCircle(renderer, x + w / 2, y + h / 2, h / 2);
		break;
	case OBJ_FLOOR_Fake:
		SDL_SetRenderDrawColor(renderer, 0x00, 0xC0, 0x00, 64);
		SDL_RenderFillRect(renderer, &rect);
		break;
	case OBJ_FLOOR_Spring:
		SDL_SetRenderDrawColor(renderer, 0x00, 0x40, 0x00, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 255);
		for (float i = 1; i <= 7; i += 2)
			SDL_RenderLine(renderer, x, y + h - i, x + w - 1, y + h - i);
		for (float i = 0; i <= w - 4; i += 5) {
			rect = { x + i, y - 1, 4, 3 };
			SDL_RenderRect(renderer, &rect);
		}
		break;
	case OBJ_FLOOR_Spine: {
		SDL_SetRenderDrawColor(renderer, 0x40, 0x20, 0x40, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0x80, 0x40, 0x00, 255);
		SDL_RenderLine(renderer, x + 20, y - 5, x + 18, y);
		SDL_RenderLine(renderer, x + 20, y - 5, x + 22, y);
		SDL_RenderLine(renderer, x + 35, y - 3, x + 33, y);
		SDL_RenderLine(renderer, x + 35, y - 3, x + 37, y);
		SDL_RenderLine(renderer, x + 50, y - 2, x + 48, y);
		SDL_RenderLine(renderer, x + 50, y - 2, x + 52, y);
		SDL_RenderLine(renderer, x + 20, y + h + 5, x + 18, y + h);
		SDL_RenderLine(renderer, x + 20, y + h + 5, x + 22, y + h);
		SDL_RenderLine(renderer, x + 35, y + h + 3, x + 33, y + h);
		SDL_RenderLine(renderer, x + 35, y + h + 3, x + 37, y + h);
		SDL_RenderLine(renderer, x + 50, y + h + 2, x + 48, y + h);
		SDL_RenderLine(renderer, x + 50, y + h + 2, x + 52, y + h);
	} break;
	case OBJ_FLOOR_SpineUD:
		SDL_SetRenderDrawColor(renderer, 0x40, 0x20, 0x40, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0x80, 0x40, 0x00, 255);
		if (status == 0) {
			SDL_RenderLine(renderer, x + 20, y - 5, x + 18, y);
			SDL_RenderLine(renderer, x + 20, y - 5, x + 22, y);
			SDL_RenderLine(renderer, x + 35, y - 3, x + 33, y);
			SDL_RenderLine(renderer, x + 35, y - 3, x + 37, y);
			SDL_RenderLine(renderer, x + 50, y - 2, x + 48, y);
			SDL_RenderLine(renderer, x + 50, y - 2, x + 52, y);
		}
		else if (status == 1) {
			SDL_RenderLine(renderer, x + 20, y + h + 5, x + 18, y + h);
			SDL_RenderLine(renderer, x + 20, y + h + 5, x + 22, y + h);
			SDL_RenderLine(renderer, x + 35, y + h + 3, x + 33, y + h);
			SDL_RenderLine(renderer, x + 35, y + h + 3, x + 37, y + h);
			SDL_RenderLine(renderer, x + 50, y + h + 2, x + 48, y + h);
			SDL_RenderLine(renderer, x + 50, y + h + 2, x + 52, y + h);
		}
		break;
	case OBJ_FLOOR_Wall:
		if (status == 0)
			SDL_SetRenderDrawColor(renderer, 0x30, 0x10, 0x80, 255);
		else if (status == 1)
			SDL_SetRenderDrawColor(renderer, 0x60, 0x30, 0xA0, 255);
		else if (status == 2)
			SDL_SetRenderDrawColor(renderer, 0xA0, 0x40, 0x80, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0x20, 0x20, 0x20, 255);
		SDL_RenderLine(renderer, x, y + 3, x + w - 1, y + 3);
		SDL_RenderLine(renderer, x, y + 6, x + w - 1, y + 6);
		for (float xx = 4; xx < w - 1; xx += 5)
			SDL_RenderLine(renderer, x + xx, y, x + xx, y + h - 1);
		break;
	case OBJ_FLOOR_Forced:
		SDL_SetRenderDrawColor(renderer, 0x80, 0x00, 0xc0, 255);
		SDL_RenderLine(renderer, x, y + h, x + w, y + h);
		if (status == 0) {
			// Force right
			SDL_RenderLine(renderer, x, y - h, x, y + h);
			SDL_RenderLine(renderer, x, y - h, x + w, y + h);
		}
		else if (status == 1) {
			// Force left
			SDL_RenderLine(renderer, x + w, y - h, x, y + h);
			SDL_RenderLine(renderer, x + w, y - h, x + w, y + h);
		}
		break;
	case OBJ_FLOOR_Decision:
		SDL_SetRenderDrawColor(renderer, 0x80, 0x40, 0x00, 255);
		if (status == 0) {
			SDL_RenderLine(renderer, x, y, x + w, y);
			SDL_RenderLine(renderer, x, y + 6, x + w, y + 6);
		}
		else if (status == 1) {
			// Force right
			SDL_RenderLine(renderer, x, y - h, x + w, y + h);
			SDL_RenderLine(renderer, x, y - h + 6, x + w, y + h + 6);
		}
		else {
			// Force left
			SDL_RenderLine(renderer, x, y + h, x + w, y - h);
			SDL_RenderLine(renderer, x, y + h + 6, x + w, y - h + 6);
		}
		SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 255);
		RenderFillCircle(renderer, x + w / 2, y + 3, 3);
		break;
	case OBJ_FLOOR_OneBounce:
		SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x00, 255);
		rect = { x, y + h / 2 - 1, w, 2 };
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0xA0, 0x40, 0x00, 255);
		rect = { x, y, 3, h };
		SDL_RenderFillRect(renderer, &rect);
		rect = { x + w - 3, y, 3, h };
		SDL_RenderFillRect(renderer, &rect);
		break;
	case OBJ_FLOOR_Glue:
		SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0x40, 255);
		SDL_RenderFillRect(renderer, &rect);
		break;
	case OBJ_FLOOR_Catapult:
		SDL_SetRenderDrawColor(renderer, 0xA0, 0x80, 0x40, 255);
		if (status == 0) {
			SDL_RenderLine(renderer, x, y - h, x + w / 2, y + h);
			SDL_RenderLine(renderer, x + w / 2, y + h, x + w, y);
		}
		else if (status == 1) {
			SDL_RenderLine(renderer, x + w, y - h, x + w / 2, y + h);
			SDL_RenderLine(renderer, x + w / 2, y + h, x, y);
		}
		break;
	case OBJ_FLOOR_Teleport:
		SDL_SetRenderDrawColor(renderer, 0x80, 0x60, 0x40, 255);
		SDL_RenderFillRect(renderer, &rect);
		break;
	case OBJ_FLOOR_Magnetic:
		SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 255);
		SDL_RenderFillRect(renderer, &rect);
		break;

		// Side objects

	case OBJ_SIDE_Plain:
		SDL_SetRenderDrawColor(renderer, 0x80, 0x40, 0xC0, 255);
		SDL_RenderFillRect(renderer, &rect);
		break;
	case OBJ_SIDE_LeftOnly:
		SDL_SetRenderDrawColor(renderer, 0xc0, 0x80, 0x00, 255);
		SDL_RenderFillRect(renderer, &rect);
		break;
	case OBJ_SIDE_RightOnly:
		SDL_SetRenderDrawColor(renderer, 0xc0, 0x80, 0x00, 255);
		SDL_RenderFillRect(renderer, &rect);
		break;
	case OBJ_SIDE_Nways:
		SDL_SetRenderDrawColor(renderer, 0x00, 0x80, 0xc0, 255);
		SDL_RenderFillRect(renderer, &rect);
		if (status > 0) {
			SDL_SetRenderDrawColor(renderer, 0xc0, 0x00, 0x00, 255);
			rect = { x, y, w, 45 };
			SDL_RenderFillRect(renderer, &rect);
			if (status > 1) {
				SDL_SetRenderDrawColor(renderer, 0xc0, 0x60, 0x00, 255);
				rect = { x, y, w, 30 };
				SDL_RenderFillRect(renderer, &rect);
				if (status > 2) {
					SDL_SetRenderDrawColor(renderer, 0xc0, 0xc0, 0x00, 255);
					rect = { x, y, w, 15 };
					SDL_RenderFillRect(renderer, &rect);
				}
			}
		}
		break;
	case OBJ_SIDE_Wall:
		if (status == 0)
			SDL_SetRenderDrawColor(renderer, 0x30, 0x10, 0x80, 255);
		else if (status == 1)
			SDL_SetRenderDrawColor(renderer, 0x60, 0x30, 0xA0, 255);
		else if (status == 2)
			SDL_SetRenderDrawColor(renderer, 0xA0, 0x40, 0x80, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0x20, 0x20, 0x20, 255);
		SDL_RenderLine(renderer, x + 3, y, x + 3, y + h - 1);
		SDL_RenderLine(renderer, x + 6, y, x + 6, y + h - 1);
		for (float yy = 4; yy < h - 1; yy += 5) {
			SDL_RenderLine(renderer, x, y + yy, x + w - 1, y + yy);
		}
		break;
	case OBJ_SIDE_Spine:
		SDL_SetRenderDrawColor(renderer, 0x40, 0x20, 0x40, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0x80, 0x40, 0x00, 255);
		SDL_RenderLine(renderer, x - 5, y + 20, x, y + 18);
		SDL_RenderLine(renderer, x - 5, y + 20, x, y + 22);
		SDL_RenderLine(renderer, x - 3, y + 35, x, y + 33);
		SDL_RenderLine(renderer, x - 3, y + 35, x, y + 37);
		SDL_RenderLine(renderer, x - 2, y + 50, x, y + 48);
		SDL_RenderLine(renderer, x - 2, y + 50, x, y + 52);
		SDL_RenderLine(renderer, x + w + 5, y + 20, x + w, y + 18);
		SDL_RenderLine(renderer, x + w + 5, y + 20, x + w, y + 22);
		SDL_RenderLine(renderer, x + w + 3, y + 35, x + w, y + 33);
		SDL_RenderLine(renderer, x + w + 3, y + 35, x + w, y + 37);
		SDL_RenderLine(renderer, x + w + 2, y + 50, x + w, y + 48);
		SDL_RenderLine(renderer, x + w + 2, y + 50, x + w, y + 52);
		break;
	case OBJ_SIDE_Shooter:
		SDL_SetRenderDrawColor(renderer, 0x00, 0x40, 0x00, 255);
		SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 255);
		for (float off = 1; off <= h - 6; off += 7) {
			SDL_RenderLine(renderer, x + 1, y + off + 1, x + w - 2, y + off + 1);
			SDL_RenderLine(renderer, x, y + off + 2, x + w - 1, y + off + 2);
			SDL_RenderLine(renderer, x + 1, y + off + 3, x + w - 2, y + off + 3);
		}
		break;
	case OBJ_SIDE_Invisible:
		if (status == 1) break;
		SDL_SetRenderDrawColor(renderer, 0x00, 0xE0, 0x00, 255);
		SDL_RenderFillRect(renderer, &rect);
		RenderFillCircle(renderer, x + w / 2, y + h / 2, w / 2);
		break;
	case OBJ_SIDE_Fake:
		SDL_SetRenderDrawColor(renderer, 0x00, 0xC0, 0x00, 128);
		SDL_RenderFillRect(renderer, &rect);
		break;
	case OBJ_SIDE_Glue:
		SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0x40, 255);
		SDL_RenderFillRect(renderer, &rect);
		break;
	case OBJ_SIDE_Face:
		if (status == 0) SDL_SetRenderDrawColor(renderer, 0x80, 0xF0, 0x80, 255);
		else if (status == 1) SDL_SetRenderDrawColor(renderer, 0x60, 0xC0, 0xF0, 255);
		else if (status == 2) SDL_SetRenderDrawColor(renderer, 0xF0, 0xC0, 0x60, 255);
		else if (status == 3) SDL_SetRenderDrawColor(renderer, 0x60, 0x60, 0xF0, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
		RenderDrawCircle(renderer, x + 3, y + 30, 2);
		RenderDrawCircle(renderer, x + 7, y + 30, 2);
		SDL_RenderLine(renderer, x + 1, y + 48, x + 3, y + 50);
		SDL_RenderLine(renderer, x + 3, y + 50, x + 7, y + 50);
		SDL_RenderLine(renderer, x + 7, y + 50, x + 9, y + 48);
		break;
	case OBJ_SIDE_Ice:
		SDL_SetRenderDrawColor(renderer, 0x00, 0xC0, 0xC0, 255);
		SDL_RenderFillRect(renderer, &rect);
		break;
	default:
		break;
	}
}

void RenderDrawCircle(SDL_Renderer* renderer, float centreX, float centreY, float radius)
{
	const float diameter = (radius * 2);
	float x = (radius - 1);
	float y = 0;
	float tx = 1;
	float ty = 1;
	float error = (tx - diameter);

	while (x >= y) {
		//  Each of the following renders an octant of the circle
		SDL_RenderPoint(renderer, centreX + x, centreY - y);
		SDL_RenderPoint(renderer, centreX + x, centreY + y);
		SDL_RenderPoint(renderer, centreX - x, centreY - y);
		SDL_RenderPoint(renderer, centreX - x, centreY + y);
		SDL_RenderPoint(renderer, centreX + y, centreY - x);
		SDL_RenderPoint(renderer, centreX + y, centreY + x);
		SDL_RenderPoint(renderer, centreX - y, centreY - x);
		SDL_RenderPoint(renderer, centreX - y, centreY + x);
		if (error <= 0) {
			++y;
			error += ty;
			ty += 2;
		}
		if (error > 0) {
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

void RenderFillCircle(SDL_Renderer* renderer, float centreX, float centreY, float radius)
{
	const float diameter = (radius * 2);

	float x = (radius - 1);
	float y = 0;
	float tx = 1;
	float ty = 1;
	float error = (tx - diameter);

	while (x >= y)
	{
		SDL_RenderLine(renderer, centreX - y, centreY + x, centreX + y, centreY + x);
		SDL_RenderLine(renderer, centreX - x, centreY + y, centreX + x, centreY + y);
		SDL_RenderLine(renderer, centreX - x, centreY - y, centreX + x, centreY - y);
		SDL_RenderLine(renderer, centreX - y, centreY - x, centreX + y, centreY - x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}

}

bool CheckCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;
	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB) return false;
	if (topA >= bottomB) return false;
	if (rightA <= leftB) return false;
	if (leftA >= rightB) return false;

	//If none of the sides from A are outside B
	return true;
}

void PlaySound(unsigned int objtype) {
	MIX_Audio* chunk = NULL;
	switch (objtype) {

	case OBJ_SIDE_Ice:
	case OBJ_SIDE_Plain:
	case OBJ_SIDE_Invisible:
	case OBJ_FLOOR_Plain:
	case OBJ_FLOOR_Invisible:
	case OBJ_FLOOR_Reducing:
		chunk = Sound_Bop;
		break;

	case OBJ_Food:
	case OBJ_Enemy:
	case OBJ_Life:
	// Floor object
	case OBJ_FLOOR_Cloud:
	case OBJ_FLOOR_Exit:
	case OBJ_FLOOR_Ice:
	case OBJ_FLOOR_Down:
	case OBJ_FLOOR_Up:
	case OBJ_FLOOR_Fake:
	case OBJ_FLOOR_Spring:
	case OBJ_FLOOR_Spine:
	case OBJ_FLOOR_SpineUD:
	case OBJ_FLOOR_Glue:
	case OBJ_FLOOR_OneBounce:
	case OBJ_FLOOR_Wall:
	case OBJ_FLOOR_Forced:
	case OBJ_FLOOR_Decision:
	case OBJ_FLOOR_Catapult:
	case OBJ_FLOOR_Teleport:
	case OBJ_FLOOR_Magnetic:
	// Side objects
	case OBJ_SIDE_LeftOnly:
	case OBJ_SIDE_RightOnly:
	case OBJ_SIDE_Nways:
	case OBJ_SIDE_Wall:
	case OBJ_SIDE_Face:
	case OBJ_SIDE_Spine:
	case OBJ_SIDE_Glue:
	case OBJ_SIDE_Shooter:
	case OBJ_SIDE_Fake:
	// World specific
	case OBJ_LevelEntrance:
	case OBJ_PathHor:
	case OBJ_PathVer:

	case OBJ_None:
	default: chunk = NULL;
		break;
	}

	//Mix_PlayChannel(-1, chunk, 0);
	MIX_PlayAudio(gMixer, chunk);
}
