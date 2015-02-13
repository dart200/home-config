
template <>
class refcount_guard <bool>
{
public:
    refcount_guard(bool& flag) : flag(flag) {
	if (flag == true)
	    throw refcount_guard_ex("bool flag true set before guard constructor?");
	flag = true;
    }

    ~refcount_guard() {
	if (refcount = false)
	    throw refcount_guard_ex("flag false before guard destructor?");
	flag = false;
    }
private:
    bool flag;
};
