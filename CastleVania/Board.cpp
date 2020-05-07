﻿#include "Board.h"
 
string Board::FillNumber(string s, UINT MaxNumber)
{ 
	while (s.size() < MaxNumber)
		s = "0" + s;
	return s;
} 

Board::Board(float X, float Y)
{
 //	_texture = TextureManager::GetInstance()->GetTexture(eType::BOARD);
	//_sprite = new GSprite(_texture, 0);

	//_spriteIconDoubleShot = new GSprite(TextureManager::GetInstance()->GetTexture(eType::ITEMDOUBLESHOT), 0);

	//x = X;
	//y = Y;

	//_boardHealth = new BoardHealth(x + 110, y + 30);
}
 

void Board::Render(CSimon * simon , int state, int RemainingTime, CGameObject * boss)
{  
	//_sprite->Draw(x,y); 

 //	_font.Draw(x + 100, y + 15, FillNumber(std::to_string(simon->GetScore()), 6));
	// 2
 //	_font.Draw(x + 295, y + 15, FillNumber(std::to_string(RemainingTime), 4));

	//_font.Draw(x + 465, y + 15, FillNumber(std::to_string(state),2));

	//_font.Draw(x + 393, y + 33, FillNumber(std::to_string(simon->GetHeartCollect()),2)); // Số lượng tim nhặt dc
	//_font.Draw(x + 393, y + 51, FillNumber(std::to_string(simon->GetLives()),2)); // số mạng sông


	//int BloodBoss = 16; 
	//if (boss != NULL)
	//{
	//	BloodBoss = (int)(boss->GetHealth()* 16 / 24);// HEALTH =24 -> 16 vạch
	//	if (BloodBoss == 0 && boss->GetHealth() > 0)
	//		BloodBoss = 1;
	//}

	//_boardHealth->Draw(simon->GetHealth(), BloodBoss);


	//eType TypeWeaponCollect = simon->GetTypeWeaponCollect();
	//switch (TypeWeaponCollect)
	//{
	//case eType::DAGGER:
	//	simon->mapWeapon[TypeWeaponCollect]->RenderIcon(x + 310.0f, y + 40.0f);
	//	break;
	//case eType::HOLYWATER:
	//	simon->mapWeapon[TypeWeaponCollect]->RenderIcon(x + 312, y + 33);
	//	break;
	//case eType::STOPWATCH:
	//	simon->mapWeapon[TypeWeaponCollect]->RenderIcon(x + 312, y + 31);
	//	break;
	//case eType::THROWINGAXE:
	//	simon->mapWeapon[TypeWeaponCollect]->RenderIcon(x + 310, y + 35);
	//	break;
	//case eType::BOOMERANG:
	//	simon->mapWeapon[TypeWeaponCollect]->RenderIcon(x + 310, y + 35);
	//	break;
	//default:
	//	break;
	//}

	//if (simon->GetIsUseDoubleShot())
	//{
	//	_spriteIconDoubleShot->Draw(x + 465, y + 35);
	//}
}


Board::~Board()
{
	SAFE_DELETE(_sprite);
}

void Board::SetTexture(CTextures * tex)
{
	//_texture = tex;
	//_sprite->texture = tex; 
}
