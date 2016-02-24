// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CameraLineTracer.generated.h"

UCLASS()
class SHIFT_API ACameraLineTracer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraLineTracer();

	UFUNCTION(BlueprintCallable, category = "InteactableObject")
		void setDistanceFromCamera(float distance) { distanceFromCamera = distance; };
	
	UFUNCTION(BlueprintPure, category = "CameraLineTracer")
		float getDistanceFromCamera()const { return distanceFromCamera; };
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
protected:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraLineTracer")
		float distanceFromCamera;
private :
	UFUNCTION()
	void TraceObject();
	

};
