// Fill out your copyright notice in the Description page of Project Settings.


#include "API_Demo.h"

// Sets default values
AAPI_Demo::AAPI_Demo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Http 요청을 관리하는 모듈을 가져온 것이다.
	//이를 통해 HTTP 요청을 생성하고 관리할 수 있음.
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
	// 요청이 성공했는지, 응답이 유요한지 검사한다.
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP request failed. URL: %s"), *Request->GetURL());
		return;
	}

	// 응답 상태 코드를 가져온다.
	int32 StatusCode = Response->GetResponseCode();

	// 응답 본문을 문자열로 가져옴
	FString ResponseContent = Response->GetContentAsString();

	// 요청이 완료되었음을 출력
	UE_LOG(LogTemp, Warning, TEXT("HTTP request completed. Status Code: %d, URL: %s"), StatusCode, *Request->GetURL());
	UE_LOG(LogTemp, Warning, TEXT("Response Content: %s"), *ResponseContent);
}

void AAPI_Demo::HttpCall(const FString& InURL, const FString& InVerb)
{
	// Http 요청 객체를 생성해 Request변수에 저장한다.
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	// Http 요청이 완료되면 OnResponseReceived함수가 호출되도록 바인딩한다.
	Request->OnProcessRequestComplete().BindUObject(this, &AAPI_Demo::OnResponseReceived);

	Request->SetURL(InURL); // URL 설정
	Request->SetVerb(InVerb); // 메서드 설정
	Request->SetHeader("Content-Type", TEXT("application/json")); // 요청의 헤더 설정

	// HTTP 요청 전송
	Request->ProcessRequest();

	// 전송했음을 알리는 로그 출력
	UE_LOG(LogTemp, Warning, TEXT("HttpCall initiated. URL: %s, Verb: %s"), *InURL, *InVerb);
}

