#include <algorithm>
#include <atomic>
#include <iostream>
#include <vector>

namespace MY_DEMO {

template<typename T>
class sp_count
{
public:
    sp_count(T *p): p_(p), use_count_(0) {
    }

    void add_ref_copy() {
        ++use_count_;
    }

    void dispose() {
        delete p_;
    }
    void release() {
        if (--use_count_ == 0) {
            dispose();
            delete this;
        }
    }

    int use_count() const {
        return use_count_;
    }

private:
    T *p_;
    std::atomic_int use_count_;
};

template<typename T>
class shared_count
{
public:
    explicit shared_count(T *p = 0): pi_(new sp_count<T>(p)) {
    }

    ~shared_count() {
        if (pi_ != 0) pi_->release();
    }

    shared_count(const shared_count &r): pi_(r.pi_) {
        if (pi_ != 0) {
            pi_->add_ref_copy();
        }
    }

    shared_count& operator=(const shared_count &r) {
        sp_count<T> *tmp = r.pi_;

        if (pi_ != tmp) {
            if (tmp != 0) tmp->add_ref_copy();
            if (pi_ != 0) pi_->release();
            pi_ = tmp;
        }

        return *this;
    }

    void swap(shared_count &r) {
        sp_count<T> *tmp = r.pi_;
        r.pi_ = pi_;
        pi_ = tmp;
    }

    int use_count() const {
        return pi_ != 0 ? pi_->use_count() : 0;
    }

private:
    sp_count<T> *pi_;
};

template<typename T>
class shared_ptr
{
public:
    typedef shared_ptr<T> this_type;

    explicit shared_ptr(T *p = 0): px_(p), pn_(p) {
    }

    shared_ptr(const shared_ptr &r): px_(r.px_), pn_(r.pn_) {
    }

    ~shared_ptr() {
    }

    void reset(T *p) {
        if (p == px_)
            return;

        this_type(p).swap(*this);
    }

    T* get() {
        return px_;
    }

    void swap(shared_ptr &r) {
        std::swap(px_, r.px_);
        pn_.swap(r.pn_);
    }

    shared_ptr& operator= (const shared_ptr<T> &r) {
        px_ = r.px_;
        pn_ = r.pn_;
        return *this;
    }

    bool operator! () const {
        return !px_;
    }

    T& operator* () const {
        return *px_;
    }

    T* operator-> () const {
        return px_;
    }

    int use_count() const {
        return pn_.use_count();
    }

    void dump() {
        std::cout << "value = " << *px_ << std::endl;
        std::cout << "use_count = " << use_count() << std::endl;
    }

private:
    T *px_;
    shared_count<T> pn_;
};

} // namespace MY_DEMO

using MY_DEMO::shared_ptr;
using std::cout;
using std::endl;
using std::vector;

void test_copy_constructor()
{
    cout << "begin test_copy_constructor" << endl;
    shared_ptr<int> p1(new int(3));
    shared_ptr<int> p2(p1);
    cout << "p1 dump:" << endl;
    p1.dump();
    cout << "p2 dump:" << endl;
    p2.dump();
    cout << "end test_copy_constructor" << endl;
}

void test_assign()
{
    cout << "begin test_assign" << endl;
    shared_ptr<int> p1(new int(3));
    shared_ptr<int> p2;
    p2 = p1;
    cout << "p1 dump:" << endl;
    p1.dump();
    cout << "p2 dump:" << endl;
    p2.dump();
    cout << "end test_assign" << endl;
}

void test_reset()
{
    cout << "begin test_reset" << endl;
    shared_ptr<int> p1(new int(3));
    int *tmp = new int(6);
    p1.reset(tmp);
    p1.reset(tmp);
    p1.dump();
    cout << "end test_reset" << endl;
}

void test_save_in_vector()
{
    cout << "begin test_save_in_vector" << endl;
    vector<shared_ptr<int> > vec;
    shared_ptr<int> p1(new int(3));
    vec.push_back(p1);
    cout << "p1 dump:" << endl;
    p1.dump();
    cout << "end test_save_in_vector" << endl;
}

int main()
{
    test_copy_constructor();
    test_assign();
    test_reset();
    test_save_in_vector();
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
