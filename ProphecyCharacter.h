// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "ProphecyCharacter.generated.h"

class UInputComponent;
class APickUp;
class AInteractable;
class APaintingPuzzleSign;
class AVillagerEnemyPawn;
class UProphecyGameInstance;
class UProphecyCharacterAnimInstance;
class APlayerSoundLocation;
class AEnemy;

UCLASS(config=Game)
class AProphecyCharacter : public ACharacter
{
	GENERATED_BODY()

public: 

	/*This actor gets left behind whenever the torch sound notifier gets activated
	It is used to let enemies walk toward the noise's last known location since a simple vector did not work for some reason (It was always invalid).*/
	UPROPERTY(EditAnywhere, Category = "PlayerCharacter")
	APlayerSoundLocation* torchFireSoundLocation;

	UFUNCTION(BlueprintCallable, Category = AI)
	void ReportNoise(USoundBase* SoundToPlay, float Volume);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPawnNoiseEmitterComponent* PawnNoiseEmitterComp;

	/**Gets called by the signboard on box enter and exit. Sets whether the player can interact with the signs belonging to the painting puzzle.*/
	void SetCanInteractWithPaintingPuzzleSigns(bool NewStatus);

	FVector GetItemExaminationPointLocation();

	/*Gets called by the OutputTextWidget when the game has started to set the sword and torch to visible
	  and display the first message on screen.*/
	void GameHasStarted();

	//These functions are used to hide/show the sword and torch when a cutscene begins or ends.
	void HideSword();
	void HideTorch();
	void ShowSword();
	void ShowTorch();

	/**Gets called by PickUp when the player enters or leaves the collision box of a PickUp*/
	void SetCanPickUp(bool NewStatus, APickUp* NewPickUp);
	/**Gets called by Interactable when the player enters or leaves the collision box of an Interactable*/
	void SetCanInteract(bool NewStatus, AInteractable* NewInteractable);

	/**This function is used to find an object in the player's collectables array
	   Returns true if the item has been picked up.*/
	bool IsCollected(uint8 CollectableIndex);
	
	bool GetFilledWithWater();

	void SetGobletFilledWithWater();

	void SetOuthouseRod(UStaticMeshComponent* newRod);

	void SetClue(FText newClue);

	bool IsOuthouseLetterRead();

	UFUNCTION()
	void ReceiveDamage(int Damage);

	UFUNCTION()
	void IsInWater(bool bStatus);

	UFUNCTION()
	void EnableInputCutscene();

	UFUNCTION()
	void DisableInputCutscene();

	/**This function gets called by bodies of water when the player enters them.
	   It is used to prevent the player from equipping the torch in water.*/
	UFUNCTION()
	void EnteredWater(bool bStatus);

	void IsBeingGrabbed(bool bStatus);

	void SetPlayerIsDead(bool bStatus);

	bool IsPlayerDead();

	bool GetIsExaminingObject();	

	/**Gets called by TheHunter to make sure that he is still in the player's meleeRange.
	   Is used to set bBeingGrabbed in the player*/
	AEnemy* InMeleeRangeOfPlayer();

	/*Adds the items to the collectibles UI*/
	void AddTextToUI(FText NewText);

	//Used for controls information etc.
	void AddInfoTextToUI(FText NewText);

private:	


	bool bIsDead;

	UPROPERTY(EditAnywhere, Category = "Player Character")
	bool bInvincible;

	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	bool bInputEnabled;

	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	UWorld* currentWorld;	

	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	UProphecyGameInstance* prophecyGameInstance;

	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	UProphecyCharacterAnimInstance* prophecyCharacterAnimInstance;

	//The player's current health.
	UPROPERTY(EditAnywhere, Category = "Player Character")
	float health;

	//The hightest amount of health the player can have.
	UPROPERTY(EditAnywhere, Category = "Player Character")
	float maxHealth;

	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	FText screenText;

	/*This variable is used to display a hint for the player on how to progress when he hits j.
	  It gets set by several items and events.*/
	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	FText clue;

	FText rotateObjectMessage = NSLOCTEXT("Normal", "rotateObjectMessage", "Rotate objects with w/a/s/d");
	FText innLetterMessage = NSLOCTEXT("Normal", "innLetterMessage", "What is this? Fairytales are not going to prevent me from collecting the tribute.\n If I return to the king without the tribute, my head is on the line.\n I need to find a way to open this gate. The villagers must be hiding there.");
	FText inLetterClue = NSLOCTEXT("Normal", "inLetterClue", "I need to find a way to open this gate.\n The villagers must be hiding there.");
	FText gobletFilledMessage = NSLOCTEXT("Normal", "gobletFilledMessage", "I filled the goblet with water.");
	FText gobletFilledClue = NSLOCTEXT("Normal", "gobletFilledClue", "I should carry the golbet back to the altar now.");	
	FText doorBackClosedMessage = NSLOCTEXT("Normal", "doorBackClosedMessage", "That sounded like the door back has closed. I can only move forward now.\nThis orb must be useful. Maybe I can fit it somewhere.");
	FText doorBackClosedClue = NSLOCTEXT("Normal", "doorBackClosedClue", "I can only keep moving forward.");


