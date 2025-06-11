// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Game/SurvivalScifi_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/Player/PlayerCharacter.h"
#include "UI/GameplayHUD/SurvivalScifi_HUD.h"
#include "Framework/Application/SlateApplication.h"
#include "Game/SurvivalScifiGameMode.h"
#include "Character/Player/PlayerTutorialComponent.h"

void ASurvivalScifi_PlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PlayerCharacter = Cast<APlayerCharacter>(aPawn);

	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());

	PlayerCharacter->OnDestroyed.AddDynamic(this, &ASurvivalScifi_PlayerController::OnPlayerDeath);

	
	if (!PlayerCharacter->IsPlayingSequence()) GetHUD<ASurvivalScifi_HUD>()->ShowGameHUD();

	UE_LOG(LogTemp, Log, TEXT("Possessed %s"), *aPawn->GetName());
}

void ASurvivalScifi_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (InputSubsystem != nullptr && InputMapping != nullptr)
	{
		InputSubsystem->ClearAllMappings();
		InputSubsystem->AddMappingContext(InputMapping, 0);
	}

	else if (InputSubsystem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing Input Subsystem Referance"), *GetName());
		return;
	}
	else if (InputMapping == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing Input Mapping Referance"), *GetName());
		return;
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	if (Input != nullptr)
	{
		Input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ASurvivalScifi_PlayerController::Move);
		Input->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ASurvivalScifi_PlayerController::Look);
		Input->BindAction(IA_Inventory, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::ToggleInventory);
		Input->BindAction(IA_Run, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::RunStart);
		Input->BindAction(IA_Run, ETriggerEvent::Completed, this, &ASurvivalScifi_PlayerController::RunEnd);
		Input->BindAction(IA_Interact, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::Interact);
		Input->BindAction(IA_Slot1, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::Slot1);
		Input->BindAction(IA_Slot2, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::Slot2);
		Input->BindAction(IA_Slot3, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::Slot3);
		Input->BindAction(IA_Slot4, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::Slot4);
		Input->BindAction(IA_Slot5, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::Slot5);
		Input->BindAction(IA_Use, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::UseItem);
		Input->BindAction(IA_Use, ETriggerEvent::Completed, this, &ASurvivalScifi_PlayerController::UseItemEnd);
		Input->BindAction(IA_Jump, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::Jump);
		Input->BindAction(IA_Pause, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::PauseToggle);
		Input->BindAction(IA_SkipTutorial, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::SkipTutorial);
		Input->BindAction(IA_Light, ETriggerEvent::Started, this, &ASurvivalScifi_PlayerController::ToggleLight);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Input Referance"));
	}
}

void ASurvivalScifi_PlayerController::Move(const FInputActionValue& Value)
{
	if (CharacterAlive() && AllowMove())
	{
		FRotator CharacterRotation = PlayerCharacter->GetControlRotation();

		PlayerCharacter->AddMovementInput(
			UKismetMathLibrary::GetForwardVector(FRotator{ 0.0f, CharacterRotation.Yaw, 0.0f }),
			Value.Get<FVector2D>().Y);

		PlayerCharacter->AddMovementInput(
			UKismetMathLibrary::GetRightVector(FRotator{ 0.0f, CharacterRotation.Yaw, CharacterRotation.Roll }),
			Value.Get<FVector2D>().X);

		if (Value.Get<FVector2D>().Size() > 0)
			PlayerCharacter->GetTutorialComponent()->HasMovement(Value.Get<FVector2D>().Size(), bIsSprinting);
	}
}

void ASurvivalScifi_PlayerController::Look(const FInputActionValue& Value)
{
	if (CharacterAlive() && !AllowLook()) return;

	AddYawInput(Value.Get<FVector2D>().X);
	AddPitchInput(-1 * Value.Get<FVector2D>().Y);

	if (Value.Get<FVector2D>().Size() > 0)
		PlayerCharacter->GetTutorialComponent()->HasLooked(Value.Get<FVector2D>().Size());
}

void ASurvivalScifi_PlayerController::ToggleInventory(const FInputActionValue& Value)
{
	if (CharacterAlive() && AllowOpenMenu())
	{
		GetHUD<ASurvivalScifi_HUD>()->ShowInventory();
		SetShowMouseCursor(true);
		if (bUIOnlyMode) SetInputMode(FInputModeUIOnly());
		else
		{
			//SetInputMode(FInputModeGameAndUI());
			FInputModeGameAndUI InputModeGameAndUI;
			InputModeGameAndUI.SetHideCursorDuringCapture(false);
			InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			SetInputMode(InputModeGameAndUI);
		}
		PlayerCharacter->GetTutorialComponent()->HasOpenedInventory();
	}

	else if (GetHUD<ASurvivalScifi_HUD>()->IsShowingInventory())
	{
		GetHUD<ASurvivalScifi_HUD>()->HideInventory();
		SetShowMouseCursor(false);
		SetInputMode(FInputModeGameOnly());
		PlayerCharacter->GetTutorialComponent()->HasClosedInventory();
	}
}

bool ASurvivalScifi_PlayerController::AllowLook()
{
	return !GetHUD<ASurvivalScifi_HUD>()->IsShowingInventory()
		&& !GetHUD<ASurvivalScifi_HUD>()->IsShowingCraftingMenu()
		&& !PlayerCharacter->GetTutorialComponent()->PreventLook
		&& PlayerCharacter->IsControlable;
}

