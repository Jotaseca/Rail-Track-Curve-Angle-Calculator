#define PI 3.14159265358979323846
#define EGravity 9.80665

float deg_to_rad (float angle_deg) {
    float angle;
    angle = angle_deg * PI / 180;
    return angle;
}

float rad_to_deg (float angle) {
    float angle_deg;
    angle_deg = angle * 180 / PI;
    return angle_deg;
}

float kmh_to_ms (float kmh) {
    float ms;
    ms = kmh / 3.6;
    return  ms;
}

float ms_to_kmh (float ms) {
    float kmh;
    kmh = ms * 3.6;
    return kmh;
}