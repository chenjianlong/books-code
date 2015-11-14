#include <string>
#include <iostream>
#include <cassert>
#include <atomic>

namespace MY_DEMO {

template<typename T>
class intrusive_ptr
{
public:
    intrusive_ptr(): px_(0) {
    }

    intrusive_ptr(T *p, bool add_ref = true): px_(p) {
        if (px_ && add_ref) T::intrusive_ptr_add_ref(px_);
    }

    intrusive_ptr(const intrusive_ptr &r): px_(r.px_) {
        if (px_) T::intrusive_ptr_add_ref(px_);
    }

    ~intrusive_ptr() {
        if (px_ != 0 ) T::intrusive_ptr_release(px_);
    }

    intrusive_ptr& operator=(const intrusive_ptr &r) {
        this_type(r).swap(*this);
        return *this;
    }

    intrusive_ptr& operator=(T *r) {
        this_type(r).swap(*this);
        return *this;
    }

    void reset(T *r = 0) {
        this_type(r).swap(*this);
    }

    T* get() const {
        return px_;
    }

    T* detach() {
        T *ret = px_;
        px_ = 0;
        return ret;
    }

    T& operator*() const {
        assert(px_ != 0);
        return *px_;
    }

    T* operator->() const {
        assert(px_ != 0);
        return px_;
    }

private:
    typedef intrusive_ptr this_type;

    void swap(intrusive_ptr &r) {
        T *tmp = px_;
        px_ = r.px_;
        r.px_ = tmp;
    }

private:
    T *px_;
};

template<typename T>
class intrusive_ref_counter
{
public:
    static void intrusive_ptr_add_ref(T *self) {
        if (self)
            ++self->ref_count_;
    }

    static void intrusive_ptr_release(T *self) {
        if (self && self->ref_count_ > 0 && !--self->ref_count_)
            delete self;
    }

protected:
    intrusive_ref_counter(): ref_count_(0) {
    }

    std::atomic_int ref_count_;
};

} // namespace MY_DEMO

using MY_DEMO::intrusive_ptr;
using MY_DEMO::intrusive_ref_counter;
using std::string;
using std::cout;
using std::endl;

class Person: public intrusive_ref_counter<Person>
{
public:
    Person(const string &name): name_(name) {
    }

    void dump() {
        cout << "name: " << name_ << endl
            << "ref_count_: " << ref_count_ << endl;
    }

private:
    string name_;
};

void test_intrusive_ptr()
{
    intrusive_ptr<Person> p(new Person("Jim"));
    p->dump();
    {
        intrusive_ptr<Person> p2(p);
        p->dump();
    }

    cout << "after p2 destruct" << endl;
    p->dump();

    {
        intrusive_ptr<Person> p3;
        p3 = p;
        p->dump();
    }

    cout << "after p3 destruct" << endl;
    p->dump();
}

int main()
{
    test_intrusive_ptr();
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
