#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main() {
  int scenarios;
  scanf("%d", &scenarios);
  for(int x=0; x<scenarios; x++) {
    double radius;
    double chambers;
    scanf("%lf %lf", &radius, &chambers);
    // We want to make a r-sided polygon
    // sin(Pi/n) = r/(Rr), solving for r gives us the circumference
    // Maths derived from: http://mathforum.org/library/drmath/view/66639.html
    double pi = 3.141592653;
    double angle = pi/chambers; // Apex angle of the regular polygon
    double r=sin(angle)*radius/(1+sin(angle)); 
    printf("Scenario #%d:\n", x+1);
    printf("%0.3f\n\n", r);
  }

  return EXIT_SUCCESS;
}
