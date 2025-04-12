// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/AnimNotify_LeftHandItemUse.h"
#include "Character/SurvivalSciFi_Character.h"
#include "Item/EquipableItem.h"
#include "Item/EquipableSkItem.h"

void UAnimNotify_LeftHandItemUse::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ASurvivalSciFi_Character* Character = MeshComp->GetOwner<ASurvivalSciFi_Character>();

	if (Character != nullptr && Character->GetLeftHandItem() != nullptr)
	{
		AEquipableItem* EquipableItem = Cast<AEquipableItem>(Character->GetLeftHandItem());
		if (EquipableItem != nullptr)
			EquipableItem->PlayUseSound();

		AEquipableSkItem* EquipableSkItem = Cast<AEquipableSkItem>(Character->GetLeftHandItem());
		if (EquipableSkItem != nullptr)
			EquipableSkItem->PlayUseSound();

		if (EquipableItem == nullptr && EquipableSkItem == nullptr)
			UE_LOG(LogTemp, Error, TEXT("Unable to cast left hand item into Equipable Item"));
	}
	else UE_LOG(LogTemp, Error, TEXT("Can play left hand use sound"));

}
