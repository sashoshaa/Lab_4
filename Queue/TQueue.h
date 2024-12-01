#pragma once
#include<iostream>

template <class T>
class TQueue
{
private:
	T* pMem;
	int size;
	int finish, start;
	int count;

public:
	TQueue();
	TQueue(int _size);                       //Конструктор по умолчанию
	~TQueue();                               //Деструктор
	TQueue(const TQueue& object);            //Конструктор копирования
	bool empty();                            //Проверка на пустоту
	bool full();                             //Проверка на полноту

	void Push(const T& element);             //Вставка в конец очереди
	T Pop();                                 //Возвращаем из начала очереди
	T front();                               //Возращает значение, которое лежит в начале очереди
	T back();                                //Возращает значение, которое лежит в начале очереди

	void operator = (const TQueue& object);  //Оператор присваивания
	bool operator ==(const TQueue& object);  //Оператор сравненияя
	bool operator !=(const TQueue& object);  //Оператор сравнения

	int GetHeadIndex();                      //Получить индекс, на котором стоит первый элемент в очереди
	int GetCurrentSize();                    //Получить текущий размер
	int GetMaxSize();                        //Получить размер хранилища
	int NumberOfElements();                  //Количество элементов в очереди

	void output();                           //Вывод
};

template <class T>
inline TQueue<T>::TQueue() :size(10)
{
    // Конструктор по умолчанию. Размер очереди установлен в 10.
}

template<class T>
inline TQueue<T>::TQueue(int _size)
{
    // Конструктор с параметром для задания размера очереди.
    if (_size < 1)
    {
        throw std::exception(); // Исключение для недопустимого размера.
    }
    size = _size; // Установка размера очереди.
    pMem = new T[size]; // Выделение памяти для хранения элементов.
    start = 0; // Начальная позиция очереди.
    finish = -1; // Конец очереди, начальное значение указывает на отсутствие элементов.
    count = 0; // Изначально очередь пуста.
}

template<class T>
inline TQueue<T>::~TQueue()
{
    // Деструктор освобождает выделенную память.
    delete[] pMem;
    start = 0;
    finish = -1;
    count = 0; // Сброс значений.
}

template<class T>
inline TQueue<T>::TQueue(const TQueue& object)
{
    // Конструктор копирования для создания копии очереди.
    delete[] pMem; // Очистка текущей памяти, если она уже была выделена.
    size = object.size; // Копирование размера очереди.
    pMem = new T[size]; // Выделение новой памяти для копии.
    std::copy(object.pMem, object.pMem + size, pMem); // Копирование элементов.
    start = object.start; // Копирование индекса начала.
    finish = object.finish; // Копирование индекса конца.
    count = object.count; // Копирование количества элементов.
}

template<class T>
inline bool TQueue<T>::empty()
{
    // Метод проверки, пуста ли очередь.
    return count == 0;
}

template<class T>
inline bool TQueue<T>::full()
{
    // Метод проверки, полна ли очередь.
    return count == size;
}

template<class T>
inline void TQueue<T>::Push(const T& element)
{
    // Добавление элемента в очередь.
    if (full())
    {
        throw std::exception(); // Исключение, если очередь переполнена.
    }
    finish++; // Увеличение индекса конца.
    finish = finish % size; // Зацикливание индекса.
    pMem[finish] = element; // Добавление элемента в очередь.
    count++; // Увеличение количества элементов.
}

template<class T>
inline T TQueue<T>::Pop()
{
    // Извлечение элемента из очереди.
    if (empty())
    {
        throw std::exception(); // Исключение, если очередь пуста.
    }
    T element = pMem[start]; // Получение элемента из начала очереди.
    start++; // Увеличение индекса начала.
    start = start % size; // Зацикливание индекса.
    count--; // Уменьшение количества элементов.
    return element; // Возврат извлеченного элемента.
}

template<class T>
inline T TQueue<T>::front()
{
    // Метод получения элемента из начала очереди без удаления.
    if (this->empty())
    {
        throw std::exception(); // Исключение, если очередь пуста.
    }
    return pMem[start]; // Возврат элемента.
}

template<class T>
inline T TQueue<T>::back()
{
    // Метод получения последнего элемента в очереди без удаления.
    if (this->empty())
    {
        throw std::exception(); // Исключение, если очередь пуста.
    }
    return pMem[finish]; // Возврат последнего элемента.
}

template<class T>
void TQueue<T>::operator=(const TQueue& object)
{
    // Перегрузка оператора присваивания.
    start = object.start;
    finish = object.finish;
    count = object.count;
    if (count == object.count)
    {
        std::copy(object.pMem, object.pMem + size, pMem); // Копирование элементов, если размеры совпадают.
    }
    else
    {
        delete[] pMem; // Очистка текущей памяти.
        size = object.size; // Копирование размера.
        pMem = new T[size]; // Выделение новой памяти.
        std::copy(object.pMem, object.pMem + size, pMem); // Копирование элементов.
    }
}

template<class T>
bool TQueue<T>::operator==(const TQueue& object)
{
    // Перегрузка оператора сравнения на равенство.
    if (count != object.count)
    {
        return false; // Если размеры не совпадают, очереди не равны.
    }
    else
    {
        TQueue this_tmp = *this; // Временная копия текущей очереди.
        TQueue obj_tmp = object; // Временная копия другой очереди.
        while (!this_tmp.empty())
        {
            if (this_tmp.front() != obj_tmp.front())
            {
                return false; // Если хотя бы один элемент отличается, очереди не равны.
            }
            this_tmp.Pop(); // Удаление элементов из временных очередей.
            obj_tmp.Pop();
        }
    }
    return true; // Очереди равны.
}

template<class T>
inline bool TQueue<T>::operator!=(const TQueue& object)
{
    // Перегрузка оператора сравнения на неравенство.
    return !(*this == object);
}

template<class T>
inline int TQueue<T>::GetHeadIndex()
{
    // Метод получения индекса начала очереди.
    return start;
}

template<class T>
inline int TQueue<T>::GetCurrentSize()
{
    // Метод получения текущего количества элементов в очереди.
    return count;
}

template<class T>
inline int TQueue<T>::GetMaxSize()
{
    // Метод получения максимального размера очереди.
    return size;
}

template<class T>
inline int TQueue<T>::NumberOfElements()
{
    // Альтернативный метод для получения текущего количества элементов.
    return count;
}

template<class T>
inline void TQueue<T>::output()
{
    // Метод вывода содержимого очереди на консоль.
    if (this->empty())
    {
        throw std::exception(); // Исключение, если очередь пуста.
    }
    TQueue<T> this_tmp(*this); // Временная копия очереди для итерации.
    std::cout << "(";
    while (!(this_tmp.empty()))
    {
        std::cout << " " << this_tmp.Pop(); // Извлечение и вывод элементов.
    }
    std::cout << " )";
    std::cout << std::endl; // Завершение вывода.
}
