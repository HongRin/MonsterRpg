#include "AbilitySystem.h"
#include "Widget/ClosableWnd/AbilityListWnd/AbilityListWnd.h"
#include "Widget/UIControllerWidget/UIControllerWidget.h"

UAbilitySystem::UAbilitySystem()
{
	static ConstructorHelpers::FClassFinder<UAbilityListWnd> BP_ABILITY_LIST_WND(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/AbilityWnd/BP_AbilityListWnd.BP_AbilityListWnd_C'"));
	if (BP_ABILITY_LIST_WND.Succeeded()) BP_AbilityListWnd = BP_ABILITY_LIST_WND.Class;
}

UAbilityListWnd* UAbilitySystem::OpenAbilityListWnd(UUIControllerWidget* uiController, EInputModeType changeInputMode, bool bShowCursor)
{
		// 이미 인벤토리 창이 띄워져 있다면 띄워진 인벤토리 창을 반환합니다.
	if (IsValid(AbilityListWnd)) return AbilityListWnd;

	// 인벤토리 창을 생성합니다.
	AbilityListWnd = Cast<UAbilityListWnd>(
		uiController->CreateWnd(BP_AbilityListWnd, true, changeInputMode, bShowCursor));
	AbilityListWnd->OnWndClosedEvent.AddLambda(
		[this](class UClosableWnd * closableWnd) 
		{ AbilityListWnd = nullptr;});

	return AbilityListWnd;
}

void UAbilitySystem::CloseAbilityListWnd()
{
	if (IsValid(AbilityListWnd))
	{
		AbilityListWnd->CloseThisWnd();
		AbilityListWnd = nullptr;
	}
}

void UAbilitySystem::ToggleAbilityListWnd(UUIControllerWidget* uiController)
{
	if (IsValid(AbilityListWnd)) CloseAbilityListWnd();
	else OpenAbilityListWnd(uiController, EInputModeType::IM_UIOnly, true);
}

