// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Projectile/ARPGProjectileBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "NiagaraComponent.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
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
		Destroy();
	}
}

void AARPGProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}

// Sets default values
AARPGProjectileBase::AARPGProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	SetRootComponent(ProjectileMesh);

	Collider = CreateDefaultSubobject<UCapsuleComponent>("Collider");
	Collider->SetupAttachment(GetRootComponent());
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Collider->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	Collider->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	Collider->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);

	ProjectileNiagara = CreateDefaultSubobject<UNiagaraComponent>("ProjectileNiagara");
	ProjectileNiagara->SetupAttachment(GetRootComponent());

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->Velocity = {1.f, 0.f, 0.f};

	NiagaraOnDestroy = CreateDefaultSubobject<UNiagaraComponent>("NiagaraOnDestroy");
	NiagaraOnDestroy->SetupAttachment(GetRootComponent());
	NiagaraOnDestroy->SetPaused(true);
}

// Called when the game starts or when spawned
void AARPGProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AARPGProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AARPGProjectileBase::BeginDestroy()
{
	Super::BeginDestroy();

	if (NiagaraOnDestroy && NiagaraOnDestroy->GetFXSystemAsset())
	{
		NiagaraOnDestroy->Activate(true);
	}
}
