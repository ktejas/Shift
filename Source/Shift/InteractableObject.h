// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractableObjectBase.h"
#include "InteractableObject.generated.h"

UCLASS()
class SHIFT_API AInteractableObject : public AInteractableObjectBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FORCEINLINE class UStaticMeshComponent* getSaticMesh()const { return m_staticMesh; };
	

	
	UFUNCTION(BlueprintPure,category = "InteactableObject")
	bool getIsActive() const { return isActive; };
	
	UFUNCTION(BlueprintCallable, category = "InteactableObject")
	void setIsActive(bool activeState) { isActive = activeState; };
	
	UFUNCTION(BlueprintPure, category = "InteactableObject")
	float getDistanceFromCamera()const { return distanceFromCamera; };
	
	UFUNCTION(BlueprintCallable, category = "InteactableObject")
	void setDistanceFromCamera(float distance) { distanceFromCamera = distance; };
	UFUNCTION(BlueprintPure, category = "InteactableObject")
		float getObjectFloatationSpeed()const { return objectFloatationSpeed; };

	UFUNCTION(BlueprintCallable, category = "InteactableObject")
		void setObjectFloatationSpeed(float magnitude) { objectFloatationSpeed = magnitude; };
	
	virtual void Tick(float delatTime) override;

	UFUNCTION()
		void keyPressed();
	UFUNCTION()
		void moveObject(float deltaTime);
	
		virtual void processHits() override;
	UFUNCTION()
		void stickToBase();
protected:
	bool isActive;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteactableObject")
	float distanceFromCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteactableObject")
	float objectFloatationSpeed;


private:
	UPROPERTY(VisibleAnywhere,BluePrintReadOnly,Category = "InteactableObject",meta =(AllowPrivateAccess = "true"))
	class UStaticMeshComponent* m_staticMesh;

	class APlayerController* playerContoller;
	
	class APlayerCameraManager* currentCameraManger;
	
	struct FRotator intialOrientation;
	
	
};
