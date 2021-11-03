#include<iostream>
#include<vector>

// Count number of inverted elements

unsigned int countInversions (std::vector<int> A){
    if (A.size() <= 1){
        return 0;
    }
    std::size_t const half_size = A.size()/2;
    unsigned int inversions = 0;

    std::vector<int> A_l(A.begin(), A.begin() + half_size);
    inversions += countInversions(A_l);

    std::vector<int> A_r(A.begin() + half_size, A.end());
    inversions += countInversions(A_r);

    unsigned int i=0, j=0;
    while ((i < A_l.size()) && (j < A_r.size())){
        if (A_l[i] > A_r[j]){
            inversions += half_size - i;
            j++;
        }
        else{
            i++;
        }
    }
    return inversions;
}


int main() {
    const std::vector<int> v = {4, 1, 5, 2, 7, 10, 6};
    std::cout << countInversions(v) << std::endl;
    return 0;
}
