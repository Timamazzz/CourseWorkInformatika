#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

struct Polinom {//��������� ������
	int Coeff; //�����
	int Degree; // �������
	Polinom* Next; //�������� ����
};

// ������ ��������
int GetSize(Polinom* Head)
{
	Polinom* ptr = Head;
	int size = 0;
	for (; ptr != NULL; ptr = ptr->Next)
		++size;

	return size;
}

//�������� ����������������� ������ (���������� � �����)
void Make_Polinom(int n, Polinom** Head) {
	if (n >= 0) {
		(*Head) = new Polinom();
		//�������� ������ ��� ����� �������

		cout << "(x^" << n << ")* "; cin >> (*Head)->Coeff;

		(*Head)->Degree = n;
		// ������ ����������� � ���������� �������

		(*Head)->Next = nullptr;//��������� ��������� ����

		Make_Polinom(n - 1, &((*Head)->Next));
	}

}

// ����� ��������
void Print_Polinom(Polinom* Head, ofstream& outf) {

	if (Head != nullptr) {
		if (Head->Next != nullptr) {
			if (Head->Next->Coeff >= 0) {
				cout << Head->Coeff << "x^" << Head->Degree << "+";
				outf << Head->Coeff << "x^" << Head->Degree << "+";
			}
			else
			{
				cout << Head->Coeff << "x^" << Head->Degree << " ";
				outf << Head->Coeff << "x^" << Head->Degree << " ";
			}
		}

		if (Head->Next == nullptr)
		{
			if (Head->Degree != 0) {
				cout << Head->Coeff << "x^" << Head->Degree;
				outf << Head->Coeff << "x^" << Head->Degree;
			}

			else {
				cout << Head->Coeff;
				outf << Head->Coeff;
			}

		}
		Print_Polinom(Head->Next, outf);//������� � ���������� ��������

	}
	else cout << "\n";
}

// �������� ������������� ������ 0
void Check_0(Polinom*& Head)
{
	while (Head && Head->Coeff == 0)
	{
		Polinom* p = Head;
		Head = Head->Next;
		delete p;
	}

	Polinom* ptr = Head;

	if (ptr != nullptr)
		while (ptr->Next != NULL)
			if (ptr->Next->Coeff != 0)
				ptr = ptr->Next;
			else
			{
				Polinom* p = ptr->Next;
				ptr->Next = p->Next;
				delete p;
			}
	else
		cout << "error";
}

//��������� ���������
void Eq_Pol(Polinom* Head1, Polinom* Head2, ofstream& outf)
{
	bool check = true;
	Polinom* ptr1 = Head1;
	Polinom* ptr2 = Head2;

	while (ptr1 && check)
	{
		if (ptr1->Degree == ptr2->Degree)
		{


			if (ptr1->Coeff != ptr2->Coeff)
				check = false;

			ptr1 = ptr1->Next;
			ptr2 = ptr2->Next;
		}
		else
			check = false;
	}

	if (check)
	{
		cout << "�������� �����" << endl;
		outf << "�������� �����" << endl;
	}
	else
	{
		cout << "�������� �� �����" << endl;
		outf << "�������� �� �����" << endl;
	}
}

//�������� �������� ��� �������� x
int Value_withX(Polinom* Head, ofstream& outf)
{
	Polinom* ptr = Head;
	int x;
	int val_pol = 0;
	cout << "������� x= "; cin >> x;

	while (ptr)
	{
		val_pol += ptr->Coeff * pow(x, ptr->Degree);
		ptr = ptr->Next;
	}
	cout << "�������� �������� ��� x=" << x << " �����:" << val_pol << endl;
	outf << "�������� �������� ��� x=" << x << " �����:" << val_pol << endl;
	return val_pol;
}

