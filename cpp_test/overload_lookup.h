
template<typename T>
struct ptr
{
    T* p;

    ptr() { p = new T(); };
    ptr(const T& init_val) { p = new T(init_val); };
    ~ptr() { delete p; };
};

/* vim: ft=cpp */
