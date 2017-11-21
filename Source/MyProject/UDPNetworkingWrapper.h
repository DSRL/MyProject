// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Object.h"
#include "Networking.h"
#include "UDPReceiveWorker.h"
#include "Json.h"
#include <regex>
#include "UDPNetworkingWrapper.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MYPROJECT_API UUDPNetworkingWrapper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category = "UDPNetworking")
		static UUDPNetworkingWrapper* ConstructUDPWrapper(const FString& Description, const FString& SenderSocketName, const FString& TheIP, const int32 ThePort, const int32 BufferSize,
			const bool AllowBroadcast, const bool Bound, const bool Reusable, const bool Blocking);

	static UUDPNetworkingWrapper* Constructor();
	/**
	* Sends the supplied message
	* @param Message The message to be sent.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Send Message", CompactNodeTitle = "Send", Keywords = "Send Message UDP"), Category = "UDPNetworking")
		bool sendMessage(FString Message);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Hello World", CompactNodeTitle = "HelloWorld", Keywords = "String Hello World"), Category = "UDPNetworking")
		static bool HelloWorld(bool success);
	UFUNCTION(BlueprintCallable, Category = "UDPNetworking")
		void UDPDestructor();

	UFUNCTION(BlueprintCallable, Category = "UDPNetworking")
		bool anyMessages();
	UFUNCTION(BlueprintCallable, Category = "UDPNetworking")
		FString GrabWaitingMessage();
	
	static FString StringFromBinaryArray(const TArray<uint8>&  BinaryArray);
	
private:

	// Holds the socket we are sending on
	FSocket* SenderSocket;

	// Description for debugging
	FString SocketDescription;

	// Remote Address
	FIPv4Endpoint RemoteEndPoint;
	FIPv4Address RemoteAdress;

	// Socket Subsystem
	ISocketSubsystem* SocketSubsystem;

	//UDPReceiveWorker* myRecieverWorker;
	// The data
	TArray<uint8> ReceivedData;
};
