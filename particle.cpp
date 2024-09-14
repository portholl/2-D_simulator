#include "particle.hpp"
#include "constans.hpp"
#include <cmath>
Namespace_box::particle::particle( double width, double height, double radiuss, double mas, double speed_x, double speed_y) : 
    radius(radiuss), mass(mas), x(width), y(height), dx(speed_x), dy(speed_y) {}
double Namespace_box::particle::get_particle_radius()
{
    return radius;
}
double Namespace_box::particle::get_particle_width()
{
    return x;
}
double Namespace_box::particle::get_particle_heigh()
{
    return y;
}
void Namespace_box::particle::update()
{
    x += dx;
	y += dy;
    if ((x - radius) < BOUND_LEFT) {dx = -dx; x = BOUND_LEFT + radius;} // Проверяем, чтобы круг не выходил за пределы окна
    if ((y - radius) < BOUND_UP) {dy = -dy; y = BOUND_UP + radius;}
    if ((x + radius) > BOUND_RIGHT) {dx = -dx; x = BOUND_RIGHT - radius;} // Проверяем, чтобы круг не выходил за пределы окна
    if ((y + radius) > BOUND_DOWN) {dy = -dy; y = BOUND_DOWN - radius;}
    
}
bool Namespace_box::particle::check_collision( Namespace_box::particle *b )
{
  if (this == b) return false;
  double r = radius + b->radius;
  r *= r;
  return r > (x - b->x)*(x - b->x) + (y - b->y)*(y - b->y);
}
void Namespace_box::particle::do_collision(Namespace_box::particle *b)
{
  double rv_x = b->dx - dx;// Вычисляем относительную скорость
  double rv_y = b->dy - dy;
  double normal_x = (b->x - x)/sqrt((b->x - x)*(b->x - x)+(b->y - y)*(b->y - y));
  double normal_y = (b->y - y)/sqrt((b->x - x)*(b->x - x)+(b->y - y)*(b->y - y));

  // Вычисляем относительную скорость относительно направления нормали
  double velAlongNormal = rv_x*normal_x +rv_y*normal_y;

  // Не выполняем вычислений, если скорости разделены
  if(velAlongNormal > 0)
    return;

  double e = 1; //абсолютно упругий удар

  // Вычисляем скаляр импульса силы
  double j = -(1 + e) * velAlongNormal;
  j /= 1 / mass + 1 / b->mass;

  // Прикладываем импульс силы
  double impulse_x = j * normal_x;
  double impulse_y = j * normal_y;
  dx-= 1 / mass * impulse_x;
  dy-= 1 / mass * impulse_y;
  b->dx += 1 / b->mass * impulse_x;
  b->dy += 1 / b->mass * impulse_y;
}
Namespace_box::big_particle::big_particle(double width, double height, double radiuss, double mas, double speed_x, double speed_y):
    particle(width, height, radiuss, mas, speed_x, speed_y) {};
Namespace_box::small_particle::small_particle(double width, double height, double speed_x, double speed_y):
    particle(width, height, SMALL_RADIUS, SMALL_MASS, speed_x, speed_y) {};
