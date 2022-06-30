#include "CStringList.h"

CStringList::CStringList()
	: m_size(0)
	, m_begin(std::make_shared<CStringNode>())
	, m_end(std::make_shared<CStringNode>("", m_begin, nullptr))
{
	m_begin->SetNext(m_end);
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
	auto newNode = std::make_shared<CStringNode>(data, m_end->GetPrev(), m_end);
	m_end->GetPrev()->SetNext(newNode);
	m_end->SetPrev(newNode);
	m_size++;
	return *this;
}

CStringList& CStringList::PushFront(const std::string& data)
{
	auto newNode = std::make_shared<CStringNode>(data, m_begin, m_begin->GetNext());
	m_begin->GetNext()->SetPrev(newNode);
	m_begin->SetNext(newNode);
	m_size++;
	return *this;
}

std::string const& CStringList::GetBack() const
{
	if (IsEmpty())
		throw std::logic_error("Empty list");

	return m_end->GetPrev()->GetData();
}

std::string const& CStringList::GetFront() const
{
	if (IsEmpty())
		throw std::logic_error("Empty list");

	return m_begin->GetNext()->GetData();
}

void CStringList::Clear()
{
	auto begin = m_begin->GetNext();
	m_begin->SetNext(m_end);
	m_end->SetPrev(m_begin);
	while (begin != m_end)
	{
		auto next = begin->GetNext();
		begin->SetPrev(nullptr);
		begin->SetNext(nullptr);
		begin = next;
	}
	m_size = 0;
}

CStringList::iterator CStringList::Insert(CStringList::const_iterator& it, std::string const& data)
{
	if (it == nullptr)
	{
		throw std::out_of_range("Invalid iterator");
	}
	if (it == m_begin.get())
	{
		throw std::logic_error("Invalid memory area");
	}
	auto newNode = std::make_shared<CStringNode>(data, it->GetPrev(), it->GetPrev()->GetNext());
	newNode->GetNext()->SetPrev(newNode);
	newNode->GetPrev()->SetNext(newNode);
	m_size++;

	return { newNode->GetPrev().get() };
}

CStringList::iterator CStringList::Delete(CStringList::const_iterator& it)
{
	if (it == nullptr)
	{
		throw std::out_of_range("Invalid iterator");
	}
	if (it == m_begin.get() || it == m_end.get())
	{
		throw std::logic_error("Invalid memory area");
	}
	it->GetPrev()->SetNext(it->GetNext());
	it->GetNext()->SetPrev(it->GetPrev());
	m_size--;
	return { it->GetNext().get() };
}

CStringList::iterator CStringList::begin()
{
	return { m_begin->GetNext().get() };
}

CStringList::iterator CStringList::end()
{
	return { m_end.get() };
}

CStringList::const_iterator CStringList::begin() const
{
	return { m_begin->GetNext().get() };
}

CStringList::const_iterator CStringList::end() const
{
	return { m_end.get() };
}

CStringList::const_iterator CStringList::cbegin() const
{
	return { m_begin->GetNext().get() };
}

CStringList::const_iterator CStringList::cend() const
{
	return { m_end.get() };
}

CStringList::reverse_iterator CStringList::rbegin()
{
	return std::make_reverse_iterator(m_end->GetPrev().get());
}

CStringList::reverse_iterator CStringList::rend()
{
	return std::make_reverse_iterator(m_begin.get());
}

CStringList::const_reverse_iterator CStringList::rbegin() const
{
	return std::make_reverse_iterator(m_end->GetPrev().get());
}

CStringList::const_reverse_iterator CStringList::rend() const
{
	return std::make_reverse_iterator(m_begin.get());
}

CStringList::const_reverse_iterator CStringList::crbegin() const
{
	return std::make_reverse_iterator(m_end->GetPrev().get());
}

CStringList::const_reverse_iterator CStringList::crend() const
{
	return std::make_reverse_iterator(m_begin.get());
}
