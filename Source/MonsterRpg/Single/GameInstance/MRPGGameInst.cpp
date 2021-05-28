#include "MRPGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

void UMRPGGameInst::RegisterManagerClass(TSubclassOf<UManagerClass> managerClass)
{
	UManagerClass* managerClassInstance = NewObject<UManagerClass>(this, managerClass,
		NAME_None, EObjectFlags::RF_MarkAsRootSet);
	/// - ������ ��ü�� GC �� �������� ���ϵ��� �մϴ�.

	managerClassInstance->InitManagerClass();

	ManagerClasses.Add(managerClass->GetName(), managerClassInstance);
}

void UMRPGGameInst::Init()
{
	Super::Init();

	RegisterManagerClass(UPlayerManager::StaticClass());
}

void UMRPGGameInst::Shutdown()
{
	for (auto pair : ManagerClasses)
	{
		// nullptr Ȯ��
		if (!pair.Value) return;

		// �ش� ��ü�� GC �� ���� ������ ��ü���� Ȯ���մϴ�.
		if (!pair.Value->IsValidLowLevel()) return;

		pair.Value->ShutdownManagerClass();

		// ��ü �Ҹ�
		pair.Value->ConditionalBeginDestroy();
	}
	ManagerClasses.Empty();

	Super::Shutdown();
}
