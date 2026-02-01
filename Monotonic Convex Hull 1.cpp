struct CHT {

    struct Line {
        int slope, yIntercept;

        Line(int slope, int yIntercept) : slope(slope), yIntercept(yIntercept) {}

        int val(int x) {
            return slope * x + yIntercept;
        }

        int intersect(Line y) {
            return (y.yIntercept - yIntercept + slope - y.slope - 1) / (slope - y.slope);
        }
    };

    deque<pair<Line, int>> dq;

    void insert(int slope, int yIntercept) {
        Line newLine(slope, yIntercept);

        while ((int)dq.size() > 1 && dq.back().second >= dq.back().first.intersect(newLine))
            dq.pop_back();

        if (dq.empty()) {
            dq.emplace_back(newLine, 0);
            return;
        }

        dq.emplace_back(newLine, dq.back().first.intersect(newLine));
    }

    int query(int x) {

        while ((int)dq.size() > 1) {
            if (dq[1].second <= x) dq.pop_front();
            else break;
        }

        return dq[0].first.val(x);
    }

    int query2(int x) {
        auto qry = *lower_bound(dq.rbegin(), dq.rend(),
                                make_pair(Line(0, 0), x),
        [&](const pair<Line, int> &a, const pair<Line, int> &b) {
            return a.second > b.second;
        });

        return qry.first.val(x);
    }
};

**************

struct CHT
{
    struct Line
    {
        lli slope, yIntercept;
        Line(lli slope, lli yIntercept)
        {
            this->slope = slope;
            this->yIntercept = yIntercept;
        }

        lli GetValue(lli x)
        {
            return slope * x + yIntercept;
        }
        lli CeilDiv(lli a, lli b)
        {
            return (a + b - 1) / b;
        }
        lli GetIntersection(Line &other)
        {
            // y1 = m1x + c
            // y2 = m2x + c2
            // m1x + c1 = m2x + c2
            // x = (c2 - c1) / (m1 - m2)

            return CeilDiv((other.yIntercept - yIntercept), (slope - other.slope));
        }
    };
    deque<pair<Line, lli>> dq;
    void InsertLine(Line new_line)
    {
        while (!dq.empty() && dq.back().ss >= dq.back().ff.GetIntersection(new_line))
        {
            dq.pop_back();
        }

        if (dq.empty())
        {
            dq.pb({new_line, 0});
        }
        else
        {
            dq.pb({new_line, dq.back().ff.GetIntersection(new_line)});
        }
    }

    lli Query(lli x)
    {
        while (dq.size() > 1)
        {
            if (dq[1].ss <= x)
                dq.pop_front();
            else
                break;
        }
        return dq[0].ff.GetValue(x);
    }
};
