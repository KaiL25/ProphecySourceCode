// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Prophecy.h"
#include "ProphecyCharacter.h"
#include "ProphecyGameInstance.h"
#include "ProphecyProjectile.h"
#include "PickUp.h"
#include "Interactable.h"
#include "PaintingPuzzleSign.h"
#include "ProphecyGameMode.h"
#include "Goblet.h"
#include "ProphecyCharacterAnimInstance.h"
#include "VillagerEnemyPawn.h"
#include "HunterEnemy.h"
#include "ParticleDefinitions.h"
#include "PlayerSoundLocation.h"
#include "Outhouse.h"
#include "InnLetter.h"
#include "ProphecyPlayerController.h"
#include "PlayerSoundLocation.h"
#include "Engine.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AProphecyCharacter

AProphecyCharacter::AProphecyCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(GetCapsuleComponent());
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	this->Tags.Add("Player");

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetMesh1P(), "Camera");
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	
	sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword"));
	sword->SetupAttachment(GetMesh1P(), "SwordSheathe");	
	bSwordDrawn = false;

	swordHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordHitbox"));
	swordHitbox->bGenerateOverlapEvents = true;
	swordHitbox->OnComponentBeginOverlap.AddDynamic(this, &AProphecyCharacter::OnEnterSwordHitbox);
	swordHitbox->SetupAttachment(sword);

	torch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Torch"));
	torch->SetupAttachment(GetMesh1P(), "TorchPocket");	
	bTorchEquipped = false;

	torchFire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TorchFire"));
	torchFire->SetupAttachment(torch);	
	torchFireSound = CreateDefaultSubobject<UAudioComponent>(TEXT("TorchFireSound"));
	torchFireSound->bAutoActivate = false;

	playerDamageSound = CreateDefaultSubobject<UAudioComponent>(TEXT("PlayerDamageSound"));
	playerDamageSound->bAutoActivate = false;

	maxHealth = 100;
	damage = 10;
	itemRotationSpeed = 40;
	health = maxHealth;
	walkSpeed = 200;
	sprintSpeed = 1000;
	currentPaintingPuzzleSign = NULL;
	previousPaintingPuzzleSign = NULL;

	inspectionLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("InspectionLight"));	
	inspectionLight->SetupAttachment(RootComponent);
	
	meleeRange = CreateDefaultSubobject<USphereComponent>(TEXT("MeleeRange"));
	meleeRange->SetupAttachment(RootComponent);
	meleeRange->bGenerateOverlapEvents = true;
	meleeRange->OnComponentBeginOverlap.AddDynamic(this, &AProphecyCharacter::OnEnemyEnterMeleeRange);
	meleeRange->OnComponentEndOverlap.AddDynamic(this, &AProphecyCharacter::OnEnemyExitMeleeRange);	

	PawnNoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmitterComp"));
	bInputEnabled = true;
}


void AProphecyCharacter::BeginPlay()
{
	Super::BeginPlay();
	currentWorld = GetWorld();
	if (currentWorld)
	{		
		inspectionLight->SetIntensity(0);		
		torchFire->DeactivateSystem();
		prophecyGameInstance = Cast<UProphecyGameInstance>(GetGameInstance());
		prophecyCharacterAnimInstance = Cast<UProphecyCharacterAnimInstance>(this->Mesh1P->GetAnimInstance());
		for (TObjectIterator<USphereComponent> Itr; Itr; ++Itr)
		{
			// Filter out objects not contained in the target world.
			if (Itr->GetWorld() != currentWorld)
			{
				continue;
			}
			else if (Itr->ComponentHasTag("Examination"))
			{				
				// Access the subclass instance with the * or -> operators.
				itemExaminationPoint = *Itr;
			}
		}		
	}

	for (TActorIterator<APlayerSoundLocation> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		if (ActorItr->ActorHasTag("PlayerSoundLocation"))
		{
			torchFireSoundLocation = *ActorItr;
		}		
	}	
}

void AProphecyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (prophecyCharacterAnimInstance->GetCurrentStateName(0) == "Slash1" || prophecyCharacterAnimInstance->GetCurrentStateName(0) == "Slash2" || prophecyCharacterAnimInstance->GetCurrentStateName(0) == "Kick" || prophecyCharacterAnimInstance->GetCurrentStateName(0) == "SlashWithTorch1" || prophecyCharacterAnimInstance->GetCurrentStateName(0) == "SlashWithTorch2" || prophecyCharacterAnimInstance->GetCurrentStateName(0) == "KickWithTorch")
	{		
		bSwordCanDamage = true;
	}
	else
	{
		bSwordCanDamage = false;
	}
	if (bCanInteractWithPaintingPuzzleSigns)
	{
		OutlineRaycast();
	}

	if (bBeingGrabbed && currentEnemy != NULL)
	{
		FRotator rotToHunter;
		rotToHunter = FRotationMatrix::MakeFromX(currentEnemy->GetActorLocation() - this->GetActorLocation()).Rotator();
		//SetActorRotation(rotToHunter);
		this->ClientSetRotation(rotToHunter);
	}

	//If the player has less than max health and is not moving...
	if (health < maxHealth)
	{
		health += .05;		
		float ratio;
		float reverseRatio;
		ratio = health / maxHealth;
		
		//The blood texture's alpha value
		reverseRatio = 1 - ratio;			
		AProphecyPlayerController* controller = Cast<AProphecyPlayerController>(this->GetController());		
		//Regenerate health
		controller->UpdateUIHealth(reverseRatio);
	}
}

void AProphecyCharacter::GameHasStarted()
{
	this->EnableInput(Cast<APlayerController>(this->GetController()));	
	clue = prophecyGameInstance->GetCurrentClue(); 
	AddTextToUI(clue);
	ShowSword();
	ShowTorch();
}

void AProphecyCharacter::EnableInputCutscene()
{
	bInputEnabled = true;
	GetController()->SetIgnoreLookInput(false);
}

void AProphecyCharacter::DisableInputCutscene()
{
	bInputEnabled = false;
	GetController()->SetIgnoreLookInput(true);
}

void AProphecyCharacter::Pause()
{
	if (bInputEnabled)
	{
		AProphecyGameMode* gameMode = Cast<AProphecyGameMode>(this->GetWorld()->GetAuthGameMode());
		AProphecyPlayerController* controller = Cast<AProphecyPlayerController>(this->GetController());
		gameMode->SetGamePaused();
		controller->TogglePauseScreen();
	}	
}

void AProphecyCharacter::SkipCutScene()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Trying to skip cutscene ");
	AProphecyGameMode* gameMode = Cast<AProphecyGameMode>(this->GetWorld()->GetAuthGameMode());
	gameMode->SkipCutscene();
}

void AProphecyCharacter::HideSword()
{
	sword->SetVisibility(false);
}

void AProphecyCharacter::HideTorch()
{
	torch->SetVisibility(false);
}

void AProphecyCharacter::ShowSword()
{
	sword->SetVisibility(true);
	
}

void AProphecyCharacter::ShowTorch()
{
	torch->SetVisibility(true);
}

void AProphecyCharacter::SetClue(FText newClue)
{
	clue = newClue;
}

void AProphecyCharacter::ShowClue()
{	
	if (bInputEnabled)
	{
		AddTextToUI(clue);
	}
}

void AProphecyCharacter::AddTextToUI(FText NewText)
{	
	AProphecyPlayerController* controller = Cast<AProphecyPlayerController>(this->GetController());
	//Converts the incoming string to FText
	screenText = NewText;
	if (controller)
	{
		controller->UpdateText(screenText);
	}
}

void AProphecyCharacter::AddInfoTextToUI(FText NewText)
{
	AProphecyPlayerController* controller = Cast<AProphecyPlayerController>(this->GetController());
	//Converts the incoming string to FText
	screenText = NewText;
	if (controller)
	{
		controller->UpdateInfoText(screenText);
	}
}

void AProphecyCharacter::ReportNoise(USoundBase* SoundToPlay, float Volume)
{
	//If we have a valid sound to play, play the sound and
	//report it to our game
	//if (SoundToPlay)
	//{
		//Play the actual sound
		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundToPlay, GetActorLocation(), Volume);

		//Report that we've played a sound with a certain volume in a specific location
		torchFireSoundLocation->SetPlayerSoundLocation(GetActorLocation());		
		MakeNoise(1, this, GetActorLocation());
	//}
}

/**MY FUNCTIONS START HERE*/
void AProphecyCharacter::SetCanInteractWithPaintingPuzzleSigns(bool NewStatus)
{
	bCanInteractWithPaintingPuzzleSigns = NewStatus;
}

