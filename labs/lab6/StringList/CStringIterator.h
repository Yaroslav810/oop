#pragma once
#include "CStringNode.h"
#include <iostream>
#include <iterator>

class CStringListIterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = ptrdiff_t;
	using value_type = CStringNode;
	using pointer = value_type*;
	using reference = value_type&;

	CStringListIterator();
	CStringListIterator(pointer ptr);
	CStringListIterator(const CStringNode::NodePtr& ptr);

	reference operator*() const;
	pointer operator->() const;

	CStringListIterator& operator++();
	CStringListIterator& operator--();
	CStringListIterator operator++(int);
	CStringListIterator operator--(int);

	bool operator==(const CStringListIterator& other) const;
	bool operator!=(const CStringListIterator& other) const;

protected:
	pointer m_ptr;
};

class CStringListConstIterator : public CStringListIterator
{
public:
	using value_type = const CStringNode;
	using pointer = value_type*;
	using reference = value_type&;

	CStringListConstIterator();
	CStringListConstIterator(const CStringNode::NodePtr& ptr);
	CStringListConstIterator(CStringNode* ptr);

	reference operator*() const;
	pointer operator->() const;

	CStringListConstIterator& operator++();
	CStringListConstIterator operator++(int);
	CStringListConstIterator& operator--();
	CStringListConstIterator operator--(int);
};
