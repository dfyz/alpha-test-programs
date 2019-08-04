#include <stddef.h>

int printf(const char*, ...);

struct Point {
  double x;
  double y;
};

const size_t N = 4;

struct Point POLY[] = {
    {40547359.805348977, 20991407.4519994},
    {40547406.539216213, 20991408.345532853},
    {40547405.607148655, 20991456.331498079},
    {40547358.891922772, 20991455.404874228},
};

int main() {
    double area = 0.0;
    double x = 0.0;
    double y = 0.0;

    for (size_t i = 0; i < N; ++i) {
        struct Point* a = &POLY[i];
        struct Point* b = &POLY[(i + 1) % N];

        double cross = a->x * b->y - b->x * a->y;

        x += (a->x + b->x) * cross;
        y += (a->y + b->y) * cross;
        area += 3.0 * cross;
    }

    x /= area;
    y /= area;
    printf("X = %f, Y = %f\n", x, y);
}
