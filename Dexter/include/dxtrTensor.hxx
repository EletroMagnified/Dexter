#pragma once

#include <exception>

#include <array>
#include <vector>
#include <unordered_map>

#include <cmath>
#include <algorithm>

#include <string>
#include <sstream>
#include <iostream>

namespace Dexter {
	template<class T, std::size_t N>
	class Tensor;

	template<class T, std::size_t N>
	bool ranks_equal (
		const Tensor<T, N>& lhs,
		const Tensor<T, N>& rhs
	);
	template<class T, std::size_t N>
	bool dims_equal(
		const Tensor<T, N>& lhs,
		const Tensor<T, N>& rhs
	);

	template<class T, std::size_t N>
	Tensor<T, N> ewa(
		const Tensor<T, N>& lhs,
		const Tensor<T, N>& rhs
	);

	template<class T, std::size_t N>
	Tensor<T, N> ewa (
		const Tensor<T, N>& lhs,
		const Tensor<T, N>& rhs
	);
	template<class T, std::size_t N>
	Tensor<T, N> ews (
		const Tensor<T, N>& lhs,
		const Tensor<T, N>& rhs
	);
	template<class T, std::size_t N>
	Tensor<T, N> ewp (
	const Tensor<T, N>& lhs,
	const Tensor<T, N>& rhs
	);
	template<class T, std::size_t N> Tensor<T, N>
	ewd(
	const Tensor<T, N>& lhs,
	const Tensor<T, N>& rhs
	);

	template<class T, std::size_t N> Tensor<T, N>
	ewe(
	const Tensor<T, N>& lhs,
	const Tensor<T, N>& rhs
	);
	template<class T, std::size_t N> Tensor<T, N>
	ewl(
	const Tensor<T, N>& lhs,
	const Tensor<T, N>& rhs
	);
};

template <class T, std::size_t N>
class Dexter::Tensor {
	public:
		typedef std::int64_t key;
		typedef std::array<std::size_t, N> uarr;
		typedef std::unordered_map<key, T> dat_map;
		typedef typename dat_map::const_iterator celem;
		typedef typename dat_map::iterator elem;
		typedef std::pair<elem, bool> elemb;
	public:
		T m_default_val;	/**< Holds the default value for any entry that
							 *	 is not listed in m_data variable.
							 */
		uarr m_dims;		/**< Holds the number of dimensions as
							 *	 the vector size and the entries hold the size
							 *	 for each dimension. 
							 */
		dat_map m_data;		/**< Holds the data in an unordered map to 
							 * save memory for large spared tensors
							 * and has "constant" time entry access
							 * according to the STL documentation.
							 */

		 bool is_valid(const std::size_t& id) const;
		 bool is_valid(const uarr& address) const;
	public:
		// constructors
		Tensor(T default_val = 0);
		Tensor(const uarr& dims, T default_val = 0);

		// destructors
		~Tensor() = default;

		bool set_val(const key k, const T& v);
		bool get_val(const key k, T& v) const;
		
		void compress(T tol = 0);

		std::size_t n_elem() const;

		uarr idtoad(const std::size_t&) const;
		uarr idtoad_nocheck(const std::size_t&) const;

		std::size_t adtoid(const uarr&) const;
		std::size_t adtoid_nocheck(const uarr&) const;

		T& at(std::size_t id);
		T& at_nocheck(std::size_t id);
		T& at(const uarr& address);
		T& at_nocheck(const uarr& address);
		
		// print functions
		std::string adtostr(const uarr&) const;
		std::string adtostr_nocheck(const uarr&) const;

		std::string idtostrad(const std::size_t&) const;
		std::string idtostrad_nocheck(const std::size_t&) const;

		void print(const char* header = "") const;
		void print_mat(const char* header = "") const;
};

#include "dxtrTensor.txx"

template<class T, std::size_t N>
bool Dexter::ranks_equal (
	const Tensor<T, N>& lhs,
	const Tensor<T, N>& rhs
) {
	return ((lhs.m_dims.size() == rhs.m_dims.size()) ? true : false);
}
template<class T, std::size_t N>
bool Dexter::dims_equal (
	const Tensor<T, N>& lhs,
	const Tensor<T, N>& rhs
) {
	if (!ranks_equal(lhs, rhs)) {
		return false;
	}

	for (std::size_t it = 0; it < lhs.m_dims.size(); it++) {
		if (lhs.m_dims.at(it) != rhs.m_dims.at(it)) {
			return false;
		}
	}

	return true;
}
template<class T, std::size_t N>
Dexter::Tensor<T, N> Dexter::ewa (
	const Tensor<T, N>& lhs,
	const Tensor<T, N>& rhs
) {
	if (!dims_equal(lhs, rhs)) {
		std::exception ex("dimensions do not match");
		throw ex;
	}
	
	T default_val = lhs.m_default_val + rhs.m_default_val;
	Tensor<T, N> res(lhs.m_dims, default_val);

	for (
		typename Tensor<T, N>::celem lhs_el = lhs.m_data.begin();
		lhs_el != lhs.m_data.end();
		lhs_el++
	) {
		//lhs_el->second;
	}

	return res;
}
template<class T, std::size_t N>
Dexter::Tensor<T, N> Dexter::ews (
	const Tensor<T, N>& lhs,
	const Tensor<T, N>& rhs
) {}

template<class T, std::size_t N>
Dexter::Tensor<T, N> Dexter::ewp (
	const Tensor<T, N>& lhs,
	const Tensor<T, N>& rhs
) {}
template<class T, std::size_t N>
Dexter::Tensor<T, N> Dexter::ewd(
	const Tensor<T, N>& lhs,
	const Tensor<T, N>& rhs
) {}

template<class T, std::size_t N>
Dexter::Tensor<T, N> Dexter::ewe(
	const Tensor<T, N>& lhs,
	const Tensor<T, N>& rhs
) {}
template<class T, std::size_t N>
Dexter::Tensor<T, N> Dexter::ewl(
	const Tensor<T, N>& lhs,
	const Tensor<T, N>& rhs
) {}

