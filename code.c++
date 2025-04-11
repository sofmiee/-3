#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

void add() // функция добавления данных в файл
{
    string str;
    cout << "Введите дополнительные данные: "; 
    cin.ignore();
    getline(cin, str); // получаем строку от пользователя
    ofstream aupa("E:\products.txt", ios::app); // открываем файл на добавление
    aupa.seekp(0, ios::end); // позиционируемся в конец файла
    aupa << str; //вывод строку в файл
    aupa.close(); // закрываем файл
}

void search() // функция для поиска по названию
{
    string stroka;
    string poisk;
    cout << "Введите название продукта: ";
    cin >> poisk; // получаем строку от пользователя
    ifstream apupa("E:\products.txt"); // открываем файл на добавление
    while (getline(apupa, stroka)) { //пока строкка не пустая, проходимся по файлу
        if (stroka.find(poisk) != string::npos) { //если не находим подстроку, то получаемя специфичное число
            cout << stroka << endl; //выводим строку, где есть подстрока
        }
    }
    apupa.close(); //закрываем файл
}

void print() // функция для поиска по цене
{
    string stroka, tmp1;
    cout << "Цена не более: " << endl;
    cin >> tmp1; // получаем строку от пользователя
    int pr = stoi(tmp1); //преобразуем строку в число

    ifstream upa("E:\products.txt"); //открываем файл для чтения
    while (getline(upa, stroka)) { // пока строка не пустая, читаем файл
        istringstream ss(stroka); // как будто поток ввода
        string name;
        int quant;
        int price;
        ss >> name >> quant >> price; // раскидываем данные из потока по переменным
        if (price <= pr) // ищем цену ниже заданной
            cout << name << " " << price << endl; //выводим
    }
    upa.close(); //закрываем файл
}

void sort() // функция для сортировки
{
    string stroka; // создаем структуру с названием, количеством и ценой
    struct Prod {
        string name;
        int quant, price;
    };
    vector <Prod *> prods; 

    // Читаем файл
    ifstream in("E:\products.txt"); //открываем файл для чтения
    while (getline(in, stroka)) { // пока строка не пустая, читаем файл
        istringstream ss(stroka); // как будто поток ввода
        Prod *p = new Prod;
        ss >> p->name >> p->quant >> p->price; // раскидываем данные из потока по переменным
        prods.push_back(p); // идем в конец вектора 
    }
    in.close(); //закрываем файл
    
    // Сортируем
    sort(prods.begin(), prods.end(), [](Prod* p1, Prod* p2) {return p1->price < p2->price; });

    // Записываем в файл
    ofstream out("E:\products.txt");
    for (auto& prod : prods)
    {
        cout << prod->name << " " << prod->quant << " " << prod->price << endl;
        out << prod->name << " " << prod->quant << " " << prod->price << endl;
        delete prod;
    }
    out.close();
}

int main() {
    setlocale(LC_ALL, "RUS");
    string stroka;

    ofstream pupa("E:\products.txt");

    cout << "Введите данные: " << endl;
    getline(cin, stroka); //считываем первую строку
    while (stroka.length()>0) { //пока строка не пустая, читаем ввод от пользователя
        pupa << stroka << endl; // записываем строки в файл
        getline(cin, stroka); //запрашиваем новую строку
    }
    pupa.close();


    int sel; // переменная для выбора пользователя
    do {
        cout << endl;
        cout << "1 Добавить" << endl;
        cout << "2 Поиск" << endl;
        cout << "3 Сортировка" << endl;
        cout << "4 Вывод" << endl;
        cout << "0 Завершить" << endl;
        cout << "Сделайте выбор:";
        cin >> sel;

        switch (sel) {
        case 1:
            add();
            break;
        case 2:
            search();
            break;
        case 3:
            sort();
            break;
        case 4:
            print();
            break;
        case 0:
            break;
        default:
            cout << "Не правильный выбор. Попробуйте снова." << endl;
        }

    } while (sel != 0);



    return 0;
}
