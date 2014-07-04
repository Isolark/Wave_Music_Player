#pragma once
#include "instrument.h"
#include "ARDecorator.h"
#include "SubNode.h"
#include <vector>
#include <string>
class CSubtractive :
	public CInstrument
{
public:
	CSubtractive(void){CARDecorator m_dar = new CARDecorator(GetSource());}
	virtual ~CSubtractive(void);

	virtual void Start();
    virtual bool Generate();

    void SetFreq(double f) {m_sub.SetFreq(f);}
    void SetAmplitude(double a) {m_amplitude = a;}
    void SetDuration(double d) {m_duration = d;}
	CAudioNode* GetSource(){return m_source;}
	void SetNote(CNote *note);

private:
	std::vector<double> wavetable; //Store samples for table playback
	CAudioNode* m_source;
	double m_frequency;
	double m_amplitude;
    double m_duration;
    double m_time;
	int style;
	CSubNode m_sub;


};

