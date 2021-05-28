#include "PlayerAnimInstance.h"

#include "Actor/Characters/PlayableCharacter/PlayableCharacter.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float dt)
{
	Super::NativeUpdateAnimation(dt);

	Owner = Cast<APlayableCharacter>(TryGetPawnOwner());

	if (!IsValid(Owner)) return;

	VelocityLength = Owner->GetVelocity().Size();

	bIsInAir = Owner->IsInAir();
}
