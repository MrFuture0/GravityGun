// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameDevCase_v4Character.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

AGameDevCase_v4Character::AGameDevCase_v4Character()
{
	
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	Health = MaxHealth;

	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
	
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);			
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	
	FP_Gun->SetupAttachment(RootComponent);

	GrabbedObjectLocation = CreateDefaultSubobject<USceneComponent>("GrabbedObjectLocation");
	GrabbedObjectLocation->SetupAttachment(FP_Gun);
}

void AGameDevCase_v4Character::BeginPlay()
{
	Super::BeginPlay();

	if(FP_Gun)
	{
		FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("FP gun has not found"));
	}

}
void AGameDevCase_v4Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AGameDevCase_v4Character::OnFire);
	PlayerInputComponent->BindAction("FireEnd", IE_Pressed, this, &AGameDevCase_v4Character::EndFire);
	
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AGameDevCase_v4Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGameDevCase_v4Character::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGameDevCase_v4Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGameDevCase_v4Character::LookUpAtRate);
}

void AGameDevCase_v4Character::OnFire()
{
	const FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(GravityGunTrace),false,this);
	const float TraceRange = 5000.0f;

	const FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
	const FVector EndTrace = (FirstPersonCameraComponent->GetForwardVector() * TraceRange) + StartTrace;

	FHitResult Hit;
	if(GetWorld()->LineTraceSingleByChannel(Hit,StartTrace,EndTrace,ECC_Visibility,QueryParams))
	{
		Prim = Hit.GetComponent();
		if(Prim)
		{
			if(Prim->IsSimulatingPhysics())
			{
				SetGrabbedObject(Prim);
			}
		}
	}

}
void AGameDevCase_v4Character::EndFire()
{
	if(GrabbedObject)
	{
		const float ShootStrength = 2000.0f;
		const FVector ShootVelocity = FirstPersonCameraComponent->GetForwardVector() * ShootStrength;

		GrabbedObject->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		GrabbedObject->SetSimulatePhysics(true);
		GrabbedObject->AddImpulse(ShootVelocity,NAME_None,true);

		SetGrabbedObject(nullptr);
	}
}


void AGameDevCase_v4Character::SetGrabbedObject(UPrimitiveComponent* ObjectToGrab)
{
	GrabbedObject = ObjectToGrab;
	if(GrabbedObject)
	{
		GrabbedObject->SetSimulatePhysics(false);
		GrabbedObject->AttachToComponent(GrabbedObjectLocation,FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

void AGameDevCase_v4Character::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AGameDevCase_v4Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AGameDevCase_v4Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGameDevCase_v4Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