	/**The point to which the objects move when the player looks at them*/
	UPROPERTY(EditAnywhere, Category = "Player Character")
	USceneComponent* itemExaminationPoint;

	UPROPERTY(EditAnywhere, Category = "Player Character")
	UStaticMeshComponent* sword;

	UPROPERTY(EditAnywhere, Category = "Player Character")
	UBoxComponent* swordHitbox;

	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	bool bSwordDrawn;

	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	bool bBeingGrabbed;

	/**Was the sword drawn before looking at an object?
	   If yes draw it again once object inspection is over.*/
	bool bSwordWasDrawn;

	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	bool bSwordCanDamage;

	UPROPERTY(EditAnywhere, Category = "Player Character")
	int32 damage;

	UPROPERTY(EditAnywhere, Category = "Player Character")
	UStaticMeshComponent* torch;

	UPROPERTY(EditAnywhere, Category = "PlayerCharacter")
	UParticleSystemComponent* torchFire;

	UPROPERTY(EditAnywhere, Category = "PlayerCharacter")
	UAudioComponent* torchFireSound;	


	UPROPERTY(EditAnywhere, Category = "PlayerCharacter")
	UAudioComponent* playerDamageSound;

		
	/**Is the torch currently equipped*/
	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	bool bTorchEquipped;

	/**Was the torch equipped before looking at an object?
	   If yes reequip it once object inspection is over.*/
	UPROPERTY()
	bool bTorchWasEquipped;

	/**Whether the player is currently in water or not.
	   Determines whether the torch can be equipped or not.*/
	UPROPERTY()
	bool bIsInWater;

	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	bool bCanInteractWithPaintingPuzzleSigns;

	/**Used to activate and deactivate the highlight*/
	APaintingPuzzleSign* currentPaintingPuzzleSign;
	APaintingPuzzleSign* previousPaintingPuzzleSign;

	/**Whether the player can currently pick up objects or not*/
	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	bool bCanPickUp;

	/**The current object the player can pick up, while he is in its collider*/
	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	APickUp* currentPickUp;

	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	UPointLightComponent* inspectionLight;

	/**If the player is currently looking at an object.
	   If yes movement gets disabled and looking around is used for object rotation*/
	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	bool bLookingAtObject;

	/**Whether the player can currently interact with objects or not*/
	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	bool bCanInteract;

	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	bool bOuthouseLetterRead;

	/**The current object the player can interact with, while he is in its collider*/
	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	AInteractable* currentInteractable;	

	/**An array of all the pick ups the player has collected*/
	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	TArray<APickUp*> collectedPickUps;	
			
	/**Determines how fast the player can turn the object when examining it*/
	UPROPERTY(EditAnywhere, Category = "Player Character")
	uint8 itemRotationSpeed;

	/**When an enemy enters into this sphere, he can attack the player*/
	UPROPERTY(EditAnywhere, Category = "Player Character")
	USphereComponent* meleeRange;
	
	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	bool bGobletFilledWithWater;

	/**If the player is currently using the rod for the outhouse puzzle or not*/
	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	bool bUsingRod;

	/**Serves as a reference for the movement of the rod in the outhouse puzzle*/
	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	UStaticMeshComponent* outhouseRod;

	UPROPERTY(EditAnywhere, Category = "Player Character")
	uint32 walkSpeed;

	UPROPERTY(EditAnywhere, Category = "Player Character")
	uint32 sprintSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Player Character")
	AEnemy* currentEnemy;
	
	/*Calls the animation controller to enable or disable the pose the player is in when examining an object*/
	void ToggleExaminationPose();	

	void CalculateNewUIHealthRatio();

	UFUNCTION()
	void PerformAction();

	UFUNCTION()
	void Pause();

	UFUNCTION()
	void SkipCutScene();

	UFUNCTION()
	void DrawSword();

	UFUNCTION()
	void Attack();

	UFUNCTION()
	void EquipTorch();	

	UFUNCTION()
	void OnEnterSwordHitbox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);
	
	UFUNCTION()
	void EnableSprint();

	UFUNCTION()
	void DisableSprint();

	UFUNCTION()
	void Jump();

	UFUNCTION()
	void StopJumping();
		
	UFUNCTION()
	void ShowClue();

	UFUNCTION()
	void Raycast();

	UFUNCTION()
	void OutlineRaycast();

	/**This function takes the collected pick up passed in, 
	   and adds it to the pick ups array.*/
	UFUNCTION()
	void StoreCollectable(APickUp* NewCollectable);

	UFUNCTION()
	void OnEnemyEnterMeleeRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);

	UFUNCTION()
	void OnEnemyExitMeleeRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex);

	//UFUNCTION()
	// SetFilledWithWater();
	
	//UFUNCTION()
	//void TurnObject(float AxisValue);

	//UFUNCTION()
	//void FlipObject(float AxisValue);

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;	

	/** First person camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;
	

public:
	AProphecyCharacter();
	void BeginPlay();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AProphecyProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

protected:
	
	/** Fires a projectile. */
	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	//UFUNCTION()
	//virtual void AddControllerYawInput(float Rate) override;
	//UFUNCTION()
	//virtual void AddControllerPitchInput(float Rate) override;
	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	



};

