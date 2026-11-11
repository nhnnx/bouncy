#ifndef ___Media_h_
#define ___Media_h_

//Using SDL, SDL_image, and strings
//#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <string>

// Global window and renderer
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Window* gWindowE;
extern SDL_Renderer* gRendererE;

// Fonts
extern TTF_Font* gFont;
extern TTF_Font* gFont48;

class LTexture;

// Objects sprites
extern LTexture txBumpy, txBumpyE;
extern LTexture txFood, txFoodE;
extern LTexture txEnemy, txEnemyE;
extern LTexture txLife, txLifeE;

extern LTexture txFloor, txFloorE;
extern LTexture txFloorUp, txFloorUpE;
extern LTexture txFloorDown, txFloorDownE;
extern LTexture txIce, txIceE;
extern LTexture txRight, txRightE;
extern LTexture txLeft, txLeftE;
extern LTexture txForced, txForcedE;
extern LTexture txDecision, txDecisionE;
extern LTexture txFake, txFakeE;
extern LTexture txInvisible, txInvisibleE;
extern LTexture txReduce1, txReduce1E;
extern LTexture txReduce2, txReduce2E;
extern LTexture txReduce3, txReduce3E;
extern LTexture txNways0, txNways0E;
extern LTexture txNways1, txNways1E;
extern LTexture txNways2, txNways2E;
extern LTexture txNways3, txNways3E;
extern LTexture txWall1, txWall1E;
extern LTexture txWall2, txWall2E;
extern LTexture txWall3, txWall3E;
extern LTexture txSpine, txSpineE;
extern LTexture txSpineDown, txSpineDownE;
extern LTexture txSpineV, txSpineVE;
extern LTexture txSpring, txSpringE;
extern LTexture txShooter, txShooterE;
extern LTexture txCloud, txCloudE;
extern LTexture txOneBounce, txOneBounceE;
extern LTexture txGlue, txGlueE;
extern LTexture txMagnetic, txMagneticE;
extern LTexture txCatapult, txCatapultE;
extern LTexture txTeleport, txTeleportE;
extern LTexture txFace1, txFace1E;

extern const int nTextures;
extern LTexture* TexturesE[];
extern int ObjTypesE[];

// Ssound effects
extern MIX_Audio* Sound_Bop;

//Texture wrapper class
class LTexture
	//------------------------------------------
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer* renderer = gRenderer);

#if defined(SDL_TTF_MAJOR_VERSION)
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer = gRenderer);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_FRect* clip = NULL, double angle = 0.0, SDL_FPoint* center = NULL, SDL_FlipMode flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

	// Get texture
	SDL_Texture* GetTexture() { return mTexture; };

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	SDL_Renderer* mRenderer;

	//Image dimensions
	int mWidth;
	int mHeight;
};


//Loads media
bool loadMedia();
void FreeMedia();


#endif // ___Media_h_