// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
//Networking
#include "Networking.h"
#include "UDPFunq.generated.h"




UCLASS()
class UUDPFunq : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		//====================================================
		//		Data Received Events!
public:
	/** Data has been received!! */
	UFUNCTION(BlueprintImplementableEvent)
		void BPEvent_DataReceived();

	//====================================================

public:
	FSocket* ListenSocket;

	FUdpSocketReceiver* UDPReceiver = nullptr;
	void Recv(const FArrayReaderPtr& ArrayReaderPtr, const FIPv4Endpoint& EndPt);

	bool StartUDPReceiver(
		const FString& YourChosenSocketName,
		const FString& TheIP,
		const int32 ThePort
	);

public:

	/** Called whenever this actor is being removed from a level */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};