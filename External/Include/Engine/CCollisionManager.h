#pragma once
#include "Singletone.h"

class CCollisionManager : public CSingleton<CCollisionManager>
{
	SINGLE(CCollisionManager)

private:
	UINT	 m_Matrix[(UINT)MAX_LAYER];


public:
	void Tick();


public:
	void LayerCheck(UINT layerLeftIndex, UINT layerRightIndex);


};

