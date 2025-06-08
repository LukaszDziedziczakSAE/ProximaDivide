// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Animation/AnimNotify_LeftHandItemUse.h"
#include "Character/SurvivalSciFi_Character.h"
#include "Item/Equipment/EquipableItem.h"
#include "Item/Equipment/EquipableSkItem.h"

void UAnimNotify_LeftHandItemUse::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ASurvivalSciFi_Character* Character = MeshComp->GetOwner<ASurvivalSciFi_Character>();

	if (Character != nullptr && Character->GetLeftHandItem() != nullptr)
	{
		AEquipableItem* EquipableItem = Cast<AEquipableItem>(Character->GetLeftHandItem());
		if (EquipableItem != nullptr)
		{
			Character->ChangeStat(EquipableItem->GetChangeStatType(), EquipableItem->GetChangeStatAmount());
			EquipableItem->PlayUseSound();
		}

		AEquipableSkItem* EquipableSkItem = Cast<AEquipableSkItem>(Character->GetLeftHandItem());
		if (EquipableSkItem != nullptr)
		{
			Character->ChangeStat(EquipableSkItem->GetChangeStatType(), EquipableSkItem->GetChangeStatAmount());
			EquipableSkItem->PlayUseSound();
		}

		if (EquipableItem == nullptr && EquipableSkItem == nullptr)
			UE_LOG(LogTemp, Error, TEXT("Unable to cast left hand item into Equipable Item"));
	}
	else UE_LOG(LogTemp, Error, TEXT("%s Can't play left hand use sound"), *Animation->GetName());

}
