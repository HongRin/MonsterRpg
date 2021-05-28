#include "PlayableController.h"
#include "Actor/Characters/PlayableCharacter/PlayableCharacter.h"

#include "Component/WndToggler/WndTogglerComponent.h"

#include "Single/GameInstance/MRPGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widget/UIControllerWidget/UIControllerWidget.h"

APlayableController::APlayableController()
{
	static ConstructorHelpers::FClassFinder<UUIControllerWidget> BP_UI_CONTROLLER_WIDGET(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/UIControllerWidget/BP_UIControllerWidget.BP_UIControllerWidget_C'"));
	if (BP_UI_CONTROLLER_WIDGET.Succeeded()) BP_UIControllerWidget = BP_UI_CONTROLLER_WIDGET.Class;
	else { UE_LOG(LogTemp, Error, TEXT("BasePlayerController.cpp :: %d LINE :: BP_WIDGET_CONTROLLER_WIDGET is not loaded!"), __LINE__); }

	WndToggler = CreateDefaultSubobject<UWndTogglerComponent>(TEXT("WND_TOGGLER"));

	DefaultInputMode = EInputModeType::IM_GameOnly;
	bDefaultCursorVisibility = false;
}

void APlayableController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	GetManager(UPlayerManager)->RegisterPlayer(this, Cast<APlayableCharacter>(aPawn));

	UIControllerWidget = CreateWidget<UUIControllerWidget>(this, BP_UIControllerWidget);
	UIControllerWidget->InitializeWidgetControllerWidget(this);
	UIControllerWidget->AddToViewport();

	RegisterToggleEvent();
}

void APlayableController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MouseX"), this, &APlayableController::MouseXInput);
	InputComponent->BindAxis(TEXT("MouseY"), this, &APlayableController::MouseYInput);
}

void APlayableController::RegisterToggleEvent()
{
}

void APlayableController::MouseXInput(float axis)
{
	AddYawInput(axis);
}

void APlayableController::MouseYInput(float axis)
{
	AddPitchInput(axis);
}

void APlayableController::ChangeViewTarget(AActor* targetActor, float blendTime)
{
	SetViewTargetWithBlend(targetActor, blendTime);
}

void APlayableController::ResetViewTarget(float blendTime)
{
	auto playableCharacter = GetManager(UPlayerManager)->GetPlayableCharacter();

	if (!IsValid(playableCharacter)) return;

	SetViewTargetWithBlend(playableCharacter, blendTime);
}
