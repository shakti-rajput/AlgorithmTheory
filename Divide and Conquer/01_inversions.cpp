#include<iostream>
#include<vector>



long count_Inversions (std::vector<int> & A, const size_t & begin, const size_t & end){
    if (end - begin == 1){
        return 0;
    }
    std::size_t const middle = (begin + end)/2;
    long inversions = 0;

    inversions += count_Inversions(A, begin, middle);
    inversions += count_Inversions(A, middle, end);

    size_t i=begin, j=middle, k=0;
    std::vector<int> aux (end - begin);
    while (i < middle && j < end){
        if (A[i] > A[j]){
            inversions += middle - i;
            aux[k++] = A[j++];
        }
        else
            aux[k++] = A[i++];
    }
    while(i < middle) aux[k++] = A[i++];
    //while(j < end) aux[k++] = A[j++]; --> overkill

    for (size_t ind=0; ind<j - begin; ind++)
        A[begin+ind] = aux[ind];
    return inversions;
}
long countInversions (std::vector<int> & A){
    return count_Inversions(A, 0, A.size());
}

long count_Inversions_inplace (std::vector<int> & A, const size_t & begin, const size_t & end){
    if (end - begin == 1){
        return 0;
    }
    std::size_t separator = (begin + end)/2;
    long inversions = 0;

    inversions += count_Inversions_inplace(A, begin, separator);
    inversions += count_Inversions_inplace(A, separator, end);

    for (size_t i=begin; i < separator && separator < end; i++){
        if (A[i] > A[separator]){
            inversions += separator - i;
            std::rotate( A.begin() + i, A.begin() + separator, A.begin() + separator + 1);
            separator++;
        }
    }
    return inversions;
}
long countInversionsInPlace (std::vector<int> & A){
    return count_Inversions_inplace(A, 0, A.size());
}


int main() {
    std::vector<int> v = {2, 1, 3, -2, -1, 0, 5, 4, 3, 2,2, 1, 3, -2, -1, 0, 5, 4, 3, 23, 2,3,1, 12 ,312,3};
    std::cout << countInversions(v) << std::endl;
    std::vector<int> p = {2, 1, 3, -2, -1, 0, 5, 4, 3, 2,2, 1, 3, -2, -1, 0, 5, 4, 3, 23, 2,3,1, 12 ,312,3};
    std::cout << countInversionsInPlace(p) << std::endl;
    return 0;
}