FVector AProphecyCharacter::GetItemExaminationPointLocation()
{
	return itemExaminationPoint->GetComponentLocation();
}

bool AProphecyCharacter::GetIsExaminingObject()
{
	return bLookingAtObject;
}

void AProphecyCharacter::SetCanPickUp(bool NewStatus, APickUp* NewPickUp)
{
	bCanPickUp = NewStatus;
	currentPickUp = NewPickUp;	
}

void AProphecyCharacter::SetCanInteract(bool NewStatus, AInteractable* NewInteractable)
{
	bCanInteract = NewStatus;
	currentInteractable = NewInteractable;
	// If the interactable is imrod we want to immediately pick it up.
	if (currentInteractable->ActorHasTag("Imrod"))
	{
		PerformAction();
	}
	if (NewStatus == false)
	{
		currentInteractable = NULL;
	}
}

void AProphecyCharacter::ToggleExaminationPose()
{
	if (bLookingAtObject)
	{
		prophecyCharacterAnimInstance->SetExaminingObject(true);
	}
	else
	{
		prophecyCharacterAnimInstance->SetExaminingObject(false);
	}
}

//May want to make this function more orderly
void AProphecyCharacter::PerformAction()
{
	if (bInputEnabled)
	{
		if (!bBeingGrabbed)
		{
			if (bCanPickUp)
			{
				/**If the player is not already looking at the object*/
				if (!bLookingAtObject)
				{
					/**If the player is holding a torch, unequip it*/
					if (bTorchEquipped)
					{
						bTorchWasEquipped = true;
						EquipTorch();
					}

					/**If the player has the sword drawn, sheathe it*/
					if (bSwordDrawn)
					{
						bSwordWasDrawn = true;
						DrawSword();
					}
					AddInfoTextToUI(rotateObjectMessage);
					GetController()->SetIgnoreLookInput(true);
					bLookingAtObject = true;
					ToggleExaminationPose();
					inspectionLight->SetIntensity(100);
					currentPickUp->axis->SetWorldLocation(itemExaminationPoint->GetComponentLocation());
					currentPickUp->axis->SetWorldRotation(itemExaminationPoint->GetComponentRotation());

					/**Enable depth of field effect*/
					GetFirstPersonCameraComponent()->PostProcessSettings.DepthOfFieldFocalDistance = 20;
					GetFirstPersonCameraComponent()->PostProcessSettings.DepthOfFieldScale = .3;
				}
				/**If the player is already looking at the object*/
				else
				{
					bLookingAtObject = false;
					GetController()->SetIgnoreLookInput(false);
					ToggleExaminationPose();
					if (bTorchWasEquipped)
					{
						EquipTorch();
						bTorchWasEquipped = false;
					}
					if (bSwordWasDrawn)
					{
						DrawSword();
						bSwordWasDrawn = false;
					}
					inspectionLight->SetIntensity(0);

					/**If the item can be collected set it invisible and set the corresponding collected bool on the player to true.*/
					if (currentPickUp->IsCollectable())
					{
						StoreCollectable(currentPickUp->GetCollectable());
						currentPickUp->SetActorHiddenInGame(true);
						currentPickUp->SetActorEnableCollision(false);

					}
					else
					{						
						currentPickUp->axis->SetWorldLocation(currentPickUp->GetOriginalLocation());
						currentPickUp->axis->SetWorldRotation(currentPickUp->GetOriginalRotation());
						/*If the player was looking at the inn letter show the screen text below and set the clue to the text below.*/
						if (currentPickUp->GetName().Contains("InnLetter"))
						{
							AddTextToUI(innLetterMessage);
							clue = inLetterClue;
						}
						if (currentPickUp->GetName().Contains("TraitorsLetter"))
						{							
							AInnLetter* tempLetter = Cast<AInnLetter>(currentPickUp);
							tempLetter->TheLetterWasRead();
						}
						if (currentPickUp->GetName().Contains("OuthouseLetter"))
						{
							bOuthouseLetterRead = true;
						}
						if (currentPickUp->GetName().Contains("InsertionSphere"))
						{
							AddTextToUI(doorBackClosedMessage);
							clue = doorBackClosedClue;
						}

					}
					if (currentPickUp && currentPickUp->ActorHasTag("Imrod"))
					{
						currentPickUp = NULL;
						bCanPickUp = false;
					}
					/**Disable depth of field effect*/
					GetFirstPersonCameraComponent()->PostProcessSettings.DepthOfFieldFocalDistance = 0;
					GetFirstPersonCameraComponent()->PostProcessSettings.DepthOfFieldScale = 0;
				}
			}
			else if (bCanInteract)
			{
				if (currentInteractable != NULL)
				{
					//THIS WILL HAVE TO BE CHANGED TO ACCESSING THE GOBLET'S VARIABLE	
					if (currentInteractable->ActorHasTag("Water"))
					{
						currentInteractable->InteractWithObject();
					}

					/**Used to toggle whether the player is using the rod in the outhouse and therefore controlling it or not*/
					if (currentInteractable->ActorHasTag("Outhouse"))
					{
						AOuthouse* outhouse = Cast<AOuthouse>(currentInteractable);
						outhouse->SetAProphecyCharacter(this);
						/*if (bUsingRod)
						{
							bUsingRod = false;
						}
						else
						{
							bUsingRod = true;
						}*/
					}
					currentInteractable->InteractWithObject();
				}
			}

			else if (bCanInteractWithPaintingPuzzleSigns)
			{
				Raycast();
			}
		}
	}
}

