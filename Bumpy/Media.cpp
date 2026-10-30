#include "Media.h"
#include "Bumpy.h"

TTF_Font* gFont = NULL;
TTF_Font* gFont48 = NULL;

// Objects sprites
LTexture txBumpy,     txBumpyE;
LTexture txFood,      txFoodE;
LTexture txEnemy,     txEnemyE;
LTexture txLife,      txLifeE;

LTexture txIce,       txIceE;
LTexture txFloor,     txFloorE;
LTexture txFloorUp,   txFloorUpE;
LTexture txFloorDown, txFloorDownE;
LTexture txRight,     txRightE;
LTexture txLeft,      txLeftE;
LTexture txForced,    txForcedE;
LTexture txDecision,  txDecisionE;
LTexture txFake,      txFakeE;
LTexture txInvisible, txInvisibleE;
LTexture txReduce1,   txReduce1E;
LTexture txReduce2,   txReduce2E;
LTexture txReduce3,   txReduce3E;
LTexture txNways0,    txNways0E;
LTexture txNways1,    txNways1E;
LTexture txNways2,    txNways2E;
LTexture txNways3,    txNways3E;
LTexture txWall1,     txWall1E;
LTexture txWall2,     txWall2E;
LTexture txWall3,     txWall3E;
LTexture txSpine,     txSpineE;
LTexture txSpineDown, txSpineDownE;
LTexture txSpineV,    txSpineVE;
LTexture txSpring,    txSpringE;
LTexture txShooter,   txShooterE;
LTexture txCloud,     txCloudE;
LTexture txOneBounce, txOneBounceE;
LTexture txExit,      txExitE;
LTexture txGlue,      txGlueE;
LTexture txMagnetic,  txMagneticE;
LTexture txCatapult,  txCatapultE;
LTexture txTeleport,  txTeleportE;
LTexture txFace1,     txFace1E;

const int nTextures = 36;
LTexture* TexturesE[nTextures] = {
	// Centered:
	&txBumpyE, &txFoodE, &txEnemyE, &txLifeE,
	// Floors:
	&txFloorE,   &txIceE,       &txWall3E,    &txReduce2E,
	&txFloorUpE, &txFloorDownE, &txForcedE,   &txDecisionE,
	&txSpineE,   &txSpineDownE, &txSpringE,   &txOneBounceE,
	&txFakeE,    &txInvisibleE, &txCloudE,    &txExitE,
	&txGlueE,    &txMagneticE,  &txCatapultE, &txTeleportE,
	//Side
	&txFloorE, &txLeftE,   &txRightE,     &txNways3E,
	&txWall3E, &txSpineVE, &txInvisibleE, &txFakeE,
	&txShooterE, &txGlueE, &txIceE,       &txFace1E
};

int ObjTypesE[nTextures] = {
	// Centered:
	OBJ_Bumpy,       OBJ_Food,            OBJ_Enemy,          OBJ_Life,
	// Floors:
	OBJ_FLOOR_Plain, OBJ_FLOOR_Ice,       OBJ_FLOOR_Wall,     OBJ_FLOOR_Reducing,
	OBJ_FLOOR_Up,    OBJ_FLOOR_Down,      OBJ_FLOOR_Forced,   OBJ_FLOOR_Decision,
	OBJ_FLOOR_Spine, OBJ_FLOOR_SpineDown, OBJ_FLOOR_Spring,   OBJ_FLOOR_OneBounce,
	OBJ_FLOOR_Fake,  OBJ_FLOOR_Invisible, OBJ_FLOOR_Cloud,    OBJ_FLOOR_Exit,
	OBJ_FLOOR_Glue,  OBJ_FLOOR_Magnetic,  OBJ_FLOOR_Catapult, OBJ_FLOOR_Teleport,
	// Side:
	OBJ_SIDE_Plain,   OBJ_SIDE_LeftOnly, OBJ_SIDE_RightOnly, OBJ_SIDE_Nways,
	OBJ_SIDE_Wall,    OBJ_SIDE_Spine,    OBJ_SIDE_Invisible, OBJ_SIDE_Fake,
	OBJ_SIDE_Shooter, OBJ_SIDE_Glue,     OBJ_SIDE_Ice,       OBJ_SIDE_Face
};

