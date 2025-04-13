// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Animation/AnimNotify_SpawnHandItems.h"
#include "Character/SurvivalSciFi_Character.h"

void UAnimNotify_SpawnHandItems::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ASurvivalSciFi_Character* Character = MeshComp->GetOwner<ASurvivalSciFi_Character>();

	if (Character != nullptr)
	{
		Character->SpawnHandItems();
	}
}
