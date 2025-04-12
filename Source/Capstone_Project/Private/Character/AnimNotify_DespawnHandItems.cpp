// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/AnimNotify_DespawnHandItems.h"
#include "Character/SurvivalSciFi_Character.h"

void UAnimNotify_DespawnHandItems::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ASurvivalSciFi_Character* Character = MeshComp->GetOwner<ASurvivalSciFi_Character>();

	if (Character != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Despawning Hands"));
		Character->DespawnHandItems();
	}
}
