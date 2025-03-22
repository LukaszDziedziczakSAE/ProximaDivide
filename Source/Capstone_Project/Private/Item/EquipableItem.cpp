// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Item/EquipableItem.h"
#include "Character/SurvivalSciFi_Character.h"

void AEquipableItem::UpdateRelatives()
{
	SetActorRelativeLocation(RelativeLocation);
	SetActorRelativeRotation(RelativeRotation);
	//SetActorRelativeScale3D(FVector::OneVector);
}

void AEquipableItem::Use()
{
	if (Busy) return;

	if (UseMontage != nullptr)
	{
		//float t = GetOwner<ASurvivalSciFi_Character>()->PlayAnimMontage(UseMontage);
		float t = GetOwner<ASurvivalSciFi_Character>()->PlayMontage(UseMontage);
		Busy = true;

		FTimerHandle  UseTimer;
		GetWorld()->GetTimerManager().SetTimer(UseTimer, this, &AEquipableItem::UseFinish, t * PercentageBusy, false);
	}
}

void AEquipableItem::UseFinish()
{
	Busy = false;
	if (GetOwner<ASurvivalSciFi_Character>()->GetUseItemDown()) Use();
}
