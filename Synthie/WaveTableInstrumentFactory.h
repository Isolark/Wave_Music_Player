#pragma once

#include "WaveInstrument.h"
#include "Wavetableinstrument.h"
#include "audio/DirSoundSource.h"
#include "msxml2.h"
#include "xmlhelp.h"
#include <vector>

class CWaveTableInstrumentFactory
{
public:
	CWaveTableInstrumentFactory(void);
	virtual ~CWaveTableInstrumentFactory(void);

	void SetNote(CNote *note);
	bool LoadFile(const char *filename);

	CWavetableinstrument *CreateInstrument();
    //CWaveTableInstrument *CreateInstrument();


private:
    std::vector<short> m_wave;
	std::wstring m_type;
};

