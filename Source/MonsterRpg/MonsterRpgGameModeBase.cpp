#include "MonsterRpgGameModeBase.h"

#include "Actor/Characters/PlayableCharacter/PlayableCharacter.h"
#include "Actor/Controllers/PlayableController/PlayableController.h"

AMonsterRpgGameModeBase::AMonsterRpgGameModeBase()
{
	DefaultPawnClass = APlayableCharacter::StaticClass();
	PlayerControllerClass = APlayableController::StaticClass();
}