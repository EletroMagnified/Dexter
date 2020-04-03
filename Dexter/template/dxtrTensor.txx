template <class T, std::size_t N>
Dexter::Tensor<T, N>::Tensor(T default_val) : m_default_val(default_val) {}
template <class T, std::size_t N>
Dexter::Tensor<T, N>::Tensor(const uarr& dims, T default_val) : m_dims(dims), m_default_val(default_val) {}


template <class T, std::size_t N> bool
Dexter::Tensor<T, N>::is_valid(
	const std::size_t& id
) const {
	bool is_valid = true;

	if (!(id < getNumberOfEntries())) {
		is_valid = false;
	}

	return is_valid;
}
template <class T, std::size_t N> bool
Dexter::Tensor<T, N>::is_valid (
	const uarr& address
) const {
	bool is_valid = true;
	
	for (std::size_t it = 0; it < m_dims.size(); it++) {
		if (!(address.at(it) < m_dims.at(it))) {
			is_valid = false;
			break;
		}
	}

	return is_valid;
}
template <class T, std::size_t N> std::size_t
Dexter::Tensor<T, N>::getNumberOfEntries (
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
Dexter::Tensor<T, N>::getAddressFromId (
	const std::size_t& id
) const {
	if (!is_valid(id)) {
		//out of bounds
		std::exception ex("Out of bounds");
		throw ex;
	}

	uarr addr;
	std::size_t stride, remainder;

	remainder = id;
	for (std::size_t it1 = 0; it1 < m_dims.size(); it1++) {
		stride = 1;
		for (std::size_t it2 = it1; it2 < m_dims.size() - 1; it2++) {
			stride *= m_dims.at(it2);
		}
		addr.at(it1) = remainder / stride;
		remainder = remainder % stride;
	}

	return addr;
}
template <class T, std::size_t N> std::size_t
Dexter::Tensor<T, N>::getIdFromAddress (
	const uarr& address
) const {
	if (!is_valid(address)) {
		//out of bounds
		std::exception ex("Out of bounds");
		throw ex;
	}

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
	typename dat_map::iterator elem = m_data.find(id);

	if (elem == m_data.end()) {
		m_data.emplace(id, m_default_val);
		elem = m_data.find(id);
	}
	return elem->second;
}

template <class T, std::size_t N> std::string
Dexter::Tensor<T, N>::addressToString (
	const std::size_t& id
) const {
	uarr address;
	std::stringstream ss;

	address = getAddressFromId(id);

	ss << "(";
	for (std::size_t it = 0; it < address.size() - 1; it++) {
		ss << address[it] << ", ";
	}
	ss << *address.rbegin() << ")";

	return ss.str();
}

template <class T, std::size_t N> void
Dexter::Tensor<T, N>::print(
) const {
	
	typename dat_map::const_iterator elem;
	for (std::size_t it = 0; it < getNumberOfEntries(); it++) {
		
		std::cout << addressToString(it) << " ";

		elem = m_data.find(it);
		if (elem != m_data.end()) {
			std::cout << elem->second << "\n";
		} else {
			std::cout << m_default_val << "\n";
		}
	}
}