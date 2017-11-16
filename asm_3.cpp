
//6. ��������� ln(x+1) = <����� �� n=1 �� ...>(-1)^n+1 *(x^n)/n
        
#include <iostream>
#include <stdio.h>
using namespace std;

double ln( double x, double eps)
{
	double summ,a;
	__asm{
		finit // ������������� ������������, ������� ���� ������������
		fld eps	//st(5)		����������� �
		fld x	//st(4)		�������� �������
		fld1	//st(3)		�������
		fld x	//st(2)		������� �
		fldz	//st(1)		������� ����
		fld x	//st(0)		����� ����
		fxch st(4)
		fchs    //��������� ����� �����
		fxch st(4)
CYCLE:
		fld1
		faddp st(4) , st(0) //����� ���������� ������� ������� ����� �����������������
		fldz
		fxch st(2)
		fstp a			//?????? ���������� ������� (����� �� �����)
		fxch st(2) // ����� ���������� �������� ����� ST(0) � ���������� ��������, ���������� � �������� �������� �������
		fmul st(0) , st(4)
		fadd st(1) , st(0)
		fxch st(2)
		fxch st(3)
		fdiv st(1) , st(0)
		fxch st(3)//������ st(0)
		//��������
		fldz
		fadd st(0) , st(2)
		fabs
		fcomp st(6)//���������
		fstsw ax//��������� ����� ���������� ���������� �������� ��������� ������������ � ������� AX ������������ ����������.
		sahf//����� ���������� �������� AH ����� ���������� � ������� ������ ������������ ���������� ��� ������ ������� SAHF
		jc FIN
		//end ��������
		fadd st(0) , st(1)
		jmp CYCLE

FIN:
		fstp summ
	}
return summ;
}
void main()
{
	double x, eps, sum1, sum2;
	cout << "Enter x " << endl;
	cin >> x;
	cout << "Enter eps error" << endl;
	cin >> eps;
	__asm{
		finit
		fldln2
		fld x
		fyl2xp1
		fstp sum2
	}
	sum1 = ln(x,eps);
	cout << endl << "(1) Ln(1+x) = " << sum1 << "   x - (x^2/2) + (x^3/3)-...";
	cout << endl << "(2) Ln(1+x) = " << sum2 << "   ln(1+x)";
	cout << endl << "(3) Ln(1+x) = " << fabs(sum2-sum1) << "  |(1)-(2)|" << endl;
	system("pause");

}
