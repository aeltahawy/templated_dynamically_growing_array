#include <iostream>
//this is my attempt at a templated dynamically growing (and shrinking) array using dynamic memory management with simple arrays

template<typename T>
class auto_dynamic_array
{
private:
	T* m_array_;
	mutable std::size_t m_size_ = 1;
	mutable std::size_t m_last_index_ = 0;
private:
	//array size is doubled when there's a need to go above the current size
	void grow()
	{
		const std::size_t new_size = m_size_ * 2;
		T* new_arr = new T[new_size];
		for (std::size_t i = 0; i < m_size_; i++)
			new_arr[i] = m_array_[i];
		delete[] m_array_;
		m_array_ = new_arr;
		m_size_ = new_size;
	}
	//array size is halved when the held items count is below half that of total capacity
	void shrink()
	{
		const std::size_t new_size = m_size_ / 2;
		T* new_arr = new T[new_size];
		for (std::size_t i = 0; i < new_size; i++)
		{
			new_arr[i] = m_array_[i];
		}
		delete[] m_array_;
		m_array_ = new_arr;
		m_size_ = new_size;
	}
	void remove(const int operation, T rhs)
	{
		std::size_t new_index = 0;
		for (std::size_t i = 0; i < m_last_index_; i++)
		{
			switch (operation)
			{
			case 0:
				if (!(m_array_[i] == rhs))
				{
					T temp = m_array_[i];
					m_array_[new_index++] = temp;
				}
				break;
			case 1:
				if (!(m_array_[i] < rhs))
				{
					T temp = m_array_[i];
					m_array_[new_index++] = temp;
				}
				break;
			case 2:
				if (!(m_array_[i] > rhs))
				{
					T temp = m_array_[i];
					m_array_[new_index++] = temp;
				}
				break;
			case 3:
				if (!(m_array_[i] <= rhs))
				{
					T temp = m_array_[i];
					m_array_[new_index++] = temp;
				}
				break;
			case 4:
				if (!(m_array_[i] >= rhs))
				{
					T temp = m_array_[i];
					m_array_[new_index++] = temp;
				}
				break;
			default:
				break;
			}
		}
		m_last_index_ = new_index;
		while (m_last_index_ < m_size_ / 2)
		{
			shrink();
		}
	}
public:
	auto_dynamic_array() { m_array_ = new T[m_size_]; }
	auto_dynamic_array(const std::size_t size) : m_size_(size) { m_array_ = new T[m_size_]; }
	std::size_t get_m_size() const { return m_size_; }
	std::size_t get_m_last_index() const { return m_last_index_; }
	void push_back(T arg)
	{
		if (m_last_index_ >= m_size_)
		{
			grow();
		}
		m_array_[m_last_index_] = arg;
		m_last_index_++;
	}
	//overloaded random access array
	T operator[](int index) const { return m_array_[index]; }
	void print_all() const
	{
		for (std::size_t i = 0; i < m_last_index_; i++)
			std::cout << m_array_[i] << std::endl;
		std::cout << std::endl;
	}
	void print_at(std::size_t index) const
	{
		std::cout << m_array_[index] << '\n' << std::endl;
	}
	void print_start() const
	{
		std::cout << m_array_[0] << '\n' << std::endl;
	}
	void print_end() const
	{
		std::cout << m_array_[m_last_index_ - 1] << '\n' << std::endl;
	}
	void print_extremes() const
	{
		std::cout << "First = " << m_array_[0] << std::endl;
		std::cout << "Last = " << m_array_[m_last_index_ - 1] << '\n' << std::endl;
	}
	void print_size() const
	{
		std::cout <<  get_m_last_index() << '\n' << std::endl;
	}
	void print_capacity() const
	{
		std::cout <<  get_m_size() << '\n' << std::endl;
	}
	void print_sizes() const
	{
		std::cout << "Size = " << get_m_last_index() << std::endl;
		std::cout << "Capacity = " << get_m_size() << '\n' << std::endl;
	}
	//please use an implemented operand ("==", "<", ">", "<=", or ">=") and stick to one simple value in the right hand side
	void remove_if(const std::string& operand, T rhs)
	{
		if (operand == "==")
			remove(0, rhs);
		if (operand == "<")
			remove(1, rhs);
		if (operand == ">")
			remove(2, rhs);
		if (operand == "<=")
			remove(3, rhs);
		if (operand == ">=")
			remove(4, rhs);
	}
	~auto_dynamic_array() { delete[] m_array_; }
};

int main()
{
	//int type examples
	auto_dynamic_array<int> arr_int_first;
	arr_int_first.push_back(8);
	arr_int_first.print_all();
	arr_int_first.print_sizes();

	arr_int_first.push_back(3);
	arr_int_first.print_all();
	arr_int_first.print_sizes();

	arr_int_first.push_back(6);
	arr_int_first.print_all();
	arr_int_first.print_sizes();


	constexpr std::size_t size = 1;
	auto_dynamic_array<int> arr_int_second(size);
	for (std::size_t i = 0; i < 1000; i++)
	{
		arr_int_second.push_back(i + 1);
	}
	//arr2.print_all();
	arr_int_second.print_extremes();
	arr_int_second.print_sizes();

	arr_int_second.remove_if(">", 500);
	//arr2.print_all();
	arr_int_second.print_extremes();
	arr_int_second.print_sizes();


	//double type examples
	auto_dynamic_array<double> arr_double_first;
	arr_double_first.push_back(8.5);
	arr_double_first.print_all();
	arr_double_first.print_sizes();

	arr_double_first.push_back(3.2);
	arr_double_first.print_all();
	arr_double_first.print_sizes();

	arr_double_first.push_back(6.6);
	arr_double_first.print_all();
	arr_double_first.print_sizes();


	constexpr std::size_t size2 = 1;
	auto_dynamic_array<double> arr_double_second(size2);
	for (std::size_t i = 0; i < 100; i++)
	{
		arr_double_second.push_back(i * 0.1);
	}
	arr_double_second.print_all();
	arr_double_second.print_extremes();
	arr_double_second.print_sizes();

	arr_double_second.remove_if(">", 5.0);
	arr_double_second.print_all();
	arr_double_second.print_extremes();
	arr_double_second.print_sizes();
}