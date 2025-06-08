// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Animation/ItemUsing_AnimNotifyState.h"
#include "Character/SurvivalSciFi_Character.h"
#include "Item/Equipment/EquipableItem.h"
#include "Item/Equipment/EquipableSkItem.h"

void UItemUsing_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ASurvivalSciFi_Character* Character = MeshComp->GetOwner<ASurvivalSciFi_Character>();
	if (Character == nullptr) return;
	AEquipableItem* EquipableItem = Cast<AEquipableItem>(Character->GetRightHandItem());
	if (EquipableItem != nullptr) EquipableItem->TurnOnColliderOverlap();

}

void UItemUsing_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ASurvivalSciFi_Character* Character = MeshComp->GetOwner<ASurvivalSciFi_Character>();
	if (Character == nullptr) return;
	AEquipableItem* EquipableItem = Cast<AEquipableItem>(Character->GetRightHandItem());
	if (EquipableItem != nullptr) EquipableItem->TurnOffColliderOverlap();
}
