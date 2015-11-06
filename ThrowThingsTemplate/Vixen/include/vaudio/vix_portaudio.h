#ifndef VIX_PORTAUDIO_H
#define VIX_PORTAUDIO_H

#include <vix_platform.h>
#include <portaudio.h>
#include <stdlib.h>

/*PORTAUDIO DEFINES*/
#define PAUDIO_SAMPLERATE   44100
#define PAUDIO_SLEEPSECONDS 2

struct PAUDIO_FILE
{
	PaStream*	stream;
	const char*	name;
};

/*
*
*	PAUDIO_Callback
*
*/
VIX_API
int PAUDIO_Callback(const void* input,
					void* output,
					unsigned long frameCnt,
					const PaStreamCallbackTimeInfo* paTimeInfo,
					PaStreamCallbackFlags statusFlags,
					void* userData);


/*
*	PAUDIO_Error
*	Checks for PortAudio error and outputs
*   error string.
*   returns true if error
*   return false if no error
*/
VIX_API
bool PAUDIO_Error(PaError err);

/*
*	PAUDIO_Init
*	Initializes PortAudio
*
*	Called on application startup
*/
VIX_API
bool PAUDIO_Init();

/*
*	PAUDIO_Term
*	Terminates PortAudio
*
*	Called on application exit
*/
VIX_API
bool PAUDIO_Term();

/*
*	PAUDIO_QueryDevices
*	Queries physical audio devices and outputs
*   information for each device.
*
*/
VIX_API
void PAUDIO_QueryDevices();

/*
*   PAUDIO_Sleep
*
*   Sleeps PortAudio caller for PAUDIO_SLEEPSECONDS
*
*/
VIX_API
void PAUDIO_Sleep();

/*
*	PAUDIO_PrintDevice
*	Prints information about specified device
*
*/
VIX_API
void PAUDIO_PrintDevice(const PaDeviceInfo* dInfo, size_t i);


VIX_API
void PAUDIO_OpenDefaultStream(PaStream* stream,
							  int inChannels,
							  int outChannels,
							  PaSampleFormat format,
							  double sampleRate,
							  unsigned long frameCnt,
							  void* data);

							  

VIX_API
bool PAUDIO_CloseStream(PaStream* stream);

#endif
