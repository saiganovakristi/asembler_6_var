#include <stdlib.h> 
#include <stdio.h> 
#include <iostream> 
using namespace std;

int* Create(int* Array, int N)
{
	__asm {
		mov eax, N
		mul eax
		shl eax, 2
		push eax
		call dword ptr[malloc]
		add esp, 4
		mov Array, eax
	}
}
void Destroy(int* Array)
{
	__asm {
		mov eax, Array
		push eax
		call dword ptr[free]
		add esp, 4
	}
}
int Get(int* Array, int i, int j, int N)
{
	__asm {
		mov eax, i
		mov edi, j
		mov ebx, Array
		mov edx, N
		mul edx
		add edi, eax
		mov eax, [ebx][edi * 4]
	}
}

void Change(int* Array, int i, int j, int new_elem, int N)
{
	__asm {
		mov edx, new_elem
		mov eax, i
		mov edi, j
		mov ebx, Array
		push edx
		mul N
		add edi, eax
		pop edx
		mov[ebx][edi * 4], edx
	}
}
void Print(int* Array, int N)
{
	char _int[] = "%d";
	char _new[] = "\n";
	__asm {
		mov ebx, Array
		mov ecx, N
		xor esi, esi
		xor edi, edi
		dec esi
		xor eax, eax
		CYCLE_1 :
		inc esi
			cmp esi, ecx
			je FIN
			mov eax, esi
			mul ecx
			push eax
			xor edi, edi
			push ecx
			lea eax, _new
			push eax
			call dword ptr[printf]
			add esp, 4
			pop ecx
			pop eax
			CYCLE_2 :
		cmp edi, ecx
			jnl CYCLE_1
			push eax
			add eax, edi
			/*push edi
			push esi*/
			push ecx

			mov edx, [ebx][eax * 4]
			push edx
			lea edx, _int
			push edx
			call dword ptr[printf]
			add esp, 8
			pop ecx
			/* pop esi
			pop edi*/
			pop eax
			inc edi
			jmp CYCLE_2
			FIN :
	}
}
bool IsSymmetric(int* Array, int N)
{
	__asm {
		mov ebx, Array
		mov ecx, N
		xor esi, esi
		xor edi, edi
		dec esi
		xor eax, eax
		CYCLE_1 :
		xor eax, eax
			inc esi
			cmp esi, ecx
			je END_1
			mov eax, esi
			mul ecx
			xor edi, edi

			CYCLE_2 :
		cmp edi, ecx
			jnl CYCLE_1
			add eax, edi
			push eax
			mov eax, edi
			mul ecx
			add eax, esi
			pop edx
			mov eax, [ebx][eax * 4]
			cmp[ebx][edx * 4], eax
			jne NO_SYMMETRIC
			inc edi
			mov eax, esi
			mul ecx
			jmp CYCLE_2
			NO_SYMMETRIC :
		mov eax, 0
			jmp FIN
			END_1 :
		mov eax, 1
			FIN :
	}
}

int main()
{
	int v;
	int* Array = 0;
	int N;
	bool flag = false;
	do
	{
		system("cls");
		cout « "1 - Create Matrix" « endl;
		cout « "2 - Fill Matrix" « endl;
		cout « "3 - Read elem" « endl;
		cout « "4 - Change elem" « endl;
		cout « "5 - Test for symmentric" « endl;
		cout « "6 - Show Matrix" « endl;
		cout « "0 - Exit" « endl;
		cin » v;
		switch (v)
		{
		case 1:
		{
			system("cls");
			cout « "Enter size of matrix:" « endl;
			cin » N;
			Array = Create(Array, N);
			flag = true;
			break;
		}
		case 2:
		{
			system("cls");
			char new_elem1[] = "%d";
			char _int[] = "%d";
			char q[] = "Enter element: ";
			__asm {
				mov ecx, N
				mov ebx, Array
				xor esi, esi
				xor edi, edi
				dec esi
				push ecx
				CYCLE_1 :
				inc esi
					mov eax, esi
					mul ecx
					push ecx
					push eax
					CYCLE_2 :
				lea eax, q
					push eax
					call dword ptr[printf]
					add esp, 4
					lea eax, new_elem1
					push eax
					lea eax, _int
					call dword ptr[scanf_s]
					add esp, 4
					mov edx, eax
					pop eax
					add eax, edi
					mov[ebx][eax * 4], edx
					inc edi
					loop CYCLE_1
					pop ecx
					loop CYCLE_2
			}
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			int el;
			int ind_i, ind_j;
			cout « "Enter index i: ";
			cin » ind_i;
			cout « "Enter index j: ";
			cin » ind_j;
			el = Get(Array, ind_i, ind_j, N);
			cout « "Element [" « ind_i « "][" « ind_j « "] = " « el « endl;
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			int new_el;
			int ind_i, ind_j;
			cout « "Enter index i: ";
			cin » ind_i;
			cout « "Enter index j: ";
			cin » ind_j;
			cout « "Enter new value element: ";
			cin » new_el;
			Change(Array, ind_i, ind_j,
				new_el, N);
			Print(Array, N);
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			if (IsSymmetric(Array, N))
				cout « "Matrix is symmetric!" « endl;
			else
				cout « "Matrix not symmetric!" « endl;
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			Print(Array, N);
			cout « endl;
			system("pause");
			break;
		}
		case 0:
		{
			if (flag)
			{
				Destroy(Array);
			}
			break;
		}
		}
	} while (v != 0);
}