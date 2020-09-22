#ifndef LIST_H_
#define LIST_H_
#include "patient.h"
#include <iostream>
#include <fstream>
#include <stdio.h>

/*
Линейный односвязный список.
Обязательные методы класса:
    - добавление элемента в начало или конец списка (на выбор)
    - просмотр списка
    - удаление элемента из начала или конца списка (на выбор)
    - Вывод списка на экран можно выполнять в любом (главное, читабельном) виде.
    - чтение списка из бинарного файла
    - запись списка в бинарный файл
*/

class List
{
public:
	typedef
	struct element
	{
	   Patient data;
	   struct element * next;
	} node;

	node * begin = NULL;

	List(){}

	struct element * add_begin (Patient& x) /*добавление в начало*/
	{
	       struct element * temp;
	       temp = new node();
	       temp->data = x;
	       temp->next = begin;
	       begin = temp;
	       return temp;
	}

	struct element * add_end (Patient& x) /*добавление в конец*/
	{
	       struct element * temp = begin, * temp1;
	       temp1 = new node();
	       temp1->data = x;
	       temp1->next = NULL;
	       if (temp) /*если список не пуст*/
	       {
	            while (temp->next) /*пока есть куда переходить*/
	               temp = temp->next; /*перемещаем указатель на последний элемент списка*/
	            temp->next = temp1; /*добавляем новый элемент в конец   */
	       }
	       else /*если добавляемый элемент первый*/
	            begin = temp1;
	       return begin;
	}

	struct element * del_begin () /*удаление первого элемента*/
	{
	     struct element * temp;
	     if (begin) /*если список не пуст*/
	     {
	           temp = begin;
	           begin = begin->next; /*переставляем указатель на следующий элемент*/
	           free (temp); /*первый удаляем*/
	     }
	     return begin;
	}

	void del_end () /*удаление последнего*/
	{
	    node * prev = begin;
	    node * cur = begin;
		while(cur->next) {
			prev = cur;
			cur = cur->next;
		}
		delete cur;
		prev->next = NULL;
	}

	void write(std::string file)
		{
			//Очищаем файл
			std::fstream ofs;
			ofs.open(file, std::ios::out | std::ios::trunc);
			ofs.close();

			node * temp = begin;
			while(temp){
				temp->data.write(file);
				temp = temp->next;
			}
		}

		void read(std::string file)
		{
			std::fstream ts(file, std::ios::in | std::ios::binary);

			long offset = 0;

			while(true)
			{
				Patient temp;
				ts.seekg(offset, std::ios::beg);
				if(ts.peek() != EOF)
				{
					offset = temp.read(file, offset);
					add_end(temp);
				} else break;
			}
		}

		void print (struct element * begin) /*печать списка*/
		{
		     if (!begin) /*если список пуст*/
		     {
		           printf ("Empty\n");
		           return;
		     }
		     while (begin) /*пока в списке есть элементы*/
		     {
		           begin->data.print();
		           std::cout << "----------" << '\n';
		           begin = begin->next; /*переставляем указатель на следующий элемент*/
		     }
		}
};

#endif /* LIST_H_ */
