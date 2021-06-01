#pragma once

#include "MonsterRpg.h"
#include "UObject/NoExportTypes.h"
#include "Enum/InputModeType.h"
#include "Structure/AbilityInfo/AbilityInfo.h"
#include "AbilitySystem.generated.h"

UCLASS()
class MONSTERRPG_API UAbilitySystem : public UObject
{
	GENERATED_BODY()

private :
	TSubclassOf<class UAbilityListWnd> BP_AbilityListWnd;

private :
	UAbilityListWnd* AbilityListWnd;

public:
	UAbilitySystem();

public :
	class UAbilityListWnd* OpenAbilityListWnd(
		class UUIControllerWidget* uiController,
		EInputModeType changeInputMode = EInputModeType::IM_Default, bool bShowCursor = true);

	void CloseAbilityListWnd();

	void ToggleAbilityListWnd(class UUIControllerWidget* uiController);

};