//����������� ������� k ��������
void Derivative_k(Polinom* Head, ofstream& outf)
{
	int k;

	do {
		cout << "������� k= "; cin >> k;
	} while (k < 0);

	cout << "����������  �������� ������� k=" << k << endl;
	outf << "����������  �������� ������� k=" << k << endl;

	if (Head != nullptr)
		if (k > Head->Degree)
		{
			cout << "0" << endl;
		}
		else
		{
			Polinom* ptr = nullptr;
			Polinom* d_k = nullptr;
			Polinom* p = nullptr;

			while (Head != nullptr)
			{
				if (p != nullptr)
				{
					ptr->Next = new Polinom;
					ptr = ptr->Next;
				}
				else {
					ptr = new Polinom;
					p = ptr;
				}

				ptr->Coeff = Head->Coeff;
				ptr->Degree = Head->Degree;
				ptr->Next = nullptr;

				Head = Head->Next;
			}


			ptr = nullptr;

			while (p != nullptr)
			{
				if (d_k != nullptr)
				{
					ptr->Next = new Polinom;
					ptr = ptr->Next;
				}
				else {
					ptr = new Polinom;
					d_k = ptr;
				}

				for (int i = 1; i <= k; i++)
				{
					ptr->Coeff = p->Coeff * p->Degree;
					ptr->Degree = p->Degree - 1;
					p->Coeff = p->Coeff * p->Degree;
					p->Degree -= 1;
				}
				ptr->Next = nullptr;
				p = p->Next;

			}

			Check_0(d_k);
			Print_Polinom(d_k, outf);
		}

	else
		cout << "error" << endl;
}

//����� ���������
void Sum_pol(Polinom* Head1, Polinom* Head2, ofstream& outf)
{
	Polinom* ptr = nullptr;
	Polinom* sum_pol = nullptr;
	Polinom* tmp1 = Head1;
	Polinom* tmp2 = Head2;

	if (tmp1 != nullptr && tmp2 != nullptr)
	{
		if (tmp1->Degree >= tmp2->Degree)
		{
			while (tmp1 != nullptr)
			{
				if (sum_pol != nullptr)
				{
					ptr->Next = new Polinom;
					ptr = ptr->Next;
				}
				else {
					ptr = new Polinom;
					sum_pol = ptr;
				}

				ptr->Coeff = tmp1->Coeff;
				ptr->Degree = tmp1->Degree;
				ptr->Next = nullptr;

				tmp1 = tmp1->Next;
			}

			ptr = sum_pol;
			while (ptr != nullptr)
				if (ptr->Degree == tmp2->Degree)
				{
					ptr->Coeff = ptr->Coeff + tmp2->Coeff;
					ptr = ptr->Next;
					tmp2 = tmp2->Next;
				}
				else
					ptr = ptr->Next;


		}
		else
		{

			while (tmp2 != nullptr)
			{
				if (sum_pol != nullptr)
				{
					ptr->Next = new Polinom;
					ptr = ptr->Next;
				}
				else {
					ptr = new Polinom;
					sum_pol = ptr;
				}

				ptr->Coeff = tmp2->Coeff;
				ptr->Degree = tmp2->Degree;
				ptr->Next = nullptr;

				tmp2 = tmp2->Next;
			}

			ptr = sum_pol;
			while (ptr != nullptr)
				if (ptr->Degree == tmp1->Degree)
				{
					ptr->Coeff = ptr->Coeff + tmp1->Coeff;
					ptr = ptr->Next;
					tmp1 = tmp1->Next;
				}
				else
					ptr = ptr->Next;
		}

		cout << "����� ���� ���������:" << endl;
		outf << "����� ���� ���������:" << endl;
		Print_Polinom(sum_pol, outf);
	}
	else
		cout << "error" << endl;
}


