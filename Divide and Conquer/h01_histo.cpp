#include<iostream>
#include<vector>
#include <algorithm>
#include <cstdlib>

// Find the largest area rectangle in a histogram

const unsigned int maxAreaAtI(std::vector<unsigned int> H, const size_t elem){
	unsigned int max_area = H[elem];
	unsigned int min_height = H[elem];
    H.insert(H.begin(), 0);
    H.push_back(0);
	size_t l=elem+1, r=elem+1;
	while (l && r < H.size()-1){
		if (H[l-1] >= H[r+1])
			min_height = std::min(min_height, H[--l]);
		else
			min_height = std::min(min_height, H[++r]);
		max_area = std::max((unsigned long)max_area, min_height * (r - l + 1));
	}
	return max_area;
}

const unsigned int maxArea(const std::vector<unsigned int> H){
	if (!H.size())
		return 0;
	if (H.size() == 1)
		return H[0];
	const size_t m = H.size()/2;
	const unsigned int area_1 = maxArea(std::vector<unsigned int>(H.begin(), H.begin() + m));
	const unsigned int area_2 = maxArea(std::vector<unsigned int>(H.begin() + m, H.end()));
	const unsigned int area_3 = maxAreaAtI(H, m);
	return std::max({area_1, area_2, area_3});

}

int main(){
    const std::vector<unsigned int> V = {2, 1, 5, 6, 2, 3};
    std::cout << maxArea(V) << std::endl;
    return 0;
}
