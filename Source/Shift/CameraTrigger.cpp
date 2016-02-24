// Fill out your copyright notice in the Description page of Project Settings.

#include "Shift.h"
#include "CameraTrigger.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACameraTrigger::ACameraTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	cameraTrigger = CreateDefaultSubobject<UBoxComponent >(TEXT("CameraTrigger"));
	RootComponent = cameraTrigger;
	cameraTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACameraTrigger::OnOverlapBegin);
	cameraTrigger->OnComponentEndOverlap.AddDynamic(this, &ACameraTrigger::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ACameraTrigger::BeginPlay()
{
	Super::BeginPlay();	
	UWorld* const World = GetWorld();
	if (World)
	{
		playerContoller = World->GetFirstPlayerController();
		playerChar = UGameplayStatics::GetPlayerCharacter(World, 0);
	}
	if (player)
	{
		player->SetActorHiddenInGame(true);
	}
}

UFUNCTION()
void ACameraTrigger::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (!OtherActor->Tags.Contains("Player"))
		return;
	if (Camera && playerContoller)
		playerContoller->SetViewTarget(Camera);
	if (player)
	{	
		player->SetActorHiddenInGame(false);
	}

}

/** called when something leaves the sphere component */
UFUNCTION()
void ACameraTrigger::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (playerChar && playerContoller)
		playerContoller->SetViewTarget(playerChar);
	if (player)
	{
		player->SetActorHiddenInGame(true);
	}
}

