#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enum/AbilityType.h"
#include "Enum/AbilityRatingType.h"
#include "AbilityInfo.generated.h"

USTRUCT()
struct MONSTERRPG_API FAbilityInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 능력 코드
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName AbilityCode;

	// 능력 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText AbilityName;

	// 능력등급
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAbilityRatingType AbilityRating;

	// 능력 타입
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<EAbilityType> AbilityTypes;

	// 캐릭터 유형 코드
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ClassCode;

	// 능력 증가량
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<float> IncreaseValue;

	// 능력 이미지
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath AbilitySpritePath;

	// 능력 설명
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText AbilityDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsGain = true;
};
