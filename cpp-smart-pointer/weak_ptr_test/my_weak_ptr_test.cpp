#include <vector>
#include <string>
#include <atomic>
#include <iostream>

namespace MY_DEMO {

inline void atomic_increment(std::atomic_int *ptr)
{
    ptr->fetch_add(1, std::memory_order_relaxed);
}

inline int atomic_decrement(std::atomic_int *ptr)
{
    return ptr->fetch_sub(1, std::memory_order_acq_rel);
}

inline int atomic_conditional_increment(std::atomic_int *ptr)
{
    // long r = *pw;
    // if( r != 0 ) ++*pw;
    // return r;

    int r;
    while (true) {
        r = ptr->load(std::memory_order_relaxed);
        if (r == 0) {
            return r;
        }

        if (ptr->compare_exchange_weak(r, r + 1,
                std::memory_order_relaxed, std::memory_order_relaxed)) {
            return r;
        }
    }
}

class sp_counted_base
{
public:
    sp_counted_base(): use_count_(1), weak_count_(1) {
    }

    virtual ~sp_counted_base() {
    }

    void add_ref_copy() {
        atomic_increment(&use_count_);
    }

    bool add_ref_lock() {
        return atomic_conditional_increment(&use_count_) != 0;
    }

    void release() {
        if (atomic_decrement(&use_count_) == 1) {
            dispose();
            weak_release();
        }
    }

    void weak_add_ref() {
        atomic_increment(&weak_count_);
    }

    void weak_release() {
        if (atomic_decrement(&weak_count_) == 1) {
            destroy();
        }
    }

    int use_count() const {
        return use_count_;
    }

    virtual void dispose() = 0;

    void destroy() {
        delete this;
    }
private:
    sp_counted_base(const sp_counted_base&);
    sp_counted_base& operator= (const sp_counted_base&);

    std::atomic_int use_count_;
    std::atomic_int weak_count_;
};

template<typename T>
class sp_count_impl: public sp_counted_base
{
public:
    sp_count_impl(T *p = 0): p_(p) {
    }

    virtual ~sp_count_impl() {
    }

    virtual void dispose() {
        delete p_;
        p_ = 0;
    }

private:
    T *p_;
};

class weak_count;

class shared_count
{
public:
    friend class weak_count;

    template<typename T>
    explicit shared_count(T *p = 0): pi_(new sp_count_impl<T>(p)) {
    }

    ~shared_count() {
        if (pi_ != 0) pi_->release();
    }

    template<typename T>
    shared_count(const shared_count &r): pi_(r.pi_) {
        if (pi_ != 0) {
            pi_->add_ref_copy();
        }
    }

    explicit shared_count(const weak_count &r);

    shared_count& operator=(const shared_count &r) {
        sp_counted_base *tmp = r.pi_;

        if (pi_ != tmp) {
            if (tmp != 0) tmp->add_ref_copy();
            if (pi_ != 0) pi_->release();
            pi_ = tmp;
        }

        return *this;
    }

    void swap(shared_count &r) {
        sp_counted_base *tmp = r.pi_;
        r.pi_ = pi_;
        pi_ = tmp;
    }

    int use_count() const {
        return pi_ != 0 ? pi_->use_count() : 0;
    }

    bool empty() const {
        return pi_ == 0;
    }

private:
    sp_counted_base *pi_;
};

class weak_count
{
public:
    friend class shared_count;

    weak_count(): pi_(0) {
    }

    ~weak_count() {
    }

    weak_count(const shared_count &r): pi_(r.pi_) {
        if (pi_ != 0) pi_->weak_add_ref();
    }

    weak_count(const weak_count &r): pi_(r.pi_) {
        if (pi_ != 0) pi_->weak_add_ref();
    }

    weak_count& operator=(const shared_count &r) {
        sp_counted_base *tmp = r.pi_;
        if (tmp != pi_) {
            if (tmp != 0) tmp->weak_add_ref();
            if (pi_ != 0) pi_->weak_release();
            pi_ = tmp;
        }

        return *this;
    }

    weak_count& operator=(const weak_count &r) {
        sp_counted_base *tmp = r.pi_;
        if (tmp != pi_) {
            if (tmp != 0) tmp->weak_add_ref();
            if (pi_ != 0) pi_->weak_release();
            pi_ = tmp;
        }

        return *this;
    }

    void swap(weak_count &r) {
        sp_counted_base * tmp = r.pi_;
        r.pi_ = pi_;
        pi_ = tmp;
    }

    int use_count() const {
        return pi_ != 0 ? pi_->use_count() : 0;
    }

    bool empty() const {
        return pi_ == 0;
    }

private:
    sp_counted_base *pi_;
};

inline shared_count::shared_count(const weak_count &r): pi_(r.pi_) {
    if (pi_ != 0 && !pi_->add_ref_lock()) {
        pi_ = 0;
    }
}

template<class T> class weak_ptr;

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

    explicit shared_ptr(const weak_ptr<T> &r): px_(0), pn_(r.pn_) {
        if (!pn_.empty()) {
            px_ = r.px_;
        }
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

private:
    T *px_;
    shared_count pn_;

    friend class weak_ptr<T>;
};

template<typename T>
class weak_ptr
{
public:
    weak_ptr(): px_(0), pn_() {
    }

    weak_ptr(const weak_ptr &r): px_(r.px_), pn_(r.pn_) {
    }

    weak_ptr(const shared_ptr<T> &r) {
        px_ = r.px_;
        pn_ = r.pn_;
    }

    weak_ptr & operator=(const weak_ptr &r) {
        px_ = r.px_;
        pn_ = r.pn_;
        return *this;
    }

    shared_ptr<T> lock() const {
        return shared_ptr<T>(*this);
    }

    int use_count() const {
        return pn_.use_count();
    }

private:
    T *px_;
    weak_count pn_;

    friend class shared_ptr<T>;
};

} // namespace MY_DEMO

using MY_DEMO::shared_ptr;
using MY_DEMO::weak_ptr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

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

void test_shared_ptr_destructor()
{
    weak_ptr<int> test;
    {
        shared_ptr<int> test2(new int(2));
        test = test2;
        if (test.lock().get()) {
            cout << "test: " << *test.lock() << endl;
        }
    }

    if (test.lock().get()) {
        cout << "test: " << *test.lock() << endl;
    } else {
        cout << "test: null" << endl;
    }
}

int main()
{
    shared_ptr<Team> pt(new Team());
    shared_ptr<Person> pp(new Person());
    pt->name = "Test team";
    pt->persons.push_back(pp);
    pp->team = pt;
    pp->name = "Jack";
    pp->show();

    test_shared_ptr_destructor();
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
