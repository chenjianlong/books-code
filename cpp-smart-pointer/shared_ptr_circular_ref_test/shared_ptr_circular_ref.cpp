#include <memory>
#include <vector>
#include <iostream>

using namespace std;

struct Person;

struct Team {
    Team() { cout << "Team constructor" << endl; }
    ~Team() { cout << "Team destructor" << endl; }
    vector<shared_ptr<Person> > persons;
};

struct Person {
    Person() { cout << "Person constructor" << endl; }
    ~Person() { cout << "Person destructor" << endl; }
    shared_ptr<Team> team;
};

int main()
{
    shared_ptr<Team> pt(new Team());
    shared_ptr<Person> pp(new Person());
    pt->persons.push_back(pp);
    pp->team = pt;
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
