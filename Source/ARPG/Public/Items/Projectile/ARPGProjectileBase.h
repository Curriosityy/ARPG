// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Actor.h"
#include "ARPGProjectileBase.generated.h"

class UNiagaraSystem;
struct FGameplayEffectSpecHandle;
class UGameplayEffect;
class UMovementComponent;
class UNiagaraComponent;

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ECollisionType : uint8
{
	None = 0 UMETA(Hidden),
	Enemy = 1,
	Friendly = 2,
};

ENUM_CLASS_FLAGS(ECollisionType);

class UCapsuleComponent;

UCLASS(Abstract)
class ARPG_API AARPGProjectileBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collider, meta = (AllowPrivateAccess))
	TObjectPtr<UCapsuleComponent> Collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Niagara, meta = (AllowPrivateAccess))
	TObjectPtr<UNiagaraComponent> ProjectileNiagara;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Niagara, meta = (AllowPrivateAccess))
	FGameplayTag CueOnDestroy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess))
	TObjectPtr<UMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly)
	ECollisionType CollisionType = ECollisionType::Enemy | ECollisionType::Friendly;

	UPROPERTY(EditDefaultsOnly)
	TArray<AActor*> AffectedActors{};

	UPROPERTY()
	TArray<FGameplayEffectSpecHandle> EffectsToApplyOnHit;

public:
	UFUNCTION(BlueprintCallable)
	void Inject(const TArray<FGameplayEffectSpecHandle>& InEffectsToApplyOnHit);

	virtual bool ProjectileShouldAffect(ETeamAttitude::Type Attitude);

	UFUNCTION()
	void Affect(AActor* ActorToAffect);
	//Place where we can implement penetrating projectiles
	virtual bool ShouldBeDestroyed() { return true; }
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                       int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                   FVector NormalImpulse, const FHitResult& Hit);
	// Sets default values for this actor's properties
	AARPGProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void DestroyProjectile();
	virtual void LifeSpanExpired() override;
};
