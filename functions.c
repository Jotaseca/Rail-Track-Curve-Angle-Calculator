#include "conversions.c"
#include <math.h>

void printTable(float speed, float radius, float angle_deg, float lat_gforce, float ver_gforce) {

    printf("\n");
    printf("1 - Speed:                   %.2fkm/h\n", speed);
    printf("2 - Radius of Curve:         %.2fm\n", radius);
    printf("3 - Track Horizontal Angle:  %.3fdeg\n", angle_deg);
    printf("Lateral G-Force:             %.3fg\n",lat_gforce);
    printf("Vertical G-force:            %.3fg\n",ver_gforce);
    printf("\n");

}

void printNotes(float speed, float radius, float angle_deg, float lat_gforce, float angle_calculated_deg, float ver_gforce) {
    short int notesnum = 0;

    printf("\n");
    printf("Notes:\n");

    // positivity errors
    if (speed <= 0) {
        printf("Error: Speed must be greater than 0.\n");notesnum++;
    }
    if (radius <= 0) {
        printf("Error: Radius must be greater than 0.\n");notesnum++;
    }
    if (angle_deg < 0) {
        printf("Error: Angle must be positive.\n");notesnum++;
    }

    // angle errors
    if (angle_deg > 8) {
        printf("Warning: The angle is too high for real world use, at %f.\n", angle_deg);notesnum++;
    }
    if (fabs(angle_calculated_deg - angle_deg) >= 1) {
        printf("Warning: The angle is not optimized for the given speed and radius of curve.\n");notesnum++;
    }
    if (angle_calculated_deg > 8) {
        printf("Warning: The optimal calculated angle for the given radius and speed is too high for real world use, at %f.\n", angle_calculated_deg);notesnum++;
        printf("Suggestion: Please consider changing the radius or speed.\n");notesnum++;
    }

    //Gforces errors
    if (lat_gforce>0.15) {
        printf("Warning: Lateral g-forces may be too high for comfort and real world use.\n");notesnum++;
    }
    if (ver_gforce>1.15) {
        printf("Warning: Vertical g-forces may be too high for comfort and real world use.\n");notesnum++;
    }

    //if there are no notes:
    if (notesnum==0) {
        printf("None.\n");
    }
}

void printSelection(float*speed,float*radius,float*angle_deg) {

    int parameter = 0;

    printf("Insert index of parameter you want to change: ");
    scanf("%d",&parameter);
    switch(parameter) {
        case 1:
            printf("Insert new speed: ");
            scanf("%f", speed);
            break;
        case 2:
            printf("Insert new radius: ");
            scanf("%f", radius);
            break;
        case 3:
            printf("Insert new Angle: ");
            scanf("%f", angle_deg);
            break;
        default:
            printf("Invalid.\n");
            break;
    }
}

void mainSelection(float*speed,float*radius,float*angle_deg) {
    int choice = 0;
    printf("\n");
    printf("Options:\n");
    printf("1 - Change Parameters\n");
    printf("\n");
    printf("Insert Selection: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            printSelection(speed,radius,angle_deg);
            break;
        default:
            printf("Error.");
            break;
    }
}

void smartCalculator(float*speed,float*radius,float*angle_deg, float lat_gforces, float ver_gforce) {

    float angle_calculated=0.0, angle_calculated_deg=0.0, radius_calculated=0.0, speed_calculated_ms=0.0, speed_calculated=0.0;
    float speedms = kmh_to_ms(*speed);
    float angle_rad = deg_to_rad(*angle_deg);

    /*
    if (smartCalculation) {
        if ((*speed!=0) && (*radius!=0) && (*angle_deg==0)) {
            // Speed and radius
            float angle = fabs(atan((speedms * speedms) / (EGravity * *radius)));
            *angle_deg = rad_to_deg(angle);
            printf("Automatically calculated angle.\n");
        } else if ((*radius!=0) && (*angle_deg!=0) && (*speed==0)) {
            // Radius and angle
            *speed = sqrt(fabs(EGravity * *radius * tan(angle_rad)));
            printf("Automatically calculated speed.\n");
        } else if ((*speed!=0)&&(*angle_deg!=0)&&(*radius==0)) {
            // Speed and angle
            *radius = fabs((speedms * speedms) / (EGravity * tan(angle_rad)));
            printf("Automatically calculated radius.\n");
        }
    }
    */

    angle_calculated = fabs(atan((speedms * speedms) / (EGravity * *radius)));
    angle_calculated_deg = angle_calculated * 180 / PI;
    radius_calculated = fabs((speedms * speedms) / (EGravity * tan(angle_rad)));
    speed_calculated_ms = sqrt(fabs(EGravity * *radius * tan(angle_rad)));
    speed_calculated = ms_to_kmh(speed_calculated_ms);

    printf("\n");
    printf("Calculator:\n");
    printf("Optimal speed assuming %.2fm radius and %.2fdeg angle: %.2fkm/h\n",*radius,*angle_deg,speed_calculated);
    printf("Optimal radius assuming %.2fkm/h speed and %.2fdeg angle: %.2fm\n",*speed,*angle_deg,radius_calculated);
    printf("Optimal track angle assuming %.2fkm/h speed and %.2fm radius: %.2fdeg\n",*speed,*radius,angle_calculated_deg);
    printNotes(*speed,*radius,*angle_deg,lat_gforces,angle_calculated_deg,ver_gforce);

}

void gcalc(float*lat_gforce,float*ver_gforce,float speed,float radius, float angle_deg) {

    float lat_acell = ((kmh_to_ms(speed))*(kmh_to_ms(speed)))/radius;
    float gforce_lat_noangle = ((kmh_to_ms(speed))*(kmh_to_ms(speed)))/(radius*EGravity);
    float gforce_lat_withangle = (gforce_lat_noangle-tan(deg_to_rad(angle_deg)))/cos(deg_to_rad(angle_deg));
    float vertical_gforces_withangleconsideration = cos(deg_to_rad(angle_deg))+(gforce_lat_noangle*sin(deg_to_rad(angle_deg)));

    *lat_gforce = gforce_lat_withangle;
    *ver_gforce = vertical_gforces_withangleconsideration;

}
