// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Abilities/VehicleAbilitySystemComponent.h"
#include "Abilities/VehicleGameplayAbility.h"
#include "AbilitySystemInterface.h"
#include "Abilities/VehicleAttributeSet.h"
#include "Widgets/VehicleBaseInfoWidget.h"
#include "Components/WidgetComponent.h"
#include "VehicleUE5/VehicleUE5.h"
#include "VehicleUE5Pawn.generated.h"

class UPhysicalMaterial;
class UCameraComponent;
class USpringArmComponent;
class UTextRenderComponent;
class UInputComponent;
class UAudioComponent;

PRAGMA_DISABLE_DEPRECATION_WARNINGS

UCLASS(config=Game)
class AVehicleUE5Pawn : public AWheeledVehiclePawn ,public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	/** SCene component for the In-Car view origin */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* InternalCameraBase;

	/** Camera component for the In-Car view */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* InternalCamera;

	/** Text component for the In-Car speed */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* InCarSpeed;

	/** Text component for the In-Car gear */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* InCarGear;

	/** Audio component for the engine sound */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* EngineSoundComponent;

	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* RotatingAnchorSceneComponent;

	TWeakObjectPtr <UVehicleAbilitySystemComponent> AbilitySystemComponent;

	TWeakObjectPtr <UVehicleAttributeSet> AttributesSetBase;

	virtual void UnPossessed() override;

public:
	AVehicleUE5Pawn();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** The current speed as a string eg 10 km/h */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText SpeedDisplayString;

	/** The current gear as a string (R,N, 1,2 etc) */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText GearDisplayString;

	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	/** The color of the incar gear text in forward gears */
	FColor	GearDisplayColor;

	/** The color of the incar gear text when in reverse */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FColor	GearDisplayReverseColor;

	/** Are we using incar camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
	bool bInCarCameraActive;

	/** Are we in reverse gear */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
	bool bInReverseGear;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI")
	UWidgetComponent* UIFloatingStatusBarComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> PlayerInfoWidgetClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI")
	UVehicleBaseInfoWidget* PlayerInfoWidget;

	UVehicleBaseInfoWidget* GetFloatingStatusBar();

	void VehicleDie();

	/** Initial offset of incar camera */
	FVector InternalCameraOrigin;

	UPROPERTY()
	bool bWelcomeClosed;

	UPROPERTY(EditAnywhere,Category = Inputs)
	UInputMappingContext* IC_Vehicle;

	UPROPERTY(EditAnywhere, Category = Inputs)
	UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, Category = Inputs)
	UInputAction* IA_MoveCamera;


	// Begin Pawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End Pawn interface

	// Begin Actor interface
	virtual void Tick(float Delta) override;

	bool ASCInputBound = false;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UFUNCTION()
	void InitializeFloatingStatusBar();

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void OnRep_PlayerState() override;

	void BindASCInput();

	void AddCharacterAbilities();

	void AddStartupEffects();

	void InitializeAttributes();

	void SetHealth(float Health);

	void SetNitroMana(float nitro);

	void RemoveCharacterAbilities();

	FORCEINLINE int32 GetAbilityLevel(EVehicleBasicAbilityID AbilityID) const { return 1; }

	FORCEINLINE int32 GetAbilityLevel(EVehiclePowerAbilityID AbilityID) const { return 1; }

	FORCEINLINE int32 GetVehicleLevel() const { return 1; }

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UVehicleGameplayAbility>> DefaultVehicleAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultVehicleEffects;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

public:
	// End Actor interface

	/** Handle pressing forwards */
	void MoveForward(float Val);
	
	/** Handle pressing forwards */
	void LookUpCamera(float Val);

	/** Setup the strings used on the hud */
	void SetupInCarHUD();

	/** Update the physics material used by the vehicle mesh */
	void UpdatePhysicsMaterial();

	/** Handle pressing right */
	void MoveRight(float Val);
	/** Handle handbrake pressed */
	UFUNCTION(BlueprintCallable)
	void OnHandbrakePressed();
	/** Handle handbrake released */
	
	UFUNCTION(BlueprintCallable)
	void OnHandbrakeReleased();
	/** Switch between cameras */
	void OnToggleCamera();
	/** Handle reset VR device */
	void OnResetVR();

	void MoveOnJoyStick(const FInputActionValue& stickPos);

	void MoveCamera(const FInputActionValue& stickPos);

	void StopWelcomeScreenCameraRotation();

	void SetForReSettingPosition();

	virtual void PossessedBy(AController* NewController) override;

	static const FName LookUpBinding;
	static const FName LookRightBinding;
	static const FName EngineAudioRPM;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetMaxMana() const;

private:
	/** 
	 * Activate In-Car camera. Enable camera and sets visibility of incar hud display
	 *
	 * @param	bState true will enable in car view and set visibility of various
	 */
	void EnableIncarView( const bool bState );

	/** Update the gear and speed strings */
	void UpdateHUDStrings();

	/* Are we on a 'slippery' surface */
	bool bIsLowFriction;
	/** Slippery Material instance */
	UPhysicalMaterial* SlipperyMaterial;
	/** Non Slippery Material instance */
	UPhysicalMaterial* NonSlipperyMaterial;


public:
	/** Returns SpringArm subobject **/
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
	/** Returns InternalCamera subobject **/
	FORCEINLINE UCameraComponent* GetInternalCamera() const { return InternalCamera; }
	/** Returns InCarSpeed subobject **/
	FORCEINLINE UTextRenderComponent* GetInCarSpeed() const { return InCarSpeed; }
	/** Returns InCarGear subobject **/
	FORCEINLINE UTextRenderComponent* GetInCarGear() const { return InCarGear; }
	/** Returns EngineSoundComponent subobject **/
	FORCEINLINE UAudioComponent* GetEngineSoundComponent() const { return EngineSoundComponent; }

	FORCEINLINE USceneComponent* GetRotatingCameraComponent() const { return RotatingAnchorSceneComponent; }

	
};

PRAGMA_ENABLE_DEPRECATION_WARNINGS
