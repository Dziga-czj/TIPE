#ifndef TOOLS_H_
#define TOOLS_H_

#include <stdlib.h>
#include "raylib.h"
#include <math.h>
#include <stdbool.h>

Vector2 dir_vector(Vector2 src, Vector2 dest, float length);
float distance2(Vector2 v1, Vector2 v2);
float distance(Vector2 v1, Vector2 v2);
float get_angle(Vector2 pos1, Vector2 pos2);
bool collision_circle_line(Vector2 pos, float radius, Vector2 pos1, Vector2 pos2, Vector2 *closest);
float norme(Vector2 p1);
bool is_between(float x, float y, float test);
float produit_scal(Vector2 v1, Vector2 v2);
float add_to_vel(float val, float add);

void write_file(const char *filename, const char *text);


#endif