#ifndef UTILS_H
#define UTILS_H

#if defined(_MSC_VER)&&(_MSC_VER>=1200)
#pragma once
#endif

#include <iostream>
#include <algorithm>

class uncopyable
{
	protected:
		uncopyable() {}
		~uncopyable() {}

	private:
		uncopyable(const uncopyable&);
		const uncopyable& operator=(const uncopyable&);
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
