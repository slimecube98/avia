#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#endif
#endif
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>
#include <cstdlib>
#include <Windows.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#if defined(max)
#undef max
#endif
using namespace std;
void typesToCheck()
{
    ifstream ttc("TypesOfAircrafts.txt");
    if (!ttc.is_open())
    {
        ofstream ttc;
        ttc.open("TypesOfAircrafts.txt");
        ttc << "Airbus A320\nAirbus A321\nAirbus A330\nBoeing 737\nBoeing 777";
    }
    ttc.close();
}
bool findIn(string str, int a)
{
    bool check = true;
    string type;
    ifstream toa("TypesOfAircrafts.txt");
    if (!toa.is_open())
    {
        typesToCheck();
        ifstream toa("TypesOfAircrafts.txt");
    }
    while (!toa.eof())
    {
        getline(toa, type);
        if (str == type)
        {
            check = false;
        break;
        }
    }
    if (check)
    {
        if (a == 1)
        {
            cout << " Данный тип самолётов не обслуживается.\n Самолёты обслуживаемые авиакомпанией :\n Airbus A320\n Airbus A321\n Airbus A330\n Boeing 737\n Boeing 777\n " << endl;
        }
        toa.close();
        return true;
    }
    else return false;
}
struct AEROFLOT
{
    string Destination;
    int FlightNumber;
    string TypeOfAircraft;
    AEROFLOT* next;
};
class BD
{
    AEROFLOT* Head, *Tail;
public:
BD() :Head(NULL), Tail(NULL) { };
    ~BD(); // прототип деструктора
    void Show(); //прототип функции отображения
    void Add(); //прототип функции добавления
    void Delete(); //прототип функции удаления
    void Search(); //прототип функции поиска
    void Sorting(); //прототип функции сортировки
    void toSave(); //прототп функции сохранения в файл
    void fromFile(); //прототип функции загрузки БД
    void listEditor();//прототип редактора списка
    void flab();
};
int CheckNumber()
{ // Проверка на число
    int x;
    while (true)
    {
        cin >> x;
        if (cin.good())
        {
            cin.ignore(numeric_limits < streamsize >::max(), '\n');
            break;
        }
        else
        {
            cin.clear();
            cout << " Неправильный ввод данных!";
            cin.ignore(numeric_limits < streamsize >::max(), '\n');
            
        }
    }
    return x;
}
BD::~BD()
{
    AEROFLOT* temp, *temp1;
    temp = Head;
    while (temp != NULL)
    {
        temp1 = temp->next;
        delete temp;
        temp = temp1;
        Head = temp;
    }
}
void BD::Show()
{
    AEROFLOT* temp = Head;
    if (Head != NULL)
    {
        for (int i = 0; i < 51; i++) cout << "_";
        cout << " " << endl;
        cout << "| Пункт назначения | Номер рейса | Тип самолёта |\n";
        while (temp != NULL)
        {
            for (int i = 0; i < 51; i++) cout << "-";
            cout << endl;
            cout << "|";
            cout << temp->Destination;
            for (int i = 0; i < 20 - (temp->Destination).length(); i++) cout << " ";
            cout << "| ";
            cout.width(4);
            cout << temp->FlightNumber;
            cout << " |" << temp->TypeOfAircraft;
            for (int i = 0; i < 14 - (temp->TypeOfAircraft).length(); i++) cout << " ";
            cout << "|" << endl;
            temp = temp->next;
        }
        for (int i = 0; i < 51; i++) cout << "-";
        cout << endl;
    }
    else cout << " Список пуст!" << endl;
    system("pause");
    system("cls");
}
void BD::Add()
{
    string Dest, Type, TypeC;
    int Num;
    bool check = true, cov = true;
    AEROFLOT* temp = Head;
    AEROFLOT* tempNew = new AEROFLOT;
    cout << " Введите пункт назначения : ";
    getline(cin, Dest);
    tempNew->Destination = Dest;
    cin.clear();
    while (check)
    {
        AEROFLOT* TCheck = Head;
        cout << " Введите номер рейса : ";
        while (true)
        {
            Num = CheckNumber();
            if ((Num > 0) && (Num <= 9999)) break;
            else cout << " Номер рейса должен содержать 4 цифры! " << endl;
        }
        while (TCheck != NULL)
        {
            if (TCheck->FlightNumber == Num)
            {
                cout << " Обнаружен рейс с таким же номером! Проверьте правильность ввода!" << endl;
            break;
            }
            else TCheck = TCheck->next;
        }
        if (TCheck == NULL)
        {
            tempNew->FlightNumber = Num;
            check = false;
        }
    }
    cin.clear();
    while (cov)
    {
        cin.clear();
        cout << " Введите тип самолёта : ";
        getline(cin, Type);
        cov = findIn(Type, 1);
    }
    tempNew->TypeOfAircraft = Type;
    cin.clear();
    if (temp != NULL)
    {
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = tempNew;
        tempNew->next = NULL;
    }
    else
    {
        Head = tempNew;
        tempNew->next = NULL;
    }
    system("pause");
    system("cls");
}
void BD::Delete()
{
    AEROFLOT* temp = Head;
    
if (temp != NULL)
    {
        AEROFLOT* tempPrev = Head;
        AEROFLOT* tempNext;
        int num, flag = 1;
        char o;
        bool del = true;
        while (del)
        {
            system("cls");
            cout << " 1. Удалить один элемент по номеру рейса " << endl;
            cout << " 2. Удалить все элементы " << endl;
            cout << " Выберите желаемое действие --> ";
            cin >> o;
            cin.clear();
            cin.ignore(numeric_limits < streamsize >::max(), '\n');
            switch (o)
            {
                case '1':
                    {
                        system("cls");
                        cout << " Введите номер рейса который желаете удалить : ";
                        while (true)
                        {
                            num = CheckNumber();
                            if ((num > 0) && (num <= 9999)) break;
                            else cout << " Номер рейса должен содержать 4 цифры! " << endl;
                        }
                        while (temp != NULL)
                        {
                            if (temp->FlightNumber == num)
                            {
                                flag = 0;
                                if (temp != Head)
                                {
                                    while (tempPrev->next != temp)
                                    {
                                        tempPrev = tempPrev->next;
                                    }
                                    tempNext = temp->next;
                                    tempPrev->next = tempNext;
                                    free(temp);
                                    break;
                                }
                                else
                                {
                                    tempNext = temp->next;
                                    Head = tempNext;
                                    free(temp);
                                    break;
                                }
                            }
                            temp = temp->next;
                        }
                        if (flag == 0) cout << " Действие выполнено. " << endl;
                        else cout << " Данные о рейсе не найдены. " << endl;
                        system("pause");
                        del = false;
                        break;
                    }
                case '2':
                    {
                        
                while (temp != NULL)
                        {
                            if (temp != Head)
                            {
                                tempNext = temp->next;
                                tempPrev->next = tempNext;
                                free(temp);
                                break;
                            }
                            else
                            {
                                Head = NULL;
                                free(temp);
                                break;
                            }
                            temp = temp->next;
                        }
                        cout << " Действие выполнено. " << endl;
                        system("pause");
                        del = false;
                        break;
                    }
                default:
                    cout << " Пожалуйста, выберите действие из предложенных. "<< endl;
                    system("pause");
                    break;
            }
        }
    }
    else
    {
        cout << " Список пуст! " << endl;
        system("pause");
    }
}
void BD::Search()
{
    AEROFLOT* temp = Head;
    if (temp != NULL)
    {
        string Type, nType;
        int counter = 0;
        cin.clear();
        cout << " Введите тип самолёта : ";
        getline(cin, Type);
        while (temp != NULL)
        {
            nType = temp->TypeOfAircraft;
            if (nType.find(Type) != string::npos)
            {
                counter++;
                cout << endl << " Пункт назначения : " << temp->Destination << "\n Номер рейса : " << temp->FlightNumber << "\n Тип самолёта : " << temp -
                > TypeOfAircraft << endl << endl;
            }
            temp = temp->next;
        }
    if (counter == 0) cout << " Не найдено ни одной записи." << endl;
        else cout << " Поиск окончен." << endl;
        system("pause");
    }
    else
    {
        cout << " Список пуст! " << endl;
        system("pause");
    }
}
void BD::Sorting()
{
    bool pov = true;
    AEROFLOT* left = Head;
    if (left != NULL)
    {
        char a;
        while (pov)
        {
            cout << " 1. Сортировка по номеру рейса " << endl;
            cout << " 2. Сортировка по направлению " << endl;
            cout << " Выберите желаемое действие --> ";
            cin >> a;
            cin.clear();
            cin.ignore(numeric_limits < streamsize >::max(), '\n');
            switch (a)
            {
                case '1':
                    {
                        AEROFLOT* a = NULL;
                        AEROFLOT* b = NULL;
                        AEROFLOT* c = NULL;
                        AEROFLOT* e = NULL;
                        AEROFLOT* tmp = NULL;
                        while (e != Head->next)
                        {
                            c = a = Head;
                            b = a->next;
                            while (a != e)
                            {
                                if (a->FlightNumber > b->FlightNumber)
                                {
                                    if (a == Head)
                                    {
                                        tmp = b->next;
                                        b->next = a;
                                        a->next = tmp;
                                        Head = b;
                                        c = b;
                                    }
                                    else
                                    {
                                        tmp = b->next;
                                        b->next = a;
                                        a->next = tmp;
                                        c->next = b;
                                        
                                    c = b;
                                    }
                                }
                                else
                                {
                                    c = a;
                                    a = a->next;
                                }
                                b = a->next;
                                if (b == e) e = a;
                            }
                        }
                        cout << " Действие выполнено." << endl;
                        system("pause");
                        pov = false;
                        break;
                    }
                case '2':
                    {
                        AEROFLOT* a = NULL;
                        AEROFLOT* b = NULL;
                        AEROFLOT* c = NULL;
                        AEROFLOT* e = NULL;
                        AEROFLOT* tmp = NULL;
                        string s, s1;
                        while (e != Head->next)
                        {
                            c = a = Head;
                            b = a->next;
                            while (a != e)
                            {
                                s = a->Destination;
                                s1 = b->Destination;
                                if (s.compare(s1) > 0)
                                {
                                    if (a == Head)
                                    {
                                        tmp = b->next;
                                        b->next = a;
                                        a->next = tmp;
                                        Head = b;
                                        c = b;
                                    }
                                    else
                                    {
                                        tmp = b->next;
                                        b->next = a;
                                        a->next = tmp;
                                        c->next = b;
                                        c = b;
                                    }
                                }
                                else
                                {
                                    c = a;
                                    a = a->next;
                                }
                                
                            b = a->next;
                                if (b == e)
                                    e = a;
                            }
                        }
                        cout << " Действие выполнено." << endl;
                        system("pause");
                        pov = false;
                        break;
                    }
                default:
                    cout << " Пожалуйста, выберите действие из предложенных. " << endl;
                    system("pause");
                    break;
            }
        }
    }
    else
    {
        cout << " Список пуст! " << endl;
        system("pause");
    }
}
void BD::toSave()
{
    ofstream file("DB.txt");
    AEROFLOT* temp = Head;
    while (temp != NULL)
    {
        if (temp->next == NULL)
            file << temp->Destination << endl << temp->FlightNumber << endl << temp->TypeOfAircraft;
        else
            file << temp->Destination << endl << temp->FlightNumber << endl << temp->TypeOfAircraft << endl;
        temp = temp->next;
    }
    file.close();
    cout << " Данные были сохранены." << endl;
    system("pause");
}
void BD::fromFile()
{
    ifstream file("DB.txt");
    string Dest, Type, Out;
    int counter = 0;
    char cnum[10];
    int Num;
    if (!file.is_open())
    {
    ofstream file;
        file.open("DB.txt");
        file.close();
        cout << " Файл был создан." << endl;
        system("pause");
    }
    else if (file.peek() == EOF)
    {
        cout << " Фаил пуст." << endl;
        system("pause");
    }
    else
    {
        while (!file.eof())
        {
            bool check = false;
            getline(file, Dest);
            if (!Dest.empty())
            {
                file >> cnum;
                if (isdigit(cnum[0]))
                {
                    Num = atoi(cnum);
                    if ((Num > 0) && (Num <= 9999))
                    {
                        AEROFLOT* t = Head;
                        getline(file, Out);
                        if (t != NULL)
                        {
                            while (t != NULL)
                            {
                                if (t->FlightNumber == Num) check = true;
                                t = t->next;
                            }
                        }
                        free(t);
                        getline(file, Type);
                        if (!check) check = findIn(Type, 0);
                    }
                    else
                    {
                        getline(file, Out);
                        getline(file, Out);
                        check = true;
                    }
                }
                else
                {
                    getline(file, Out);
                    getline(file, Out);
                    check = true;
                }
            }
            else
            {
                getline(file, Out);
                getline(file, Out);
                check = true;
            }
            if (!check)
            {
                
            AEROFLOT* tempNew = new AEROFLOT;
                tempNew->next = NULL;
                tempNew->Destination = Dest;
                tempNew->FlightNumber = Num;
                tempNew->TypeOfAircraft = Type;
                if (Head != NULL)
                {
                    Tail->next = tempNew;
                    Tail = tempNew;
                }
                else
                {
                    Head = Tail = tempNew;
                }
            }
            else
            {
                counter++;
            }
        }
        file.close();
    }
    if (counter != 0)
    {
        cout << " " << counter << " запись(-и/-ей) повреждена(-ы) и пропущена(-ы)." << endl;
        system("pause");
    }
}
void BD::listEditor()
{
    AEROFLOT* temp = Head;
    if (temp != NULL)
    {
        AEROFLOT* doubles;
        int Num, cNum, count = 0;
        char p;
        string Dest, Type, Out;
        bool check = true;
        while (check)
        {
            system("cls");
            cout << " Введите номер рейса, данные которого хотите отредактировать: ";
        while (true)
            {
                cNum = CheckNumber();
                if ((cNum > 0) && (cNum <= 9999)) break;
                else cout << " Номер рейса должен содержать 4 цифры! " << endl;
            }
            while (temp != NULL)
            {
                if (temp->FlightNumber == cNum)
                {
                    count++;
                    break;
                }
                temp = temp->next;
               
            }
            if (count != 0)
            {
                doubles = temp;
                system("cls");
                cout << " Пункт назначения : " << temp->Destination << endl;
                cout << " Номер рейса : " << temp->FlightNumber << endl;
                cout << " Тип самолёта : " << temp->TypeOfAircraft << endl;
                cout << "\n Выберите какое поле вы желаете отредактировать :"<< endl;
                cout << " 1. Место назначения " << endl;
                cout << " 2. Номер рейса " << endl;
                cout << " 3. Тип самолёта " << endl;
                cout << " Выберите действие --> ";
                cin >> p;
                cin.clear();
                cin.ignore(numeric_limits < streamsize >::max(), '\n');
                system("cls");
                switch (p)
                {
                    case '1':
                        {
                            cin.clear();
                            cout << " Введите пункт назначения : ";
                            getline(cin, Dest);
                            temp->Destination = Dest;
                            cout << " Действие выполнено. " << endl;
                            system("pause");
                            check = false;
                            break;
                        }
                    case '2':
                        {
                            cin.clear();
                            while (check)
                            {
                                AEROFLOT* TCheck = Head;
                                cout << " Введите номер рейса : ";
                                while (true)
                                {
                                    Num = CheckNumber();
                                    if ((Num > 0) && (Num <= 9999)) break;
                                    else cout << " Номер рейса должен содержать 4 цифры! " << endl;
                                }
                                while (TCheck != NULL)
                                {
                                    if ((TCheck->FlightNumber == Num) &&
                                    (TCheck != doubles))
                                    {
                                        cout << " Обнаружен рейс с таким же номером!Проверьте правильность ввода!" << endl;
                                    break;
                                    }
                                    else TCheck = TCheck->next;
                                }
                                if (TCheck == NULL)
                                {
                                    temp->FlightNumber = Num;
                                   
                                check = false;
                                }
                            }
                            cout << " Действие выполнено. " << endl;
                            system("pause");
                            check = false;
                            break;
                        }
                    case '3':
                        {
                            bool tp = true;
                            while (tp)
                            {
                                cin.clear();
                                cout << " Введите тип самолёта : ";
                                getline(cin, Type);
                                tp = findIn(Type, 1);
                            }
                            temp->TypeOfAircraft = Type;
                            cout << " Действие выполнено. " << endl;
                            system("pause");
                            check = false;
                            break;
                        }
                    default:
                        cout << " Пожалуйста, выберите пункт меню." << endl;
                        system("pause");
                        break;
                }
            }
            else
            {
                cout << " Данные о рейсе не найдены. " << endl;
                system("pause");
                check = false;
            }
        }
    }
    else
    {
        cout << " Список пуст! " << endl;
        system("pause");
    }
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    bool POV = true, CTS = true;
    char p, o;
    BD data;
    data.fromFile();
    while (POV)
    {
        system("cls");
        cout << " 1. Вывод на экран " << endl;
        
    cout << " 2. Добавить запись " << endl;
        cout << " 3. Удалить запись " << endl;
        cout << " 4. Поиск записи по типу самолёта " << endl;
        cout << " 5. Редактирование запись " << endl;
        cout << " 6. Сортировка " << endl;
        cout << " 7. Сохранение " << endl;
        cout << " 8. Выход " << endl;
        cout << " Выберите желаемое действие --> ";
        cin >> p;
        cin.clear();
        cin.ignore(numeric_limits < streamsize >::max(), '\n');
        cout << endl;
        switch (p)
        {
            case '1':
                system("cls");
                data.Show();
                break;
            case '2':
                system("cls");
                data.Add();
                CTS = true;
                break;
            case '3':
                system("cls");
                data.Delete();
                CTS = true;
                break;
            case '4':
                system("cls");
                data.Search();
                break;
            case '5':
                system("cls");
                data.listEditor();
                CTS = true;
                break;
            case '6':
                system("cls");
                data.Sorting();
                CTS = true;
                break;
            case '7':
                system("cls");
                data.toSave();
                CTS = false;
                break;
            case '8':
                {
                    if (CTS)
                    {
                        cout << " Желаете ли вы сохранить данные? (Y для подтверждения) ";
                    char check;
                        
                    cin >> check;
                        cin.clear();
                        cin.ignore(numeric_limits < streamsize >::max(), '\n');
                        if (check == 'y' || check == 'Y' || check == 'Н' || check == 'н')
                        {
                            data.toSave();
                        }
                    }
                    POV = false;
                    break;
                }
            default:
                {
                    cout << " Пожалуйста, выберите действие из предложенных в меню." << endl;
                    system("pause");
                    break;
                }
        }
    }
    data.~BD();
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    _CrtDumpMemoryLeaks();
    return 0;
}