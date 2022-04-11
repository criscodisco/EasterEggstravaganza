

#pragma once

#include "WeaponContainer.h"
#include "Misc/OutputDeviceNull.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
	float Health;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
	float Stamina;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
	float MaxStamina;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
	float Armor;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
	float MaxArmor;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
	float Damage;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
	FVector Location;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
	FRotator Rotation;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
	int32 Eggs;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
	int32 SpoiledEggs;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
	int32 EnemyKills;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
	FString WeaponName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
	bool bWeaponParticles;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
	FString LevelName;




};

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal UMETA(DisplayName = "Normal"),
	EMS_Sprinting UMETA(DisplayName = "Sprinting"),
	EMS_Dead UMETA(DisplayName = "Dead"),

	EMS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EStaminaStatus :uint8
{
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted UMETA(DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering UMETA(DisplayName = "ExhaustedRecovering"),

	ESS_MAX UMETA(DisplayName = "DefaultMax")

};

UCLASS()
class FIRSTPROJECT_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

	FCharacterStats CharacterStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
		bool bHasCombatTarget;

	FORCEINLINE void SetHasCombatTarget(bool HasTarget) { bHasCombatTarget = HasTarget; }

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Combat")
		FVector CombatTargetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
		class AMainPlayerController* MainPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		class UParticleSystem* SmokeParticleSystem;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		class USoundCue* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		USoundCue* SwingSound;

	TArray<FVector> PickupLocations;

	UFUNCTION(BlueprintCallable)
		void ShowPickupLocations();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
		EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
		EStaminaStatus StaminaStatus;

	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MinSprintStamina;

	float InterpSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		bool bInterpToEnemy;
	void SetInterpToEnemy(bool Interp);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
		class AEnemy* CombatTarget;

	FORCEINLINE void SetCombatTarget(AEnemy* Target) { CombatTarget = Target; }

	FRotator GetLookAtRotationYaw(FVector Target);

	/** Set movement status and running speed */
	void SetMovementStatus(EMovementStatus Status);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
		float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
		float SprintingSpeed;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
		bool bCurrentLineTrace;


	bool bShiftKeyDown;

	/** Pressed down to enable sprinting */
	void ShiftKeyDown();

	/** Released to stop sprinting */
	void ShiftKeyUp();

	/** Camera boom positioning the camera behind the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* CombatCollision;

	/** Base turn rates to scale turning functions for the camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		float BaseLookUpRate;

	/**
	/*
	/* Player Stats
	/*
	*/

	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
		float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Stamina;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
		float Armor;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SavedData")
		float MaxArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		int Eggs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		int SpoiledEggs;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy Kills")
		int EnemyKills;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
		float Damage;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
		int PointTotal;

	void DecrementHealth(float Amount);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void IncrementEggs(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void IncrementSpoiledEggs(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void IncrementKills(int32 Amount);

	UFUNCTION(BlueprintCallable)
		void IncrementHealth(float Amount);

	UFUNCTION(BlueprintCallable)
		void IncrementArmor(float Amount);

	UFUNCTION(BlueprintCallable)
		void DecrementArmor(float Amount);

	UFUNCTION(BlueprintCallable)
		void Die();

	UFUNCTION(BlueprintCallable)
		void DelayAndDisableInput();

	UFUNCTION()
	int CallPointTotalFromBlueprint();

	UPROPERTY(EditAnywhere, Category = "CPPCallableFunction")
	UUserWidget* ScoreboardWidget;

	EMontagePlayReturnType ReturnValueType;

	virtual void Jump() override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for forwards/backwards input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	bool bMovingForward;
	bool bMovingRight;

	/** Called via input to turn at a given rate
	* @param Rate This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/** Called via input to look up/down at a given rate
	* @param Rate This is a normalized rate, i.e. 1.0 means 100% of desired look up/down rate
	*/
	void LookUpAtRate(float Rate);

	/** Called for mouse input add yaw rotation */
	UFUNCTION(BlueprintCallable, Category = "Camera Input")
		void Turn(float Value);

	/** Called for mouse input add pitch rotation */
	void LookUp(float Value);

	bool bLMBDown;
	void LMBDown();
	void LMBUp();

	bool bESCDown;
	void ESCDown();
	void ESCUp();
	
	bool bMenuSelect;
	void MenuSelect();

	bool AllowInput(float Value);

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Items)
		class AWeapon* EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
		class AItem* ActiveOverlappingItem;

	void SetEquippedWeapon(AWeapon* WeaponToSet);

	UFUNCTION(BlueprintCallable)
		AWeapon* GetEquippedWeapon() { return EquippedWeapon; }

	UFUNCTION()
		void CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void CombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void ActivateCollision();

	UFUNCTION(BlueprintCallable)
		void DeactivateCollision();

	FORCEINLINE void SetActiveOverlappingItem(AItem* Item) { ActiveOverlappingItem = Item; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anims")
		bool bAttacking;

	void Attack();

	UFUNCTION(BlueprintCallable)
		void AttackEnd();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
		class UAnimMontage* CombatMontage;

	UFUNCTION(BlueprintCallable)
		void DeathEnd();

	UFUNCTION(BlueprintCallable)
	void DeathMovementStatus();

	void UpdateCombatTarget();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		TSubclassOf<AEnemy> EnemyFilter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		TSubclassOf<UDamageType> DamageTypeClass;

	UFUNCTION(BlueprintCallable)
	void SwitchLevel(FName LevelName);

	UFUNCTION(BlueprintCallable)
		void SaveGame();

	UFUNCTION(BlueprintCallable)
		void LoadGame(bool LoadPosition);

	UFUNCTION(BlueprintCallable)
		void LoadGameNoSwitch();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeaponContainerActor> WeaponContainer;
private:
	FTimerHandle TimerHandle;

};