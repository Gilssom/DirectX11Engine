#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CLevel : public CEntity
{
private:
	CLayer* m_arrLayer[MAX_LAYER];


public:
<<<<<<< Updated upstream
	void Begin();
=======
<<<<<<< HEAD
	void Init();
=======
	void Begin();
>>>>>>> a41b0ec58dbec60568cd283e74472e1a6b6b4fa3
>>>>>>> Stashed changes
	void Tick();
	void FinalTick();
	void Render();


public:
	void AddObject(UINT layerIdx, CGameObject* object);

<<<<<<< Updated upstream

=======
<<<<<<< HEAD
=======

>>>>>>> a41b0ec58dbec60568cd283e74472e1a6b6b4fa3
>>>>>>> Stashed changes
public:
	CLevel();
	~CLevel();
};

