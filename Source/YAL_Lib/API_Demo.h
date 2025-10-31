// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "API_Demo.generated.h"

UCLASS()
class YAL_LIB_API AAPI_Demo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAPI_Demo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	FHttpModule* Http;

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// ������ URL�� HTTP ��û�� ������.
	// InVerb�� Get,Post �� ��û �޼����̴�.
	UFUNCTION(BlueprintCallable)
	void HttpCall(const FString& InURL, const FString& InVerb);


	UFUNCTION(BlueprintPure)
	const FString& GetAnswer() { return Answer; }


private:
	UPROPERTY()
	FString Answer = "";

};
