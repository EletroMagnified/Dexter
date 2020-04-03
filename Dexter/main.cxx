#include <iostream>
#include "dxtrTensor.hxx"


using namespace Dexter;

int main() {

	Tensor<double, 1>::uarr dims = {3};
	Tensor<double, 1> A(dims);

	//A.at({0}) = 1;

	A.print();

	std::cout << "End of program. (press any key to continue... )" << std::endl;
	std::cin.get();
	return 0;
}