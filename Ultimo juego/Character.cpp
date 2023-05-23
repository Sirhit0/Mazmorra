#include "character.h"

const int WIDTH = 10;
const int HEIGHT = 10;

Character::Character()
    : x(WIDTH / 2), y(HEIGHT / 2), health(100), attack(10), magicAttackUsed(false)
{
}

Character::Character(int startX, int startY, int initialHealth, int initialAttack)
    : x(startX), y(startY), health(initialHealth), attack(initialAttack), magicAttackUsed(false)
{
}

int Character::getX() const
{
    return x;
}

int Character::getY() const
{
    return y;
}

int Character::getHealth() const
{
    return health;
}

int Character::getAttack() const
{
    return attack;
}

bool Character::hasMagicAttackUsed() const
{
    return magicAttackUsed;
}

void Character::setX(int newX)
{
    x = newX;
}

void Character::setY(int newY)
{
    y = newY;
}

void Character::setHealth(int newHealth)
{
    health = newHealth;
}

void Character::setAttack(int newAttack)
{
    attack = newAttack;
}

void Character::setMagicAttackUsed(bool used)
{
    magicAttackUsed = used;
}

void Character::moveUp()
{
    if (y < HEIGHT - 1)
    {
        y++;
    }
}

void Character::moveDown()
{
    if (y > 0)
    {
        y--;
    }
}

void Character::moveLeft()
{
    if (x > 0)
    {
        x--;
    }
}

void Character::moveRight()
{
    if (x < WIDTH - 1)
    {
        x++;
    }
}

void Character::decreaseHealth(int damage)
{
    health -= damage;
}

void Character::useMagicAttack()
{
    magicAttackUsed = true;
}
