#include <vix_portaudio.h>
#include <vix_debugutil.h>
#include <vix_sndfile.h>

int
PAUDIO_Callback(const void* input,
				void* output,
				unsigned long frameCnt,
				const PaStreamCallbackTimeInfo* paTimeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData)
{
	SNDFILE_DATA* data = (SNDFILE_DATA*)userData;
	long readcount = 0;
	float* out = (float*)output;

	readcount = sf_read_float(data->handle, out, frameCnt * 2);
	for(int i = 0; i < frameCnt * 2; i++)
		out[i] *= data->amplitude;

	if(readcount <= 0) {
		printf("File ended");

		return paComplete;
	}

	return paContinue;
}

bool
PAUDIO_Error(PaError err)
{
	using namespace Vixen;

	if (err != paNoError) {
		const char* errText = Pa_GetErrorText(err);
#ifdef UNICODE
		UConverter cv;
		UString text = cv.from_bytes(errText);
		DebugPrintF(VTEXT("PortAudio Error: %s\n"), text.c_str());
#else
		DebugPrintF(VTEXT("PortAudio Error: %s\n"), errText);
#endif
		return true;
	}
	else {
		return false;
	}
}

bool
PAUDIO_Init()
{
	PaError err;
	err = Pa_Initialize();
	return PAUDIO_Error(err); //check error
}

bool
PAUDIO_Term()
{
	PaError err;
	err = Pa_Terminate();
	return PAUDIO_Error(err); //check error
}

void PAUDIO_QueryDevices()
{
	using namespace Vixen;

	int numDevices;
	numDevices = Pa_GetDeviceCount();
	if (numDevices < 0) {
		PAUDIO_Error(numDevices);
		return;
	}

	const PaDeviceInfo* deviceInfo;
	for (int i = 0; i < numDevices; i++)
	{
		deviceInfo = Pa_GetDeviceInfo(i);
		PAUDIO_PrintDevice(deviceInfo, i);
	}
}

void
PAUDIO_OpenDefaultStream(PaStream* stream,
							int inChannels,
							int outChannels,
							PaSampleFormat format,
							double sampleRate,
							unsigned long frameCnt,
							void* data)
{
	PaError error;
	error = Pa_OpenDefaultStream(&stream,  /* stream is a 'token' that we need
to save for future portaudio calls */
                        0,  /* no input */
						2,
						paFloat32,
						PAUDIO_SAMPLERATE,  /* use the same
sample rate as the sound file */
                        paFramesPerBufferUnspecified,  /* le*/
						PAUDIO_Callback,  /* callback function defined above */
                        data ); /* pass in our data structure so the
callback knows what's up */
	PAUDIO_Error(error);
}


bool
PAUDIO_CloseStream(PaStream* stream)
{
    PaError err;
    err = Pa_CloseStream(stream);
    return PAUDIO_Error(err);
}

void
PAUDIO_Sleep()
{
    Pa_Sleep(PAUDIO_SLEEPSECONDS * 1000);
}

void
PAUDIO_PrintDevice(const PaDeviceInfo* dInfo, size_t i)
{
	using namespace Vixen;

	if (!dInfo)
		return;


#ifdef UNICODE
	UConverter cv;
	UString name = cv.from_bytes(dInfo->name);
#else
	UString name(dInfo->name);
#endif


	DebugPrintF(VTEXT("AUDIO DEVICE [%d]\n"), i);
	DebugPrintF(VTEXT("\tNAME: %s\n"), name.c_str());
	DebugPrintF(VTEXT("\tMAX_ICHANNELS: %d\n"), dInfo->maxInputChannels);
	DebugPrintF(VTEXT("\tMAX_OCHANNELS: %d\n"), dInfo->maxOutputChannels);
}
