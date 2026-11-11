#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include "media.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int FLOOR_HEIGHT = 10;
const int FLOOR_WIDTH = 70;

enum LevelObjectsID
{
	OBJ_None = 0,
	// objects in the center of the cells
	OBJ_Bumpy,
	OBJ_Food,
	OBJ_Enemy,   // Movement missing
	OBJ_Life,
	// Floor object
	OBJ_FLOOR_Plain,
	OBJ_FLOOR_Cloud,
	OBJ_FLOOR_Exit,
	OBJ_FLOOR_Ice,
	OBJ_FLOOR_Down,
	OBJ_FLOOR_Up,
	OBJ_FLOOR_Reducing,
	OBJ_FLOOR_Invisible,
	OBJ_FLOOR_Fake,
	OBJ_FLOOR_Spring,
	OBJ_FLOOR_Spine,
	OBJ_FLOOR_SpineUD,
	OBJ_FLOOR_Glue,     // Interaction missing
	OBJ_FLOOR_OneBounce,
	OBJ_FLOOR_Wall,
	OBJ_FLOOR_Forced,
	OBJ_FLOOR_Decision,
	OBJ_FLOOR_Catapult,
	OBJ_FLOOR_Teleport,
	OBJ_FLOOR_Magnetic, // Interaction missing
	// Side objects
	OBJ_SIDE_Plain,
	OBJ_SIDE_LeftOnly,
	OBJ_SIDE_RightOnly,
	OBJ_SIDE_Nways,
	OBJ_SIDE_Wall,
	OBJ_SIDE_Face,
	OBJ_SIDE_Ice,
	OBJ_SIDE_Spine,
	OBJ_SIDE_Glue,    // to do
	OBJ_SIDE_Shooter,
	OBJ_SIDE_Invisible,
	OBJ_SIDE_Fake,
	// World specific
	OBJ_LevelEntrance,
	OBJ_PathHor,
	OBJ_PathVer
};

#define mIsCentered(id) (id < OBJ_FLOOR_Plain)
#define mIsFloor(id) ((id >= OBJ_FLOOR_Plain) && (id < OBJ_SIDE_Plain))
#define mIsSide(id) ((id >= OBJ_SIDE_Plain) && (id < OBJ_LevelEntrance))

//------------------------------------------
// Classes
//------------------------------------------

class cCell;
class cGrid;
class cLevel;
class cObject;
class cBumpy;
class cEnemy;
class cExit;
class cCloud;
class cEditor;

enum _WorldID_ {
	WORLD_TEST = 0x0,
	WORLD_1 = 0x100,
	WORLD_2 = 0x200,
	WORLD_3 = 0x300,
	WORLD_EDITOR = 0xF00
};

#define nWorlds 9
#define Passworld1 ""
#define Passworld2 "ACCESS"
#define Passworld3 "WORLD3"
#define Passworld4 "WORLD4"
#define Passworld5 "WORLD5"
#define Passworld6 "WORLD6"
#define Passworld7 "WORLD7"
#define Passworld8 "RETRO"
#define Passworld9 "THEEND"
#define PassEditor "EDITOR"

class cWorld
//------------------------------------
{
public:
	cWorld(int id, int lives, int score);
	~cWorld();
	
	int Run();
	void HandleEvents();
	void Update();
	void Render();
	void ShowPassword() const;

	bool NewObject(int type, int col, int row, int id = 0);
	void AddObject(cObject* obj);
	cCell* SetGrid(int cols, int rows);
	cCell* grid(int col, int row);

	int WorldID;
	const char* Password;
	int Lives;
	int Score;
	char bfrScore[100];
	LTexture txScore;
	int Rows;
	int Cols;
	cCell* Grid;
	int nLevels;
	int nCompleted;
	LTexture* Background;
	int nObj;
	cObject** Objects;
	int CellX;
	int CellY;
	bool Quit;
	cBumpy* Bumpy;
	cCloud* Cloud;
};

class cCell
//------------------------------------
{
public:
	cCell();
	~cCell();
	void AddObject(cObject* obj);
	void RemoveObject(cObject* obj);
public:
	int row;
	int col;
	int nObj;
	cObject** Objects;
};

