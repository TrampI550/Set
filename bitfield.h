#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
typedef unsigned int TELEM;
class MyException
{
private:
	int err;
	std::string txt[2] = { "Wrong data", "Something goes wrong" };
public:
	MyException(int _err) : err(_err) {}
	std::string text() { return txt[err]; }
};
class Tbitfield
{
private:
	int BitLen; // длина битового поля - макс. к-во битов
	TELEM* pMem; // память для представления битового поля (16 бит)
	int MemLen; // к-во эл-тов Мем для представления бит.поля

	// методы реализации

	// индекс в pМем для бита n
	int GetMemIndex(const int n) const
	{
		return n >> 4;//Сдвиг вправо на 4 бита
	}

	// битовая маска для бита n
	TELEM GetMemMask(const int n) const
	{
		return 1 << (n & 15);//Сдвиг влево
	}
public:
	Tbitfield(int len): BitLen(len),MemLen((len + 15) >> 4)
	{
		pMem = new TELEM[MemLen];
		if (pMem != nullptr)
		{
			for (int i(0); i < MemLen; ++i)
			{
				pMem[i] = 0;
			}
		}
	}

	Tbitfield(const Tbitfield& bf): BitLen(bf.BitLen),MemLen(bf.MemLen)
	{
		pMem = new TELEM[MemLen];
		if (pMem != nullptr)
		{
			for (int i=0; i < MemLen; ++i) 
			{
				pMem[i] = bf.pMem[i];
			}
		}
	}

	~Tbitfield()
	{
		delete pMem;
	}

	// доступ к битам

	// получить длину (к-во битов)
	int GetLength(void) const
	{
		return BitLen;
	}

	// установить бит
	void SetBit(const int n)
	{
		if ((n > -1) && (n < BitLen))
		{
			pMem[GetMemIndex(n)] |= GetMemMask(n);
		}
		else throw MyException(0);
	}

	// очистить бит
	void ClrBit(const int n)
	{
		if ((n > -1) && (n < BitLen))
		{
			pMem[GetMemIndex(n)] &= ~GetMemMask(n);//Дополнение до единицы(~)(меняем 0 на 1 и 1 на 0), 
		}
		else throw MyException(0);
	}

	// получить значение бита
	int GetBit(const int n) const
	{
		if ((n > -1) && (n < BitLen))
		{
			return pMem[GetMemIndex(n)] & GetMemMask(n);
		}
		else throw MyException(0);
	}

	// битовые операции

	// сравнение
	int operator==(const Tbitfield& bf)
	{
		if (BitLen != bf.BitLen) { return 0; }
		else
		{
			for (int i(0); i < MemLen, pMem != nullptr; ++i)
			{
				if (pMem[i] != bf.pMem[i]) { return 0; }
			}
		}
		return 1;
	}

	// присваивание
	Tbitfield& operator=(const Tbitfield& bf)
	{
		if (MemLen != bf.MemLen)
		{
			MemLen = bf.MemLen;
			if (pMem != nullptr)
			{
				delete pMem;
			}
			pMem = new TELEM[MemLen];
		}
		for (int i(0); i < MemLen, pMem != nullptr; ++i) { pMem[i] = bf.pMem[i]; }
		return *this;
	}

	// операция "или"
	Tbitfield operator|(const Tbitfield& bf)
	{
		int tempLen;
		if (BitLen < bf.BitLen) 
		{ 
			tempLen = bf.BitLen;
		}
		else tempLen = BitLen;
		Tbitfield tempBit(tempLen);
		for (int i(0); i < MemLen; ++i) 
		{
			tempBit.pMem[i] = pMem[i];
		}
		for (int i(0); i < bf.MemLen; ++i) 
		{
			tempBit.pMem[i] |= bf.pMem[i];
		}
		return tempBit;
	}

	// операция "и"
	Tbitfield operator&(const Tbitfield& bf)
	{
		int tempLen;
		if (BitLen < bf.BitLen)
		{
			tempLen = bf.BitLen;
		}
		else tempLen = BitLen;
		Tbitfield tempBit(tempLen);
		for (int i(0); i < MemLen; i++)
		{
			tempBit.pMem[i] = pMem[i];
		}
		for (int i(0); i < bf.MemLen; i++)
		{
			tempBit.pMem[i] &= bf.pMem[i];
		}
		return tempBit;
	}

	// отрицание
	Tbitfield operator~(void)
	{
		int tempLen = BitLen;
		Tbitfield tempBit(tempLen);
		for (int i(0); i < MemLen; i++) 
		{
			tempBit.pMem[i] = ~pMem[i]; 
		}
		return tempBit;
	}

	// ввод-вывод
	friend std::istream& operator>>(std::istream& istr, Tbitfield& bf)
	{
		//for (int i(0); i < bf.MemLen, bf.pMem != nullptr; ++i)
		//{
		//	std::cin >> bf.pMem[i];
		//}
		//return istr;
		int i = 0; char ch;
		// поиск {
		do { istr >> ch; } while (ch != ' ');
		// ввод элементов и включение в множество
		while (1) {
			istr >> ch;
			if (ch == '0') bf.ClrBit(i++);
			else if (ch == '1') bf.SetBit(i++); else break;
		}
		return istr;
	}

	friend std::ostream& operator<<(std::ostream& outstr, const Tbitfield& bf)
	{
		for (int i(0); i < bf.MemLen, bf.pMem != nullptr; ++i)
		{
			std::cout << bf.pMem[i] << " ";
		}
		std::cout << std::endl;
		return outstr;
	}
};
