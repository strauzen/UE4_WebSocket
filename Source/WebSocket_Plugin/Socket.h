// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AllowWindowsPlatformTypes.h"
#include "libwebsockets.h"
#include <string>
#include "HideWindowsPlatformTypes.h"
#include "GameFramework/Actor.h"
#include "Socket.generated.h"

UCLASS()
class WEBSOCKET_PLUGIN_API ASocket : public AActor
{
	GENERATED_BODY()

	enum demo_protocols {

		PROTOCOL_DUMB_INCREMENT,
		//PROTOCOL_LWS_MIRROR,

		/* always last */
		DEMO_PROTOCOL_COUNT
	};

public:
	// Sets default values for this actor's properties
	ASocket();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void test();

	int callback_dumb_increment(struct libwebsocket_context* context, 
								struct libwebsocket* wsi, 
								enum libwebsocket_callback_reasons reason, 
								void* user, void* in, size_t len);

	unsigned int opts;
	int was_closed;
	int deny_deflate;
	int deny_mux;
	struct libwebsocket *wsi_mirror;
	int mirror_lifetime;
	volatile int force_exit;
	int longlived;
	struct libwebsocket_protocols protocols[2];

	FString stdStringToFString(std::string in);
};
