#pragma once
#include "UnitBase.h"
class EnemyUnit :
    public UnitBase
{
public:
    EnemyUnit();
    EnemyUnit(std::string unitFile, int unitNum);
    ~EnemyUnit();

    void Init(void)override;
    void Update(void)override;
    void Draw(void)override;
    //void Release(void);


};