class cLevel
//------------------------------------
{
	friend class cBumpy;
	friend class cEnemy;
	friend class cEditor;
	friend class cWorld;

public:
	cLevel(int levelID);
	cLevel(cLevel* copylevel); // copy constructor
	~cLevel();
	
	int Run();

	// Create a new object with grid coordinates
	cObject* NewObject(int type, int col, int row, int status = 0);
	bool DeleteObject(int type, int col, int row);
	void ClearAllObjects();

	cCell* SetGrid(int cols, int rows);
	cCell* grid(int col, int row);
	cObject* FindNextObject(cCell* cell, unsigned int objtype);

	void ExportCode();

	// Don't use these from extern
	void handleEvents();
	void update();
	void render();
	void AddObject(cObject* obj);
	void RemoveObject(cObject* obj);

protected:
	int nObj;
	cObject** Objects;
	int Rows;
	int Cols;
	cCell* Grid;
	int CellX;
	int CellY;
	LTexture* Background;
	cBumpy* Bumpy;

	int LevelID;
	bool QuitLevel;
	bool Started;
	bool Completed;
	bool ShowGrid;

	int nFood; // minimum food to eat to open the exit
	int nEaten;
	cExit* Exit;
	cEnemy* Enemy;
};

class cObject
//------------------------------------
{
public:
    cObject();
    ~cObject();

    //Takes key presses and adjusts the dot's velocity
    virtual void handleEvent(SDL_Event& e) { }
    virtual void update() { } // Move/animate object
	virtual void render(SDL_Renderer* renderer) = 0;

public:
    //The X and Y offsets
    float X, Y;
    float W, H;

	// LevelObjectsID
	unsigned int type;

	int Status; // 0 default; -1 means invisible; >0 object-specific

    // The texture/sprite
    LTexture* Texture;

    //The velocity
    float VelX, VelY;

    // Collider rect
    SDL_Rect Collider;

	cWorld* myWorld;
	cLevel* myLevel;
	cCell* myCell;
};

//Maximum Y velocity and acceleration of Bumpy
static float ShotVelX = 6.0;
static float MaxVelX = 4.0;
static float MaxVelY = 4.0;
static float AccelY = 0.4f;
static float EnemyVel = 2.0f;

class cBumpy : public cObject
//------------------------------------
{
public:
    cBumpy();
    ~cBumpy();

    //Takes key presses and adjusts the dot's velocity
    void handleEvent(SDL_Event& e);
    void update(); // Move Bumpy
    void render(SDL_Renderer* renderer);
	
	enum StatusID {
		BOUNCING,
		JUMPING,
		FALLING,
		SLIDING,
		CATAPULT,
		SHOT,
		GLUED,
		CLOUD,
		TELEPORTING,
		MAGNETIC,
		WON,
		DEAD
	};

private:
	void MoveOnCloud();
	bool crossingfloor; // could be a status mode?
	bool crossingside; // could be a status mode?

	bool pressedUp;
	bool pressedDown;
	bool pressedLeft;
	bool pressedRight;
	bool pressedSpace;

	cCloud* myCloud;
};

//------------------------------------
// Floor objects
//------------------------------------

