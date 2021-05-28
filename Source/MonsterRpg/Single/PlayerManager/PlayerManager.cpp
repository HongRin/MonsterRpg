#include "PlayerManager.h"
#include "Actor/Characters/PlayableCharacter/PlayableCharacter.h"
#include "Actor/Controllers/PlayableController/PlayableController.h"

void UPlayerManager::RegisterPlayer(APlayableController* newPlayableController, APlayableCharacter* newPlayableCharacter)
{
	PlayableController = newPlayableController;
	PlayableCharacter = newPlayableCharacter;
}

void UPlayerManager::InitManagerClass()
{

}

void UPlayerManager::ShutdownManagerClass()
{

}
