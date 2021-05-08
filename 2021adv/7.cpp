#include <iostream>
#include <queue>
#include <stack>

const int TYPE_STACK = 0;
const int TYPE_QUEUE = 1;
const int TYPE_PRIOR = 2;

class Container {
    void* container;
    int x;
    public:
        Container(int x):x(x)
        {
            switch (x)
            {
                case TYPE_STACK: container = new std::stack<int>;break;
                case TYPE_QUEUE: container = new std::queue<int>;break;
                case TYPE_PRIOR: container = new std::priority_queue<int>;break;
            }
        }
        int pull()
        {
            switch (x)
            {
                int a;
                case TYPE_STACK: a = ((std::stack<int>*)container)->top(), ((std::stack<int>*)container)->pop(); return a;break;
                case TYPE_QUEUE: a = ((std::queue<int>*)container)->front(), ((std::queue<int>*)container)->pop(); return a;break;
                case TYPE_PRIOR: a = ((std::priority_queue<int>*)container)->top(), ((std::priority_queue<int>*)container)->pop(); return a;break;
            }
        }
        void push(int a)
        {
            switch (x)
            {
                case TYPE_STACK: ((std::stack<int>*)container)->push(a);break;
                case TYPE_QUEUE: ((std::queue<int>*)container)->push(a);break;
                case TYPE_PRIOR: ((std::priority_queue<int>*)container)->push(a);break;
            }
        }
};

int main() {
    int n;
    Container s(TYPE_STACK), q(TYPE_QUEUE), p(TYPE_PRIOR);
    std::cin >> n;
    while (n--) {
        int t, x;
        std::cin >> t;
        if (t) {
            std::cout << s.pull() << ' ' << q.pull() << ' ' << p.pull() << std::endl;
        } else {
            std::cin >> x;
            s.push(x);
            q.push(x);
            p.push(x);
        }
    }
    return 0;
}