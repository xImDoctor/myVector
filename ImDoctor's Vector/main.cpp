#include <iostream>

namespace DocVector {
	template<typename tp>
	class vector {
		tp* data;
		size_t size;

	public:
		//Default constructor
		vector() {
			data = NULL;
			size = 0;
		}

		//Constructor to fill size with written value
		vector(size_t _size, tp value) {
			size = _size;
			data = new tp[size];

			for (size_t i = 0; i < size; i++)
				data[i] = value;
		}

		//Constructor to fill size with nulls 
		vector(size_t _size) {
			size = _size;
			data = new tp[size];

			for (size_t i = 0; i < size; i++)
				data[i] = 0;
		}

		//Copy constructor
		vector(const vector& other) {
			makeCopy(other);
		}

		//Destructor
		~vector() {
			delete[] data;
		}

		tp& operator[](int index) {
			return indexFind(index);
		}
		const tp& operator[](int index) const {
			return indexFind(index);
		}

		vector& operator=(const vector& other) {
			delete[] data;
			makeCopy(other);
			return *this;
		}

		//Summary with another vector
		vector operator+(const vector& other) {
			vector temp = *this;

			if (temp.size <= other.size)
				for (size_t i = 0; i < temp.size; i++)
					temp.data[i] += other.data[i];

			else for (size_t i = 0; i < other.size; i++)
				temp.data[i] += other.data[i];

			return temp;
		}

		template<size_t N> //to give size of array
		//Summary with array of the same type
		vector<tp> operator+(const tp(&arr)[N]) {
			vector temp = *this;

			if (temp.size < N) {
				resize(N);
				for (size_t i = 0; i < N; i++)
					temp.data[i] += arr[i];
			}
			else for (size_t i = 0; i < N; i++)
				temp.data[i] += +arr[i];

			return temp;
		}

		template<size_t N> //to give size of array
		vector<tp>& operator=(const tp(&arr)[N]) {
			size_t arrSize = N;

			if (size >= arrSize) {
				for (size_t i = 0; i < arrSize; i++)
					data[i] = arr[i];
			}
			else {
				resize(arrSize);
				for (size_t i = 0; i < arrSize; i++)
					data[i] = arr[i];
			}

			return *this;
		}

		//Equal operator
		friend bool operator==(const vector& first, const vector& second) {
			return isEqual(first, second);
		}
		//No-equal operator
		friend bool operator!=(const vector& first, const vector& second) {
			return !isEqual(first, second);
		}

		void showAll() {
			for (size_t i = 0; i < size; i++)
				std::cout << data[i] << " ";
			std::cout << std::endl;
		}

		//set an element to the end of array by array's resizing
		void push_back(tp element) {
			resize(size + 1);
			data[size - 1] = element;
		}

		//remove an element from the end of array by array's resizing
		void pop_back() {
			resize(size - 1);
		}

		//push one element to any place
		void push_at(size_t position, tp element) {
			size_t targetPos = position - 1;
			vector temp = *this;
			delete[] data;

			size = size + 1;
			data = new tp[size];
			for (size_t i = 0; i < size; i++) {
				if (i < targetPos)
					data[i] = temp.data[i];
				else if (i == targetPos)
					data[i] = element;
				else data[i] = temp.data[i - 1];
			}
		}

		//push array of elements to any place
		template<size_t N>
		void push_at(size_t position, const tp(&arr)[N]) {
			size_t targetPos = position - 1;
			int elementsPushed = 0;

			vector temp = *this;
			delete[] data;

			size = size + N;
			data = new tp[size];
			for (size_t i = 0; i < size; i++) {
				if (i < targetPos)
					data[i] = temp.data[i];
				else if (i >= targetPos && elementsPushed < N)
					data[i] = arr[elementsPushed++];
				else data[i] = temp.data[i - N];
			}
		}

		//get size
		size_t getSize() const {
			return size;
		}
		//get data
		tp* getData() {
			return data;
		}
		//get data if const
		const tp* getData() const {
			return data;
		}

	private:
		//for []
		tp& indexFind(int index) {
			if (index < 0 || index >(size - 1)) {
				std::cerr << "Index is outside of bounds. Returned index 0." << std::endl;
				return data[0];
			}
			return data[index];
		}

		//for copy constructor and =
		void makeCopy(const vector& other) {
			size = other.size;
			data = new tp[size];

			for (size_t i = 0; i < size; i++)
				data[i] = other.data[i];
		}

		//Recreate array with new size. If size less then before it returns array with fit elements; if bigger then new elemenets return as 0
		void resize(size_t newSize) {
			vector temp = *this;
			delete[] data;
			data = new tp[newSize];

			for (int i = 0; i < newSize; i++) {
				if (i < temp.size)
					data[i] = temp.data[i];
				else data[i] = 0;
			}
			size = newSize;
		}

		//function to check equality
		friend bool isEqual(const vector& v1, const vector& v2) {
			if (v1.size == v2.size)
				for (size_t i = 0; i < v1.size; i++)
					if (v1.data[i] != v2.data[i])
						return false;
			return true;
		}

	};
}

template<typename ab>
void Test(DocVector::vector<ab>& v) {
	v.showAll();
	std::cout << v.getSize() << std::endl;
}

int main() {
	int a[] = { 1, 2, 4 };
	DocVector::vector<int> _vec(5, 0);
	_vec = a;
	_vec.showAll();

	DocVector::vector<float> first(3);
	float first_values[] = { 12.5, 13.0, 14.0 };
	first = first_values;
	first.showAll();

	DocVector::vector<float> second(3);
	float second_values[] = { 0, 5.2, 8.0 };
	second = second_values;
	second.showAll();

	DocVector::vector<float> summary(3, 0);
	DocVector::vector<float> sum;
	summary = first + second;
	summary.showAll();

	summary.push_back(3.2);
	sum = summary + second;
	sum.showAll();
	sum.push_at(3, 12.5);
	sum.showAll();

	float abab[] = { 0, 3, 0 };
	sum.push_at(4, abab);
	sum.showAll();

	
	first = summary;
	std::cout << (first == summary) << std::endl;
	std::cout << (first == second) << std::endl;
	std::cout << (first != second) << std::endl;
	
	return 0;
}