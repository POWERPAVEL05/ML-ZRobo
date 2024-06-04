#include <cmath>
#include <iostream>
#include <utility>

#define PI 3.14159265358979

struct Point
{
    double x,y;
    Point(double ix, double iy): x(ix), y(iy)
    {}
    Point operator-(Point other)
    {
        return Point(x-other.x, y-other.y);
    }
    
    Point operator+(Point other)
    {
        return Point(x+other.x, y+other.y);
    }

    Point operator*(double div)
    {
        return Point(x*div, y*div);
    }
    Point operator/(double div)
    {
        return Point(x/div, y/div);
    }
};
std::ostream& operator<<(std::ostream &os, Point p)
{
    os << '[' << p.x << ' ' << p.y<<']';
  
    return os;
}
class Arm
{
    double l1,l2;
    Point current;

    public:
        //arm with the two sections l1,l2. At start both facing upwards
        Arm(double ll1, double ll2):
            l1(ll1), l2(ll2),
            current(0,l1+l2)
        {}

        //calculates the angles of the two sections so the end of the second is at point p
        auto angles(Point p)
        {
            double ph2= acos(
                (p.x*p.x+p.y*p.y-l1*l1-l2*l2)/
                    (2*l1*l2));
            double phi1 = atan2(p.y,p.x)
                -atan2(l2*sin(ph2),
                       (l1+l2*cos(ph2)));
            return std::make_pair(phi1/PI*180, ph2/PI*180);
        }

        //goes form current position to point b in a "straight" line by dividing it in s Sections
        void straightline(Point b, int s)
        {
            Point delta=(b-current)/s;
            //std::cout<< delta<<std::endl;
                for(int i=0;i<s;i++)
                {
                    gotoP(current+delta);
                }
        }
        
        //goes form current to point b
        void gotoP(Point b)
        {
            std::cout<< current<<':';
            auto [phi1, phi2] = angles(current);
            std::cout << phi1 << " " << phi2 << std::endl;
            current=b;
        }

        //lift/dops the pen on/off the canvas
        void shiftPen()
        {
            
        }

};


int main()
{
    Arm a(2,1);
    Point b(3,0);
    a.straightline(b,10);
    //auto [phi1, phi2] = a.angles(Point{1,2});
    //std::cout << phi1 << " " << phi2 << std::endl;
}