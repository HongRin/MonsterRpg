#pragma once

#include "MonsterRPG.h"
#include "Actor/Characters/BaseCharacter.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class MONSTERRPG_API APlayableCharacter : public ABaseCharacter
{
	GENERATED_BODY()

private:
	TSubclassOf<class UPlayerAnimInstance> BP_PlayerAnimInstance;

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UZoomableSpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

private :
	float WalkSpeed;
	float RunSpeed;

public :
	APlayableCharacter();

protected :
	virtual void BeginPlay() override;

public :
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private :
	void InitailizeComponents();

private:
	void RunKeyPressed();
	void RunKeyReleased();

	void JumpKeyPressed();

	void InputHorizontal(float axis);
	void InputVertical(float axis);


public :

	FORCEINLINE bool IsInAir() const
	{ return GetCharacterMovement()->IsFalling(); }
	FORCEINLINE class UZoomableSpringArmComponent* GetSpringArm() const
	{ return SpringArm; }
};
