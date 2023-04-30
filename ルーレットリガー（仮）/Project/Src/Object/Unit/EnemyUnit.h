#pragma once
#include "UnitBase.h"
class EnemyUnit :
    public UnitBase
{
public:
    EnemyUnit();
    EnemyUnit(std::string unitFile, int unitNum);
    ~EnemyUnit();

    void Init(void);
    void Update(void);
    void Draw(void);
    //void Release(void);


};

