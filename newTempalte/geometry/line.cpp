struct Line {
    Point s, e;
    double k;
    Line(){}
    Line(Point _s, Point _e) {
        s = _s;
        e = _e;
        k = atan2(e.y - s.y, e.x - s.x);
    }
    Point operator &(const Line& b) const {
        Point res = s;
        double t = ((s - b.s) * (b.s - b.e)) / ((s - e) * (b.s - b.e));
        res.x += (e.x - s.x) * t;
        res.y += (e.y - s.y) * t;
        return res;
    }
};
