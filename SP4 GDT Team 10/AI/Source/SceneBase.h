#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include "GameObject.h"
#include "DepthFBO.h"
#include "LoadTGA.h"
#include <vector>

class SceneBase : public Scene
{
public:

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_TYPE,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE1_ENABLED,
		U_COLOR_TEXTURE2_ENABLED,
		U_COLOR_TEXTURE3_ENABLED,
		U_COLOR_TEXTURE4_ENABLED,
		U_COLOR_TEXTURE5_ENABLED,
		U_COLOR_TEXTURE6_ENABLED,
		U_COLOR_TEXTURE7_ENABLED,
		U_COLOR_TEXTURE,
		U_COLOR_TEXTURE1,
		U_COLOR_TEXTURE2,
		U_COLOR_TEXTURE3,
		U_COLOR_TEXTURE4,
		U_COLOR_TEXTURE5,
		U_COLOR_TEXTURE6,
		U_COLOR_TEXTURE7,
		U_UV_OFFSET,
		U_FOG_COLOR,
		U_FOG_START,
		U_FOG_END,
		U_FOG_DENSITY,
		U_FOG_TYPE,
		U_FOG_ENABLED,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_LIGHT_DEPTH_MVP_GPASS,
		U_LIGHT_DEPTH_MVP,
		U_SHADOW_MAP,
		U_SHADOW_COLOR_TEXTURE,
		U_SHADOW_COLOR_TEXTURE1,
		U_SHADOW_COLOR_TEXTURE2,
		U_SHADOW_COLOR_TEXTURE3,
		U_SHADOW_COLOR_TEXTURE4,
		U_SHADOW_COLOR_TEXTURE5,
		U_SHADOW_COLOR_TEXTURE6,
		U_SHADOW_COLOR_TEXTURE7,
		U_SHADOW_COLOR_TEXTURE_ENABLED,
		U_SHADOW_COLOR_TEXTURE_ENABLED1,
		U_SHADOW_COLOR_TEXTURE_ENABLED2,
		U_SHADOW_COLOR_TEXTURE_ENABLED3,
		U_SHADOW_COLOR_TEXTURE_ENABLED4,
		U_SHADOW_COLOR_TEXTURE_ENABLED5,
		U_SHADOW_COLOR_TEXTURE_ENABLED6,
		U_SHADOW_COLOR_TEXTURE_ENABLED7,
		U_ALPHA,
		U_TOTAL,
	};
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_LIGHT_DEPTH_QUAD,
		GEO_TEXT,
		GEO_BALL,
		GEO_CUBE,
		GEO_BG,
		GEO_TICTACTOE,
		GEO_CROSS,
		GEO_CIRCLE,
		GEO_REVERSI,
		GEO_BLACK,
		GEO_WHITE,
		GEO_TOOFULL,
		GEO_FULL,
		GEO_HUNGRY,
		GEO_DEAD,
		GEO_SHARK,
		GEO_FISHFOOD,
		GEO_CRAZY,
		GEO_HAPPY,
		GEO_CHESSBOARD,
		GEO_QUEEN,

		GEO_SOLDIER,
		GEO_COMMANDER,
		GEO_CAVALRY,
		GEO_ANIMAL,
		GEO_KING,

		GEO_WHITEQUAD,
		GEO_GREYQUAD,
		GEO_BLACKQUAD,

		GEO_BLACKHEX,
		GEO_WHITEHEX,
		GEO_GREYHEX,

		GEO_GREENQUAD,
		GEO_REDQUAD,
		GEO_YELLOWQUAD,

		GEO_LINE,
		GEO_RAY_WHITE,

		GEO_RED_TRIANGLE,
		GEO_BLUE_TRIANGLE,

		GEO_RED_MELEE,
		GEO_RED_CASTER,
		GEO_RED_TOWER,
		GEO_BLUE_MELEE,
		GEO_BLUE_CASTER,
		GEO_BLUE_TOWER,

		GEO_HAND_DEFAULT,
		GEO_HAND_GRAB,
		GEO_HAND_POINT,

		GEO_EFFECT_CLOUD,

		GEO_RETICLE,
		GEO_RETICLE_CROSS,

		GEO_ISLAND,
		GEO_GRASS,
		GEO_SEA,
		GEO_VILLAGER,
		GEO_TREE,
		GEO_HALFTREE,
		GEO_BUSH,
		GEO_BERRIES,
		GEO_BUILDING,
		GEO_BROKEN_BUILDING,
		GEO_ALTAR,
		GEO_MOUNTAIN,
		GEO_LOGS,
		GEO_GRANARY,
		GEO_BROKEN_GRANARY,
		GEO_WOODSHED,
		GEO_BROKEN_WOODSHED,
		GEO_HATCHET,
		GEO_BASKET,
		GEO_HAMMER,
		GEO_PICKAXE,
		GEO_TSUNAMI,

		GEO_BACKGROUND,
		GEO_SPLASHSCREEN,	// opengl
		GEO_LOGO,			// game logo
		GEO_BACKBUTTON,
		GEO_STARTBUTTON,
		GEO_OPTIONSBUTTON,
		GEO_QUITBUTTON,

		GEO_WOODRESEARCH,
		GEO_STONERESEARCH,
		GEO_FULLSTONERESEARCH,
		GEO_RESEARCHTICK,

		GEO_TEXT_GUNGSUH,
		GEO_UI_BOARD_BLANK,
		GEO_UI_BOARD_FOOD,
		GEO_UI_BOARD_DAY,
		GEO_UI_BOARD_POPULATION,
		GEO_UI_BOARD_STONE,
		GEO_UI_BOARD_TIME,
		GEO_UI_BOARD_WOOD,

		GEO_GRID,

		GEO_OFFERING,

		NUM_GEOMETRY,
	};
	enum RENDER_PASS
	{
		RENDER_PASS_PRE,
		RENDER_PASS_MAIN,
	};
public:
	SceneBase();
	~SceneBase();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	virtual bool Handle(Message* message);

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMesh(Mesh *mesh, bool enableLight, float alpha = 1.0f);

	MS modelStack;
	MS viewStack;
	MS projectionStack;
	unsigned m_parameters[U_TOTAL];
	Mtx44 m_lightDepthProj;
	Mtx44 m_lightDepthView;
	RENDER_PASS m_renderPass;
	float m_worldWidth;
	float m_worldHeight;
protected:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_gPassShaderID;
	DepthFBO m_lightDepthFBO;

	Camera camera;

	Light lights[1];

	bool bLightEnabled;

	float fps;
};

#endif