// Fill out your copyright notice in the Description page of Project Settings.

#include "Shift.h"
#include "InteractableObjectBase.h"


// Sets default values
AInteractableObjectBase::AInteractableObjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractableObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableObjectBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

