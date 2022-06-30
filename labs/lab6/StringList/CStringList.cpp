#include "CStringList.h"

CStringList::CStringList()
	: m_size(0)
	, m_begin(nullptr)
	, m_end(nullptr)
{
}

bool CStringList::IsEmpty() const
{
	return m_size == 0;
}

size_t CStringList::GetSize() const
{
	return m_size;
}

CStringList& CStringList::PushBack(const std::string& data)
{
	auto newNode = std::make_shared<CStringNode>(data, m_end, nullptr);
	if (!m_size)
	{
		m_begin = newNode;
	}
	else
	{
		m_end->SetNext(newNode);
	}
	m_end = newNode;
	m_size++;
	return *this;
}

CStringList& CStringList::PushFront(const std::string& data)
{
	auto newNode = std::make_shared<CStringNode>(data, nullptr, m_begin);
	if (!m_size)
	{
		m_end = newNode;
	}
	else
	{
		m_begin->SetPrev(newNode);
	}
	m_begin = newNode;
	m_size++;
	return *this;
}

CStringList::iterator CStringList::begin()
{
	return { m_begin.get() };
}

CStringList::iterator CStringList::end()
{
	return { m_end->GetNext().get() };
}

CStringList::const_iterator CStringList::begin() const
{
	return { m_begin.get() };
}

CStringList::const_iterator CStringList::end() const
{
	return { m_end->GetNext().get() };
}

CStringList::reverse_iterator CStringList::rbegin()
{
	return std::make_reverse_iterator(end());
}

CStringList::reverse_iterator CStringList::rend()
{
	return std::make_reverse_iterator(begin()->GetNext().get());
}

CStringList::const_reverse_iterator CStringList::rbegin() const
{
	return std::make_reverse_iterator(end());
}

CStringList::const_reverse_iterator CStringList::rend() const
{
	return std::make_reverse_iterator(begin()->GetNext().get());
}
