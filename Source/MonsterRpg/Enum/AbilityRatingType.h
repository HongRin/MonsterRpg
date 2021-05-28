#pragma once

#include "CoreMinimal.h"
#include "AbilityRatingType.generated.h"

UENUM(BlueprintType)
enum class EAbilityRatingType : uint8
{
	AR_NORMAL		UMETA(DisplayName = Normal),
	AR_RARE			UMETA(DisplayName = Rare),
	AR_UNIQUE		UMETA(DisplayName = Unique),
	AR_LEGENDARY	UMETA(DisplayName = Legendary)
};
