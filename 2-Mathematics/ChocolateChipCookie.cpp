#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#define EPS 1e-4

double location[205][2];
int diameter = 5;
double mx1, my1, mx2, my2;

double calculateDistance (double midX, double midY, double x, double y);
void calculateCentres (double x1, double y1, double x2, double y2);

int main() {
  // Read in the coordinates
  double x, y;
  int loc = 0;
  while (scanf("%lf %lf\n", &x, &y) != EOF) {
    location[loc][0] = x;
    location[loc][1] = y;
    loc ++;
  }

  // Find max number of things in places
  // Pick two points:
	// If theyre more than 5cm apart, they cant be on a circle
	// Otherwise, there are 2 midpoints the circle could be drawn from
		// Calculate these midpoints
  int greatest = 1;

  for (int i=0; i<loc-1; i++) {
    for (int j=i+1; j<loc; j++) {
      double x1 = location[i][0];
      double y1 = location[i][1];
      double x2 = location[j][0];
      double y2 = location[j][1];

      if ((sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)) - 5) < EPS) { // Can be circle
//        printf("MEBE A THING\n");
        // Calculate midpoint
        calculateCentres(x1, y1, x2, y2);
      //  printf("Points: %f %f %f %f\n", x1, y1, x2, y2);
      //  printf("Midpoints: %f %f %f %f\n", mx1, my1, mx2, my2);
        // Check if other points are on the edge (distance of 5)
        int points1 = 0;
        int points2 = 0;
        for(int k=0; k<loc; k++) {
          double x = location[k][0];
          double y = location[k][1];
          if (calculateDistance(mx1, my1, x, y) - 2.5 < EPS) {
            points1 ++;
          }
          if (calculateDistance(mx2, my2, x, y) - 2.5 < EPS) {
            points2 ++;
          }
        }
        if (points1 > greatest) {
          greatest = points1;
        }
        if (points2 > greatest) {
          greatest = points2;
        }
      }
    }
  }
  printf("%d\n", greatest);

  return EXIT_SUCCESS;
}

double calculateDistance (double midX, double midY, double x, double y) {
  return sqrt((midX-x)*(midX-x) + (midY-y)*(midY-y));
}

void calculateCentres (double x1, double y1, double x2, double y2) {
  // Calculate coords of the midpoint
  double midX = (x1+x2)/2.0;
  double midY = (y1+y2)/2.0;
  double radius = 2.5;

  // Calculate distance to the midpoint
  double distance = sqrt((midX-x1)*(midX-x1) + (midY-y1)*(midY-y1));

  // Calculate length of the mid-centre line
  double length = sqrt(radius*radius - distance*distance);

  // Calculate normal to the vector p1->p2
  double vx = (y1-y2)/distance/2.0;
  double vy = (x2-x1)/distance/2.0;

//  printf("vx: %f vy: %f midX: %f midY: %f length: %f\n", vx, vy, midX, midY, length);  

  // Get the midpoints of the circles
  mx1 = midX + length*vx;
  my1 = midY + length*vy;
  mx2 = midX - length*vx;
  my2 = midY - length*vy;
}