void AProphecyCharacter::DrawSword()
{
	if (!bBeingGrabbed && bInputEnabled)
	{
		if (!bLookingAtObject)
		{
			prophecyCharacterAnimInstance->DrawSword();
			if (!bSwordDrawn)
			{
				sword->AttachSocketName = "Sword";				
				bSwordDrawn = true;
			}
			else
			{
				sword->AttachSocketName = "SwordSheathe";				
				bSwordDrawn = false;
			}
		}
	}
}

void AProphecyCharacter::EquipTorch()
{
	if (bInputEnabled)
	{
		if (!bIsInWater || !bBeingGrabbed)
		{
			if (!bLookingAtObject)
			{
				prophecyCharacterAnimInstance->EquipTorch();
				if (!bTorchEquipped)
				{
					bTorchEquipped = true;
					torch->AttachSocketName = "Torch";
					torchFireSound->Play();
					torchFire->ActivateSystem();
				}
				else
				{
					bTorchEquipped = false;
					torch->AttachSocketName = "TorchPocket";
					torchFireSound->Stop();
					torchFire->DeactivateSystem();
				}
			}
		}
	}
}

void AProphecyCharacter::EnteredWater(bool bStatus)
{
	/**If the player just entered water...*/
	if (bStatus)
	{
		/**If the torch is equipped...*/
		if (bTorchEquipped)
		{
			/**Unequip the torch*/
			EquipTorch();
		}
		/**Set bIsInWater to true*/
		bIsInWater = bStatus;
	}
	/**If the player just left the water...*/
	else
	{
		/**Set is in water to false.*/
		bIsInWater = bStatus;
	}
}

void AProphecyCharacter::IsInWater(bool bStatus)
{
	bIsInWater = bStatus;
}

void AProphecyCharacter::Attack()
{
	if (!bLookingAtObject && !bBeingGrabbed && bInputEnabled)
	{
		prophecyCharacterAnimInstance->Attack();
		
	}
}

bool AProphecyCharacter::IsOuthouseLetterRead()
{
	return bOuthouseLetterRead;
}

void AProphecyCharacter::OnEnterSwordHitbox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult)
{
	if (bSwordCanDamage)
	{
		if (OtherActor->ActorHasTag("Enemy"))
		{
			//CODE TO DAMAGE ENEMY AND PLAY STAGGER ANIM.			
			AEnemy* HitEnemy = Cast<AEnemy>(OtherActor);
			HitEnemy->ReceiveDamage(this, 10);
		}
	}
}

void AProphecyCharacter::ReceiveDamage(int Damage)
{
	
	if (!bInvincible)
	{
		playerDamageSound->Play();				
		health -= Damage;			
		CalculateNewUIHealthRatio();
		if (health <= 0)
		{
			DisableInput(Cast<AProphecyPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld())));				
			prophecyGameInstance->SetCurrentClue(clue);
			prophecyCharacterAnimInstance->SetPlayerDying(true);
		}
	}
	
}

