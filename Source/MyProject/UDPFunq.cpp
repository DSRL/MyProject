// Fill out your copyright notice in the Description page of Project Settings.

#include "UDPFunq.h"

//#include "UDPSendReceive.h"

UUDPFunq::UUDPFunq(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ListenSocket = NULL;
}

void UUDPFunq::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//~~~~~~~~~~~~~~~~

	delete UDPReceiver;
	UDPReceiver = nullptr;

	//Clear all sockets!
	//		makes sure repeat plays in Editor dont hold on to old sockets!
	if (ListenSocket)
	{
		ListenSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenSocket);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Rama's Start TCP Receiver
bool UUDPFunq::StartUDPReceiver(
	const FString& YourChosenSocketName,
	const FString& TheIP,
	const int32 ThePort
) {

	ScreenMsg("RECEIVER INIT");

	//~~~

	FIPv4Address Addr;
	FIPv4Address::Parse(TheIP, Addr);

	//Create Socket
	FIPv4Endpoint Endpoint(Addr, ThePort);

	//BUFFER SIZE
	int32 BufferSize = 2 * 1024 * 1024;

	ListenSocket = FUdpSocketBuilder(*YourChosenSocketName)
		.AsNonBlocking()
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.WithReceiveBufferSize(BufferSize);
	;

	FTimespan ThreadWaitTime = FTimespan::FromMilliseconds(100);
	UDPReceiver = new FUdpSocketReceiver(ListenSocket, ThreadWaitTime, TEXT("UDP RECEIVER"));
	UDPReceiver->OnDataReceived().BindUObject(this, &UUDPFunq::Recv);
	UDPReceiver->Start();
	return true;
}

void UUDPFunq::Recv(const FArrayReaderPtr& ArrayReaderPtr, const FIPv4Endpoint& EndPt)
{
	ScreenMsg("Received bytes", ArrayReaderPtr->Num());

	FAnyCustomData Data;
	*ArrayReaderPtr << Data;		//Now de-serializing! See AnyCustomData.h

									//BP Event
	BPEvent_DataReceived();
}