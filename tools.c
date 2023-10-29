#include "tools.h"
#include <stdio.h>

float distance2(Vector2 v1, Vector2 v2)
{
    return ((v2.x - v1.x)*(v2.x - v1.x) + (v2.y - v1.y)*(v2.y - v1.y));
}

float distance(Vector2 v1, Vector2 v2)
{
    return sqrt((v2.x - v1.x)*(v2.x - v1.x) + (v2.y - v1.y)*(v2.y - v1.y));
}

float get_angle(Vector2 pos1, Vector2 pos2)
{
    return atan2(pos2.y - pos1.y, pos2.x - pos1.x) * 180 / PI;
}

float norme(Vector2 p1)
{
    return sqrt(p1.x * p1.x + p1.y * p1.y);
}

Vector2 dir_vector(Vector2 v1, Vector2 dest, float length)
{
    float norme = 1/sqrt((dest.x - v1.x)*(dest.x - v1.x) + (dest.y - v1.y)*(dest.y - v1.y));
    return ((Vector2) {(dest.x - v1.x)*norme*length, (dest.y - v1.y)*norme*length});
}

bool is_between(float x, float y, float test)
{
    if(x >= y)
    {
        return (x >= test) && (test >= y);
    }else
    {
        return (y >= test) && (test >= x);
    }
}

float produit_scal(Vector2 v1, Vector2 v2)
{
    return (v1.x * v2.y - v1.y * v2.x);
}

float add_to_vel(float val, float add)
{
    if(val*add < 0)
    {
        if(add >= val) return 0;
        else return val+add;
        
    }else return val+add;
}
    
bool col_test_corners(Vector2 pos, float radius, Vector2 pos1, Vector2 pos2, Vector2 *closest)
{
    float d1 = distance(pos, pos1);
    if (d1 < radius-radius/5)
    {
        (*closest).x = pos1.x;
        (*closest).y = pos1.y;
        return true;
    }

    float d2 = distance(pos, pos2);
    if (d2 < radius-radius/5)
    {
        (*closest).x = pos2.x;
        (*closest).y = pos2.y;
        return true;
    }
    return false;
}

bool collision_circle_line(Vector2 pos, float radius, Vector2 pos1, Vector2 pos2, Vector2 *closest)
{
    
    float A = pos2.y - pos1.y;
    float B = pos2.x - pos1.x;
    if(A == 0)
    {
        float delta = abs(pos.y - pos1.y);
        if(delta <= radius && is_between(pos1.x, pos2.x, pos.x))
        {
            (*closest).x = pos.x;
            if(pos1.y >= pos.y)
            {
                (*closest).y = pos.y + delta;
            }else
                (*closest).y = pos.y - delta;
            
            return true;
        }else return(col_test_corners(pos, radius, pos1, pos2, closest));
    }
    if(B == 0)
    {
        float delta = abs(pos.x - pos1.x);
        if(delta <= radius && is_between(pos1.y, pos2.y, pos.y))
        {
            (*closest).y = pos.y;
            if(pos1.x >= pos.x)
            {
                (*closest).x = pos.x + delta;
            }else
                (*closest).x = pos.x - delta;
            
            return true;
        }else return(col_test_corners(pos, radius, pos1, pos2, closest));
    }
    float ba = B/A;
    float D = pos1.x - ba*pos1.y;
    float C = D - pos.x;

    float a = ba*ba+1;
    float b = 2*(C*ba-pos.y);
    float c = C*C + pos.y*pos.y - radius*radius;
    
    if(b*b-4*a*c >= 0)
    {
        float y = -b/(2*a);
        float x = ba*y+D;

        if(is_between(pos1.x, pos2.x, x) && is_between(pos1.y, pos2.y, y))
        {
            (*closest).x = x;
            (*closest).y = y;
            return true;
        } else return(col_test_corners(pos, radius, pos1, pos2, closest));

    }else 
    return false;

}
