#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
//�������  ��  �������, ������� ���� � ������ ������, �� �������  ���  �� ������.
//

//������� �������, �� ������ �� ����� ����� ����������

char* readString(int stringSize) {
	//������� �������� ������ ������� stringsize
	//� ��������� �������� ������, ��������� �� �����
	__asm {
		//����� � ������� ������ ������ � �������� ��� � ����
		mov 	eax, stringSize 
		push 	eax
		//�������� ������� ��������� ������
		call 	malloc
		//����� ������ � ��� � �������� ��� ����� ����� �������� ������ �������
		//������ �� ����� ����
		pop 	ebx

		//������ �������� ������� ������ ������ � �������
		//������� gets_s(�����, ������)
		mov ebx, stringSize
		//��������� ������ � ����, �������� �������, ���������� ����
		push ebx
		push eax
		call gets_s
		pop eax
		pop ebx
	}
}

int contains_c(int charCode, char* strng) {
	//������� ��������� �������� �� ������ ������ � ����� charCode
	//������� ����������� 0 ���� �� �������� � 1 �����
	//charcode = 0000 0000 0000 char �� ��� ������� � ��������� �����
	__asm {
		//������� �� ��������� ��� � ������ ��� ����� �������
		mov 	eax, 0 
		//������ ��� ����� ����������� ������ ��� � �������� bl
		mov 	ebx, charCode
		//�������� ����� ������ � esi
		mov 	esi, strng
		//������ ������� �� 0
		mov 	ecx, 0 //������ ������������ ������� �� ������
		CYCLE:
			//� bh ����������� ��� ������� �� ������� (�� �� ��������� ��� ������� ��������� bh)
			mov 	bh, [esi+ecx]
			cmp 	bh, bl
			je 		CONT

			cmp 	bh, 0
			je 		FIN
			inc 	ecx
			jmp CYCLE
			//� cont �������� ���� ����� ����� �� ������ � ����������� ������
			CONT :
				mov 	eax, 1
			FIN :
	}
}

void problem(int stringSize) {

	__asm {
		//�������� �������, ������ ������ �������
		mov 	eax, stringSize
		push 	eax
		call    readString
		//����� ����� � eax � ��� ����� ������ ������ ������
		//�� ��� ����� � ���� � ������ ����� ������ (�� �������� ebx)
		
		pop 	ebx
		push 	eax
		push 	ebx
		//����� �������� �������
		//������ � eax ����� ������ ������
		
		call 	readString
		pop 	ebx
		push 	eax
		//����� ������ ������ ������ - �������� ������ ��� �������-����� (������� 3)
		//����� ������-������ ����� � eax
		
		push 	ebx
		call 	malloc 
		pop 	ebx
		
		//���������� � �������� �����
		
		//������ �������-����� ������ ������� �������� � ��� ������ ����� ������
		mov 	cl, 0
		mov 	[eax], cl
		
		mov 	edx, eax //� edx ����� ������-������
		mov 	eax, 0 //������ ����� ������-������
		pop 	esi //����� ������ 2
		pop 	edi //����� ������ 1
		mov 	ecx, 0 //������ �������� ������ 1
		// � ebx �� ������ ����������� ������ ������ ������
		
		MAIN_CYCLE:
			//�������� � ebx ��������� ������ ������ ������
			//������� ������� ebx
			// � bl ����������� ������
			mov 	ebx, 0
			mov 	bl, [edi + ecx]
			cmp 	bl, 0
			je 		FIN
			
			//��������, ���� �� ���� ������ � ������-�����
			//������ �������� � ����
			push 	eax
			push 	ecx
			push 	edi
			push 	esi
			
			//��������� ������� � ����
			push 	edx
			push 	ebx
			//������� �������
			//���� ������� ��� - ������ ���� ������. ����� ALREADY
			call  	contains_c
			cmp 	eax, 0
			jne 	ALREADY
			
			
			pop 	ebx
			pop 	edx
			pop 	esi
			
			push 	edx
			push 	esi
			push 	ebx
			
			call 	contains_c
			cmp 	eax, 0
			jne 	MATCH_FOUND
			
			pop 	ebx
			pop 	esi
			pop 	edx
			pop 	edi
			pop 	ecx
			pop 	eax
			
			mov 	[edx+eax], bl
			mov 	bl, 0
			inc 	eax
			mov 	[edx+eax], bl
			jmp 	GO_NEXT_CHAR
			
			
			MATCH_FOUND:
			
			pop 	ebx
			pop 	esi
			pop 	edx
			pop 	edi
			pop 	ecx
			pop 	eax
			jmp 	GO_NEXT_CHAR
			
			
			ALREADY:
			
			pop 	ebx
			pop 	edx
			pop 	esi
			pop 	edi
			pop 	ecx
			pop 	eax
			
			GO_NEXT_CHAR:
			inc 	ecx
			
		
		jmp MAIN_CYCLE
		
		FIN:
		push 	edx
		call   	puts
		pop 	edx
	}
}




int main()
{
	problem(256);
	_getch();
	return 0;

}