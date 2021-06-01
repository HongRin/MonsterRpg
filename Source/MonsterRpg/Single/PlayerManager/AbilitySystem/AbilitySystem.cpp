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
		// �̹� �κ��丮 â�� ����� �ִٸ� ����� �κ��丮 â�� ��ȯ�մϴ�.
	if (IsValid(AbilityListWnd)) return AbilityListWnd;

	// �κ��丮 â�� �����մϴ�.
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

