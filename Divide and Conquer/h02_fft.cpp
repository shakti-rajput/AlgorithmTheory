#include<iostream>
#include<vector>
#include<complex>

// Compute the Fast Fourier Transform of any polynomial, prints added

const double pi = std::acos(-1);

const std::vector<std::complex<double>> fft(const std::vector<std::complex<double>> A, unsigned int step){
    
    size_t N = A.size();

    // Base Case
    if (N <= 1) // cover the case of passing empty vector, i.e. implicit f(x) = 0
        return A;

    // Divide
    std::vector<std::complex<double>> D0, D1;
    for (size_t ind=0; ind < N; ++ind)
        if (ind & 1)
            D1.push_back(A[ind]); // odds 
        else
            D0.push_back(A[ind]); // evens

    // print the odd and the even splits
    step++; // recursion depth
    std::cout << "d[" << step << "_0] = [ ";
    for(const auto& d0: D0)
        std::cout << std::real(d0) << " ";
    std::cout << "]\n";
    std::cout << "d[" << step << "_1] = [ ";
    for(const auto& d1: D1)
        std::cout << std::real(d1) << " ";
    std::cout << "]\n";

    // Conquer (recursively call fft on each part)
    D0 = fft(D0, step);
    D1 = fft(D1, step);

    // auxilirary variables as in slides
    const std::complex<double> i(0, 1); // complex imag unit
    const std::complex<double> omega_n = std::exp(2.0 * pi * i / (double) N);
    std::complex<double> omega(1, 0); // 1 (real)
    std::vector<std::complex<double>> D(N);

    // Combine
    for (size_t k = 0; k < N/2; ++k){
        std::complex<double> x = omega * D1[k];
        D[k] = D0[k] + x;
        D[k + N/2] = D0[k] - x;
        omega *= omega_n;        
    }

    // print temporary d, containing (w, p(w))
    std::cout << "d[" << step << "] = [ ";
    for(const auto& d: D)
        std::cout << d << " ";
    std::cout << "]\n";
    return D;
}

const std::vector<std::complex<double>> CallFFT(const std::vector<int> A){
    const std::vector<std::complex<double>> ComplexA(A.begin(), A.end());
    return fft(ComplexA, 0);
}

int main(){
    
    // V is of the form f(x) = V[0] + V[1]*x + V[2]*(x^2) + ...
    const std::vector<int> V = {1, 2, 3, 4, 5, 6, 7, 8};
    const std::vector<std::complex<double>> D = CallFFT(V);
    for(const auto& d: D)
        std::cout << d << " ";
    std::cout << std::endl;
    return 0;
}

/*
Expected Result:
d[1_0] = [ 1 3 5 7 ]
d[1_1] = [ 2 4 6 8 ]
d[2_0] = [ 1 5 ]
d[2_1] = [ 3 7 ]
d[3_0] = [ 1 ]
d[3_1] = [ 5 ]
d[3] = [ (6,0) (-4,0) ]
d[3_0] = [ 3 ]
d[3_1] = [ 7 ]
d[3] = [ (10,0) (-4,0) ]
d[2] = [ (16,0) (-4,-4) (-4,0) (-4,4) ]
d[2_0] = [ 2 6 ]
d[2_1] = [ 4 8 ]
d[3_0] = [ 2 ]
d[3_1] = [ 6 ]
d[3] = [ (8,0) (-4,0) ]
d[3_0] = [ 4 ]
d[3_1] = [ 8 ]
d[3] = [ (12,0) (-4,0) ]
d[2] = [ (20,0) (-4,-4) (-4,0) (-4,4) ]
d[1] = [ (36,0) (-4,-9.65685) (-4,-4) (-4,-1.65685) (-4,0) (-4,1.65685) (-4,4) (-4,9.65685) ]
(36,0) (-4,-9.65685) (-4,-4) (-4,-1.65685) (-4,0) (-4,1.65685) (-4,4) (-4,9.65685) 
*/

