#pragma once
#include "bitfield.h"

class set
{
private:
	int MaxPower; // ������������ �������� ���������
	Tbitfield BitField; // ������� ���� ��� �������� ���-�� �������
public:
	set(int mp): MaxPower(mp),BitField(mp)
	{

	}

	// ����������� �����������
	set(const set& s): MaxPower(s.MaxPower), BitField(s.BitField)
	{

	}

	// ����������� �������������� ����
	set(const Tbitfield& bf);

	// �������������� ���� � �������� ����
	operator Tbitfield()
	{
		Tbitfield tmp(BitField);
	}

	// ������ � �����

	// ������������ �������� ���������
	int GetMaxPower(void) const
	{
		return MaxPower;
	}

	// �������� ������� � ���������
	void InsElem(const int n)
	{
		BitField.SetBit(n);
	}

	// ������� ������� �� ���������
	void DelElem(const int n)
	{
		BitField.ClrBit(n);
	}

	// ��������� ������� �������� � ���������
	int IsMember(const int elem) const
	{
		return BitField.GetBit(elem);
	}

	// ���������-������������� ��������

	// ���������
	int operator== (const set& s)
	{
		return BitField == s.BitField;
	}

	// ������������
	set& operator=(const set& s)
	{
		MaxPower = s.MaxPower;
		BitField == s.BitField;
		return *this;
	}

	// ��������� �������� � ���������
	set operator+ (const int n)
	{
		BitField.SetBit(n);
	}

	// �������� �������� �� ���������
	set operator- (const int n)
	{
		BitField.ClrBit(n);
	}

	// �����������
	set operator+ (const set& s)
	{
		set tmp(BitField | s.BitField);
		return tmp;
	}

	// �����������
	set operator* (const set& s)
	{
		set tmp(BitField & s.BitField);
		return tmp;
	}

	// ����������
	set operator~ (void)
	{
		set tmp(~BitField);
		return tmp;
	}

	// ����-�����
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
