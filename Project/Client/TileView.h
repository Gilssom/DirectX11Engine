#pragma once
#include "TileMapSubUI.h"

// �ڽ� UI �� �ƴ�, ������ ������ �����ִ� �������� UI
// (��, �ش� â �� ������ Tile Map Editor �� ���������� ������)

class TileView : public TileMapSubUI
{
private:

public:
	virtual void Render_Tick() override;

public:
	TileView();
	~TileView();
};