// Sound effects
Mix_Chunk* Sound_Bop = NULL;  // reducing
Mix_Chunk* Sound_Tup = NULL;  // wall, spine?
Mix_Chunk* Sound_Flap = NULL; // only right/left, up/down
Mix_Chunk* Sound_Dum = NULL;  // plain
Mix_Chunk* Sound_Chom = NULL; // food
Mix_Chunk* Sound_Gnam = NULL; // food
Mix_Chunk* Sound_Chop = NULL; // nways
Mix_Chunk* Sound_Gnek = NULL; // decision
Mix_Chunk* Sound_Zam = NULL;  // shooter
Mix_Chunk* Sound_Wish = NULL; // ice
Mix_Chunk* Sound_Boin = NULL; // spring
Mix_Chunk* Sound_Ciaf = NULL; // catapult
Mix_Chunk* Sound_Bof = NULL;  // cloud?
Mix_Chunk* Sound_Win = NULL;  // exit?, teleport
Mix_Chunk* Sound_Tik = NULL;  // one bounce
Mix_Chunk* Sound_Wawa = NULL; // dead
Mix_Chunk* Sound_Glue = NULL; // glue

//---------------------------------
// Load media
//---------------------------------

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load textures
	success &= txBumpy.loadFromFile("Images/bumpy.png");		 success &= txBumpyE.loadFromFile("Images/bumpy.png", gRendererE);
	success &= txIce.loadFromFile("Images/ice.png");			 success &= txIceE.loadFromFile("Images/ice.png", gRendererE);
	success &= txFloor.loadFromFile("Images/floor.png");		 success &= txFloorE.loadFromFile("Images/floor.png", gRendererE);
	success &= txFloorUp.loadFromFile("Images/up.png");			 success &= txFloorUpE.loadFromFile("Images/up.png", gRendererE);
	success &= txFloorDown.loadFromFile("Images/down.png");		 success &= txFloorDownE.loadFromFile("Images/down.png", gRendererE);
	success &= txRight.loadFromFile("Images/right.png");		 success &= txRightE.loadFromFile("Images/right.png", gRendererE);
	success &= txLeft.loadFromFile("Images/left.png");			 success &= txLeftE.loadFromFile("Images/left.png", gRendererE);
	success &= txForced.loadFromFile("Images/forced.png");		 success &= txForcedE.loadFromFile("Images/forced.png", gRendererE);
	success &= txDecision.loadFromFile("Images/decision.png");	 success &= txDecisionE.loadFromFile("Images/decision.png", gRendererE);
	success &= txFake.loadFromFile("Images/fake.png");			 success &= txFakeE.loadFromFile("Images/fake.png", gRendererE);
	success &= txInvisible.loadFromFile("Images/invisible.png"); success &= txInvisibleE.loadFromFile("Images/invisible.png", gRendererE);
	success &= txReduce1.loadFromFile("Images/reduce1.png");	 success &= txReduce1E.loadFromFile("Images/reduce1.png", gRendererE);
	success &= txReduce2.loadFromFile("Images/reduce2.png");	 success &= txReduce2E.loadFromFile("Images/reduce2.png", gRendererE);
	success &= txReduce3.loadFromFile("Images/reduce3.png");	 success &= txReduce3E.loadFromFile("Images/reduce3.png", gRendererE);
	success &= txNways0.loadFromFile("Images/nways0.png");		 success &= txNways0E.loadFromFile("Images/nways0.png", gRendererE);
	success &= txNways1.loadFromFile("Images/nways1.png");		 success &= txNways1E.loadFromFile("Images/nways1.png", gRendererE);
	success &= txNways2.loadFromFile("Images/nways2.png");		 success &= txNways2E.loadFromFile("Images/nways2.png", gRendererE);
	success &= txNways3.loadFromFile("Images/nways3.png");		 success &= txNways3E.loadFromFile("Images/nways3.png", gRendererE);
	success &= txWall1.loadFromFile("Images/wall1.png");		 success &= txWall1E.loadFromFile("Images/wall1.png", gRendererE);
	success &= txWall2.loadFromFile("Images/wall2.png");		 success &= txWall2E.loadFromFile("Images/wall2.png", gRendererE);
	success &= txWall3.loadFromFile("Images/wall3.png");		 success &= txWall3E.loadFromFile("Images/wall3.png", gRendererE);
	success &= txSpine.loadFromFile("Images/spineh.png");		 success &= txSpineE.loadFromFile("Images/spineh.png", gRendererE);
	success &= txSpineDown.loadFromFile("Images/spineh2.png");	 success &= txSpineDownE.loadFromFile("Images/spineh2.png", gRendererE);
	success &= txSpineV.loadFromFile("Images/spinev.png");		 success &= txSpineVE.loadFromFile("Images/spinev.png", gRendererE);
	success &= txSpring.loadFromFile("Images/spring.png");		 success &= txSpringE.loadFromFile("Images/spring.png", gRendererE);
	success &= txShooter.loadFromFile("Images/shooter.png");	 success &= txShooterE.loadFromFile("Images/shooter.png", gRendererE);
	success &= txCloud.loadFromFile("Images/cloud.png");		 success &= txCloudE.loadFromFile("Images/cloud.png", gRendererE);
	success &= txOneBounce.loadFromFile("Images/onebounce.png"); success &= txOneBounceE.loadFromFile("Images/onebounce.png", gRendererE);
	success &= txLife.loadFromFile("Images/life.png");			 success &= txLifeE.loadFromFile("Images/life.png", gRendererE);
	success &= txTeleport.loadFromFile("Images/teleport.png");	 success &= txTeleportE.loadFromFile("Images/teleport.png", gRendererE);
	success &= txGlue.loadFromFile("Images/glue.png");			 success &= txGlueE.loadFromFile("Images/glue.png", gRendererE);
	success &= txMagnetic.loadFromFile("Images/magnetic.png");	 success &= txMagneticE.loadFromFile("Images/magnetic.png", gRendererE);

	//Load sound effects
	Sound_Bop = Mix_LoadWAV("audio/bop.wav");
	if (Sound_Bop == NULL) success = false;

	//Open the font
	gFont = TTF_OpenFont("RetroGaming.ttf", 24);
	gFont48 = TTF_OpenFont("RetroGaming.ttf", 48);

