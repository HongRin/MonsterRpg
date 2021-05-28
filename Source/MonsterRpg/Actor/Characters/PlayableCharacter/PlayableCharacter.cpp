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

	// ĳ���� �⺻ ��ġ / ȸ�� ����
	GetMesh()->SetRelativeLocationAndRotation(
		FVector::DownVector * 88.0f,
		FRotator(0.0f, -90.0f, 0.0f));

	// �� ������ ȸ���� ��Ʈ�ѷ��� Yaw ȸ���� ������� �ʵ��� �մϴ�.
	bUseControllerRotationYaw = false;

	// �̵��ϴ� �������� ĳ���͸� ȸ����ŵ�ϴ�.
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// ȸ�� �ӵ��� �����մϴ�.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 450.0f, 0.0f);

	WalkSpeed = 300.0f;
	RunSpeed = 600.0f;

	InitailizeComponents();
}

void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ���߿��� ĳ���͸� 80% ���� �����ϵ��� �մϴ�.
	GetCharacterMovement()->AirControl = 0.8f;

	// ĳ���Ͱ� �޴� �߷� ����
	GetCharacterMovement()->GravityScale = 2.5f;

	// ���� �ʱ� ���ӷ� ����
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

	// Spring Arm Component �� ��Ʈ ������Ʈ�� �߰��մϴ�.
	SpringArm->SetupAttachment(GetRootComponent());

	// Camera Component �� SpringArm ������Ʈ�� �߰��մϴ�.
	Camera->SetupAttachment(SpringArm);

	// ��Ʈ�ѷ��� ȸ������ SpringArm Component ȸ�������� ����մϴ�.
	SpringArm->bUsePawnControlRotation = true;

	// ��Ʈ�ѷ��� ȸ���� Yaw, Pitch ȸ���� ����մϴ�.
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
	// ��Ʈ�ѷ� ȸ���� Yaw ȸ������ �����մϴ�.
	FRotator yawRotation(0.0f, GetControlRotation().Yaw, 0.0f);

	// ��Ʈ�ѷ� ���� ������ ������ �����մϴ�.
	FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	// FRotationMatrix : ȸ���� ��ǥ�� ������ �����ϴ� ����� ��Ÿ���ϴ�.
	// GetUnitAxis(EAxis) : EAxis �������� ������ ��ȯ�մϴ�.

	AddMovementInput(rightVector, axis);
}

void APlayableCharacter::InputVertical(float axis)
{
	// ��Ʈ�ѷ� ȸ���� Yaw ȸ�� ���
	FRotator yawRotation(0.0f, GetControlRotation().Yaw, 0.0f);

	// ��Ʈ�ѷ� ���� �� ���� ����
	FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(forwardVector, axis);
}
