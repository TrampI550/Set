#pragma once
#include "bitfield.h"

class set
{
private:
	int MaxPower; // максимальная мощность множества
	Tbitfield BitField; // битовое поле для хранения хар-го вектора
public:
	set(int mp): MaxPower(mp),BitField(mp)
	{

	}

	// конструктор копирования
	set(const set& s): MaxPower(s.MaxPower), BitField(s.BitField)
	{

	}

	// конструктор преобразования типа
	set(const Tbitfield& bf);

	// преобразование типа к битовому полю
	operator Tbitfield()
	{
		Tbitfield tmp(BitField);
	}

	// доступ к битам

	// максимальная мощность множества
	int GetMaxPower(void) const
	{
		return MaxPower;
	}

	// включить элемент в множество
	void InsElem(const int n)
	{
		BitField.SetBit(n);
	}

	// удалить элемент из множества
	void DelElem(const int n)
	{
		BitField.ClrBit(n);
	}

	// проверить наличие элемента в множестве
	int IsMember(const int elem) const
	{
		return BitField.GetBit(elem);
	}

	// теоретико-множественные операции

	// сравнение
	int operator== (const set& s)
	{
		return BitField == s.BitField;
	}

	// присваивание
	set& operator=(const set& s)
	{
		MaxPower = s.MaxPower;
		BitField == s.BitField;
		return *this;
	}

	// включение элемента в множество
	set operator+ (const int n)
	{
		BitField.SetBit(n);
	}

	// удаление элемента из множества
	set operator- (const int n)
	{
		BitField.ClrBit(n);
	}

	// объединение
	set operator+ (const set& s)
	{
		set tmp(BitField | s.BitField);
		return tmp;
	}

	// пересечение
	set operator* (const set& s)
	{
		set tmp(BitField & s.BitField);
		return tmp;
	}

	// дополнение
	set operator~ (void)
	{
		set tmp(~BitField);
		return tmp;
	}

	// ввод-вывод
	friend std::istream& operator>>(std::istream& instr, set& bf)
	{
		//int temp;
		//for (int i(0); i < bf.GetMaxPower(); ++i)
		//{
		//	instr >> temp;
		//	bf.InsElem(temp);
		//}
		return instr;
	}

	friend std::ostream& operator<<(std::ostream& outstr, const set& bf)
	{
		//for (int i(0); i < bf.GetMaxPower(); ++i)
		//{
		//	;
		//}
		return outstr;
	}
};