void AProphecyCharacter::CalculateNewUIHealthRatio()
{	
	float ratio;
	float reverseRatio;
	//Subtracting Health  
	
	ratio = health / maxHealth;
	
	//The blood texture's alpha value
	reverseRatio = 1 - ratio;	
	AProphecyPlayerController* controller = Cast<AProphecyPlayerController>(this->GetController());
	controller->UpdateUIHealth(reverseRatio);
}

void AProphecyCharacter::SetOuthouseRod(UStaticMeshComponent* newRod)
{
	outhouseRod = newRod;
}

void AProphecyCharacter::Raycast()
{
	FHitResult* HitResult = new FHitResult();
	FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
	FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();
	FVector EndTrace = (ForwardVector * 5000.f) + StartTrace;
	FCollisionQueryParams* CQP = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *CQP))
	{
		if (HitResult->GetActor()->IsA(APaintingPuzzleSign::StaticClass()))
		{			
			AProphecyGameMode* gm = (AProphecyGameMode*)GetWorld()->GetAuthGameMode();
			gm->PlayerTryingToPressInSign(Cast<APaintingPuzzleSign>(HitResult->GetActor()));
		}
	}
}

void AProphecyCharacter::OutlineRaycast()
{
	FHitResult* HitResult = new FHitResult();
	FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
	FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();
	FVector EndTrace = (ForwardVector * 5000.f) + StartTrace;
	FCollisionQueryParams* CQP = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *CQP))
	{	
		if (HitResult->GetActor()->IsA(APaintingPuzzleSign::StaticClass()))
		{			
			currentPaintingPuzzleSign = Cast<APaintingPuzzleSign>(HitResult->GetActor());
			currentPaintingPuzzleSign->ActivateOutline();			
			if (previousPaintingPuzzleSign != NULL)
			{
				if (currentPaintingPuzzleSign->GetName() != previousPaintingPuzzleSign->GetName())
				{					
					previousPaintingPuzzleSign->DeactivateOutline();
				}
			}
			previousPaintingPuzzleSign = currentPaintingPuzzleSign;					
		}
		else if (previousPaintingPuzzleSign != NULL)
		{
			previousPaintingPuzzleSign->DeactivateOutline();
		}		
	}
}

void AProphecyCharacter::StoreCollectable(APickUp* NewCollectable)
{
	collectedPickUps.Add(NewCollectable);	
}

bool AProphecyCharacter::IsCollected(uint8 CollectableIndex)
{
	for (int32 i = 0; i < collectedPickUps.Num(); i++)
	{
		if (collectedPickUps[i]->GetCollectableIndex() == CollectableIndex)
		{
			return true;
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Collectable not found! " + bCanPickUp);
	return false;
}

bool AProphecyCharacter::GetFilledWithWater()
{
	return bGobletFilledWithWater;
}

void AProphecyCharacter::SetGobletFilledWithWater()
{
	bGobletFilledWithWater = true;
	AddTextToUI(gobletFilledMessage);
	SetClue(gobletFilledClue);
}

void AProphecyCharacter::EnableSprint()
{
	this->GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
}
	

void AProphecyCharacter::DisableSprint()
{
	this->GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}


void AProphecyCharacter::Jump()
{
	if (!bLookingAtObject && !bBeingGrabbed && bInputEnabled)
	{
		bPressedJump = true;
		JumpKeyHoldTime = 0.0f;
	}
}

void AProphecyCharacter::StopJumping()
{
	if (!bLookingAtObject && !bBeingGrabbed && bInputEnabled)
	{
		bPressedJump = false;
		JumpKeyHoldTime = 0.0f;
	}
}

void AProphecyCharacter::OnEnemyEnterMeleeRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult)
{
	if (OtherActor->ActorHasTag("Enemy"))
	{
		currentEnemy = Cast<AEnemy>(OtherActor);
		if (currentEnemy != NULL)
		{
			currentEnemy->CanAttackPlayer(true);			
		}
	}	
	//else if (OtherActor->GetName().Contains("Hunter"))
	//{
	//	currentEnemy = Cast<AHunterEnemy>(OtherActor);
	//	if (currentEnemy != NULL)
	//	{
	//		currentEnemy->CanAttackPlayer(true);
	//	}
	//}
}

AEnemy* AProphecyCharacter::InMeleeRangeOfPlayer()
{
	return currentEnemy;
}


void AProphecyCharacter::OnEnemyExitMeleeRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex)
{
	currentEnemy = Cast<AVillagerEnemyPawn>(OtherActor);
	if (currentEnemy != NULL)
	{
		currentEnemy->CanAttackPlayer(false);
		currentEnemy = NULL;		
	}
}

