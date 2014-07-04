#pragma once
#include "WaveInstrument.h"
#include "audio/DirSoundSource.h"
#include "msxml2.h"
#include "xmlhelp.h"
#include <vector>

class CWaveInstrumentFactory
{
public:
    CWaveInstrumentFactory(void);
    ~CWaveInstrumentFactory(void);

    void SetNote(CNote *note);
	void SetDrumNote(CNote *note);
	void SetDrumPitch(const std::wstring notefreq);
	bool LoadFile(const char *filename);

	CWaveInstrument *CreateDrum(std::wstring drumtype, CNote *note);
    //CWaveInstrument *CreateInstrument();

private:
    std::vector<short> m_wave;
	std::wstring m_type;
};