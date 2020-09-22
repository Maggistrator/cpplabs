#include <iostream>
#include <string>     // std::string, std::stoi
#include <fstream>

#include "list_stack.h"
#include "carrige.h"

using namespace std;

/*
Разработайте класс, реализующий стек с помощью указателей.
Методы класса: добавление элемента в стек, удаление элемента из стека, получение значения с вершины стека, проверка заполнения стека, проверка пустоты стека, очистка стека.

Написать программу, использующую стек для моделирования Т-образного сортировочного узла на железной дороге.
Программа должна разделять на два направления состав, состоящий из вагонов двух типов (на каждое направление формируется состав из вагонов одного типа).
Предусмотреть возможность формирования состава из файла и с клавиатуры.
*/

//TODO: написать ввод вагонов с клавиатуры
//TODO: написать ввод вагонов из файла
//TODO: написать сортировку вагонов на нужные направления
//TODO: написать консольный интерфейс пользователя

//--- ПРОТОТИПЫ ------------//
list_stack* keyboard_fill();
list_stack* file_fill();

int main()
{
    list_stack* train = nullptr;

    //Формирование состава
    int ans = 9999;
    while ( ans ) {
        cout << "Выберите способ формирования состава:" << endl;
        cout << "1. С клавиатуры" << endl;
        cout << "2. Из файла" << endl;
        cout << "0. Выход" << endl;

        cout << "Ваш ответ: "; cin >> ans;
        switch (ans)
        {
            case 1:
                train = keyboard_fill();
                goto RESOLVE;
                break;
            case 2:
                train = file_fill();
                goto RESOLVE;
                break;
            case 0:
                /*никаких действий не требуется*/
                break;
            default:
                cout << "Неверный ввод, попробуйте ещё раз." << endl;
        }
    }

    RESOLVE:
    //сортировка состава по разным направлениям
    list_stack direction1;
    list_stack direction2;

    cout << "--- SORT ---" << endl;
    while (!train->isEmpty()){
        carrige* c = train->pop();
        cout << "№"<< c->id + 1 << "\t" << "Тип: " << (c->type == 0 ? "CARGO" : "PASSANGER") << endl;
        if(c->type == carrige::CARGO) {
            direction1.push(c);
        } else {
            direction2.push(c);
        }
    }

    cout << "Грузовое направление, вагоны №:" << endl;
    while (!direction1.isEmpty()) cout << direction1.pop()->id + 1 << " ";
    cout << endl;

    cout << "Пассажирское направление, вагоны №:" << endl;
    while (!direction2.isEmpty()) cout << direction2.pop()->id + 1 << " ";

    delete train;
    return 0;
}

/// формирование состава с клавиатуры
list_stack* keyboard_fill(){
    list_stack* train = new list_stack();
    carrige* c;

    int ans = 9999, id = 0;
    while ( ans ) {
        cout << "Введите тип вагона:" << endl;
        cout << "1. Пассажирский" << endl;
        cout << "2. Грузовой" << endl;
        cout << "0. Завершить формирование состава" << endl;
        cout << "Ваш ответ: "; cin >> ans;
        switch (ans)
        {
            case 1:
                c = new carrige(carrige::PASSENGER , id++);
                train->push(c);
                break;
            case 2:
                c = new carrige(carrige::CARGO, id++);
                train->push(c);
                break;
            case 0:
                /*никаких действий не требуется*/
                break;
            default:
                cout << "Неверный ввод, попробуйте ещё раз." << endl;
        }
    }
    return train;
}

/// формирование состава из файла
list_stack* file_fill(){
    int id = 0;
    string row_data, item;
    list_stack* train = new list_stack();

    ifstream MyReadFile("train.dat");
    std::string::size_type sz;

    while (getline (MyReadFile, item)) {
        int i_dec = std::stoi (item, &sz);
        if(i_dec == 0){
            carrige* cargo = new carrige(carrige::CARGO, id++);
            train->push(cargo);
        } else {
            carrige* pas = new carrige(carrige::PASSENGER , id++);
            train->push(pas);
        }
    }

    MyReadFile.close();
    return train;
}

