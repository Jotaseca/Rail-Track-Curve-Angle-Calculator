#include <stdio.h>
#include <stdlib.h>
#include "functions.c"

int main() {
    float speed=0.0, radius=0.0, angle_deg=0.0, lat_gforce=0.0, ver_gforce=0.0;
    short int main_loop = 1;
    #ifdef _WIN32
        system("cls");   // Windows
    #else
        system("clear"); // Unix/Linux/Mac
    #endif // had to put this here to avoid errors.
    printf("This executable calculates speed, radius and angle of curves for rail infrastructure.\n");
    printf("When asked, insert speed in km/h, radius in meters and angle in degrees.\n");
    printf("The angle is the angle of the curve relative to the horizon.\n");

    while (main_loop == 1) {

        gcalc(&lat_gforce,&ver_gforce,speed,radius,angle_deg);
        smartCalculator(&speed,&radius,&angle_deg,lat_gforce,ver_gforce);
        printTable(speed, radius, angle_deg,lat_gforce,ver_gforce);
        mainSelection(&speed,&radius,&angle_deg);

        #ifdef _WIN32
            system("cls");   // Windows
        #else
            system("clear"); // Unix/Linux/Mac
        #endif
    }
    return 0;
}