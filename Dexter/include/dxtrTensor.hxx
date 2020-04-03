#pragma once

#include <array>
#include <vector>
#include <unordered_map>
#include <exception>

#include <string>
#include <sstream>
#include <iostream>

namespace Dexter {
	template<class T, std::size_t N>
	class Tensor;

	template<class T, std::size_t N> Tensor<T, N>
	entryWiseAdd (
		const Tensor<T, N> &lhs,
		const Tensor<T, N>&rhs
	);
	template<class T, std::size_t N> Tensor<T, N>
	entryWiseSub (
		const Tensor<T, N>& lhs,
		const Tensor<T, N>& rhs
	);

	template<class T, std::size_t N> Tensor<T, N>
	entryWiseProd (
		const Tensor<T, N>& lhs,
		const Tensor<T, N>& rhs
	);
	template<class T, std::size_t N> Tensor<T, N>
	entryWiseDiv (
		const Tensor<T, N>& lhs,
		const Tensor<T, N>& rhs
	);

	template<class T, std::size_t N> Tensor<T, N>
	entryWiseExp (
		const Tensor<T, N>& lhs,
		const Tensor<T, N>& rhs
	);
	template<class T, std::size_t N> Tensor<T, N>
	entryWiseLog (
		const Tensor<T, N>& lhs,
		const Tensor<T, N>& rhs
	);
};



template <class T, std::size_t N>
class Dexter::Tensor {
	public:
		typedef std::array<std::size_t, N> uarr;
		typedef std::unordered_map<std::size_t, T> dat_map;
	private:
		T m_default_val;
		/* holds the  number of dimensions as
		 * the vector size and entries hold the size
		 * of each dimension. 
		 */ uarr m_dims;
		/* holds the dat in an unordered map to 
		 * save memory for large spared tensors
		 * and have "constant" time entry access
		 * according to the STL documentation
		 */ dat_map m_data;

		 bool is_valid(const std::size_t& id) const;
		 bool is_valid(const uarr& address) const;
	public:
		// constructors
		Tensor(T default_val = 0);
		Tensor(const uarr& dims, T default_val = 0);

		// destructors
		~Tensor() = default;
		
		std::size_t getNumberOfEntries() const;
		uarr getAddressFromId(const std::size_t& id) const;
		std::size_t getIdFromAddress(const uarr& address) const;
		T& at(const uarr& address);

		// print functions
		std::string addressToString(const std::size_t& id) const;
		void print() const;
};

#include "dxtrTensor.txx"
