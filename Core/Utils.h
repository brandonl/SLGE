#ifndef UTILS_H
#define UTILS_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <iostream>
#include <algorithm>

class Uncopyable
{
	protected:
		Uncopyable() {}
		~Uncopyable() {}

	private:
		Uncopyable(const Uncopyable&);
		const Uncopyable& operator=(const Uncopyable&);
};

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
