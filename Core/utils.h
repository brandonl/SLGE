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

struct delete_map_functor
{
	template<typename A, typename B>
    void operator()( std::pair<A,B> x ) const
    {
        delete x.second;
    }
};

struct delete_functor
{
	template <typename T>
	void operator()( const T* ptr ) const
	{
		if( ptr )
			delete ptr;
	}
};

struct print_functor
{
	template <typename T>
	void operator()( const T* ptr ) const
	{
		std::cout << T << std::endl;
	}
};

#endif