// Fill out your copyright notice in the Description page of Project Settings.

#include "WebSocket_Plugin.h"
#include "Socket.h"

//int ASocket::was_closed;
//int ASocket::deny_deflate;
//int ASocket::deny_mux;

// Sets default values
ASocket::ASocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mirror_lifetime = 0;
	force_exit = 0;
	longlived = 0;

	libwebsocket_protocols temp = {
		"dumb-increment-protocol,fake-nonexistant-protocol",
		this->callback_dumb_increment,
		0,
		20
	};
	protocols[0] = temp;
	temp = { NULL, NULL, 0, 0 };
	protocols[1] = temp;
}

// Called when the game starts or when spawned
void ASocket::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASocket::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASocket::test()
{

}

int ASocket::callback_dumb_increment(struct libwebsocket_context* context,
struct libwebsocket* wsi,
enum libwebsocket_callback_reasons reason,
	void* user, void* in, size_t len)
{
	switch (reason) {

	case LWS_CALLBACK_CLIENT_ESTABLISHED:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("callback_dumb_increment: LWS_CALLBACK_CLIENT_ESTABLISHED\n")));
		//fprintf(stderr, "callback_dumb_increment: LWS_CALLBACK_CLIENT_ESTABLISHED\n");
		break;

	case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("callback_dumb_increment: LWS_CALLBACK_CLIENT_CONNECTION_ERROR\n")));
		was_closed = 1;
		break;

	case LWS_CALLBACK_CLOSED:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("callback_dumb_increment: LWS_CALLBACK_CLOSED\n")));
		was_closed = 1;
		break;

	case LWS_CALLBACK_CLIENT_RECEIVE:
		((char *)in)[len] = '\0';
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("callback_dumb_increment: rx %d '%s'\n"), (int) length, (char *) in));
		break;

		/* because we are protocols[0] ... */

	case LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:
		if ((strcmp((char *)in, "deflate-stream") == 0) && deny_deflate) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("callback_dumb_increment: denied deflate-stream extension\n")));
			return 1;
		}
		if ((strcmp((char *)in, "deflate-frame") == 0) && deny_deflate) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("callback_dumb_increment: denied deflate-frame extension\n")));
			return 1;
		}
		if ((strcmp((char *)in, "x-google-mux") == 0) && deny_mux) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("callback_dumb_increment: denied x-google-mux extension\n")));
			return 1;
		}

		break;

	default:
		break;
	}

	return 0;
}

/* Private Functions*/

FString ASocket::stdStringToFString(std::string in)
{
	return FString(in.c_str());
}