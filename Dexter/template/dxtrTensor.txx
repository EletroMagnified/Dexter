template <class T, std::size_t N>
Dexter::Tensor<T, N>::Tensor(
	T default_val
)
	:	m_default_val(default_val) {}
template <class T, std::size_t N>
Dexter::Tensor<T, N>::Tensor(
	const uarr& dims,
	T default_val
)
	:	m_dims(dims), 
		m_default_val(default_val) {
}

template <class T, std::size_t N> bool
Dexter::Tensor<T, N>::set_val (
	const key k,
	const T& v
) {
	
}
template <class T, std::size_t N> bool
Dexter::Tensor<T, N>::get_val(
	const key k,
	T& val
) const {

}

/**
 * Searches for values equal in the data
 * that are equal to the default value and
 * deletes them to from the data to save
 * momery resources
 */
template <class T, std::size_t N> void
Dexter::Tensor<T, N>::compress(T tol) {
	elem it = m_data.begin();
	while (it != m_data.end()) {
		if (std::abs(it->second) == std::abs(m_default_val)) {
			it = m_data.erase(it);
		} else {
			it++;
		}
	}
}

template <class T, std::size_t N> bool
Dexter::Tensor<T, N>::is_valid (
	const std::size_t& id
) const {
	bool is_valid = true;

	if (!(id < n_elem())) {
		is_valid = false;
	}

	return is_valid;
}
/**
 * Validates the input address. makes sure
 * the input is within a valid address range
 * set by in m_dims.
 */
template <class T, std::size_t N> bool
Dexter::Tensor<T, N>::is_valid (
	const uarr& address
) const {
	bool is_valid = true;
	
	for (
		std::size_t it = 0;
		it < m_dims.size();
		it++
	) {
		if (!(address.at(it) < m_dims.at(it))) {
			is_valid = false;
			break;
		}
	}

	return is_valid;
}
template <class T, std::size_t N> std::size_t
Dexter::Tensor<T, N>::n_elem (
) const {
	std::size_t n_elem = 0;

	if (m_dims.size() > 0) {
		n_elem = m_dims.at(0);
		for (std::size_t it = 1; it < m_dims.size(); it++) {
			n_elem *= m_dims.at(it);
		}
	}

	return n_elem;
}
template <class T, std::size_t N> typename Dexter::Tensor<T, N>::uarr
Dexter::Tensor<T, N>::idtoad (
	const std::size_t& id
) const {
	if (!is_valid(id)) {
		//out of bounds
		std::exception ex("Out of bounds");
		throw ex;
	}

	return idtoad_nocheck(id);
}
template <class T, std::size_t N> typename Dexter::Tensor<T, N>::uarr
Dexter::Tensor<T, N>::idtoad_nocheck (
	const std::size_t& id
) const {
	uarr addr;
	std::size_t stride, remainder;

	remainder = id;
	for (
		std::size_t it1 = 0;
		it1 < m_dims.size();
		it1++
	) {
		stride = 1;
		for (
			std::size_t it2 = it1;
			it2 < m_dims.size() - 1;
			it2++
		) {
			stride *= m_dims.at(it2);
		}
		addr.at(it1) = remainder / stride;
		remainder = remainder % stride;
	}

	return addr;
}
template <class T, std::size_t N> std::size_t
Dexter::Tensor<T, N>::adtoid (
	const uarr& addr
) const {
	if (!is_valid(addr)) {
		//out of bounds
		std::exception ex("Out of bounds");
		throw ex;
	}

	return adtoid_nocheck(addr);
}
template <class T, std::size_t N> std::size_t
Dexter::Tensor<T, N>::adtoid_nocheck (
	const uarr& address
) const {

	std::size_t id = 0;
	for (std::size_t it = 0; it < m_dims.size() - 1; it++) {
		id += address.at(it);
		id *= m_dims.at(it);
	}
	id += *address.rbegin();

	return id;
}
template <class T, std::size_t N> T&
Dexter::Tensor<T, N>::at (
	const uarr& address
) {
	std::size_t id = getIdFromAddress(address);
	at(id);
}
template <class T, std::size_t N> T&
Dexter::Tensor<T, N>::at (
	const std::size_t id
) {
	if (!is_valid(id)) {
		//out of bounds
		std::exception ex("Out of bounds");
		throw ex;
	}
	return at_nocheck(id);
}
template <class T, std::size_t N> T&
Dexter::Tensor<T, N>::at_nocheck (
	const std::size_t id
) {
	elemb elb;
	elb = m_data.emplace(id, m_default_val);

	return elb.first->second;
}

template <class T, std::size_t N> std::string
Dexter::Tensor<T, N>::adtostr (
	const uarr& addr
) const {
	if (!is_valid(addr)) {
		//out of bounds
		std::exception ex("Out of bounds");
		throw ex;
	}

	return adtostr_nocheck(addr);
}
template <class T, std::size_t N> std::string
Dexter::Tensor<T, N>::adtostr_nocheck (
	const uarr& addr
) const {
	std::stringstream ss;

	ss << "(";
	for (std::size_t it = 0; it < addr.size() - 1; it++) {
		ss << addr[it] << ", ";
	}
	ss << *addr.rbegin() << ")";

	return ss.str();
}
template <class T, std::size_t N> std::string
Dexter::Tensor<T, N>::idtostrad (
	const std::size_t& id
) const {
	if (!is_valid(id)) {
		//out of bounds
		std::exception ex("Out of bounds");
		throw ex;
	}

	return idtostrad_nocheck(id);
}
template <class T, std::size_t N> std::string
Dexter::Tensor<T, N>::idtostrad_nocheck (
	const std::size_t& id
) const {
	uarr addr;
	addr = idtoad_nocheck(id);
	return adtostr_nocheck(addr);
}
template <class T, std::size_t N> void
Dexter::Tensor<T, N>::print (
	const char* h
) const {	
	celem el;

	std::cout << "\n" << h << ":\n\n";
	for (std::size_t it = 0; it < n_elem(); it++) {
		
		std::cout << idtostrad_nocheck(it) << " ";

		el = m_data.find(it);
		if (el != m_data.end()) {
			std::cout << el->second << "\n";
		} else {
			std::cout << m_default_val << "\n";
		}
	}
}
template <class T, std::size_t N> void
Dexter::Tensor<T, N>::print_mat (
	const char* h
) const {
	celem el;
	uarr addr;

	std::cout << "\n" << h << ":\n\n";
	for (std::size_t it = 0; it < n_elem(); it++) {
		addr = idtoad_nocheck(it);
		el = m_data.find(it);
		if (el != m_data.end()) {
			std::cout << el->second << " ";
		} else {
			std::cout << m_default_val << " ";
		}

		if (
			addr.at(addr.size() - 1) == 
			(m_dims.at(m_dims.size() - 1) - 1)
		) {
			std::cout << "\n";
		}
	}
}