//#ifdef _DEBUG
	return true;
//#endif // _DEBUG

	return success;
}

void FreeMedia()
{
	txBumpy.free();	    txBumpyE.free();
	txFloor.free();	    txFloorE.free();
	txFloorUp.free();   txFloorUpE.free();
	txFloorDown.free(); txFloorDownE.free();
	txIce.free();	    txIceE.free();
	txRight.free();	    txRightE.free();
	txLeft.free();	    txLeftE.free();
	txForced.free();    txForcedE.free();
	txDecision.free();  txDecisionE.free();
	txFake.free();	    txFakeE.free();
	txInvisible.free(); txInvisibleE.free();
	txReduce1.free();   txReduce1E.free();
	txReduce2.free();   txReduce2E.free();
	txReduce3.free();   txReduce3E.free();
	txNways0.free();    txNways0E.free();
	txNways1.free();    txNways1E.free();
	txNways2.free();    txNways2E.free();
	txNways3.free();    txNways3E.free();
	txWall1.free();	    txWall1E.free();
	txWall2.free();	    txWall2E.free();
	txWall3.free();	    txWall3E.free();
	txSpine.free();	    txSpineE.free();
	txSpineDown.free(); txSpineDownE.free();
	txSpineV.free();    txSpineVE.free();
	txSpring.free();    txSpringE.free();
	txShooter.free();   txShooterE.free();
	txCloud.free();	    txCloudE.free();
	txOneBounce.free(); txOneBounceE.free();
	txLife.free();	    txLifeE.free();
	txTeleport.free();  txTeleportE.free();
	txGlue.free();	    txGlueE.free();
	txMagnetic.free();  txMagneticE.free();

	//Free the sound effects
	Mix_FreeChunk(Sound_Bop);

	//Free global font
	TTF_CloseFont(gFont);
	TTF_CloseFont(gFont48);
	gFont = NULL;
	gFont48 = NULL;
}

//------------------------------------------
// class LTexture
//------------------------------------------

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mRenderer = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		SDL_Log("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		//Color key image
		SDL_SetSurfaceColorKey(loadedSurface, true, SDL_MapSurfaceRGB(loadedSurface, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			// Set the renderer
			mRenderer = renderer;

			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_DestroySurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, textureText.c_str(), 0, textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL)
		{
			SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// Set the renderer
			mRenderer = renderer;

			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_DestroySurface(textSurface);
	}
	else
	{
		SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", SDL_GetError());
	}


	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mRenderer = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_FRect* clip, double angle, SDL_FPoint* center, SDL_FlipMode flip)
{
	//Set rendering space and render to screen
	SDL_FRect renderQuad = { (float)x, (float)y, (float)mWidth, (float)mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	bool ok = SDL_RenderTextureRotated(mRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
