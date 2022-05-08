#pragma once

template<typename T>
class Iterator
{
	public:
		using ValueType = typename T::ValueType;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;

	public:
		Iterator(PointerType ptr)
			: m_ptr(ptr) {}

		Iterator& operator++()
		{
			++m_ptr;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator it = *this;
			++(*this);
			return it;
		}

		Iterator& operator--()
		{
			--m_ptr;
			return *this;
		}

		Iterator operator--(int)
		{
			Iterator it = *this;
			--(*this);
			return it;
		}

		PointerType operator->()
		{
			return m_ptr;
		}

		ReferenceType operator*()
		{
			return *m_ptr;
		}

		ReferenceType operator[](int index)
		{
			return *(m_ptr+index);
		}

		bool operator==(const Iterator& other)
		{
			return m_ptr == other.m_ptr;
		}

		bool operator!=(const Iterator& other)
		{
			return !(*this == other);
		}

	private:
		PointerType m_ptr;
};
