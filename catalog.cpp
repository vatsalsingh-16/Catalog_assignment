#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// Function to decode the y-values based on their base
long long decode_value(int base, const std::string& value) {
    return std::stoll(value, nullptr, base);
}

// Function to calculate the constant term using Lagrange Interpolation
double lagrange_interpolation(const std::vector<int>& x_values, const std::vector<long long>& y_values, int k) {
    double constant_term = 0;
    
    // Loop over each point (x_i, y_i)
    for (int i = 0; i < k; ++i) {
        int xi = x_values[i];
        double yi = static_cast<double>(y_values[i]);
        
        // Compute the Lagrange basis polynomial L_i(0)
        double term = yi;
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                int xj = x_values[j];
                term *= (0 - xj) / static_cast<double>(xi - xj);  // L_i(0) = Π (0 - xj) / (xi - xj)
            }
        }
        
        // Add the contribution of this term to the constant term
        constant_term += term;
    }
    
    return constant_term;
}

void run_test_case(int n, int k, const std::vector<int>& x_values, const std::vector<int>& bases, const std::vector<std::string>& y_encoded_values) {
    std::vector<long long> y_values;
    
    // Decode y_values from the base and encoded string
    for (int i = 0; i < n; ++i) {
        long long y = decode_value(bases[i], y_encoded_values[i]);
        y_values.push_back(y);
    }
    
    // Apply Lagrange interpolation to find the constant term
    double constant_term = lagrange_interpolation(x_values, y_values, k);
    
    // Output the result
    std::cout << "Constant term: " << constant_term << std::endl;
}

int main() {
    // Test Case 1
    int n1 = 4;  // Number of points
    int k1 = 3;  // Minimum number of points required to solve for the polynomial
    
    std::vector<int> x_values1 = {1, 2, 3, 6};
    std::vector<int> bases1 = {10, 2, 10, 4};
    std::vector<std::string> y_encoded_values1 = {"4", "111", "12", "213"};
    
    std::cout << "Test Case 1:" << std::endl;
    run_test_case(n1, k1, x_values1, bases1, y_encoded_values1);
    
    // Test Case 2
    int n2 = 9;
    int k2 = 6;
    
    std::vector<int> x_values2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> bases2 = {10, 16, 12, 11, 16, 10, 14, 9, 8};
    std::vector<std::string> y_encoded_values2 = {
        "28735619723837",
        "1A228867F0CA",
        "32811A4AA0B7B",
        "917978721331A",
        "1A22886782E1",
        "28735619654702",
        "71AB5070CC4B",
        "122662581541670",
        "642121030037605"
    };
    
    std::cout << "Test Case 2:" << std::endl;
    run_test_case(n2, k2, x_values2, bases2, y_encoded_values2);
    
    return 0;
}
