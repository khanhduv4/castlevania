#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include"Tilemap.h"
#include "Torch.h"
#include "UpgradeMorningStar.h"
#include "GameBoard.h"
#include "CBurningEffect.h"


using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_TILEMAP 7 

#define OBJECT_TYPE_SIMON	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_TORCH	2
#define OBJECT_TYPE_WEAPON_MORNINGSTAR	3

#define OBJECT_TYPE_PORTAL 99

#define MAX_SCENE_LINE 1024


void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}
void CPlayScene::_ParseSection_TILEMAP(string line) {
	vector<string> tokens = split(line);
	if (tokens.size() != 2)
		return;
	TiledMap::Initialize(tokens[0], tokens[1]);
	DebugOut(L"Loaded map");
}
void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}
void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}
void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_SIMON:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CSimon(x, y);
		player = (CSimon*)obj;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	case OBJECT_TYPE_TORCH: obj = new CTorch(); break;

	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}
void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[TILEMAP]") {
			section = SCENE_SECTION_TILEMAP; continue;
		}

		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_TILEMAP: _ParseSection_TILEMAP(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"Resources\\textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	//Load UI
	CGameBoard::GetIntance()->Load();
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}
void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;


	CheckCollisionWeaponWithObject(dt, &coObjects);


	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	CGame* game = CGame::GetInstance();

	float mapWidth = TiledMap::GetCurrentMap()->GetWidth();

	if (cx > game->GetScreenWidth() / 2)
		cx -= game->GetScreenWidth() / 2;
	else cx = 0;
	if (cx + game->GetScreenWidth() >= mapWidth - 15)
		cx = mapWidth - 15   - game->GetScreenWidth();

	DebugOut(L"Map width = %f ", mapWidth);
	cy -= game->GetScreenHeight() / 2;
	game->SetCamPos(cx, 0.f);
}
void CPlayScene::Render()
{
	TiledMap::GetCurrentMap()->Render();
	CGameBoard::GetIntance()->Render();
	int simon_Index = -1;
	for (int i = 0; i < objects.size(); i++) {
		if (dynamic_cast<CSimon*>(objects[i]))
		{
			simon_Index = i;
			continue;
		}
		objects[i]->Render();
	}
	if (simon_Index != -1)
		objects[simon_Index]->Render();
}
void CPlayScene::CheckCollisionWeaponWithObject(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	auto morStar = player->getMorningStar();

	if (morStar->IsActive()) {
		for (UINT i = 0; i < coObjects->size(); i++) {
			if (dynamic_cast<CTorch*>((*coObjects)[i])) {
				if (morStar->isCollision((*coObjects)[i])) {
					auto torch = dynamic_cast<CTorch*>((*coObjects)[i]);
					float x = 0, y = 0;

					torch->GetPosition(x, y);

					torch->Disappear();
					auto fire = new CBurningEffect(x, y);
				}
			}
		}
	}
}
/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}
void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{

	CSimon* simon = ((CPlayScene*)scence)->GetPlayer();
	if (simon->IsAttacking()) return;

	switch (KeyCode)
	{
	case DIK_SPACE:
		if (simon->IsSitting()) return;
		simon->SetState(SIMON_STATE_JUMPING);
		break;
	case DIK_S:
		simon->SetState(SIMON_STATE_ATTACKING);
		simon->Attack();
		break;

	case DIK_A:
		simon->Reset();
		break;
	}
}
void CPlayScenceKeyHandler::OnKeyUp(int KeyCode) {
	CSimon* simon = ((CPlayScene*)scence)->GetPlayer();

	if (KeyCode == DIK_DOWN) {
		simon->setSitting(0);
	}
}
void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CSimon* simon = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when SIMON
	if (simon->GetState() == SIMON_STATE_DIE) return;

	if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT)) {
		if (simon->IsAttacking()) return;

		simon->SetState(SIMON_STATE_WALKING);
		if (game->IsKeyDown(DIK_RIGHT)) simon->setDirection(1);
		else simon->setDirection(-1);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		if (simon->IsJumping()) return;
		simon->SetState(SIMON_STATE_SITTING);
	}
	else
		simon->SetState(SIMON_STATE_IDLE);
}