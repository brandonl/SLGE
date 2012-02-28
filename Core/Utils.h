#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <algorithm>
#include <vector>

class Uncopyable
{
	protected:
		Uncopyable() {}
		~Uncopyable() {}

	private:
		Uncopyable(const Uncopyable&);
		const Uncopyable& operator=(const Uncopyable&);
};

template<typename T>
void eraseUnordered( std::vector<T>& v, size_t index)
{
    v[index] = std::move( v.back() );
    v.pop_back();
}

struct deleteMapFunctor
{
	template<typename A, typename B>
    void operator()( std::pair<A,B> x ) const
    {
        delete x.second;
    }
};

struct deleteFunctor
{
	template <typename T>
	void operator()( const T* ptr ) const
	{
		if( ptr )
			delete ptr;
	}
};

struct printFunctor
{
	template <typename T>
	void operator()( const T* ptr ) const
	{
		std::cout << T << std::endl;
	}
};
#endif
