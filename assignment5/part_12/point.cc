/**
 * @file point.cc
 * @author C. Eom
 * @date 16-May-2023
*/

#include "point.h"
/**
 * @brief Overloads the equality comparison operator(==) for two Point
 * @param rhs       The Point object to compare against
 * @return True if x, y are equal, false otherwise
*/
bool Point::operator==(const Point& rhs){

    bool result = (x == rhs.x) && (y == rhs.y);
    std::cout << "Comparing Points" << *this << " == " << rhs << " -> " << std::boolalpha << result << std::endl;
    
    return result;
}

/**
 * @brief Writes a vector of Point to a file
 * @param fn    file name
 * @param pts   A vector of Point to be written to the file
*/
void write_to_file(std::string fn, std::vector<Point> pts){
    std::ofstream file(fn);
    if (file.is_open()){
        for (const auto& point : pts){
            file << point << '\n';
        }
        file.close();
    }
}

/**
 * @brief Calculate the cross products of two vectors
 * @brief Determine whether it is orientated in the negative k direction
 * @param p1, p2, p3    Three Points
 * @return True if the cross product is negative or 0, False otherwise
*/
bool cross_prod(Point p1, Point p2, Point p3){
    double equation = ((p2.x - p1.x) * (p3.y - p1.y)) - ((p2.y - p1.y) * (p3.x - p1.x));
    
    return equation <= 0;
}

/**
 * @brief Sort a vector of Point in ascending orer of the x
 * @brief if two points have the same x, it sorts them based on their y
 * @param points
*/
void sort_points(std::vector<Point>& points){
    std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        if (a.x == b.x){
            return a.y < b.y;
        }
        return a.x < b.x;
    });
}
