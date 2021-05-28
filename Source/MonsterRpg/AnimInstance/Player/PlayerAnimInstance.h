#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class MONSTERRPG_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	class APlayableCharacter* Owner;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float VelocityLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsInAir;


public:
	virtual void NativeUpdateAnimation(float dt) override;

};
