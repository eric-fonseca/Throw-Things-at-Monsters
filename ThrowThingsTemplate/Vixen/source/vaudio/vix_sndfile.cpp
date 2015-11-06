#include <vix_sndfile.h>

SNDFILE_DATA*
SNDFILE_ReadFile(const char* filePath)
{
	SNDFILE_DATA* data = new SNDFILE_DATA;
	data->handle = sf_open(filePath, SFM_READ, &data->sfinfo);
	data->amplitude = 1.0f;
	
	return data;
}