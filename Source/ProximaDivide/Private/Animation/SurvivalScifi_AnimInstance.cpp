// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Animation/SurvivalScifi_AnimInstance.h"
#include "Character/SurvivalSciFi_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Components/PaperdollComponent.h"
#include "Item/Equipment/EquipableItem.h"
#include "Item/Equipment/EquipableSkItem.h"

void USurvivalScifi_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Character = Cast<ASurvivalSciFi_Character>(GetOwningActor());
	
	if (Character == nullptr) return;
	UpdateHandsType();
	Character->GetPaperdollComponent()->OnSlotChange.AddDynamic(this, &USurvivalScifi_AnimInstance::UpdateHandsType);
}

void USurvivalScifi_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr) return;

	Speed = Character->GetCharacterMovement()->Velocity.Length();
}

void USurvivalScifi_AnimInstance::UpdateHandsType()
{
	AnimHandsType = Character->GetPaperdollComponent()->GetCurrentAnimHandsType();
}

void USurvivalScifi_AnimInstance::SpawnHandItems()
{
}

void USurvivalScifi_AnimInstance::DespawnHandItems()
{
	if (Character != nullptr)
	{
		Character->DespawnHandItems();
	}
}

void USurvivalScifi_AnimInstance::StartTalking()
{
	IsTalking = true;
}

void USurvivalScifi_AnimInstance::StopTalking()
{
	IsTalking = false;
}
