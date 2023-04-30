#pragma once
#include "UnitBase.h"
class PlayerUnit :
    public UnitBase
{
public:
    PlayerUnit();
    PlayerUnit(std::string unitFile,int unitNum);
    ~PlayerUnit();

    void Init(void);
    void Update(void);
    void Draw(void);
    //void Release(void);


private:
};

