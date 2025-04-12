// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/ItemUsing_AnimNotifyState.h"
#include "Character/SurvivalSciFi_Character.h"
#include "Item/EquipableItem.h"
#include "Item/EquipableSkItem.h"

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