void AProphecyCharacter::IsBeingGrabbed(bool bStatus)
{
	bBeingGrabbed = bStatus;
	prophecyCharacterAnimInstance->SetBeingGrabbed(true);
}
	
void AProphecyCharacter::SetPlayerIsDead(bool bStatus)
{
	bIsDead = bStatus;
	if (bIsDead)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "Prophecy");
	}
}


bool AProphecyCharacter::IsPlayerDead()
{
	return bIsDead;
}

/*
void AProphecyCharacter::SetFilledWithWater()
{
	if (CollectedPickUps[0])
	{
		CollectedPickUps[0]->SetFilledWithWater();
	}
}

void AProphecyCharacter::TurnObject(float AxisValue)
{		
	if (LookingAtObject)
	{	
		if (CurrentPickUp)
		{			
			CurrentPickUp->AddActorWorldRotation(FRotator(0, GetWorld()->GetDeltaSeconds() * AxisValue * 10, 0));			
		}
	}
}

void AProphecyCharacter::FlipObject(float AxisValue)
{	
	
}
*/
/**MY FUNCTIONS END HERE*/

//////////////////////////////////////////////////////////////////////////
// Input

void AProphecyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AProphecyCharacter::TouchStarted);
	if( EnableTouchscreenMovement(InputComponent) == false )
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &AProphecyCharacter::OnFire);
	}
	
	InputComponent->BindAxis("MoveForward", this, &AProphecyCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AProphecyCharacter::MoveRight);
	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AProphecyCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AProphecyCharacter::LookUpAtRate);

	InputComponent->BindAction("Action", IE_Pressed, this, &AProphecyCharacter::PerformAction);
	InputComponent->BindAction("Draw/SheatheSword", IE_Pressed, this, &AProphecyCharacter::DrawSword);
	InputComponent->BindAction("Equip/UnequipTorch", IE_Pressed, this, &AProphecyCharacter::EquipTorch);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AProphecyCharacter::EnableSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AProphecyCharacter::DisableSprint);
	InputComponent->BindAction("Attack", IE_Pressed, this, &AProphecyCharacter::Attack);
	InputComponent->BindAction("Attack", IE_Released, this, &AProphecyCharacter::Attack);
	InputComponent->BindAction("ShowClue", IE_Pressed, this, &AProphecyCharacter::ShowClue);
	InputComponent->BindAction("Pause", IE_Pressed, this, &AProphecyCharacter::Pause).bExecuteWhenPaused = true;
	InputComponent->BindAction("SkipCutscene", IE_Pressed, this, &AProphecyCharacter::SkipCutScene);
	//InputComponent->BindAxis("TurnObject", this, &AProphecyCharacter::TurnObject);
	//InputComponent->BindAxis("FlipObject", this, &AProphecyCharacter::FlipObject);
}

void AProphecyCharacter::OnFire()
{ 
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<AProphecyProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if(FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if(AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

}

void AProphecyCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if( TouchItem.bIsPressed == true )
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AProphecyCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if( ( FingerIndex == TouchItem.FingerIndex ) && (TouchItem.bMoved == false) )
	{
		OnFire();
	}
	TouchItem.bIsPressed = false;
}

void AProphecyCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{	
	if ((TouchItem.bIsPressed == true) && ( TouchItem.FingerIndex==FingerIndex))
	{
		if (TouchItem.bIsPressed)
		{
			if (GetWorld() != nullptr)
			{
				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
				if (ViewportClient != nullptr)
				{
					FVector MoveDelta = Location - TouchItem.Location;
					FVector2D ScreenSize;
					ViewportClient->GetViewportSize(ScreenSize);
					FVector2D ScaledDelta = FVector2D( MoveDelta.X, MoveDelta.Y) / ScreenSize;									
					if (ScaledDelta.X != 0.0f)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.X * BaseTurnRate;
						AddControllerYawInput(Value);
					}
					if (ScaledDelta.Y != 0.0f)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.Y* BaseTurnRate;
						AddControllerPitchInput(Value);
					}
					TouchItem.Location = Location;
				}
				TouchItem.Location = Location;
			}
		}
	}
}

