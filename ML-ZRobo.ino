#include "Motor.hpp"
//#define PI 3.14159265358979

template<typename T1, typename T2>
struct Pair
{
    T1 a;
    T2 b;
};

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
// std::ostream& operator<<(std::ostream &os, Point p)
// {
//     os << '[' << p.x << ' ' << p.y<<']';

//     return os;
// }
class Arm
{
    double l1,l2;
    Point current;
    Motor *m1,*m2;

    public:
        //arm with the two sections l1,l2. At start both facing upwards
        template<typename M1, typename M2>
        Arm(double ll1, double ll2, M1 &&m1, M2 &&m2):
            l1(ll1), l2(ll2), current(0,l1+l2), m1(new M1(m1)), m2(new M2(m2))
        {}

        //calculates the angles of the two sections so the end of the second is at point p
        Pair<double, double> angles(Point p)
        {
            double ph2= acos(
                (p.x*p.x+p.y*p.y-l1*l1-l2*l2)/
                    (2*l1*l2));
            double phi1 = atan2(p.y,p.x)
                -atan2(l2*sin(ph2),
                       (l1+l2*cos(ph2)));

            return Pair<double,double>{phi1/PI*180, ph2/PI*180};
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
            current=b;
            auto a = angles(current);
            m1->setAngle(a.a);
            m2->setAngle(a.b);
            
        }

        //lift/dops the pen on/off the canvas
        void shiftPen()
        {
            
        }

};


void setup()
{
    Serial.begin(115200);
    Arm a(1,2,
        MotorServo(19),
        MotorServo(20));
    Point goal(3,0);
    a.straightline(goal, 10);

}
void loop()
{

}

// int main()
// {
//     Arm a(2,1);
//     Point b(3,0);
//     a.straightline(b,10);
//     //auto [phi1, phi2] = a.angles(Point{1,2});
//     //std::cout << phi1 << " " << phi2 << std::endl;
// }
