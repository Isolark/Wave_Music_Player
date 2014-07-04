#pragma once
#include "audionodedecorator.h"
class CEnvelopeDecorator :
	public CAudioNodeDecorator
{
public:
	CEnvelopeDecorator(CAudioNode* decoratedAudioNode);
	virtual ~CEnvelopeDecorator(void);

	const double& GetAttack() const { return m_attack; };
	void SetAttack(const double& attack) { m_attack = attack; };
	const double& GetRelease() const { return m_release; };
	void SetRelease(const double& release) { m_release = release; };
	const double& GetDuration() const { return m_duration; };
	void SetDuration(const double& duration) { m_duration = duration; };

	virtual void Start();
	virtual bool Generate();
    virtual const double *Frame() { return m_frame; };
    virtual double Frame(int c) { return m_frame[c]; };



private:
	CEnvelopeDecorator(void);

	double m_attack;
	double m_decay;
	double m_sustain;
	double m_release;
	double m_duration;
	double m_time;

};

