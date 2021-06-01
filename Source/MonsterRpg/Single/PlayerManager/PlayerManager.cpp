#include "PlayerManager.h"
#include "Single/PlayerManager/AbilitySystem/AbilitySystem.h"
#include "Actor/Characters/PlayableCharacter/PlayableCharacter.h"
#include "Actor/Controllers/PlayableController/PlayableController.h"

void UPlayerManager::RegisterPlayer(APlayableController* newPlayableController, APlayableCharacter* newPlayableCharacter)
{
	PlayableController = newPlayableController;
	PlayableCharacter = newPlayableCharacter;
}

void UPlayerManager::InitManagerClass()
{
	AbilitySystem = NewObject<UAbilitySystem>(this, UAbilitySystem::StaticClass(),
		NAME_None, EObjectFlags::RF_MarkAsRootSet);
}

void UPlayerManager::ShutdownManagerClass()
{
	if (!AbilitySystem->IsValidLowLevel()) return;
	AbilitySystem->ConditionalBeginDestroy();
}
