double angleClock(int hour, int minutes)
{
    double angle;
    
    hour = hour % 12;
    
    double minutes_angle = minutes * 6.0;
    
    double hours_angle = hour * 30.0 + minutes * 0.5;
    
    angle = fabs(minutes_angle - hours_angle);
    
    if (angle > 180.0)
        angle = 360.0 - angle;
    
    return angle;
}