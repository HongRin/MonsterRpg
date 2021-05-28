#pragma once

#include "CoreMinimal.h"
#include "PlayerInfo.generated.h"

// 플레이어의 정보를 담는 구조체입니다.

USTRUCT()
struct MONSTERRPG_API FPlayerInfo
{

	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY()
	float MaxHp;

	UPROPERTY()
	float Hp;

	UPROPERTY()
	float Atk;

	UPROPERTY()
	float Critical;

	// 캐릭터의 유형을 나타내는 코드입니다.
	UPROPERTY()
	FName ClassCode;

	UPROPERTY()
	FName SkillReinforceCode;

	FPlayerInfo();
};
