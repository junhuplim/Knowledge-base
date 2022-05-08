#pragma once
#include <cassert>
#include "iterator.hh"

template<typename T, size_t S>
class Array
{
	public:
		using ValueType = T;

	public:
		Array() {}

		// function is evaluated at compile-time [constexpr]
		constexpr size_t size() const { return S; }

		T& operator[](size_t index) { 
			assert (index >= 0 && index < S);
			return m_data[index]; 
		}

		const T& operator[](size_t index) const { 
			assert (index >= 0 && index < S);
			return m_data[index]; 
		}

		const T* data() const { return m_data; }

		Iterator<Array> begin()
		{
			return m_data;
		}

		Iterator<Array> end()
		{
			return m_data + S;
		}

	private:
		T m_data[S];
};

