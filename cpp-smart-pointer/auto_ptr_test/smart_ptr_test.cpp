#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class smart_ptr
{
public:
    smart_ptr(): p_(0) {}
    explicit smart_ptr(T *p): p_(p) {}
    smart_ptr(smart_ptr<T> &rhs): p_(rhs.release()) {}
    ~smart_ptr() {
        clean();
    }

    void reset(T *p) {
        clean();
        p_ = p;
    }

    T* get() {
        return p_;
    }

    T* release() {
        T* tmp = p_;
        p_ = 0;
        return tmp;
    }

    smart_ptr<T>& operator= (smart_ptr<T> &rhs) {
        if (this != &rhs) {
            this->reset(rhs.release());
        }

        return *this;
    }

    bool operator! () const {
        return !p_;
    }

    T& operator* () const {
        return *p_;
    }

    T* operator-> () const {
        return p_;
    }

    void clean() {
        if (p_) {
            delete p_;
            p_ = 0;
        }
    }
private:
    T *p_;
};

int *make_int()
{
    int *tmp = new int(3);
    if (!tmp)
        return 0;

    bool cond = true;
    if (!cond)
        return 0;

    return tmp;
}

struct some_type {
    int a_int;
    float b_float;
};

some_type *make_some_type()
{
    return new some_type();
}

bool some_func()
{
    smart_ptr<int> int_p(make_int());
    if (!int_p.get())
        return false;

    // set int to 4
    *int_p = 4;
    smart_ptr<some_type> some_type_p(make_some_type());
    if (!some_type_p)
        return false;

    // set a_int field to 4
    // set b_float field to 8.0
    some_type_p->a_int = 4;
    some_type_p->b_float = 8.0;
    return true;
}

int main(int, char **)
{
    bool rc = some_func();
    cout << "some_func return " << rc << endl;
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
