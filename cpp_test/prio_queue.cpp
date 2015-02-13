
class inodePrioQueue
{
    struct inodePrio {
	D::UUID uuid;
	U64 prio;

	inodePrio(const Inode& inode) {
	    uuid = inode.uuid();
	    prio = (D::Time::nowIs().sec() - inode.scrubTime().sec()) * inode.weight();
	};
    };

    bool operator< (const inodePrio& l, const inodePrio& r) {
	return l.prio < r.prio;
    };

    std::priority_queue<inodePrio> q;

    void push(const Inode& inode) {
	assert(inode.scrubTime().sec());
	q.emplace(inode);
    };

    int limit = 0;

public:
    

    const Inode& top() {
	return getInodes()->inode(q.top().uuid);
    };

    const Inode& pop() {
	const Inode& inode = top();
	q.pop();
	return inode;
    };

    /*
     * Push with respect to the limit, the amount of inodes
     * we are selecting for:
     *	    - if limit isn't reached, just push
     *	    - if limit is reached:
     *		- 
     */
    void pushLimited(const Inode& inode) {

    }

}

