#pragma once
#include "CStringIterator.h"
#include "CStringNode.h"
#include <iostream>

class CStringList
{
public:
	using iterator = CStringListIterator;
	using const_iterator = CStringListConstIterator;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	CStringList();

	CStringList(CStringList const& other) = delete;
	CStringList(CStringList&& other) = delete;

	iterator begin();
	iterator end();
	[[nodiscard]] const_iterator begin() const;
	[[nodiscard]] const_iterator end() const;
	[[nodiscard]] const_iterator cbegin() const;
	[[nodiscard]] const_iterator cend() const;
	reverse_iterator rbegin();
	reverse_iterator rend();
	[[nodiscard]] const_reverse_iterator rbegin() const;
	[[nodiscard]] const_reverse_iterator rend() const;
	[[nodiscard]] const_reverse_iterator crbegin() const;
	[[nodiscard]] const_reverse_iterator crend() const;

	[[nodiscard]] bool IsEmpty() const;
	[[nodiscard]] size_t GetSize() const;

	CStringList& PushBack(std::string const& data);
	CStringList& PushFront(std::string const& data);

	[[nodiscard]] std::string const& GetBack() const;
	[[nodiscard]] std::string const& GetFront() const;

	void Clear();

	iterator Insert(CStringListIterator& it, std::string const& data);
	iterator Delete(const_iterator& it);

private:
	size_t m_size;
	CStringNode::NodePtr m_begin, m_end;
};