class cPlainFloor : public cObject
	//------------------------------------
{
public:
	cPlainFloor();
	~cPlainFloor();

	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cIceFloor : public cObject
	//------------------------------------
{
public:
	cIceFloor();
	~cIceFloor();

	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cFakeFloor : public cObject
	//------------------------------------
{
public:
	cFakeFloor();
	~cFakeFloor();

	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cInvisibleFloor : public cObject
	//------------------------------------
{
public:
	cInvisibleFloor();
	~cInvisibleFloor();

	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cReducingFloor : public cObject
	//------------------------------------
{
public:
	cReducingFloor(int status);
	~cReducingFloor();

	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cFloorWall : public cObject
	//------------------------------------
{
public:
	cFloorWall(int status);
	~cFloorWall();

	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cFloorUp : public cObject
	//------------------------------------
{
public:
	cFloorUp();
	~cFloorUp();
	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cFloorDown : public cObject
	//------------------------------------
{
public:
	cFloorDown();
	~cFloorDown();
	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cForced: public cObject
	//------------------------------------
{
public:
	cForced(int status);
	~cForced();
	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cDecision: public cObject
	//------------------------------------
{
public:
	cDecision(int status = 0);
	~cDecision();
	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cSpine: public cObject
	//------------------------------------
{
public:
	cSpine();
	~cSpine();
	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cSpineUD : public cObject
	//------------------------------------
{
public:
	cSpineUD(int status = 0);
	~cSpineUD();
	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cExit : public cObject
	//------------------------------------
{
public:
	cExit();
	~cExit();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};

class cSpring: public cObject
	//------------------------------------
{
public:
	cSpring();
	~cSpring();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};

class cCloud: public cObject
	//------------------------------------
{
public:
	cCloud();
	~cCloud();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};

class cOneBounce : public cObject
	//------------------------------------
{
public:
	cOneBounce();
	~cOneBounce();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};

class cGlue: public cObject
	//------------------------------------
{
public:
	cGlue();
	~cGlue();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};

class cCatapult: public cObject
	//------------------------------------
{
public:
	cCatapult(int status);
	~cCatapult();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};

class cMagnetic: public cObject
	//------------------------------------
{
public:
	cMagnetic();
	~cMagnetic();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};

class cTeleport: public cObject
	//------------------------------------
{
public:
	cTeleport();
	~cTeleport();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};

//------------------------------------
// Side objects
//------------------------------------

class cPlainSide : public cObject
	//------------------------------------
{
public:
	cPlainSide();
	~cPlainSide();

	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cLeftOnly: public cObject
	//------------------------------------
{
public:
	cLeftOnly();
	~cLeftOnly();

	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cRightOnly : public cObject
	//------------------------------------
{
public:
	cRightOnly();
	~cRightOnly();

	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cNways: public cObject
	//------------------------------------
{
public:
	cNways(int status);
	~cNways();

	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cSideWall: public cObject
	//------------------------------------
{
public:
	cSideWall(int status);
	~cSideWall();

	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cSpineSide : public cObject
	//------------------------------------
{
public:
	cSpineSide();
	~cSpineSide();
	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cSpringH : public cObject
	//------------------------------------
{
public:
	cSpringH();
	~cSpringH();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};

class cFakeSide : public cObject
	//------------------------------------
{
public:
	cFakeSide();
	~cFakeSide();

	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cInvisibleSide : public cObject
	//------------------------------------
{
public:
	cInvisibleSide();
	~cInvisibleSide();

	void handleEvent(SDL_Event& e);
	void update();
	void render(SDL_Renderer* renderer);
};

class cIceSide: public cObject
	//------------------------------------
{
public:
	cIceSide();
	~cIceSide();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};

class cFace : public cObject
	//------------------------------------
{
public:
	cFace(int status);
	~cFace();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};

class cGlueSide : public cObject
	//------------------------------------
{
public:
	cGlueSide();
	~cGlueSide();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};

//------------------------------------
// Centered objects
//------------------------------------

class cFood : public cObject
	//------------------------------------
{
public:
	cFood();
	~cFood();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};

class cLife : public cObject
	//------------------------------------
{
public:
	cLife();
	~cLife();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};

class cEnemy: public cObject
	//------------------------------------
{
public:
	cEnemy(int status);
	~cEnemy();

	enum StatusID_ {
		SUPERDUMB,
		DUMB,
		RANDOM,
		NASTY
	};

	void handleEvent(SDL_Event& e) {};
	void update();
	void render(SDL_Renderer* renderer);
	void SetDirection(int dir);
	int GetDirection();
};

//------------------------------------
// World objects
//------------------------------------

class cLevelEntrance: public cObject
	//------------------------------------
{
public:
	cLevelEntrance(int LevelID);
	~cLevelEntrance();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);

	int LevelID;
};

class cPathHor: public cObject
	//------------------------------------
{
public:
	cPathHor();
	~cPathHor();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};

class cPathVer : public cObject
	//------------------------------------
{
public:
	cPathVer();
	~cPathVer();

	void handleEvent(SDL_Event& e) {};
	void update() {};
	void render(SDL_Renderer* renderer);
};


//------------------------------------------
// Support functions
//------------------------------------------

void RenderObjectDefault(SDL_Renderer* renderer, int objtype, float x, float y, float w = 0, float h = 0, int status = 0);

void RenderDrawCircle(SDL_Renderer* renderer, float centreX, float centreY, float radius);
void RenderFillCircle(SDL_Renderer* renderer, float centreX, float centreY, float radius);

//Box collision detector
bool CheckCollision(SDL_Rect a, SDL_Rect b);

void PlaySound(unsigned int objtype);
