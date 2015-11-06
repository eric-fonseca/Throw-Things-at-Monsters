#include <vix_paudiomanager.h>

namespace Vixen {
		
	PAudioStream::PAudioStream()
	{
		m_stream = NULL;
	}

	PAudioStream::~PAudioStream()
	{
		Pa_CloseStream(m_stream);
	}

}