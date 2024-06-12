#ifndef GUNS_H
#define GUNS_H

class Guns {
public:
    float fire_rate;
    float last_bullet_timer;
    int damage;

    Guns();
    void increse_timer(float dt);

};
#endif // GUNS_H