void AProphecyCharacter::MoveForward(float Value)
{
	if (!bBeingGrabbed && bInputEnabled)
	{
		if (Value != 0.0f && !bLookingAtObject && !bUsingRod)
		{
			// add movement in that direction
			AddMovementInput(GetActorForwardVector(), Value);
		}
		else if (bLookingAtObject)
		{
			if (currentPickUp)
			{
				currentPickUp->axis->AddLocalRotation(FRotator(0, 0, GetWorld()->GetDeltaSeconds() * Value * itemRotationSpeed));
			}
		}
	}
}

void AProphecyCharacter::MoveRight(float Value)
{
	if (!bBeingGrabbed && bInputEnabled)
	{
		if (Value != 0.0f && !bLookingAtObject && !bUsingRod)
		{
			// add movement in that direction
			AddMovementInput(GetActorRightVector(), Value);
		}

		else if (bLookingAtObject)
		{
			if (currentPickUp)
			{
				currentPickUp->axis->AddLocalRotation(FRotator(GetWorld()->GetDeltaSeconds() * Value * itemRotationSpeed, 0, 0));
			}
		}		
	}
}

/*
void AProphecyCharacter::AddControllerYawInput(float Rate)
{
	if (!LookingAtObject)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, "not looking at object a!");
		// calculate delta for this frame from the rate information
		
			FRotator NewRotation = GetActorRotation();
			NewRotation.Yaw += Rate;
			FirstPersonCameraComponent->AddRelativeRotation(this->GetControlRotation()* GetWorld()->GetDeltaSeconds() * 10);	
	}
	else if (LookingAtObject)
	{
		if (CurrentPickUp)
		{		
			if (!flippingObject)
			{
				turningObject = true;
				CurrentPickUp->AddActorWorldRotation(FRotator(0, GetWorld()->GetDeltaSeconds() * Rate * 10, 0));
			}
			if (Rate == 0)
			{
				turningObject = false;
			}
		}
	}
}


void AProphecyCharacter::AddControllerPitchInput(float Rate)
{
	if (!LookingAtObject)
	{		
		// calculate delta for this frame from the rate information
		if (Rate > 0)
		{
			
		}
	}
	else if (LookingAtObject)
	{
		if (CurrentPickUp)
		{		
			if (!turningObject)
			{
				flippingObject = true;				
				CurrentPickUp->AddActorWorldRotation(FRotator(GetWorld()->GetDeltaSeconds() * Rate * 10, 0, 0));
			}
			if (Rate == 0)
			{
				flippingObject = false;
			}
		}
	}
}
*/

void AProphecyCharacter::TurnAtRate(float Rate)
{
	if (!bLookingAtObject)
	{		
		// calculate delta for this frame from the rate information
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
	else if (bLookingAtObject)
	{
		if (currentPickUp)
		{			
			//CurrentPickUp->AddActorWorldRotation(FRotator(0, 0, Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds()));
		}
	}
}

void AProphecyCharacter::LookUpAtRate(float Rate)
{
	if (!bLookingAtObject)
	{
		
		// calculate delta for this frame from the rate information
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
	else if (bLookingAtObject)
	{		
		if (currentPickUp)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, "Rotating!");
			//FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(FirstPersonCameraComponent->GetComponentLocation(), CurrentPickUp->GetActorLocation());
			//FRotator Rot = FRotationMatrix::MakeFromX(FirstPersonCameraComponent->GetComponentLocation() - CurrentPickUp->GetActorLocation()).Rotator();
			//CurrentPickUp->SetActorRelativeRotation(FRotator(GetWorld()->GetRealTimeSeconds() * Rate, 0, 0));
		}
	}
}

bool AProphecyCharacter::EnableTouchscreenMovement(class UInputComponent* InputComponent)
{
	bool bResult = false;
	if(FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch )
	{
		bResult = true;
		InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AProphecyCharacter::BeginTouch);
		InputComponent->BindTouch(EInputEvent::IE_Released, this, &AProphecyCharacter::EndTouch);
		InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AProphecyCharacter::TouchUpdate);
	}
	return bResult;
}