// ������������ ���������
void Composition_pol(Polinom* Head1, Polinom* Head2, ofstream& outf)
{
	Polinom* ptr = nullptr;
	Polinom* com_pol_0 = nullptr;
	Polinom* com_pol_f = nullptr;

	Polinom* tmp1 = Head1;
	Polinom* tmp2 = Head2;
	int size = GetSize(tmp1) * GetSize(tmp2);



	if (tmp1 != nullptr && tmp2 != nullptr)
	{
		if (tmp1->Degree >= tmp2->Degree)
		{
			while (size > 0)
			{
				if (tmp2 == nullptr)
				{
					tmp1 = tmp1->Next;
					tmp2 = Head2;
				}

				if (com_pol_0 != nullptr)
				{
					ptr->Next = new Polinom;
					ptr = ptr->Next;
				}
				else {
					ptr = new Polinom;
					com_pol_0 = ptr;
				}

				ptr->Coeff = tmp1->Coeff * tmp2->Coeff;
				ptr->Degree = tmp1->Degree + tmp2->Degree;
				ptr->Next = nullptr;



				tmp2 = tmp2->Next;

				size--;
			}



		}
		else
		{
			while (size > 0)
			{
				if (tmp1 == nullptr)
				{
					tmp2 = tmp2->Next;
					tmp1 = Head1;
				}

				if (com_pol_0 != nullptr)
				{
					ptr->Next = new Polinom;
					ptr = ptr->Next;
				}
				else {
					ptr = new Polinom;
					com_pol_0 = ptr;
				}

				ptr->Coeff = tmp1->Coeff * tmp2->Coeff;
				ptr->Degree = tmp1->Degree + tmp2->Degree;
				ptr->Next = nullptr;


				tmp1 = tmp1->Next;

				size--;
			}
		}

		ptr = nullptr;
		tmp1 = nullptr;
		tmp2 = com_pol_0;

		while (tmp2 != nullptr)
		{
			if (tmp1 != nullptr)
			{
				ptr->Next = new Polinom;
				ptr = ptr->Next;
			}
			else {
				ptr = new Polinom;
				tmp1 = ptr;
			}

			ptr->Coeff = tmp2->Coeff;
			ptr->Degree = tmp2->Degree;
			ptr->Next = nullptr;

			tmp2 = tmp2->Next;
		}

		int d = tmp1->Degree;

		while (d >= 0)
		{

			if (com_pol_f != nullptr)
			{
				ptr->Next = new Polinom;
				ptr = ptr->Next;
			}
			else {
				ptr = new Polinom;
				com_pol_f = ptr;
			}

			ptr->Coeff = 0;

			while (tmp1 != nullptr)
			{
				if (tmp1->Degree == d)
					ptr->Coeff += tmp1->Coeff;
				tmp1 = tmp1->Next;
			}
			ptr->Degree = d;
			ptr->Next = nullptr;

			tmp1 = com_pol_0;

			d--;
		}

		Check_0(com_pol_f);
		cout << "������������ ���� ���������:" << endl;
		outf << "������������ ���� ���������:" << endl;
		Print_Polinom(com_pol_f, outf);
	}
	else
		cout << "error";
}


int main()
{
	int n1, n2, p;
	Polinom* pol1;
	Polinom* pol2;
	ofstream outf("OutputFile.txt");


	setlocale(LC_ALL, "ru");

	do {
		cout << "������� ������� ��������, ������� �� ����� ���� ���� 0 n1= "; cin >> n1;
	} while (n1 < 0);
	Make_Polinom(n1, &pol1);

	do {
		cout << "������� ������� ��������, ������� �� ����� ���� ���� 0 n2= "; cin >> n2;
	} while (n2 < 0);
	Make_Polinom(n2, &pol2);

	Check_0(pol1);
	Check_0(pol2);

	system("cls");

	outf << "������ �������" << endl;
	cout << "������ �������" << endl; Print_Polinom(pol1, outf);
	outf << endl;

	outf << "������ �������" << endl;
	cout << "������ �������" << endl; Print_Polinom(pol2, outf);
	outf << endl;

	Eq_Pol(pol1, pol2, outf);

	do {
		cout << "������� 1 ���� ��������� �������� ��� x � ������ �������� ��� 2 �� ������ "; cin >> p;
	} while (p != 1 && p != 2);
	if (p == 1)
		Value_withX(pol1, outf);
	else
		Value_withX(pol2, outf);

	do {
		cout << "������� 1 ���� ��������� ����������� � ������ �������� ��� 2 �� ������ "; cin >> p;
	} while (p != 1 && p != 2);
	if (p == 1)
		Derivative_k(pol1, outf);
	else
		Derivative_k(pol2, outf);
	outf << endl;


	Sum_pol(pol1, pol2, outf);
	outf << endl;


	Composition_pol(pol1, pol2, outf);



	return 0;
}