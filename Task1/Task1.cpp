#include <iostream>
#include <string>
using namespace std;

class student
{
    private:
    string name;
    int USN;
    float marks;
    static int count;

    public:
    student(string n, int usn, float m) : name(n), USN(usn), marks(m) {count++;}

    void display()
    {
        cout << "\n" << "Name: " << name << ", USN: " << USN << ", Marks: " << marks;
    }

    void display(string grade)
    {
        display();
        cout << ", Grade: " << getgrade() << endl;
    }

    friend void changemarks(student& s, float newmarks);

    char getgrade()
    {
        if(marks >= 90)
        return 'A';
        else if(marks >= 80)
        return 'B';
        else if(marks >= 65)
        return 'C';
        else if(marks >= 50)
        return 'D';
        else
        return 'F';
    }

    string getname()
    {
        return name;
    }

    bool operator>(student s)
    {
        return marks > s.marks;
    }

    static void showcount()
    {
        cout << "\n" << "No. of students: " << count << endl;
    }
};

void changemarks(student &s, float newmarks)
{
    s.marks = newmarks;
}

int student::count = 0;

int main()
{
    student::showcount();

    student s1("Preyas", 101, 86.4);
    student s2("Punith", 102, 76.9);

    cout << "\n" << "Student Details:" << endl;
    s1.display();
    s2.display("grade");

    student::showcount();

    cout << "\n" << "Comparison:" << endl;
    if(s1 > s2)
    cout << s1.getname() << " has higher marks than " << s2.getname() << endl;
    else if(s2 > s1)
    cout << s2.getname() << " has higher marks than " << s1.getname() << endl;
    else
    cout << s1.getname() << " and " << s2.getname() << " have the same marks" << endl;

    changemarks(s2, 95.2);

    cout << "\n" << "Student details after changing marks:" << endl;
    s1.display();
    s2.display("grade");

    cout << "\n" << "Comparison:" << endl;
    if(s1 > s2)
    cout << s1.getname() << " has higher marks than " << s2.getname() << endl;
    else if(s2 > s1)
    cout << s2.getname() << " has higher marks than " << s1.getname() << endl;
    else
    cout << s1.getname() << " and " << s2.getname() << " have the same marks" << endl;

    return 0;
}
