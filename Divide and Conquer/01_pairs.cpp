#include<iostream>
#include<vector>

// Find closest pair of 2d-points

bool sortbysec(const std::pair<int,int> &a, const std::pair<int,int> &b){
    return (a.second < b.second);
}

const unsigned int l1Norm(std::pair<int, int> p1, std::pair<int, int> p2){
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

unsigned int closestDistance(std::vector<std::pair<int, int>> S){
	if (S.size() <= 1){
		return 0;
	}
    else if (S.size() <= 3){
        unsigned int d = UINT_MAX;
        for (unsigned int i = 0; i < S.size(); ++i)
            for (unsigned int j = i+1; j < S.size(); ++j)
                d = std::min(d, l1Norm(S[i], S[j]));
        return d;
    }
    std::sort(S.begin(), S.end());
    std::size_t const half_size = S.size()/2;
    unsigned int d_l = closestDistance(std::vector<std::pair<int, int>> (S.begin(), S.begin() + half_size));
    unsigned int d_r = closestDistance(std::vector<std::pair<int, int>> (S.begin() + half_size, S.end()));
    unsigned int d = std::min(d_l, d_r);

    std::vector<std::pair<int, int>> CloseCenter;
    for(const auto& point: S)
        if (l1Norm(point, S[half_size]) < d)
            CloseCenter.push_back(point);
    sort(CloseCenter.begin(), CloseCenter.end(), sortbysec);
    for (unsigned int i = 0; i < CloseCenter.size(); ++i)
        for (unsigned int j = i+1; (j < CloseCenter.size()) && (CloseCenter[j].second - CloseCenter[i].second) < d; ++j)
            d = std::min(d, l1Norm(CloseCenter[i], CloseCenter[j]));
    return d;
}

int main() {
    const std::vector<std::pair<int, int>> v = {{0, 0}, {-1, 2}, {3, 4}, {5, 4}};
    std::cout << closestDistance(v) << std::endl;
    return 0;
}