// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThrowableActor.h"
#include "Sound/SoundCue.h"
#include "TantrumnCharacterBase.generated.h"

UENUM(BlueprintType)
enum class ECharacterThrowState : uint8
{
	None				UMETA(DIsplayName = "None"),
	RequestingPull		UMETA(DIsplayName = "RequestingPull"),
	Pulling				UMETA(DIsplayName = "Pulling"),
	Attached			UMETA(DIsplayName = "Attached"),
	Throwing			UMETA(DIsplayName = "Throwing"),
};


UCLASS()
class CG_P2_API ATantrumnCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATantrumnCharacterBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable)
	void RequestThrowObject();
	UFUNCTION(BlueprintCallable)
	void RequestPullObjectStart();
	UFUNCTION(BlueprintCallable)
	void RequestPullObjectStop();
	UFUNCTION(BlueprintCallable)
	void ResetThrowableObject();

	void OnThrowableAttached(AThrowableActor* InThrowableActor);

	void SphereCastPlayerView();

	void SphereCastActorTransform();

	void LineCastActorTransform();

	void ProcessTraceResult(const FHitResult& HitResult);

	bool CanThrowObject() const { return CharacterThrowState == ECharacterThrowState::Attached; }

	UFUNCTION(BlueprintPure)
		bool IsPullingObject() const { return CharacterThrowState == ECharacterThrowState::RequestingPull || CharacterThrowState == ECharacterThrowState::Pulling; }

	UFUNCTION(BlueprintPure)
		ECharacterThrowState GetCharacterThrowState() const { return CharacterThrowState; }

	UFUNCTION(BlueprintPure)
		bool IsStunned() const { return bIsStunned; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool PlayThrowMontage();

	void UnbindMontage();

	UFUNCTION()
		void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
		void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
		void OnNotifyBeginRecieved(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	UFUNCTION()
		void OnNotifyEndRecieved(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	void OnStunBegin(float StunRatio);
	void UpdateStun();
	void OnStunEnd();

	UPROPERTY(EditAnywhere, Category = "Movement")
		float SprintSpeed = 1200.0f;

	UPROPERTY(EditAnywhere, Category = "Fall Impact")
		float MinImpactSpeed = 600.0f;

	UPROPERTY(EditAnywhere, Category = "Fall Impact")
		float MaxImpactSpeed = 1200.0f;

	// Time in Seconds
	UPROPERTY(EditAnywhere, Category = "Fall Impact")
		float MinStunTime = 1.0f;
	// Time in Seconds
	UPROPERTY(EditAnywhere, Category = "Fall Impact")
		float MaxStunTime = 1.0f;

	USoundCue* HeavyLandSound = nullptr;

	float StunTime = 0.0f;
	float StunBeginTimestamp = 0.0f;

	bool bIsStunned = false;
	bool bIsSprinting = false;

	float MaxWalkSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Throw")
		ECharacterThrowState CharacterThrowState = ECharacterThrowState::None;

	UPROPERTY(EditAnywhere, Category = "Throw", meta = (ClampMin = "0.0", Unit = "ms"))
		float ThrowSpeed = 2000.0f;

	UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimMontage* ThrowMontage = nullptr;

	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;

private:

	UPROPERTY()
		AThrowableActor* ThrowableActor;
};
