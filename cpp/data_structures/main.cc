#include <iostream>
#include "vector.hh"
#include "array.hh"

struct Point 
{
	float x=0.0f, y=0.0f, z=0.0f;
	int* m_memoryBlock = nullptr;

	Point() {
		printf("Constructed A\n");
	}
	Point(float scalar)
		: x(scalar), y(scalar), z(scalar) {
			printf("Constructed B\n");
			m_memoryBlock = new int[5];
		}
	Point(float x, float y, float z) 
		: x(x), y(y), z(z) {
			printf("Constructed C\n");
			m_memoryBlock = new int[5];
		}

	Point(const Point& other)
		: x(other.x), y(other.y), z(other.z) 
	{
		printf("Copy constructed\n");
		for (size_t i=0; i < 5; i++)
			m_memoryBlock[i] = other.m_memoryBlock[i];
	}

	Point& operator=(const Point& other)
	{
		printf("Copy assignment\n");
		x=other.x;
		y=other.y;
		z=other.z;
		m_memoryBlock = new int[5];
		for (int i=0; i<5; i++) 
			m_memoryBlock[i] = other.m_memoryBlock[i];
		return *this;
	}

	Point(Point&& other)
		: x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z)) 
	{
		std::cout << "Move constructor\n";
		m_memoryBlock = other.m_memoryBlock;
		other.m_memoryBlock = nullptr;
	}

	Point& operator=(Point&& other) 
	{
		std::cout << "Move assignment\n";
		x=std::move(other.x);
		y=std::move(other.y);
		z=std::move(other.z);
		m_memoryBlock = other.m_memoryBlock;
		other.m_memoryBlock = nullptr;
		return *this;
	}
	
	~Point() 
	{
		std::cout << "Destroyed\n";
		delete[] m_memoryBlock;
	}
};

template<typename T>
void printVector(const Vector<T>& vector)
{
	for (size_t i=0; i<vector.size(); ++i)
		std::cout << vector[i].x << ", " << vector[i].y << ", " << vector[i].z << std::endl;

	std::cout << "--------------------\n";
}

int main()
{
	// ==== array examples ====
	Array<int, 5> arr;
	std::memset(&arr[0], 0, arr.size() * sizeof(int));
	
	for (auto val: arr)
		std::cout << val << std::endl;

	// ==== vector examples ====
	Vector<int> v_int;
	v_int.emplaceBack(1);
	v_int.emplaceBack(2);
	v_int.emplaceBack(3);
	for (auto val: v_int)
		std::cout << val << std::endl;

	Vector<Point> vector;	
	Point p(2.0f);
	vector.pushBack(p);
	vector.pushBack(Point(4.0f));
	vector.emplaceBack(1.0f);
	vector.popBack(); 
	vector.emplaceBack(3, 4, 5);	
	vector.emplaceBack(3.0f); 
	printVector(vector);
	vector.clear();
	printVector(vector);
}
