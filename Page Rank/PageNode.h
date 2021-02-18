#ifndef PAGE_NODE_H
#define PAGE_NODE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <math.h>

#define e 0.00000001;
#define dampingFactor 0.85

class PageNode
{
private:

	float previousRank;
	float currentRank;
	std::string nameURL;
	std::vector<PageNode*> pointingTo;
	std::vector<PageNode*> pointedBy;

public:

	//Constructor meeting our needs
	PageNode() = default;
	PageNode(std::string& nameURL, const int& countOfAllPages);
	~PageNode() = default;

	//Methods to push_back new PageNodes into the vectors of neighbours
	void addPointingTo(PageNode* toAdd);
	void addPointedBy(PageNode* toAdd);

	//Used to update the currentRank and previousRank
	void calculateRank(const int& countOfAllPages);

	//Overloading operator> for sort (descending) 
	bool operator>(const PageNode& rhs) const;

	//Defining operator<< for easier printing of objects
	friend std::ostream& operator<<(std::ostream& os, const PageNode& pn);

	//Getters
	float getPreviousRank() const;
	float getCurrentRank() const;

};

PageNode::PageNode(std::string& nameURL, const int& countOfAllPages)
	: nameURL(nameURL)
	, pointingTo()
	, pointedBy() 
{
	//Initial Rank is same for each PageNode
	this->currentRank = (float) 1 / countOfAllPages;
	this->previousRank = this->currentRank;
}

void PageNode::addPointingTo(PageNode* toAdd) {
	this->pointingTo.push_back(toAdd);
}

void PageNode::addPointedBy(PageNode* toAdd) {
	this->pointedBy.push_back(toAdd);
}

void PageNode::calculateRank(const int& countOfAllPages) {
	this->previousRank = this->currentRank;
	float newRank = 0;

	for (PageNode* page : pointedBy) {
		newRank += (*page).previousRank / (int)(*page).pointingTo.size();
	}

	newRank = (1 - dampingFactor) / countOfAllPages + newRank * dampingFactor;

	this->currentRank = newRank;
}

bool PageNode::operator>(const PageNode& rhs) const {
	return (this->currentRank - rhs.currentRank) > e;
}

std::ostream& operator<<(std::ostream& os, const PageNode& pn) {
	os << std::setw(24) << std::left << pn.nameURL << "Rank:" << pn.currentRank << "\n";
	return os;
}

float PageNode::getPreviousRank() const {
	return this->previousRank;
}

float PageNode::getCurrentRank() const {
	return this->currentRank;
}

#endif // !PAGE_NODE_H