#include "Font.h"



Font::Font()
{
	//_texture = CTextures::GetInstance()->GetTexture(eType::FONT);
	//_sprite = new CSprites(_texture, 0);
}


Font::~Font()
{ 
	SAFE_DELETE(_sprite);
}

void Font::Draw(float x, float y, const string & s)
{ 
	//for (UINT i = 0; i < s.size(); i++)
	//{
	//	if (s[i] == ' ')
	//		continue;
	//	if (s[i] >= 'A' && s[i] <= 'Z')
	//	{
	//		_sprite->SelectFrame(s[i] - 'A');
	//	}
	//	else
	//		if (s[i] >= '0' && s[i] <= '9')
	//		{
	//			_sprite->SelectFrame(s[i] - '0' + 26);
	//		}
	//		else
	//			_sprite->SelectFrame(36);
	//	_sprite->Draw(x + i * _texture->GetFrameWidth(), y);
	//}
}
