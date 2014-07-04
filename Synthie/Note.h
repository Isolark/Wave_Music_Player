#pragma once

#include "EffectsSendTable.h"

#include "msxml2.h"
#include <string>

class CNote
{
public:
	CNote(void);
	CNote(int repeat);
	virtual ~CNote(void);

    int Measure() const {return m_measure;}
    double Beat() const {return m_beat;}
    const std::wstring &Instrument() const {return m_instrument;}  
    IXMLDOMNode *Node() {return m_node;}
	const CEffectsSendTable &GetSendTable() const { return m_sendTable; };

	void XmlLoad(IXMLDOMNode * xml, std::wstring & instrument, CEffectsSendTable *sendTable);

	bool operator<(const CNote &b);

private:
    std::wstring m_instrument;
    int m_measure;
	int m_repeat;
    double m_beat;
    CComPtr<IXMLDOMNode> m_node;
	CEffectsSendTable m_sendTable;
};

