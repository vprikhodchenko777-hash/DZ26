

#include <iostream>
#include <windows.h>
using namespace std;

class Gradebook
{
private:
    int* grades;
    int count;

public:
    explicit Gradebook(int count) : count(count < 1 ? 1 : count)
    {
        grades = new int[this->count] {};
    }

    Gradebook(double count) = delete;
    Gradebook(const Gradebook& other) = delete;
    Gradebook& operator=(const Gradebook& other) = delete;

    ~Gradebook()
    {
        delete[] grades;
    }

    int& operator[](int i) { return grades[i]; }
    int operator[](int i) const { return grades[i]; }
    int getCount() const { return count; }

    double average() const
    {
        int sum = 0, n = 0;
        for (int i = 0; i < count; i++)
            if (grades[i] != 0)
            {
                sum += grades[i];
                n++;
            }
        return n == 0 ? 0 : (double)sum / n;
    }

    explicit operator bool() const
    {
        for (int i = 0; i < count; i++)
            if (grades[i] != 0) return true;
        return false;
    }

    bool setGrade(int i, int grade)
    {
        if (i < 0 || i >= count || grade < 1 || grade > 12)
            return false;
        grades[i] = grade;
        return true;
    }

    friend ostream& operator<<(ostream& out, const Gradebook& b);
    friend istream& operator>>(istream& in, Gradebook& b);
};

ostream& operator<<(ostream& out, const Gradebook& b)
{
    out << "Оценки: ";
    for (int i = 0; i < b.count; i++)
    {
        if (b.grades[i] == 0) out << "- ";
        else out << b.grades[i] << " ";
    }
    return out << "| средний балл: " << b.average();
}

istream& operator>>(istream& in, Gradebook& b)
{
    for (int i = 0; i < b.count; i++)
    {
        int grade;
        if (!(in >> grade)) return in;
        b.grades[i] = (grade >= 0 && grade <= 12) ? grade : 0;
    }
    return in;
}

int bestGrade(const Gradebook& b)
{
    int best = 0;
    for (int i = 0; i < b.getCount(); i++)
        if (b[i] > best) best = b[i];
    return best;
}

bool operator<(const Gradebook& a, const Gradebook& b)
{
    return a.average() < b.average();
}

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Gradebook book(5);
    cout << book << endl;

    if (!book) cout << "Оценок ещё нет" << endl;

    book[0] = 10;
    book[1] = 12;
    book[3] = 9;

    cout << book << endl;
    cout << "Лучшая оценка: " << bestGrade(book) << endl;


    if (!book.setGrade(2, 15))
        cout << "Неверная оценка!" << endl;

    Gradebook book2(5);
    cout << "Введите 5 оценок: ";
    if (!(cin >> book2)) return 1;

    cout << book2 << endl;

    if (book < book2)
        cout << "У второго студента балл выше" << endl;
    else if (book2 < book)
        cout << "У первого студента балл выше" << endl;
    else
        cout << "Средние баллы равны" << endl;

    return 0;
}



/*


  1. 

     Потому что слева находится cout, а не объект Gradebook.
     

  2. 
     Первая версия нужна для изменения оценок.
     Вторая версия нужна для чтения оценок константного объекта.
     


  3.

     Потому что [] возвращает ссылку на элемент массива.
     


  4. 

     explicit запрещает автоматическое преобразование объекта в bool.
     Без explicit можно было бы написать:

     


  5.  
  
       Скопировался бы только указатель grades.
       Оба объекта работали бы с одним массивом.
     

  6.   Я сделал его глобальной функцией.
      Он сравнивает средние баллы двух журналов.
     

*/
