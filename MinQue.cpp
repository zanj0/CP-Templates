class MinQue {
public:
    deque < pair <int , int> > dq;
    void enqueue(int x) {
        int cnt = 1;
        while (!dq.empty() && dq.back().first > x) {
            cnt += dq.back().second;
            dq.pop_back();
        }
        dq.push_back({x, cnt});
    }
    void dequeue() {
        dq.front().second--;
        if (dq.front().second == 0) {
            dq.pop_front();
        }
    }
    int getMin() {
        return dq.front().first;
    }
};


class MaxQue {
public:
    deque < pair <int , int> > dq;
    void enqueue(int x) {
        int cnt = 1;
        while (!dq.empty() && dq.back().first < x) {
            cnt += dq.back().second;
            dq.pop_back();
        }
        dq.push_back({x, cnt});
    }
    void dequeue() {
        dq.front().second--;
        if (dq.front().second == 0) {
            dq.pop_front();
        }
    }
    int getMax() {
        return dq.front().first;
    }
};