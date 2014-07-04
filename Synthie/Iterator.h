#pragma once

template <class T>
class CIterator
{
public:
	virtual ~CIterator() { };

	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool Done() = 0;
	virtual T Current() = 0;

protected:
	CIterator() { };

private:
	CIterator(const CIterator &);
	CIterator &operator=(const CIterator &);
};

