#include <memory>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Person;

struct Team {
    Team() { cout << "Team constructor" << endl; }
    ~Team() { cout << "Team destructor" << endl; }
    vector<shared_ptr<Person> > persons;
    string name;
};

struct Person {
    Person() { cout << "Person constructor" << endl; }
    ~Person() { cout << "Person destructor" << endl; }
    weak_ptr<Team> team;
    string name;

    void show() {
        shared_ptr<Team> t = team.lock();
        if (!t) {
            cout << "Team not found" << endl;
            return;
        }

        cout << name << " in " << t->name << endl;
    }
};

int main()
{
    shared_ptr<Team> pt(new Team());
    shared_ptr<Person> pp(new Person());
    pt->name = "Test team";
    pt->persons.push_back(pp);
    pp->team = pt;
    pp->name = "Jack";
    pp->show();
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
