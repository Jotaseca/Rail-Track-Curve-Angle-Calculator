#include <stdio.h>
#include <stdlib.h>
#include "functions.c"
#define PI 3.14159265358979323846

int main() {
    float speed=0.0, radius=0.0, angle_deg=0.0;
    short int main_loop = 1, smartCalculation = 1;
    #ifdef _WIN32
        system("cls");   // Windows
    #else
        system("clear"); // Unix/Linux/Mac
    #endif // had to put this here to avoid errors.
    printf("This executable calculates speed, radius and angle of curves for rail infrastructure.\n");
    printf("When asked, insert speed in km/h, radius in meters and angle in degrees.\n");
    printf("The angle is the angle of the curve relative to the horizon, the radius is the radius of the curve and the speed is the speed of the train.\n");
    while (main_loop == 1) {

        smartCalculator(&speed,&radius,&angle_deg,smartCalculation);
        printTable(speed, radius, angle_deg,smartCalculation);
        mainSelection(&speed,&radius,&angle_deg,&smartCalculation);
        
        #ifdef _WIN32
            system("cls");   // Windows
        #else
            system("clear"); // Unix/Linux/Mac
        #endif
    }
    return 0;
}