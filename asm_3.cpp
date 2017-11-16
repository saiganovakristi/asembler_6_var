
//6. вычислить ln(x+1) = <сумма от n=1 до ...>(-1)^n+1 *(x^n)/n
        
#include <iostream>
#include <stdio.h>
using namespace std;

double ln( double x, double eps)
{
	double summ,a;
	__asm{
		finit // инициализация сопроцессора, очищает стек сопроцессора
		fld eps	//st(5)		погрешность е
		fld x	//st(4)		значение функции
		fld1	//st(3)		счетчик
		fld x	//st(2)		степени х
		fldz	//st(1)		элемент ряда
		fld x	//st(0)		сумма ряда
		fxch st(4)
		fchs    //Изменение знака числа
		fxch st(4)
CYCLE:
		fld1
		faddp st(4) , st(0) //после выполнения команды вершина стека восстанавливается
		fldz
		fxch st(2)
		fstp a			//?????? выталкиваю вершину (взять из стека)
		fxch st(2) // обмен содержимым верхушки стека ST(0) и численного регистра, указанного в качестве операнда команды
		fmul st(0) , st(4)
		fadd st(1) , st(0)
		fxch st(2)
		fxch st(3)
		fdiv st(1) , st(0)
		fxch st(3)//модуль st(0)
		//проверка
		fldz
		fadd st(0) , st(2)
		fabs
		fcomp st(6)//сравнение
		fstsw ax//программа может переписать содержимое регистра состояния сопроцессора в регистр AX центрального процессора.
		sahf//Далее содержимое регистра AH можно переписать в регистр флагов центрального процессора при помощи команды SAHF
		jc FIN
		//end проверка
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