bool ASurvivalScifi_PlayerController::AllowMove()
{
	return !GetHUD<ASurvivalScifi_HUD>()->IsShowingInventory()
		&& !GetHUD<ASurvivalScifi_HUD>()->IsShowingCraftingMenu()
		&& !PlayerCharacter->GetTutorialComponent()->PreventMovement
		&& PlayerCharacter->IsControlable;
}

bool ASurvivalScifi_PlayerController::AllowInteraction()
{
	return !GetHUD<ASurvivalScifi_HUD>()->IsShowingInventory()
		&& !PlayerCharacter->GetTutorialComponent()->PreventInteract
		&& PlayerCharacter->IsControlable;
}

bool ASurvivalScifi_PlayerController::AllowOpenMenu()
{
	return !GetHUD<ASurvivalScifi_HUD>()->IsShowingInventory()
		&& !GetHUD<ASurvivalScifi_HUD>()->IsShowingCraftingMenu()
		&& !PlayerCharacter->GetTutorialComponent()->PreventInventoryOpen
		&& PlayerCharacter->IsControlable;
}

void ASurvivalScifi_PlayerController::RunStart()
{
	if (CharacterAlive())
	{
		PlayerCharacter->SetMovementSpeed(true);
		bIsSprinting = true;
	}
}

void ASurvivalScifi_PlayerController::RunEnd()
{
	if (CharacterAlive())
	{
		PlayerCharacter->SetMovementSpeed(false);
		bIsSprinting = false;
	}
}

void ASurvivalScifi_PlayerController::Interact()
{
	if (CharacterAlive() && AllowInteraction())
	{
		PlayerCharacter->Interact();
	}
}

void ASurvivalScifi_PlayerController::Slot1()
{
	if (CharacterAlive() && !PlayerCharacter->GetTutorialComponent()->PreventActionBarUse)
	{
		PlayerCharacter->SelectSlot(1);
		PlayerCharacter->GetTutorialComponent()->HasUsedSlot();
	}
}

void ASurvivalScifi_PlayerController::Slot2()
{
	if (CharacterAlive() && !PlayerCharacter->GetTutorialComponent()->PreventActionBarUse)
	{
		PlayerCharacter->SelectSlot(2);
		PlayerCharacter->GetTutorialComponent()->HasUsedSlot();
	}
}

void ASurvivalScifi_PlayerController::Slot3()
{
	if (CharacterAlive() && !PlayerCharacter->GetTutorialComponent()->PreventActionBarUse)
	{
		PlayerCharacter->SelectSlot(3);
		PlayerCharacter->GetTutorialComponent()->HasUsedSlot();
	}
}

void ASurvivalScifi_PlayerController::Slot4()
{
	if (CharacterAlive() && !PlayerCharacter->GetTutorialComponent()->PreventActionBarUse)
	{
		PlayerCharacter->SelectSlot(4);
		PlayerCharacter->GetTutorialComponent()->HasUsedSlot();
	}
}

void ASurvivalScifi_PlayerController::Slot5()
{
	if (CharacterAlive() && !PlayerCharacter->GetTutorialComponent()->PreventActionBarUse)
	{
		PlayerCharacter->SelectSlot(5);
		PlayerCharacter->GetTutorialComponent()->HasUsedSlot();
	}
}

void ASurvivalScifi_PlayerController::UseItem()
{
	if (CharacterAlive()) PlayerCharacter->UseItemRepeating();
}

void ASurvivalScifi_PlayerController::UseItemEnd()
{
	if (CharacterAlive()) PlayerCharacter->UseItemEnd();
}

void ASurvivalScifi_PlayerController::Jump()
{
	if (CharacterAlive())
	{
		PlayerCharacter->Jump();
		PlayerCharacter->GetTutorialComponent()->HasJumped();
	}
}

bool ASurvivalScifi_PlayerController::CharacterAlive()
{
	return PlayerCharacter != nullptr && PlayerCharacter->IsAlive();
}

void ASurvivalScifi_PlayerController::OnPlayerDeath(AActor* DestroyedActor)
{
	GetHUD<ASurvivalScifi_HUD>()->HideDeathScreen();

	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->OnDestroyed.RemoveDynamic(this, &ASurvivalScifi_PlayerController::OnPlayerDeath);
	}

	ASurvivalScifiGameMode* GameMode = Cast<ASurvivalScifiGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode != nullptr) GameMode->RestartPlayer(this);
}

void ASurvivalScifi_PlayerController::SkipTutorial()
{
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->GetTutorialComponent()->SkipTutorial();
	}
}

void ASurvivalScifi_PlayerController::ToggleLight()
{
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->ToggleHelmetLight();
	}
}

void ASurvivalScifi_PlayerController::PauseToggle()
{
	if (GetHUD<ASurvivalScifi_HUD>()->IsShowingPauseMenu())
	{
		GetHUD<ASurvivalScifi_HUD>()->HidePauseMenu();
		SetPause(false);

		if (GetHUD<ASurvivalScifi_HUD>()->IsShowingCraftingMenu())
			SetInputMode(FInputModeGameAndUI());
		else if (!GetHUD<ASurvivalScifi_HUD>()->IsShowingInventory())
			SetInputMode(FInputModeGameOnly());

		SetShowMouseCursor(!AllowOpenMenu());
	}
	else
	{
		GetHUD<ASurvivalScifi_HUD>()->ShowPauseMenu();
		SetPause(true);

		FInputModeGameAndUI InputModeGameAndUI;
		InputModeGameAndUI.SetHideCursorDuringCapture(false);
		InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputModeGameAndUI);
		SetShowMouseCursor(true);
	}
	
}
