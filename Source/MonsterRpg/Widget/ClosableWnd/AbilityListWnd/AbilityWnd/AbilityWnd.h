#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structure/AbilityInfo/AbilityInfo.h"
#include "AbilityWnd.generated.h"

UCLASS()
class MONSTERRPG_API UAbilityWnd : public UUserWidget
{
	GENERATED_BODY()

private :
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Type;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Description;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Background;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Sprite;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Select;

protected :
	virtual void NativeConstruct() override;

private :
	void InitializeRating(EAbilityRatingType abilityType);

public :
	void InitializeAbilityWnd(FAbilityInfo abilityInfo);

public :
	UFUNCTION()
	void OnClickedSelectButton();
};
