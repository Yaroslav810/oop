#include "CStringIterator.h"

CStringListIterator::CStringListIterator()
	: m_ptr()
{
}

CStringListIterator::CStringListIterator(CStringListIterator::pointer ptr)
	: m_ptr(ptr)
{
}

CStringListIterator::CStringListIterator(const CStringNode::NodePtr& ptr)
	: m_ptr(ptr.get())
{
}

CStringListIterator::reference CStringListIterator::operator*() const
{
	return *m_ptr;
}

CStringListIterator::pointer CStringListIterator::operator->() const
{
	return m_ptr;
}

CStringListIterator& CStringListIterator::operator++()
{
	if (!m_ptr)
	{
		throw std::logic_error("unavailable iterator");
	}
	m_ptr = m_ptr->GetNext().get();
	return *this;
}

CStringListIterator& CStringListIterator::operator--()
{
	if (!m_ptr)
	{
		throw std::logic_error("unavailable iterator");
	}
	m_ptr = m_ptr->GetPrev().get();
	return *this;
}

CStringListIterator CStringListIterator::operator++(int)
{
	if (!m_ptr)
	{
		throw std::logic_error("unavailable iterator");
	}
	CStringListIterator temp(m_ptr);
	m_ptr = m_ptr->GetNext().get();
	return temp;
}

CStringListIterator CStringListIterator::operator--(int)
{
	{
		if (!m_ptr)
		{
			throw std::logic_error("unavailable iterator");
		}
		CStringListIterator temp(m_ptr);
		m_ptr = m_ptr->GetPrev().get();
		return temp;
	}
}

bool CStringListIterator::operator==(const CStringListIterator& iterator) const
{
	return m_ptr == iterator.m_ptr;
}

bool CStringListIterator::operator!=(const CStringListIterator& iterator) const
{
	return m_ptr != iterator.m_ptr;
}

CStringListConstIterator::CStringListConstIterator()
	: CStringListIterator()
{
}

CStringListConstIterator::CStringListConstIterator(const CStringNode::NodePtr& ptr)
	: CStringListIterator(ptr)
{
}

CStringListConstIterator::reference CStringListConstIterator::operator*() const
{
	return *m_ptr;
}

CStringListConstIterator::pointer CStringListConstIterator::operator->() const
{
	return m_ptr;
}

CStringListConstIterator& CStringListConstIterator::operator++()
{
	if (!m_ptr)
	{
		throw std::logic_error("unavailable iterator");
	}
	m_ptr = m_ptr->GetNext().get();
	return *this;
}

CStringListConstIterator& CStringListConstIterator::operator--()
{
	if (!m_ptr)
	{
		throw std::logic_error("unavailable iterator");
	}
	m_ptr = m_ptr->GetPrev().get();
	return *this;
}

CStringListConstIterator CStringListConstIterator::operator++(int)
{
	if (!m_ptr)
	{
		throw std::logic_error("unavailable iterator");
	}
	CStringListConstIterator temp(static_cast<const CStringNode::NodePtr>(m_ptr));
	m_ptr = m_ptr->GetNext().get();
	return temp;
}

CStringListConstIterator CStringListConstIterator::operator--(int)
{
	{
		if (!m_ptr)
		{
			throw std::logic_error("unavailable iterator");
		}
		CStringListConstIterator temp(static_cast<const CStringNode::NodePtr>(m_ptr));
		m_ptr = m_ptr->GetPrev().get();
		return temp;
	}
}
