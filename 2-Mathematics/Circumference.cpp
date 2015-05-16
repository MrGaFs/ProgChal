#include<stdlib.h>
#include<stdio.h>
#include<math.h>

double calculateRadius(double p1, double p2, double m1, double midpoint1x, double midpoint1y, double m2, double midpoint2x, double midpoint2y);

int main() {
  double p1, p2, q1, q2, r1, r2;
  double pi = 3.141592653589793;
  
  while(scanf("%lf %lf %lf %lf %lf %lf\n", &p1, &p2, &q1, &q2, &r1, &r2) != EOF) {
    // Perpendicular bisector of a chord must pass through the centre.
    // Sometimes, picking the wrong ones causes infinity things to happen, so we have to try all of them.
    double m1 = -1/((p2-q2)/(p1-q1)); // Perpendicular
    double midpoint1x = (p1+q1)/2;
    double midpoint1y = (p2+q2)/2; 
    double m2 = -1/((q2-r2)/(q1-r1));
    double midpoint2x = (r1+q1)/2;
    double midpoint2y = (r2+q2)/2;
    double m3 = -1/((r2-p2)/(r1-p1));
    double midpoint3x = (r1+p1)/2;
    double midpoint3y = (r2+p2)/2;

    // y - y1 = m(x-x1)

    double radius = calculateRadius(p1, p2, m1, midpoint1x, midpoint1y, m2, midpoint2x, midpoint2y);
    if (isnan(radius) != 0) {
      radius = calculateRadius(p1, p2, m1, midpoint1x, midpoint1y, m3, midpoint3x, midpoint3y);
    }
    if (isnan(radius) != 0) {
      radius = calculateRadius(p1, p2, m2, midpoint2x, midpoint2y, m3, midpoint3x, midpoint3y);
    }

    printf("%0.2f\n", 2*pi*radius);
  }

  return EXIT_SUCCESS;
}

double calculateRadius(double p1, double p2, double m1, double midpoint1x, double midpoint1y, double m2, double midpoint2x, double midpoint2y) {
  double centreX = (m1*midpoint1x - m2*midpoint2x + midpoint2y - midpoint1y)/(m1-m2);
  double centreY = m2*(centreX-midpoint2x)+midpoint2y;
  double radius = sqrt((p1-centreX)*(p1-centreX) + (p2-centreY)*(p2-centreY));
  return radius;

}
