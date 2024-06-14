#include "include/Guns.h"

Guns::Guns() { // trzyma wartosci po jakim czasie moze strzelic i jak duzo zadaje, latwa zmiana
    fire_rate = 0.1f;
    damage = 1;
}

void Guns::increse_timer(float dt) { // czas od ostatniego wystrzalu
    last_bullet_timer += dt;
}
