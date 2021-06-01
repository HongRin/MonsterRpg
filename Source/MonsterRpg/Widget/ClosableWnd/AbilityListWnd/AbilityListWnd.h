#pragma once

#include "MonsterRpg.h"
#include "Widget/ClosableWnd/ClosableWnd.h"
#include "Enum/AbilityRatingType.h"
#include "AbilityListWnd.generated.h"

UCLASS()
class MONSTERRPG_API UAbilityListWnd : public UClosableWnd
{
	GENERATED_BODY()
	
private :
	TSubclassOf<class UAbilityWnd> BP_AbilityWnd;

private :
	class UDataTable* DT_AbilityInfo;

	class UAbilitySystem* AbilitySystem;

private :
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* HorizontalBox_AbilityList;

public :
	UAbilityListWnd(const FObjectInitializer& ObjInitializer);

protected :
	virtual void NativeConstruct() override;

private:
	void InitializeAbilityList();
};
