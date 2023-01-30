//Sanaz Rabinia Haratbar, January 29, 2023 
//Data Incubator coding challenge
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>

using namespace std;

//seive of Erathosthenes
bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

class Point {
private:
    double x;
    double y;

public:

    //default constructor
    Point() {
        x = 0;
        y = 0;
    }
    //constructor
    Point(double x, double y) {
        this->x = x;
        this->y = y;

    }
    //getters
    double getX() {
        return x;
    }
    double getY() {
        return y;
    }
    //setters
    void setPoint(double a, double b) {
        x = a;
        y = b;

    }


    double distance(double a, double b) {
        double euclideanDistance;

        euclideanDistance = sqrt(pow((x-a), 2)+ pow((y-b), 2));

        return euclideanDistance;
    }

    double distanceFromOrigin(int N) {
        double finalDistance = 0;
        double x1 = 0, y1 = 0; 
        double count1 =0 , count2 = 0;
        for (int i = 1; i < N + 1; i++) {
            if (isPrime(i) == false) {
                count1++;
            }
            else {
                count2++;
                
            }
        }
        y1 = y1 + count1;
        x1 = x1 + count2;
        finalDistance = sqrt(pow((x1 - x), 2) + pow((y1 - y), 2));
        return finalDistance;

    }

    double randomMove(int N) {
        vector<double> move;
        vector<double> selectedMovements;
        double py= 1, ny = -1, px = 2, nx=-2;
        double randomValue;
        double averageDistanceFromOrigin = 0;
        double distance = 0;
        double x1 = 0, y1 = 0;
        vector<double> allDistance;
        double variance =0 ;
        for (int i = 1; i < 101; i++) {
            if (i <= 50) {
                move.push_back(py);
            }
            else if (50<i && i<= 60) {
                move.push_back(ny);
            }
            else if (60 < i && i <= 80) {
                move.push_back(px);
            }
            else {
                move.push_back(nx);
            }

        }
        cout << "\noutput of vector: ";
        for (auto i = move.begin(); i != move.end(); ++i)
            cout << *i << " ";
        for (int i = 0; i < N; i++) {
             randomValue = rand() % move.size();
             selectedMovements.push_back(move[randomValue]);
        }
        cout << "\noutput of selected movements: ";
        for (auto i = selectedMovements.begin(); i != selectedMovements.end(); ++i)
            cout << *i << " ";

        for (int i = 0; i < N ; i++) {
            if (selectedMovements[i] == 1) {
                y1 = y1 + 1;
            }
            else if (selectedMovements[i] == -1) {
                y1 = y1 - 1;

            }
            else if (selectedMovements[i] == 2) {
                x1 = x1 + 1;

            }
            else {
                x1 = x1 - 1;

            }
            distance = sqrt(pow((x1 - x), 2) + pow((y1 - y), 2));
            allDistance.push_back(distance);

        }
        cout << "\nprint vetors of distance: ";
        for (auto i = allDistance.begin(); i != allDistance.end(); ++i)
            cout << *i << " ";
        
        for (int i = 0; i < allDistance.size(); i++) {
            averageDistanceFromOrigin += (allDistance[i])/N;
        }
        cout << "\nAverage distance from origin after " << N << " movements: " << averageDistanceFromOrigin << endl;
        for (int i = 0; i < allDistance.size(); i++) {
            variance += (pow((allDistance[i] - averageDistanceFromOrigin), 2)) / (N - 1);
        }

        cout << "variance of distance from origin after "<< N<< " movements: " << variance << endl;
        
        return variance;

    }


};


int main()
{
    Point p1;
    p1.setPoint(0, 0);
    
    cout << "p1: (" << p1.getX() << ", " << p1.getY() << ")" << endl;

    cout << "Euclidean Distance: " << p1.distance(3, 4)<< endl;

    cout << "(Question 2.1) distance from origin is: " << p1.distanceFromOrigin(100)<< endl;
    cout << "(Question 2.2 and 2.3) Average distance from origin and variance of the distance form the origin after 6 moves: " << endl;
    p1.randomMove(6);
    cout << "(Question 2.4 and 2.5) Average distance from origin and variance of the distance form the origin after 20 moves: " << endl;
    p1.randomMove(20);

  


    return 0;
    
}

