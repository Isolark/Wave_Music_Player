#pragma once
#include "Instrument.h"
#include "Harmonic.h"
#include "AddNode.h"
#include <map>

class CAdditive :
	public CInstrument
{
public:
	CAdditive(void);
	virtual ~CAdditive(void); 

	virtual void Start();
    virtual bool Generate();

	void SetFreq(double f) {m_frequency = f;}
    void SetDuration(double d) {m_duration = d;}
	void SetNote(CNote *note);
	void AddHarmonic(CHarmonic harmonicNumber);

private:
	std::vector<CHarmonic> m_harmonics; //Store harmonics to add
	std::map<int,double> m_crossFades;
	CAudioNode* m_source;
	CAddNode* m_addNode;
	bool m_vibrato;
	double m_frequency;
    double m_duration;
    double m_time;
};

