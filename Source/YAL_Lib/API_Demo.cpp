// Fill out your copyright notice in the Description page of Project Settings.


#include "API_Demo.h"

// Sets default values
AAPI_Demo::AAPI_Demo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Http ��û�� �����ϴ� ����� ������ ���̴�.
	//�̸� ���� HTTP ��û�� �����ϰ� ������ �� ����.
	Http = &FHttpModule::Get();
}

// Called when the game starts or when spawned
void AAPI_Demo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAPI_Demo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAPI_Demo::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	// ��û�� �����ߴ���, ������ �������� �˻��Ѵ�.
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP request failed. URL: %s"), *Request->GetURL());
		return;
	}

	// ���� ���� �ڵ带 �����´�.
	int32 StatusCode = Response->GetResponseCode();

	// ���� ������ ���ڿ��� ������
	FString ResponseContent = Response->GetContentAsString();

	// ��û�� �Ϸ�Ǿ����� ���
	UE_LOG(LogTemp, Warning, TEXT("HTTP request completed. Status Code: %d, URL: %s"), StatusCode, *Request->GetURL());
	UE_LOG(LogTemp, Warning, TEXT("Response Content: %s"), *ResponseContent);
}

void AAPI_Demo::HttpCall(const FString& InURL, const FString& InVerb)
{
	// Http ��û ��ü�� ������ Request������ �����Ѵ�.
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	// Http ��û�� �Ϸ�Ǹ� OnResponseReceived�Լ��� ȣ��ǵ��� ���ε��Ѵ�.
	Request->OnProcessRequestComplete().BindUObject(this, &AAPI_Demo::OnResponseReceived);

	Request->SetURL(InURL); // URL ����
	Request->SetVerb(InVerb); // �޼��� ����
	Request->SetHeader("Content-Type", TEXT("application/json")); // ��û�� ��� ����

	// HTTP ��û ����
	Request->ProcessRequest();

	// ���������� �˸��� �α� ���
	UE_LOG(LogTemp, Warning, TEXT("HttpCall initiated. URL: %s, Verb: %s"), *InURL, *InVerb);
}

