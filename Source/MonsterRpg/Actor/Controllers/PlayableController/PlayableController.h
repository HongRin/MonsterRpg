#pragma once

#include "MonsterRPG.h"
#include "GameFramework/PlayerController.h"
#include "Enum/InputModeType.h"
#include "PlayableController.generated.h"

UCLASS()
class MONSTERRPG_API APlayableController : public APlayerController
{
	GENERATED_BODY()

private:
	TSubclassOf<class UUIControllerWidget> BP_UIControllerWidget;

private:
	UPROPERTY()
	class UWndTogglerComponent* WndToggler;

protected:
	class UUIControllerWidget* UIControllerWidget;
	EInputModeType DefaultInputMode;
	bool bDefaultCursorVisibility;

public:
	APlayableController();

protected:
	virtual void OnPossess(APawn* aPawn) override;

	virtual void SetupInputComponent() override;

private:
	void RegisterToggleEvent();

private:
	// MouseX, MouseY 입력에 바인딩될 메서드
	void MouseXInput(float axis);
	void MouseYInput(float axis);

public:
	FORCEINLINE class UUIControllerWidget* GetWidgetControllerWidget() const
	{ return UIControllerWidget; }

	FORCEINLINE class UWndTogglerComponent* GetWndToggler() const
	{ return WndToggler; }

	FORCEINLINE EInputModeType GetDefaultInputMode() const
	{ return DefaultInputMode; }

	FORCEINLINE bool GetDefaultCursorVisibility() const
	{ return bDefaultCursorVisibility; }

	FORCEINLINE void SetInputModeFromNewInputModeType(EInputModeType newInputMode)
	{
		switch (newInputMode)
		{
		case EInputModeType::IM_GameOnly:	SetInputMode(FInputModeGameOnly());		break;
		case EInputModeType::IM_UIOnly:		SetInputMode(FInputModeUIOnly());		break;
		case EInputModeType::IM_GameAndUI:	SetInputMode(FInputModeGameAndUI());	break;
		}
	}

	FORCEINLINE void ChangeInputModeToDefault()
	{
		switch (DefaultInputMode)
		{
		case EInputModeType::IM_GameOnly:	SetInputMode(FInputModeGameOnly());		break;
		case EInputModeType::IM_UIOnly:		SetInputMode(FInputModeUIOnly());		break;
		case EInputModeType::IM_GameAndUI:	SetInputMode(FInputModeGameAndUI());	break;
		}
	}

	// 카메라 뷰 타깃을 변경합니다.
	/// - targetActor : 변경할 뷰 타깃 카메라 컴포넌트를 갖는 액터를 전달합니다.
	/// - blendTime : 블랜딩 시간을 전달합니다.
	void ChangeViewTarget(class AActor* targetActor, float blendTime = 0.5f);

	void ResetViewTarget(float blendTime = 0.5f);
	
};
