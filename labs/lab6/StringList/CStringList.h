#pragma once
#include "CStringIterator.h"
#include "CStringNode.h"
#include <iostream>

class CStringList
{
public:
	CStringList();

	CStringList(CStringList const& other) = delete;
	CStringList(CStringList&& other) = delete;

	[[nodiscard]] bool IsEmpty() const;
	[[nodiscard]] size_t GetSize() const;

	CStringList& PushBack(std::string const& data);
	CStringList& PushFront(std::string const& data);

	using iterator = CStringIterator<CStringNode>;
	using const_iterator = CStringIterator<const CStringNode>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	iterator begin();
	iterator end();
	[[nodiscard]] const_iterator begin() const;
	[[nodiscard]] const_iterator end() const;
	reverse_iterator rbegin();
	reverse_iterator rend();
	[[nodiscard]] const_reverse_iterator rbegin() const;
	[[nodiscard]] const_reverse_iterator rend() const;

private:
	size_t m_size;
	CStringNode::NodePtr m_begin, m_end;
};
