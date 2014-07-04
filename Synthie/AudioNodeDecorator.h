#pragma once
#include "audionode.h"
class CAudioNodeDecorator :
	public CAudioNode
{
public:
	virtual ~CAudioNodeDecorator(void) { delete m_decoratedAudioNode; };

    //! Start the node generation
	virtual void Start() { m_decoratedAudioNode->Start(); }

    //! Cause one sample to be generated
	virtual bool Generate() { return m_decoratedAudioNode->Generate(); }
    
    //! Get the sample rate in samples per second
	virtual double GetSampleRate() { return m_decoratedAudioNode->GetSampleRate(); }

    //! Get the sample period in seconds
	virtual double GetSamplePeriod() { return m_decoratedAudioNode->GetSamplePeriod(); }

    //! Set the sample rate
	virtual void SetSampleRate(double s) { m_decoratedAudioNode->SetSampleRate(s); }

    //! Access a generated audio frame
	virtual const double *Frame() { return m_decoratedAudioNode->Frame(); }

	//! Access one channel of a generated audio frame
	virtual double Frame(int c) { return m_decoratedAudioNode->Frame(c); }

	//! Get the beats per minute
	virtual double GetBPM() { return m_decoratedAudioNode->GetBPM(); }

	//! Set the beats per minute
	virtual void SetBPM(double bpm) { m_decoratedAudioNode->SetBPM(bpm); }

	void ReleaseDecoratedAudioNode() { m_decoratedAudioNode = NULL; }

protected:
	CAudioNodeDecorator(CAudioNode* decoratedAudioNode) { m_decoratedAudioNode = decoratedAudioNode; }

	CAudioNode* m_decoratedAudioNode;

private:
	CAudioNodeDecorator(void);
};

