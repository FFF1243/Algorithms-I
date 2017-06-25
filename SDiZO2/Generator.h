#pragma once
template<typename RandomGenerator, typename Graph>
class erdos_renyi_iterator
{
public:
	typedef std::input_iterator_tag iterator_category;
	typedef std::pair<vertices_size_type, vertices_size_type> value_type;
	typedef const value_type& reference;
	typedef const value_type* pointer;
	typedef void difference_type;

	erdos_renyi_iterator();
	erdos_renyi_iterator(RandomGenerator& gen, vertices_size_type n,
		double fraction = 0.0, bool allow_self_loops = false);
	erdos_renyi_iterator(RandomGenerator& gen, vertices_size_type n,
		edges_size_type m, bool allow_self_loops = false);

	// Iterator operations
	reference operator*() const;
	pointer operator->() const;
	erdos_renyi_iterator& operator++();
	erdos_renyi_iterator operator++(int);
	bool operator==(const erdos_renyi_iterator& other) const;
	bool operator!=(const erdos_renyi_iterator& other) const;
};