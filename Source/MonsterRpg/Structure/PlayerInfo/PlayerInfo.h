#pragma once

#include "CoreMinimal.h"
#include "PlayerInfo.generated.h"

// �÷��̾��� ������ ��� ����ü�Դϴ�.

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

	// ĳ������ ������ ��Ÿ���� �ڵ��Դϴ�.
	UPROPERTY()
	FName ClassCode;

	UPROPERTY()
	FName SkillReinforceCode;

	FPlayerInfo();
};