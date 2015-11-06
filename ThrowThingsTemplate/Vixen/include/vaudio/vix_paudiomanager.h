#ifndef VIX_PAUDIOMANAGER_H
#define VIX_PAUDIOMANAGER_H

#include <vix_platform.h>
#include <vix_manager.h>
#include <vix_portaudio.h>
#include <vix_sndfile.h>

namespace Vixen {

	class VIX_API PAudioStream
	{
	public:
		PAudioStream();

		~PAudioStream();

	private:
		PaStream* m_stream;
	};

	class VIX_API PAudioManager
	{
	public:
		PAudioManager(void);

		void Init();
		void Term();
		void Play();
		void Stop();

	private:
	};

}

#endif