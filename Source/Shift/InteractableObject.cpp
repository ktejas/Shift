// Fill out your copyright notice in the Description page of Project Settings.

#include "Shift.h"
#include "InteractableObject.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteratableObject"));
	RootComponent = m_staticMesh;
	isActive = false;
}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	UWorld* const World = GetWorld();
	if (World)
	{
		playerContoller = World->GetFirstPlayerController();
	}
	distanceFromCamera > 0 ? distanceFromCamera = distanceFromCamera : distanceFromCamera = 10.0f;
	intialOrientation = GetActorRotation();
	
}


UFUNCTION()
void AInteractableObject::Tick(float delatTime)
{
	Super::Tick(delatTime); // Call parent class tick function  

	if (isActive != true || currentCameraManger == nullptr)
	{
		return;
	}
	moveObject(delatTime);

}

UFUNCTION()
void AInteractableObject::moveObject(float deltaTime)
{
	
	FVector cameraLocation = currentCameraManger->GetCameraLocation();
	FRotator rotation = currentCameraManger->GetCameraRotation();
	rotation.Normalize();
	FVector CameraDirection = rotation.Vector();
	CameraDirection.Normalize();
	cameraLocation = cameraLocation + (CameraDirection * distanceFromCamera);
	FVector currentLocation = GetActorLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %f"), size));
	cameraLocation = UKismetMathLibrary::VInterpTo(currentLocation, cameraLocation, deltaTime, objectFloatationSpeed);
	SetActorLocation(cameraLocation);

}
UFUNCTION()
void AInteractableObject::processHits()
{
	if (isActive)
		return;
	
	check(InputComponent);
	InputComponent->BindKey(EKeys::E, IE_Released, this,&AInteractableObject::keyPressed);
	
}

UFUNCTION()
void  AInteractableObject::keyPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("keyPressed")));
	if (!isActive)
	{
		isActive = true;
		if (playerContoller)
		{
			APlayerCameraManager* cameraManger = playerContoller->PlayerCameraManager;
			if (cameraManger)
			{
				currentCameraManger = cameraManger;
			}
		

		}

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("else")));
		isActive = false;
		SetActorRotation(intialOrientation);
		stickToBase();


	}
	

}
void  AInteractableObject::stickToBase()
{
	FVector StartLocation = GetActorLocation();
	FVector Endlocation;
	FVector down(0.0f,0.0f,-1.0f);
	Endlocation = StartLocation + (down * distanceFromCamera);
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);

	UWorld* const World = GetWorld();
	World->LineTraceSingle(
		RV_Hit,        //result
		StartLocation,    //start
		Endlocation, //end
		ECC_Pawn, //collision channel
		RV_TraceParams
		);

	if (RV_Hit.bBlockingHit) {
		if (RV_Hit.GetActor())
		{
	
			FVector baseLocation(StartLocation.X, StartLocation.Y, RV_Hit.GetActor()->GetActorLocation().Z);
			SetActorLocation(baseLocation);
		}
	}
}