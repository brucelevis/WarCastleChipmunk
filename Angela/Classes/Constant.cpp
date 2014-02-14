#include "Constant.h"
#include "Monster.h"
#include "CCLayerParent.h"

USING_NS_CC;
cocos2d::extension::CCControlSlider* sliders[SLIDENUM];
int deckscount = 0;
bool gameresult = false;
int fontSizeBig = 24;
int fontSizeSmall = 16;
int fontSizeTiny = 8;
 float SPEEDRATIO = 2;
const char* slideratlas[] = {"slide_sel.png","slide_sel_darkred.png","slide_sel_lightblue.png","slide_sel_green.png",
							"slide_sel_orange.png","slide_sel_purple.png","slide_sel_pink.png"};
const char* sliderintro[] = {"HitPoint","maxVelocity","buildTime","Damage","FireRate","Price","FoodCap"};
const char* atlas[] = {"quirk1.png","zap1.png","munch1.png","dragon1.png","phoenix1.png","charlie1.png","miles1.png","neville1.png"};
const char* atlas2[] = {"quirk2.png","zap2.png","munch2.png","dragon2.png","phoenix2.png"};
const char* atlas_deck[] = {"deck_quirk.png","deck_zap.png","deck_munch.png","deck_dragon.png","deck_phoenix.png",
	"deck_charlie.png","deck_miles.png","deck_neville.png"};
const char* atlas_sel[] = {"deck_quirk_sel.png","deck_zap_sel.png","deck_munch_sel.png","deck_dragon_sel.png","deck_phoenix_sel.png",
	"deck_charlie_sel.png","deck_miles_sel.png","deck_neville_sel.png"};
bool selection[] = {false,false,false,false,false,false,false,false};
int values[2][9] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
const char* backgrounds[] = {"home.png","craft.png","background_universe.png","background_universe1.png",
	"background_comet1.png","background_earth1.png"};
const char* airplanes[] = {
	"airplane_def.png",
	"airplane1_def.png",
	"airplane2_def.png",
	"airplane3_def.png",
	"airplane4_def.png"
};
const char* airplanes_atk[] = {
	"airplane_atk.png",
	"airplane1_atk.png",
"airplane2_atk.png",
"airplane3_atk.png",
"airplane4_atk.png"
};
bool PAIDUSER = false;
float PAIDRATE = 0.1f;
int g_level = 1;
int xMARGIN = 26;
int yMARGIN = 26;
int yOffset = (720-640)/2;
int MAX_SELECTED = 4;
cocos2d::ccColor3B fontColor = ccc3(41,49,52);
//cocos2d::CCSpriteBatchNode *_batchNodes;
bool level_passed[]={true,false,false,false,false,false,false,false,false};
Effect effects[] = {
	{"bullet.plist","bullet.png",NULL},
	{"explosion1.plist","explosion1.png",NULL},
	{"aoe1.plist","aoe1.png",NULL},
	{"coldline1.plist","coldline1.png",NULL},
	{"5color.plist","5color.png",NULL},
	{"BoilingFoam.plist","BoilingFoam.png",NULL},
	{"BurstPile.plist","BurstPile.png",NULL},
	{"Flower.plist","Flower.png",NULL},
	{"Phoenix.plist","Phoenix.png",NULL},
	{"Comet.plist","Comet.png",NULL},
	{"LavaFlow.plist","LavaFlow.png",NULL},
	{"Galaxy.plist","Galaxy.png",NULL},
	{"ExplodingRing.plist","ExplodingRing.png",NULL},
	{"Spiral.plist","Spiral.png",NULL},
	{"Upsidedown.plist","Upsidedown.png",NULL},
};
Deck decks[] = {
	{
		{"",""},
		"",
		false,
		"",
		"pew.wav",
		0,
		0,
		true,
		NULL,
		NULL,
		//NULL,
		{
			10000,
			0,
			200,
			308.0f,
			2.0f,
			200,
			false,
			false,
			false,
			0
		}
	},
	{
		{"quirk1.png","quirk2.png"},
		"quirk_sel.png",
		false,
		"quirk",
		"smallHit.wav",
		50,
		2.0f,
		true,
		NULL,
		NULL,
		//NULL,
		{
			1056,
			75,
			75,
			110.0f,
			1.0f,
			25,
			true,
			false,
			false,
			4
		}
	},
	{
		{"zap1.png","zap2.png"},
		"zap_sel.png",
		false,
		"zap",
		"pew.wav",
		50,
		2.0f,
		true,
		NULL,
		NULL,
		//NULL,
		{
			492,
			40,
			40,
			286.0f,
			1.5f,
			100,
			false,
			true,
			false,
			4
		}
	},
	{
		{"munch1.png","munch2.png"},
		"munch_sel.png",
		false,
		"munch",
		"bigHit.wav",
		50,
		2.0f,
		true,
		NULL,
		NULL,
		//NULL,
		{
			422,
			75,
			75,
			308.0f,
			1.0f,
			50,
			true,
			false,
			true,
			4
		}
	},
	{
		{"dragon1.png","dragon2.png"},
		"dragon_sel.png",
		false,
		"dragon",
		"bigHit.wav",
		50,
		2.0f,
		true,	
		NULL,
		NULL,
		//NULL,
		{
			393,
			75,
			75,
			316.0f,
			1.0f,
			25,
			true,
			false,
			false,
			4
		}
	},
	{
		{"phoenix1.png","phoenix2.png"},
		"phoenix_sel.png",
		false,
		"phoenix",
		"bigHit.wav",
		50,
		2.0f,
		true,
		NULL,
		NULL,
		//NULL,
		{
			915,
			75,
			75,
			154.0f,
			1.0f,
			25,
			true,
			false,
			false,
			4
		}
	},
	{
		{"charlie1.png","charlie2.png"},
		"charlie_sel.png",
		false,
		"charlie",
		"bigHit.wav",
		50,
		2.0f,
		true,
		NULL,
		NULL,
		//NULL,
		{
			704.0f,
			40,
			40,
			220.0f,
			1.5f,
			100,
			false,
			true,
			false,
			4
		}
	}
	,
	{
		{"miles1.png","miles2.png"},
		"miles_sel.png",
		false,
		"miles",
		"bigHit.wav",
		50,
		2.0f,
		true,
		NULL,
		NULL,
		//NULL,
		{
			422.0f,
			40,
			40,
			308.0f,
			1.5f,
			100,
			true,
			false,
			false,
			4
		}
	}
	,
	{
		{"neville1.png","neville2.png"},
		"neville_sel.png",
		false,
		"neville",
		"bigHit.wav",
		50,
		2.0f,
		true,
		NULL,
		NULL,
		//NULL,
		{
			393,
			75,
			75,
			316.0f,
			1.0f,
			50,
			true,
			false,
			true,
			4
		}
	}
};
Deck bullet[]=	{
	{
		{"",""},
		"",
		false,
		"",
		"smallHit.wav",
		10,
		0.1f,
		false,
		NULL,
		NULL,
		//NULL,
		{
			10,
			50,
			50,
			5.0f,
			1.0f,
			0,
			true,
			false,
			false,
			4
		}
	}
};

Deck maxDeck[]=	{
	{
		{"",""},
		"",
		false,
		"",
		"smallHit.wav",
		50,
		1.0f,
		false,
		NULL,
		NULL,
		//NULL,
		{
			1056,
			100,
			100,
			316.f,
			1.0f,
			0,
			true,
			false,
			false,
			4
		}
	}
};
