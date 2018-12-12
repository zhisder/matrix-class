
#include <matrix.hpp>
#include <iostream>

int main() {
	auto m1 = Matrix::matrix<int>(3, 3);
	m1("I");
	std::cout << m1 << std::endl;
	auto m2 = Matrix::matrix<int>(3, 3);
	m2(1, 2) = 1;
	std::cout << m2 << std::endl;
	m2("T");
	std::cout << m2 << std::endl;
	auto m3 = m1 * m2;
	std::cout << m3*m1 << std::endl;

	
}