// Fill out your copyright notice in the Description page of Project Settings.


#include "HitComponentActor.h"

// Sets default values
AHitComponentActor::AHitComponentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(HitBox);

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube1"));
	Cube->AttachTo(HitBox);
	
	HitBox->OnComponentHit.AddDynamic(this,&AHitComponentActor::OnHit);
}

// Called when the game starts or when spawned
void AHitComponentActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitComponentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHitComponentActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	OtherActor->TakeDamage(25.0f, FDamageEvent(), GetInstigatorController(), this);

	if (OtherActor->IsPendingKill())
	{
		GEngine->AddOnScreenDebugMessage(-1,1,FColor::Green,TEXT("Destroyed"),false);
		OtherActor->GetWorld()->SpawnActor<AActor>(OtherActor->GetClass(),OtherActor->GetActorLocation(),OtherActor->GetActorRotation());
		KillCount++;
	}
}




