#ifndef VIX_SNDFILE_H
#define VIX_SNDFILE_H

//VIXEN INCLUDES
#include <vix_platform.h>

#include <sndfile.h>

#define SNDFILE_BUFFERLEN 4096

struct SNDFILE_DATA
{
	SNDFILE*  handle;
	SF_INFO   sfinfo;
	int       position;
	float     amplitude;
};

VIX_API
SNDFILE_DATA* SNDFILE_ReadFile(const char* filePath);

#endif