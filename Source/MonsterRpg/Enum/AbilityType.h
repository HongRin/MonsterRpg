#pragma once

#include "CoreMinimal.h"
#include "AbilityType.generated.h"

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	AT_INCREASEATK				UMETA(DisplayName = IncreaseAtk),
	AT_INCREASEHP				UMETA(DisplayName = IncreaseHp),
	AT_INCREASECRITICAL    		UMETA(DisplayName = IncreaseCritical),
	AT_PASSIVE					UMETA(DisplayName = Passive),
	AT_REDUCTIONATKATK			UMETA(DisplayName = ReductionAtk),
	AT_REDUCTIONATKHP			UMETA(DisplayName = ReductionHp),
	AT_REDUCTIONATKCRITICAL		UMETA(DisplayName = ReductionCritical)
};
