#pragma once
#include <memory>
#include <string>

class CStringNode
{
public:
	using NodePtr = std::shared_ptr<CStringNode>;

	CStringNode() = default;
	CStringNode(std::string data, CStringNode::NodePtr prev, CStringNode::NodePtr next);

	[[nodiscard]] std::string const& GetData() const;
	[[nodiscard]] NodePtr GetPrev() const;
	[[nodiscard]] NodePtr GetNext() const;

	void SetPrev(NodePtr const& ptr);
	void SetNext(NodePtr const& ptr);

private:
	std::string m_data;
	NodePtr m_prev, m_next;
};
