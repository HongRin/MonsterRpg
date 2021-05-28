#include "PlayableCharacter.h"

#include "AnimInstance/Player/PlayerAnimInstance.h"

#include "Component/ZoomableSpringArm/ZoomableSpringArmComponent.h"

#include "Single/GameInstance/MRPGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

APlayableCharacter::APlayableCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MESH(
		TEXT("SkeletalMesh'/Game/Resource/Characters/Friendly/Mesh/SK_Mushroom.SK_Mushroom'"));
	if (SK_MESH.Succeeded()) GetMesh()->SetSkeletalMesh(SK_MESH.Object);

	 static ConstructorHelpers::FClassFinder<UPlayerAnimInstance> BP_PLAYER_CHARACTER_ANIM_INST(
	 	TEXT("AnimBlueprint'/Game/Blueprints/Actor/Player/AnimBP_Player.AnimBP_Player_C'"));
	 if (BP_PLAYER_CHARACTER_ANIM_INST.Succeeded()) BP_PlayerAnimInstance = BP_PLAYER_CHARACTER_ANIM_INST.Class;

	 
	 if (IsValid(BP_PlayerAnimInstance))
	 GetMesh()->SetAnimClass(BP_PlayerAnimInstance);

	// 캐릭터 기본 위치 / 회전 설정
	GetMesh()->SetRelativeLocationAndRotation(
		FVector::DownVector * 88.0f,
		FRotator(0.0f, -90.0f, 0.0f));

	// 이 액터의 회전이 컨트롤러의 Yaw 회전을 사용하지 않도록 합니다.
	bUseControllerRotationYaw = false;

	// 이동하는 방향으로 캐릭터를 회전시킵니다.
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 회전 속도를 지정합니다.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 450.0f, 0.0f);

	WalkSpeed = 300.0f;
	RunSpeed = 600.0f;

	InitailizeComponents();
}

void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 공중에서 캐릭터를 80% 제어 가능하도록 합니다.
	GetCharacterMovement()->AirControl = 0.8f;

	// 캐릭터가 받는 중력 설정
	GetCharacterMovement()->GravityScale = 2.5f;

	// 점프 초기 가속력 설정
	GetCharacterMovement()->JumpZVelocity = 1000.0f;

}

void APlayableCharacter::Tick(float DeltaTime)
{ Super::Tick(DeltaTime); }

void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed,
		this, &APlayableCharacter::RunKeyPressed);

	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released,
		this, &APlayableCharacter::RunKeyReleased);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed,
		this, &APlayableCharacter::JumpKeyPressed);

	PlayerInputComponent->BindAxis(TEXT("MouseWheel"),
		SpringArm, &UZoomableSpringArmComponent::ZoomCamera);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"),
		this, &APlayableCharacter::InputHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Vertical"),
		this, &APlayableCharacter::InputVertical);
}

void APlayableCharacter::InitailizeComponents()
{
	SpringArm = CreateDefaultSubobject<UZoomableSpringArmComponent>(TEXT("SPRING_ARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetConstraintAspectRatio(true);

	// Spring Arm Component 를 루트 컴포넌트에 추가합니다.
	SpringArm->SetupAttachment(GetRootComponent());

	// Camera Component 를 SpringArm 컴포넌트에 추가합니다.
	Camera->SetupAttachment(SpringArm);

	// 컨트롤러의 회전값을 SpringArm Component 회전값으로 사용합니다.
	SpringArm->bUsePawnControlRotation = true;

	// 컨트롤러의 회전중 Yaw, Pitch 회전을 사용합니다.
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritPitch = true;


	GetCapsuleComponent()->SetCapsuleHalfHeight(34.0f);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -28.0f));
}



void APlayableCharacter::RunKeyPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void APlayableCharacter::RunKeyReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayableCharacter::JumpKeyPressed()
{
	Jump();
}

void APlayableCharacter::InputHorizontal(float axis)
{
	// 컨트롤러 회전중 Yaw 회전만을 저장합니다.
	FRotator yawRotation(0.0f, GetControlRotation().Yaw, 0.0f);

	// 컨트롤러 기준 오른쪽 방향을 저장합니다.
	FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	// FRotationMatrix : 회전된 좌표계 정보를 저장하는 행렬을 나타냅니다.
	// GetUnitAxis(EAxis) : EAxis 축으로의 방향을 반환합니다.

	AddMovementInput(rightVector, axis);
}

void APlayableCharacter::InputVertical(float axis)
{
	// 컨트롤러 회전중 Yaw 회전 얻기
	FRotator yawRotation(0.0f, GetControlRotation().Yaw, 0.0f);

	// 컨트롤러 기준 앞 방향 저장
	FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(forwardVector, axis);
}
