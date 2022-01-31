#pragma once

#include <cstdlib>
#include <algorithm>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
	SimpleVector() : _data(nullptr), _capacity(0), _size(0)
	{}
	explicit SimpleVector(size_t size) {
		_data = new T[size];
		_capacity = size;
		_size = size;
	}
	SimpleVector(const SimpleVector& source): _data(new T[source.Size()]), _capacity(source.Capacity()), _size(source.Size()) {
		std::copy(source.begin(), source.end(), begin());
	}

	~SimpleVector() {
		delete[] _data;
		_capacity = 0;
		_size = 0;
	}

	T& operator[](size_t index) {
		return *(_data + index);
	}

	T* begin() {
		return _data;
	}
	T* end() {
		return _data + _size;
	}
	const T* begin() const {
		return _data;
	}
	const T* end() const {
		return _data + _size;
	}

	size_t Size() const {
		return _size;
	}
	size_t Capacity() const {
		return _capacity;
  }
	void PushBack(const T& value) {
		if (_size == _capacity) {
			_capacity = _capacity > 0 ? _capacity * 2 : 1;
			T* new_data = new T[_capacity];
			for (size_t i = 0; i < _size; i++) {
				*(new_data + i) = *(_data + i);
			}
			delete[] _data;
			_data = new_data;
		}
		_size++;					  //
		*(_data + _size - 1) = value; //можно _data[_size++] = value
  }

	void operator=(const SimpleVector& other) {
		if (_data) {
			delete _data;
		}
		_data = new T[other.Capacity()];
		_capacity = other.Capacity();
		_size = other.Size();
		std::copy(other.begin(), other.end(), begin());
	}

private:
  // Добавьте поля для хранения данных вектора
	T* _data;
	size_t _capacity;
	size_t _size;
};

