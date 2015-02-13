template <typename T>
class refcount_guard
{
public:
    refcount_guard(T& refcount) : refcount(refcount) {
	refcount++;
    }
    ~refcount_guard() {
	refcount--;
    }
private:
    T& refcount;
}

// vim:ft=cpp
