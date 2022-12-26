// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

template <class T>
class Stack
{
public:
	Stack(size_t _size = 10);

	bool IsEmpty();
	bool IsFull();

	T Pop();
	void Push(const T& el);

	int GetSize();
	int GetHead();
	T GetLastEl();

	void Clear();

	~Stack();

private:
	T* flag;
	size_t size;
	int head;
};

template<class T>
Stack<T>::Stack(size_t _size = 10)
{
	if (_size <= 0)
	{
		throw "U choice size which <= 0";
	}
	else
	{
		size = _size;
		head = -1;
		flag = new T[size];
	}
}

template<class T>
bool Stack<T>::IsEmpty()
{
	if (head == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
bool Stack<T>::IsFull()
{
	if (head == size - 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
T Stack<T>::Pop()
{
	if (IsEmpty() == 1)
	{
		throw "Stack is Empty";
	}
	else
	{
		return flag[head--];
	}
}

template<class T>
void Stack<T>::Push(const T& el)
{
	if (IsFull() == 0)
	{
		flag[++head] = el;
	}
	else
	{
		size = size * 2;
		T* tmp = new T[size];
		for (int i = 0; i < head + 1; i++)
		{
			tmp[i] = flag[i];
		}
		delete[] flag;
		flag = tmp;
		flag[++head] = el;
	}
}

template<class T>
int Stack<T>::GetSize()
{
	return size;
}

template<class T>
int Stack<T>::GetHead()
{
	return head;
}

template<class T>
T Stack<T>::GetLastEl()
{
	if (IsEmpty())
	{
		throw "Stack is Empty";
	}
	return flag[head];
}

template<class T>
void Stack<T>::Clear()
{
	head = -1;
}

template<class T>
Stack<T>::~Stack()
{
	delete[] flag;
}
