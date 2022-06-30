#include "CStringNode.h"
#include <iostream>
#include <utility>

CStringNode::CStringNode(std::string data, CStringNode::NodePtr prev, CStringNode::NodePtr next)
	: m_data(std::move(data))
	, m_prev(std::move(prev))
	, m_next(std::move(next))
{
}

std::string const& CStringNode::GetData() const
{
	return m_data;
}

CStringNode::NodePtr CStringNode::GetPrev() const
{
	return m_prev;
}

CStringNode::NodePtr CStringNode::GetNext() const
{
	return m_next;
}

void CStringNode::SetPrev(NodePtr const& ptr)
{
	m_prev = ptr;
}

void CStringNode::SetNext(NodePtr const& ptr)
{
	m_next = ptr;
}
