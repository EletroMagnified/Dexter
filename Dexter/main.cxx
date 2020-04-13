#include <iostream>
#include <chrono>
#include "dxtrTensor.hxx"

/** 
 * \mainpage Dexter User Manual
 *
 * - \subpage intro "Intro"
 * - \subpage advanced "Advance usage"
 *
 */

/**
 * \page intro "Introduction"
 * This is the introduction page
 */

/**
 * \page advanced "Not for faaint in heart."
 * This is the advanced page documentation
 */

using namespace Dexter;

bool Test1();
bool Test2();

int main() {
	constexpr std::size_t rank = 2;
	Tensor<double, rank>::uarr addr, dims;
	std::size_t id;
	std::size_t dimSize = 3;

	// initializing Tensors
	for (std::size_t it = 0; it < rank; it++) {
		dims[it] = dimSize;
	}
	
	Tensor<double, rank> A(dims), B(dims), C(dims);

	for (std::size_t it = 0; it < A.n_elem(); it++) {
		A.at_nocheck(it) = it + 1;
	}
	for (std::size_t it = 0; it < B.n_elem(); it++) {
		B.at_nocheck(it) = it + 1;
	}
	
	C = ewa(A, B);

	A.print_mat("A");
	B.print_mat("B");
	C.print_mat("C");

	std::cout << "\nEnd of program. (press any key to continue... )\n";
	std::cin.get();
	return 0;
}

/**
 * Tests weather idtoad and adtoid work as intentioned.
 */
bool Test1() {
	bool passed = true;

	constexpr std::size_t rank = 3;
	Tensor<double, rank>::uarr addr, dims;

	std::size_t id;
	std::size_t dimSize = 3;

	// initializing Tensor
	for (std::size_t it = 0; it < rank; it++) {
		dims[it] = dimSize;
	} Tensor<double, rank> A(dims);

	for (std::size_t it = 0; it < A.n_elem(); it++) {
		addr = A.idtoad(it);
		id = A.adtoid(addr);

		if (it != id) {
			passed = false;
			break;
		}
		//std::cout << it << " " << id << "\n";
	}

	return passed;
}

/**
 * Tests the speed of idtoad and adtoid.
 */
bool Test2() {
	bool passed = true;
	constexpr std::size_t rank = 3;
	Tensor<double, rank>::uarr addr, dims;

	std::size_t id;
	std::size_t dimSize = 3;

	// initializing Tensor
	for (std::size_t it = 0; it < rank; it++) {
		dims[it] = dimSize;
	} Tensor<double, rank> A(dims);

	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;



	start = std::chrono::steady_clock::now();
	//std::vector<double> a(dimSize * dimSize * dimSize, 0);
	for (std::size_t it = 0; it < A.n_elem(); it++) {
		addr = A.idtoad(it);
		id = A.adtoid(addr);
	}
	end = std::chrono::steady_clock::now();

	elapsed_seconds = end - start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";



	A.print();

	return passed;
}