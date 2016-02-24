// Fill out your copyright notice in the Description page of Project Settings.

#include "Shift.h"
#include "CameraLineTracer.h"
#include "Engine.h"
#include "InteractableObjectBase.h"
// Sets default values
ACameraLineTracer::ACameraLineTracer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraLineTracer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraLineTracer::Tick( float DeltaTime )
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("1")));
	Super::Tick( DeltaTime );
	TraceObject();
}

void ACameraLineTracer::TraceObject()
{
	//if for some reason things go wrong;
	UWorld* world = GetWorld();
	if (world == nullptr)
	{
		return;
	}
	APlayerController* controller = world->GetFirstPlayerController();
	if (controller == nullptr) return;
	if (controller->PlayerCameraManager == nullptr) return;
	
	FVector StartLocation = controller->PlayerCameraManager->GetCameraLocation();
	FVector Endlocation;
	FVector CameraDirection = controller->PlayerCameraManager->GetCameraRotation().Vector();
	CameraDirection.Normalize();
	Endlocation = StartLocation + (CameraDirection * distanceFromCamera);
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);


		world->LineTraceSingle(
		RV_Hit,        //result
		StartLocation,    //start
		Endlocation, //end
		ECC_Pawn, //collision channel
		RV_TraceParams
		);
		
		if (RV_Hit.bBlockingHit) {
			if (RV_Hit.GetActor()->IsA(AInteractableObjectBase::StaticClass()))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HitEvents")));
				AInteractableObjectBase* HitCharacter = Cast<AInteractableObjectBase>(RV_Hit.GetActor());
				if (!HitCharacter) return;
				HitCharacter->processHits();
				//do stuff to the HitCharacter
			}
		}


}

