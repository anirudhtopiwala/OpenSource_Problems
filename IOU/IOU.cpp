#include <iostream>
#include <algorithm>


//Top Left Corner of the rectangle
struct Rect{ 
    double x;
    double y;
    double length;
    double breadth;
};

double GetIou(const Rect& a, const Rect& b) {
  const auto bottom_right_corner_x = std::min(a.x + a.length, b.x + b.length);
  const auto bottom_right_corner_y = std::min(a.y + a.breadth, b.y + b.breadth);

  const auto top_left_corner_x = std::max(a.x, b.x);
  const auto top_left_corner_y = std::max(a.y, b.y);

  const auto intersescting_length = bottom_right_corner_x - top_left_corner_x;
  const auto intersecting_breadth = bottom_right_corner_y - top_left_corner_y;

  if (intersescting_length < 0.0 || intersecting_breadth < 0.0) {
    return 0.0;
  }
  const auto iou_area = std::abs(intersescting_length * intersecting_breadth);

  return (iou_area / (a.length * a.breadth + b.length * b.breadth - iou_area));
}

int main() {
    
    Rect b{2,2,1,1};
    Rect a{1.5,1.5,1,1};
    auto iou = GetIou(a,b);
    std::cout<< iou << std::endl;
    return 0;
}
