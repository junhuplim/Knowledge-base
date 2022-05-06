#pragma once
#include <cassert>

template<typename T, size_t S>
class Array
{
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

	private:
		T m_data[S];
};

