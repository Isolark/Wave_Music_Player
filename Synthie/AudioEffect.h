#pragma once
class CAudioEffect
{
public:
	virtual ~CAudioEffect() { }

	// initializes the effect
	virtual void Start() = 0;

	// this method uses frame as both an in and out parameter
	//   a frame of input will be read from frame
	//   and the result will be written to frame when complete
	virtual void Process(double * const &frame) = 0;

	const unsigned int& GetChannels() const { return m_channels; };
	void SetChannels(const unsigned int& channels) { m_channels = channels; };

	const double& GetSampleRate() const { return m_sampleRate; };
	void SetSampleRate(const double& sampleRate) { m_sampleRate = sampleRate; m_samplePeriod = 1.0 / sampleRate; };

	const double& GetSamplePeriod() const { return m_samplePeriod; };
	void SetSamplePeriod(const double& samplePeriod) { m_samplePeriod = samplePeriod; m_sampleRate = 1.0 / samplePeriod; };

	const double& GetBPM() const { return m_bpm; };
	void SetBPM(const double& bpm) { m_bpm = bpm; };

	class Factory
	{
	public:
		virtual ~Factory() { };

		virtual CAudioEffect *Create() = 0;

		virtual void XmlLoad(IXMLDOMNode * xml) = 0;

	protected:
		Factory() { }

	private:
		Factory(const Factory &);
		Factory &operator=(const Factory &);
	};

protected:
	// protect the audio effect to prevent instantion of this class directly
	CAudioEffect(): m_channels(2), m_sampleRate(44100.0), m_bpm(120) { m_samplePeriod = 1.0 / m_sampleRate; }

private:
	CAudioEffect(const CAudioEffect &);
	CAudioEffect &operator=(const CAudioEffect &);

	unsigned int m_channels;
	double m_sampleRate;
	double m_samplePeriod;
	double m_bpm;
};

