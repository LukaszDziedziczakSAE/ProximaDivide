// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/SurvivalScifi_AnimInstance.h"
#include "Character/SurvivalSciFi_Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void USurvivalScifi_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Character = Cast<ASurvivalSciFi_Character>(GetOwningActor());
}

void USurvivalScifi_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr) return;

	Speed = Character->GetCharacterMovement()->Velocity.Length();
}
