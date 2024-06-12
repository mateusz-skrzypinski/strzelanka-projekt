#include "include/Guns.h"

Guns::Guns() {
    fire_rate = 0.1f;
    damage = 1;
}

void Guns::increse_timer(float dt) {
    last_bullet_timer += dt;
}
