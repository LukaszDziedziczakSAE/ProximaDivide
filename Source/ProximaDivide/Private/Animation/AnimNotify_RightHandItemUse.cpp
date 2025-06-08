// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Animation/AnimNotify_RightHandItemUse.h"
#include "Character/SurvivalSciFi_Character.h"
#include "Item/EquipableItem.h"
#include "Item/EquipableSkItem.h"

void UAnimNotify_RightHandItemUse::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ASurvivalSciFi_Character* Character = MeshComp->GetOwner<ASurvivalSciFi_Character>();

	if (Character != nullptr && Character->GetRightHandItem() != nullptr)
	{
		AEquipableItem* EquipableItem = Cast<AEquipableItem>(Character->GetRightHandItem());
		if (EquipableItem != nullptr)
		{
			Character->ChangeStat(EquipableItem->GetChangeStatType(), EquipableItem->GetChangeStatAmount());
			EquipableItem->PlayUseSound();
		}

		AEquipableSkItem* EquipableSkItem = Cast<AEquipableSkItem>(Character->GetRightHandItem());
		if (EquipableSkItem != nullptr)
		{
			Character->ChangeStat(EquipableSkItem->GetChangeStatType(), EquipableSkItem->GetChangeStatAmount());
			EquipableSkItem->PlayUseSound();
		}

		if (EquipableItem == nullptr && EquipableSkItem == nullptr)
			UE_LOG(LogTemp, Error, TEXT("Unable to cast right hand item into Equipable Item"));
	}
	else UE_LOG(LogTemp, Error, TEXT("%s Can't play right hand use sound"), *Animation->GetName());
}
