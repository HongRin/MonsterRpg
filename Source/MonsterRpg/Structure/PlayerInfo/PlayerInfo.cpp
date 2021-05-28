#include "PlayerInfo.h"

FPlayerInfo::FPlayerInfo()
{
	MaxHp = Hp = 400.0f;
	
	Atk = 30.0f;
	
	Critical = 10.0f;
	
	ClassCode = FName(TEXT("0001"));
}
