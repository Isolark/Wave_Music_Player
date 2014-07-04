#pragma once

#include "AudioNode.h"
#include "Note.h"
#include "EffectsSendTable.h"

#include <vector>

class CInstrument :
	public CAudioNode
{
public:
	CInstrument(void);
	virtual ~CInstrument(void);

	virtual void SetNote(CNote *note) = 0;

	const CEffectsSendTable &GetSendTable() const { return m_sendTable; };
	void SetSendTable(const CEffectsSendTable &sendTable) { m_sendTable = sendTable; };

private:
	CEffectsSendTable m_sendTable;
};

