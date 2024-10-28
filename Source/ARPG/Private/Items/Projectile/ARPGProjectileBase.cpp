// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Projectile/ARPGProjectileBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "DebugHelper.h"
#include "GenericTeamAgentInterface.h"
#include "NiagaraActor.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystemInstance.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "Engine/World.h"
#include "FunctionLibraries/ARPGFunctionLibrary.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/ProjectileMovementComponent.h"

void AARPGProjectileBase::Inject(const TArray<FGameplayEffectSpecHandle>& InEffectsToApplyOnHit)
{
	EffectsToApplyOnHit = InEffectsToApplyOnHit;
}

bool AARPGProjectileBase::ProjectileShouldAffect(ETeamAttitude::Type Attitude)
{
	const bool IsAffectingFriendly = Attitude == ETeamAttitude::Friendly &&
		(ECollisionType::Friendly & CollisionType) == ECollisionType::Friendly;

	const bool IsAffectingEnemy = Attitude == ETeamAttitude::Hostile &&
		(ECollisionType::Enemy & CollisionType) == ECollisionType::Enemy;

	return IsAffectingFriendly || IsAffectingEnemy;
}

void AARPGProjectileBase::Affect(AActor* ActorToAffect)
{
	UARPGAbilitySystemComponent* OwnerASC = Cast<UARPGAbilitySystemComponent>(
		Cast<IAbilitySystemInterface>(GetInstigator())->GetAbilitySystemComponent());
	UARPGAbilitySystemComponent* TargetASC = Cast<UARPGAbilitySystemComponent>(
		Cast<IAbilitySystemInterface>(ActorToAffect)->GetAbilitySystemComponent());

	for (FGameplayEffectSpecHandle& Effect : EffectsToApplyOnHit)
	{
		OwnerASC->ApplyGameplayEffectSpecToTarget(*Effect.Data.Get(), TargetASC);
	}
}

void AARPGProjectileBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	IGenericTeamAgentInterface* Team = Cast<IGenericTeamAgentInterface>(GetInstigator());
	checkf(Team, TEXT("%s not implementing IGenericTeamAgentInterface"), *GetInstigator()->GetFullName());

	ETeamAttitude::Type Attitude = Team->GetTeamAttitudeTowards(*OtherActor);

	if (!ProjectileShouldAffect(Attitude) || AffectedActors.Contains(OtherActor))
	{
		return;
	}

	Affect(OtherActor);
	AffectedActors.Add(OtherActor);

	if (ShouldBeDestroyed())
	{
		DestroyProjectile();
	}
}

void AARPGProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DestroyProjectile();
}

// Sets default values
AARPGProjectileBase::AARPGProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Collider = CreateDefaultSubobject<UCapsuleComponent>("Collider");
	SetRootComponent(Collider);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Collider->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_MAX);
	Collider->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_MAX);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	Collider->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	ProjectileMesh->SetupAttachment(GetRootComponent());

	ProjectileNiagara = CreateDefaultSubobject<UNiagaraComponent>("ProjectileNiagara");
	ProjectileNiagara->SetupAttachment(GetRootComponent());

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->Velocity = {1.f, 0.f, 0.f};
}

// Called when the game starts or when spawned
void AARPGProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	ExecuteCue(CueOnSpawn);
	ExecuteCue(CueToAttach);
}

// Called every frame
void AARPGProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AARPGProjectileBase::ExecuteCue(FGameplayTag CueToPlay)
{
	FGameplayCueParameters Parameters;
	Parameters.Instigator = GetInstigator();
	Parameters.Location = GetActorLocation();
	Parameters.Normal = GetActorForwardVector() * -1;
	Parameters.TargetAttachComponent = GetRootComponent();

	Cast<IAbilitySystemInterface>(GetInstigator())->GetAbilitySystemComponent()->ExecuteGameplayCue(
		CueToPlay, Parameters);
}

void AARPGProjectileBase::DestroyProjectile()
{
	if (!GetInstigator() || !IsValidChecked(GetInstigator()))
	{
		return;
	}

	ExecuteCue(CueOnDestroy);
	Destroy();
}

void AARPGProjectileBase::LifeSpanExpired()
{
	DestroyProjectile();
}
