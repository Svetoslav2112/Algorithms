//This is an algorithm to calculate the PageRank of each website
//according to the probability he would be clicked by the user (popularity)
//Damping factor is used to handle with pages that do not lead to other pages(they are called sinks).
//We use the constant 0.85 for damping factor, which is considered precise enough for our purposes.
//The total sum of Page Ranks should evaluate to 1.00, which stands for 100% (% distributed among each page).
//In our case, due to the fact that damping factor is approx, if we have a "sink" Page, the sum will not evaluate to 1.00

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "PageNode.h"

#define iterations 100

int main() {
	//N pages, M edges between 2 URLs
	int N, M;
	std::cin >> N >> M;

	std::map<std::string, PageNode> pages;

	//M directed edges: url1 -> url2
	std::string url1, url2;
	for (int i = 0; i < M; i++) {
		std::cin >> url1 >> url2;

		//Put each PageNode into the map and update their vectors of neighbours
		if (pages.find(url1) == pages.end()) {
			pages.emplace(url1, PageNode(url1, N));
		}
		if (pages.find(url2) == pages.end()) {
			pages.emplace(url2, PageNode(url2, N));
		}

		pages[url1].addPointingTo(&pages[url2]);
		pages[url2].addPointedBy(&pages[url1]);
	}

	//Iterating 100 times to compute Rank of each PageNode in the map
	//O(N*K), where K is how many PageNodes point to the current PageNode (K comes from calculateRank() method)
	//Considering the limitation that each page points to less than 15 other pages, time complexity is acceptable
	//We can consider our graph sparse with the above limitation
	for (int i = 0; i < iterations; i++) {
		for (auto& page : pages) {
			page.second.calculateRank(N);
		}
	}

	//Using loop with O(N) complexity to collect PageNodes in a vector
	//Then sorting the vector by Rank(descending) - O(NlogN) complexity
	std::vector<PageNode> result;
	for (auto& page : pages) {
		result.push_back(page.second);
	}
	std::sort(result.begin(), result.end(), std::greater<PageNode>());

	//Printing result
	std::cout << "\n";
	std::cout.precision(3);
	for (PageNode& page: result) {
		std::cout << std::fixed << page;
	}

	return 0;
}