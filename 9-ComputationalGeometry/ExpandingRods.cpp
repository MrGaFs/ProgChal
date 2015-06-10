#include <stdio.h>
#include <cmath>
#include <cstddef>
#include <limits>

using namespace std;

static double INF = 0xfffffff;
static double EPS = 1e-20;

double calculateLength(double n, double L, double C);
double newtonsMethod(double L, double seg);

int main() {
	double n, L, C; //degrees, length, coefficient
	scanf("%lf %lf %lf", &L, &n, &C);
	while (L > -1 && n > -1 && C > -1) {
		if (n*C < EPS || L == 0) { // too small
			printf("0.000\n");
		} else {
			double seg = calculateLength(n, L, C);
			// http://en.wikipedia.org/wiki/Sagitta_%28geometry%29
		    double mid, low, high;
			double oldAngle = -1;
		    low = 0;
		    high = INF;
		    while (high-low > EPS) {
		        mid = (high+low)/2;
		        double angle = asin(L/(mid*2)); // ?this is the issue
				if (angle == oldAngle) {
					break;
				} else {
					oldAngle = angle;
				}
		        double circ = 2*angle*mid;
		        if(circ < seg) {
		            high = mid;
		        } else {
		            low = mid;
		        }
		    }

			double h = mid - sqrt(mid*mid-L*L/4);
//			printf("seg: %lf\nmid: %lf\n", seg, r);
			printf("%0.3f\n", h);
		}
		scanf("%lf %lf %lf", &L, &n, &C);
	}
	return 0;
}

// In hindsight, this is actually binary search
/*double newtonsMethod(double L, double seg) {
	double mid, low, high;
	low = 0;
	high = INF;
	while (std::fabs(high-low) > EPS) {
		mid = (high+low)/2;
		double r =  L/(2*sin(mid/2)) //-> radius.
		double a = sin((L/2)/r);
		if(a > Pi) {
			high = mid;
		} else {
			low = mid;
		}
	}
	return mid; // found our radius.
}*/

double calculateLength(double n, double L, double C) {
	return (1+n*C)*L;
}
