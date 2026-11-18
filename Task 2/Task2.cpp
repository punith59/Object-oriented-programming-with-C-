#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <exception>
#include <string>
using namespace std;

class InvalidMarks : public exception
{
    string msg;
    public:
    InvalidMarks(int m) : msg("Invalid marks: " + to_string(m) + " (must be 0 to 100)") {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class Student
{
    protected:
    int id;
    string name;
    public:
    Student(int i, string n) : id(i), name(n) {}
    virtual ~Student() {}

    virtual void displayDetails() const
    {
        cout << "\nID: " << id << "\nName: " << name << endl;
    }
    virtual void displayMarks() const
    {
        cout << "Marks not available" << endl;
    }
    virtual int getTotal() const { return 0; }
    int getId() const { return id; }
    string getName() const { return name; }
};

class Result : public Student
{
    int m1, m2, m3;
public:
    Result(int i, string n, int a, int b, int c) : Student(i, n), m1(a), m2(b), m3(c)
    {
        if (a < 0 || a > 100) throw InvalidMarks(a);
        if (b < 0 || b > 100) throw InvalidMarks(b);
        if (c < 0 || c > 100) throw InvalidMarks(c);
    }

    int getTotal() const override { return m1 + m2 + m3; }

    void displayDetails() const override
    {
        Student::displayDetails();
    }
    void displayMarks() const override
    {
        cout << "Marks: " << m1 << ", " << m2 << ", " << m3
             << "\nTotal: " << getTotal() << "/300"
             << "\nResult: " << (m1 >= 35 && m2 >= 35 && m3 >= 35 ? "PASS" : "FAIL") << endl;
    }

    void writeTo(ostream &out) const
    {
        out << id << " " << name << " " << m1 << " " << m2 << " " << m3 << "\n";
    }
};

void displayAll(const vector<unique_ptr<Student>> &v)
{
    if (v.empty()) { cout << "No records.\n"; return; }
    for (const auto &s : v)
    {
        s->displayDetails();
        s->displayMarks();
        cout << "\n" << "-----------------------------" << endl;
    }
}

void saveToFile(const vector<unique_ptr<Student>> &v)
{
    ofstream out("results.txt");
    if (!out) { cout << "Cannot open file for writing\n"; return; }
    for (const auto &s : v)
        static_cast<Result*>(s.get())->writeTo(out);
    cout << v.size() << " record(s) saved to results.txt\n";
}

void loadFromFile(vector<unique_ptr<Student>> &v, string fileName)
{
    ifstream in(fileName);
    if (!in) { cout << fileName << " not found\n"; return; }
    v.clear();
    int id, a, b, c;
    string name;
    while (in >> id >> name >> a >> b >> c)
    {
        try { v.push_back(make_unique<Result>(id, name, a, b, c)); }
        catch (const InvalidMarks &e) { cout << "[ERROR] " << e.what() << endl; }
    }
    cout << v.size() << " record(s) loaded from " << fileName << endl;
}

void showAbove(const vector<unique_ptr<Student>> &v)
{
    int limit;
    cout << "\nEnter total marks limit (out of 300): ";
    cin >> limit;

    int n = count_if(v.begin(), v.end(),
                     [limit](const unique_ptr<Student> &s) { return s->getTotal() > limit; });
    cout << "Students scoring above " << limit << ": " << n << endl;

    for (const auto &s : v)
        if (s->getTotal() > limit)
        {
            s->displayDetails();
            s->displayMarks();
        }
}

int main()
{
    vector<unique_ptr<Student>> students;

    loadFromFile(students, "students.txt");

    cout << "\n--- Student Records ---\n";
    displayAll(students);

    saveToFile(students);

    showAbove(students);
    return 0;
}