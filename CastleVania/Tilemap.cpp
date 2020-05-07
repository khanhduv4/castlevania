#include "Tilemap.h"
#include"Utils.h"
TiledMap* TiledMap::__instance = NULL;
TiledMap* TiledMap::GetCurrentMap() {
	return __instance;
}
TiledMap* TiledMap::Initialize(string infoPath, string tilesetPath)
{ 
	delete __instance; 
	__instance = new TiledMap(infoPath, tilesetPath);
	return __instance;
}



//-------------------
//Lấy dữ liệu đọc chuyển thành dòng trong ma trận
Row TiledMap::GetMatrixRow(int lineNum, string line, string delimiter)
{
	size_t pos = 0;
	string token;
	Row result = Row();
	int rowNum = 0;
	while ((pos = line.find(delimiter)) != string::npos)
	{
		token = line.substr(0, pos);
		Tile curTile;
		curTile.x = rowNum * tileSize;
		curTile.y = lineNum * tileSize;
		curTile.tileId = stoi(token);
		result.push_back(curTile);
		line.erase(0, pos + delimiter.length());
		rowNum++;
	}
	return result;
}
std::wstring s2ws(const string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
//-------------------

TiledMap::TiledMap(string infoPath, string tilesetPath)
{
	LoadMap(s2ws(infoPath).c_str(), s2ws(tilesetPath).c_str());
}
void TiledMap::LoadMap(LPCWSTR infoPath, LPCWSTR tilesetPath)
{
	LoadMatrix(infoPath);

	LoadTileSet(tilesetPath);
}
void TiledMap::LoadMatrix(LPCWSTR filePath)
{
	string rawTileSize;

	ifstream tilesInfo;
	tilesInfo.open(filePath);
	this->mapWidth = 0;
	this->mapHeight = 0;

	if (tilesInfo.is_open())
	{
		//Lay tile size
		getline(tilesInfo, rawTileSize);
		this->tileSize = stoi(rawTileSize);


		string tmp;
		//Đọc width của tileset
		getline(tilesInfo, tmp);
		this->tileSetSize = stoi(tmp) / (this->tileSize);
		//Đọc thông tin width, height của map
		getline(tilesInfo, tmp);
		this->mapWidth = stoi(tmp);
		//DebugOut(L"day la width ############################### %d", this->mapWidth);
		getline(tilesInfo, tmp);
		this->mapHeight = stoi(tmp);
		//Đọc map
		string line;
		Row matrixRow;

		this->matrix.clear();
		int lineNum = 0;
		while (getline(tilesInfo, line))
		{
			matrixRow = GetMatrixRow(lineNum, line, " ");

			this->matrix.push_back(matrixRow);

			lineNum++;
		}
		tilesInfo.close();
	}


}

//Cắt và đưa các tile vào mảng sprite chung
void TiledMap::LoadTileSet(LPCWSTR tilesLocation)
{
	CTextures::GetInstance()->Add(1000, tilesLocation, D3DCOLOR_XRGB(255, 0, 255));

	for (int i = 0; i < this->tileSetSize; i++)
	{
		RECT rect;
		rect.left = (i % this->tileSetSize) * tileSize;
		rect.right = rect.left + tileSize;
		rect.top = (i / this->tileSetSize) * tileSize;
		rect.bottom = rect.top + tileSize;

		CSprites::GetInstance()->Add(1000 + i, rect.left, rect.top, rect.right, rect.bottom, CTextures::GetInstance()->Get(1000));

	}
}


TiledMap::~TiledMap()
{

}

int TiledMap::GetWidth()
{
	return mapWidth;
}
int TiledMap::GetHeight()
{
	return mapHeight;
}



void TiledMap::Update(DWORD dt)
{

}
void TiledMap::Render()
{
	for (int i = 0; i < matrix.size(); i++)
	{
		Row curRow = matrix[i];
		for (int j = 0; j < curRow.size(); j++)
		{
			Tile curTile = curRow[j];
			CSprites::GetInstance()->Get(1000 + curTile.tileId)->Draw(curTile.x, curTile.y);
			/*DebugOut(L"\nRender tile at "  );
			string coord = to_string(curTile.x) + "-" + to_string(curTile.y);
			DebugOut(const_cast<wchar_t *>(std::wstring(coord.begin(), coord.end()).c_str()));*/
			 
		}
		
	}
}
