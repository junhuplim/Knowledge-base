#pragma once

template<typename T>
class Vector 
{
	public: 
		Vector() {}

		~Vector()
		{
			clear();
			::operator delete(m_data, m_capacity * sizeof(T));
		}

		void pushBack(const T& value)
		{
			if (m_size >= m_capacity)
				realloc(m_capacity + m_capacity/2 + 1);
			
			m_data[m_size] = value;
			++m_size;
		}

		void pushBack(T&& value) 
		{
			if (m_size >= m_capacity)
				realloc(m_capacity + m_capacity/2 + 1);

			m_data[m_size] = std::move(value);
			++m_size;
		}

		template<typename... Args>
		T& emplaceBack(Args&&... args)
		{
			if (m_size >= m_capacity)
				realloc(m_capacity + m_capacity/2 + 1);
			
			// this constructs T in place on heap, instead of constructing T on stack then moving to heap
			new(&m_data[m_size]) T(std::forward<Args>(args)...);
			return m_data[m_size++];
		}

		void popBack()
		{
			if (m_size > 0)
			{
				m_data[m_size--].~T();
			}
		}

		void clear()
		{
			for (size_t i=0; i < m_size; i++)
				m_data[i].~T();

			m_size=0;
		}

		size_t size() const { return m_size; }

		const T& operator[](size_t index) const
		{
			return m_data[index];
		}

	private:
		void realloc(size_t newCapacity) 
		{
			std::cout << "Realloc: " << newCapacity << "\n";
			std::cout << newCapacity * sizeof(T) << "\n";
			T* newBlock = (T*)::operator new(newCapacity * sizeof(T));
			if (newCapacity < m_size)
				m_size = newCapacity;
 
			for (size_t i=0; i<m_size; ++i)
				newBlock[i] = std::move(m_data[i]);

			for (size_t i=0; i<m_size; ++i)
				m_data[i].~T();

			::operator delete(m_data, m_capacity * sizeof(T));
			m_data = newBlock;
			m_capacity = newCapacity;
		}

	private:
		T* m_data = new T[0];
		size_t m_size = 0;
		size_t m_capacity = 0;

};





