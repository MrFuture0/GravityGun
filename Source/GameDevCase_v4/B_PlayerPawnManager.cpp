// Fill out your copyright notice in the Description page of Project Settings.


#include "B_PlayerPawnManager.h"

// Sets default values
AB_PlayerPawnManager::AB_PlayerPawnManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AB_PlayerPawnManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AB_PlayerPawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AB_PlayerPawnManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Fire",IE_Pressed,this,&AB_PlayerPawnManager::GravityGun);

}

void AB_PlayerPawnManager::GravityGun()
{

}

