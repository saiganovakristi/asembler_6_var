#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
//“казать  те  символы, которые есть в первой строке, но которых  нет  во второй.
//

//указать символы, те вывода на экран будет достаточно

char* readString(int stringSize) {
	//функциЯ выделЯет памЯть размера stringsize
	//и считывает вводимую строку, возвращаЯ ее адрес
	__asm {
		//ложим в регистр размер строки и помещаем его в стек
		mov 	eax, stringSize 
		push 	eax
		//вызываем функцию выделениЯ памЯти
		call 	malloc
		//после вызова у нас в регистре еах лежит адрес сегмента памЯти размера
		//чистим за собой стек
		pop 	ebx

		//теперь вызываем функцию чтениЯ строки с консоли
		//функциЯ gets_s(адрес, размер)
		mov ebx, stringSize
		//поместили данные в стек, вызывали функцию, почитстили стек
		push ebx
		push eax
		call gets_s
		pop eax
		pop ebx
	}
}

int contains_c(int charCode, char* strng) {
	//функциЯ проверЯет содержит ли строка символ с кодом charCode
	//функциЯ вовзвращает 0 если не содержит и 1 иначе
	//charcode = 0000 0000 0000 char те код символа в последнем байте
	__asm {
		//считаем по умолчанию что в строке нет этого символа
		mov 	eax, 0 
		//делаем так чтобы проверЯемый символ был в регистре bl
		mov 	ebx, charCode
		//помещаем адрес строки в esi
		mov 	esi, strng
		//ставим счетчик на 0
		mov 	ecx, 0 //индекс проверЯемого символа из строки
		CYCLE:
			//в bh проверЯютсЯ все символы из строчки (те мы пробегаем все символы регистром bh)
			mov 	bh, [esi+ecx]
			cmp 	bh, bl
			je 		CONT

			cmp 	bh, 0
			je 		FIN
			inc 	ecx
			jmp CYCLE
			//в cont попадаем если нашли такой же символ в проверЯемой строке
			CONT :
				mov 	eax, 1
			FIN :
	}
}

void problem(int stringSize) {

	__asm {
		//вызываем функцию, читаем первую строчку
		mov 	eax, stringSize
		push 	eax
		call    readString
		//после этого в eax у нас адрес первой строки строки
		//мы его ложим в стек а сверху опЯть размер (из регистра ebx)
		
		pop 	ebx
		push 	eax
		push 	ebx
		//снова вызываем функцию
		//теперь в eax адрес второй строки
		
		call 	readString
		pop 	ebx
		push 	eax
		//опЯть размер строки сверху - выделЯем памЯть под строчку-ответ (строчка 3)
		//адрес строки-ответа лежит в eax
		
		push 	ebx
		call 	malloc 
		pop 	ebx
		
		//подготовка к главному циклу
		
		//делаем строчку-ответ пустой строкой добавлЯЯ в нее символ конца строки
		mov 	cl, 0
		mov 	[eax], cl
		
		mov 	edx, eax //в edx адрес строки-ответа
		mov 	eax, 0 //индекс конца строки-ответа
		pop 	esi //адрес строки 2
		pop 	edi //адрес строки 1
		mov 	ecx, 0 //индекс элемента строки 1
		// в ebx мы храним проверЯемый символ первой строки
		
		MAIN_CYCLE:
			//помещаем в ebx очередной символ первой строки
			//очищаем регистр ebx
			// в bl проверЯемый символ
			mov 	ebx, 0
			mov 	bl, [edi + ecx]
			cmp 	bl, 0
			je 		FIN
			
			//проверим, есть ли этот символ в строке-ответ
			//важные регистры в стек
			push 	eax
			push 	ecx
			push 	edi
			push 	esi
			
			//аргументы функции в стек
			push 	edx
			push 	ebx
			//вызвали функцию
			//если символа нет - значит идем дальше. иначе ALREADY
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