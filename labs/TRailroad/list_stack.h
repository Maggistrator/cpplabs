#ifndef LIST_STACK_H_INCLUDED
#define LIST_STACK_H_INCLUDED
#include "carrige.h"
using namespace std;

/*
 * Разработайте класс, реализующий стек с помощью указателей.
 */

//------------------------//
//  СПИСКОВАЯ РЕАЛИЗАЦИЯ  //
//------------------------//

//TODO: Реализовать функцию: добавление элемента в стек             [готово]
//TODO: Реализовать функцию: удаление элемента из стека             [готово]
//TODO: Реализовать функцию: получение значения с вершины стека     [готово]
//TODO: Реализовать функцию: проверка заполнения стека              [готово]
//TODO: Реализовать функцию: проверка пустоты стека                 [готово]
//TODO: Реализовать функцию: очистка стека                          [готово]

///Класс стека вагонов
//---- Интерфейс класса -------------------------------------//
class list_stack
{
    struct element
    {
        element(carrige* c, element* n) : payload(c), next(n) {}    //конструктор с двумя элементами

        carrige* payload;
        element* next;
    };

    element *head = nullptr;
    element* getTail();

    public:
    ///Добавление нового элемента в вершину стека
    void push(carrige* c);
    ///Удаление произвольного элемента стека
    void pop(carrige* c);
    ///Получение последнего элемента c удалением его из стека
    carrige* pop();
    ///Получение последнего элемента, без его удаления
    carrige* peek();
    ///Проверка на переполнение стека
    bool isFull();
    ///Проверка стека на пустоту
    bool isEmpty();
    ///Очищение стека
    void clearAll();

    ~list_stack();
};


//---- Реализация класса -------------------------------------//
// не вынесено в отдельный файл ввиду простоты класса + это можно сделать в любой момент по мере масштабирования программы

void list_stack::push(carrige* c){
    if(isEmpty()){
        head = new element(c, nullptr);
    } else {
        element* tail = this->getTail();
        tail->next = new element(c, nullptr);
    }
}

void list_stack::pop(carrige* c){
    element* neighbour = this->head;
    while(neighbour->next != nullptr && neighbour->next->payload != c){
        neighbour = neighbour->next;
    }
    if(neighbour->next != nullptr) {
        delete neighbour->next;                      // удаляем метаданные ненужного звена стека
        neighbour->next = neighbour->next->next;    // соединяем звено предшествующее удаленному со звеном следующим за ним
    } else if (neighbour->payload == c){
        delete neighbour;
        head = nullptr;
    }

}

carrige* list_stack::pop(){
    if(!isEmpty()){
        element* prev = nullptr;
        element* tail = this->head;
        while(tail->next != nullptr){
            prev = tail;
            tail = tail->next;
        }
        carrige* temp = tail->payload;
        delete tail;
        if(prev != nullptr) prev->next = nullptr;
        else head = nullptr;
        return temp;
    } else return nullptr;
}

carrige* list_stack::peek(){
    if(!isEmpty()){
        element* tail = getTail();
        return tail->payload;
    } else return nullptr;
}

bool list_stack::isEmpty(){
    return this->head == nullptr;
}

//единственная возможность переполнения стека - это нехватка памяти
bool list_stack::isFull(){
    //если стек пуст, то он не может быть полон
    if(!isEmpty()){
        //проверим, хватит ли места на новое звено стека
        element* e = new element(nullptr, nullptr);
        if(e != nullptr) {
            delete e;
            return true;
            //хватит места - освободим память и вернём true
        } else return false; //не хватит - вернем false
    } return false;
}

void list_stack::clearAll(){
    if(!isEmpty()){
        for(element *current = head, *temp; current->next != nullptr; current = temp){
            temp = current->next;
            delete current->payload;
            delete current;
        }
    }
}

list_stack::element* list_stack::getTail(){
    if(!isEmpty()){
        element* tail = this->head;
        while(tail->next != nullptr){
            tail = tail->next;
        }
        return tail;
    } else return nullptr;
}

list_stack::~list_stack(){
    clearAll();
}

#endif // LIST_STACK_H_INCLUDED
