// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameDevCase_v4Character.h"
#include "GameFramework/Pawn.h"
#include "B_PlayerPawnManager.generated.h"

UCLASS()
class GAMEDEVCASE_V4_API AB_PlayerPawnManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AB_PlayerPawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void GravityGun();

	UPROPERTY()
	AGameDevCase_v4Character* PlayerController;

};
