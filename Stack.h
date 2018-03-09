#pragma once

template <typename T>
class Stack
{
private:

	// ���������� ���������, ��� ������� � ����� �������� ������.
	unsigned int m_capacity;

	// ���������� ��������� � �����.
	unsigned int m_size;

	// ������ ��� �������� ������.
	T* m_stack;

public:
	Stack();
	Stack(const Stack& stack);
	~Stack();

	Stack& operator=(const Stack& right);

	// ������� �����.
	void Clear();

	// �������� ������������� ��������� � �����.
	bool IsEmpty();

	// �������� �������� � ������� �����.
	T Peek();

	// ��������� �������� �� �����.
	T Pop();

	// ���������� �������� � ����.
	void Push(const T value);

	// ��������� ���������� ��������� � �����.
	unsigned int GetSize();

	T& operator[](const int index);

	T PeekFisrt();
};

template <typename T>
Stack<T>::Stack() :
	m_capacity(10U),
	m_size(0U),
	m_stack(new T[10])
{
}

template <typename T>
Stack<T>::~Stack()
{
	delete[] m_stack;
}

template <typename T>
Stack<T>::Stack(const Stack& stack) :
	m_capacity(stack.m_capacity),
	m_size(stack.m_size),
	m_stack(new T[stack.m_capacity])
{
	for (unsigned int i = 0U; i < stack.m_size; ++i)
	{
		m_stack[i] = stack.m_stack[i];
	}
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& right)
{
	if (this != &right)
	{
		// ������� �����.
		delete[] m_stack;

		m_capacity = right.m_capacity;
		m_size = right.m_size;
		m_stack = new T[right.m_capacity];

		for (unsigned int i = 0U; i < right.m_size; ++i)
		{
			m_stack[i] = right.m_stack[i];
		}
	}

	return *this;
}

template <typename T>
void Stack<T>::Clear()
{
	// ����������� "�������" ����� (������ � ������� ��� ��� ����������, �� ������ ������, ��������������� �� ������ � 
	// �������� �����, ����� �� ������������).
	m_size = 0U;
}

template <typename T>
unsigned int Stack<T>::GetSize()
{
	// ���������� �������������� � ����� ���������.
	return m_size;
}

template <typename T>
bool Stack<T>::IsEmpty()
{
	return m_size == 0U;
}

template <typename T>
T Stack<T>::Peek()
{
	T result = -1;

	// ������� �������� ��������, ���� � ����� ���� ��������.
	if (!IsEmpty())
	{
		result = m_stack[m_size - 1U];
	}

	return result;
}

template <typename T>
T Stack<T>::Pop()
{
	T result = -1;

	// ������� �������� �������� � ���������� �������, ���� � ����� ���� ��������.
	if (!IsEmpty())
	{
		result = m_stack[m_size - 1U];

		--m_size;
	}

	return result;
}

template <typename T>
void Stack<T>::Push(const T value)
{
	if (m_capacity == m_size)
	{
		m_capacity += 2U;

		T* copy = new T[m_capacity];

		for (unsigned int i = 0U; i < m_size; ++i)
		{
			copy[i] = m_stack[i];
		}

		delete[] m_stack;

		m_stack = copy;
	}

	// ���������� ������ ��������.
	m_stack[m_size] = value;

	// ���������� ������� �����.
	++m_size;
}

template <typename T>
T& Stack<T>::operator[](const int index)
{
	return m_stack[index];
}

template <typename T>
T Stack<T>::PeekFisrt()
{
	T result = -1;

	// ������� �������� ��������, ���� � ����� ���� ��������.
	if (!IsEmpty())
	{
		result = m_stack[0];
	}

	return result;
}
