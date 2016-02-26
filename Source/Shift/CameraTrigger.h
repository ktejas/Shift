// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CameraTrigger.generated.h"

UCLASS()
class SHIFT_API ACameraTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraTrigger();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FORCEINLINE class UBoxComponent* getBoxeComponent()const  { return cameraTrigger; } ;

	UFUNCTION()
		void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** called when something leaves the sphere component */
	UFUNCTION()
		void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditAnywhere)
	class AActor* Camera;
	UPROPERTY(EditAnywhere)
	class AActor* player;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CameraTrigger", meta = (AllowPrivateAccess = true))
	class  UBoxComponent* cameraTrigger;
	class APlayerController* playerContoller;
	class ACharacter* playerChar;

	
};
