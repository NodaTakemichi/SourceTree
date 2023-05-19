#include<DxLib.h>
#include "Grid.h"

Grid::Grid(void)
{
}

Grid::~Grid(void)
{
}

void Grid::Init(void)
{
}

void Grid::Update(void)
{
}

void Grid::Draw(void)
{
	//ƒOƒŠƒbƒh‚Ì•`‰æ
	for (int i = 0; i < NUM; i++)
	{
		//Z
		VECTOR start = { -600.0f,0.0f,-HLEN };
		VECTOR end = { -600.0f,0.0f,HLEN };
		DrawLine3D({ start.x + i * TERM, start.y, start.z },
					{ end.x + i * TERM, end.y, end.z }, 0x0000ff);
		DrawSphere3D({ end.x + i * TERM, end.y, end.z }, 20.0f, 10, 0x0000ff, 0x0000ff, true);

		//X
		start = { -HLEN,0.0f,-550.0f };
		end = { HLEN,0.0f,-550.0f };
		DrawLine3D({ start.x , start.y, start.z + i * TERM },
					{ end.x, end.y, end.z + i * TERM }, 0xff0000);
		DrawSphere3D({ end.x, end.y, end.z + i * TERM }, 20.0f, 10, 0xff0000, 0xff0000, true);

		
	}
}

void Grid::Release(void)
{
}
