
#ifndef LANE_H
#define LANE_H

#include <vector>
#include "mobi_test/Point.h"

struct Lane {
    int id;
    std::vector<int> predecessor_ids;
    std::vector<int> successor_ids;
    std::vector<Point> points;
    float length;
};

#endif // LANE_H
