#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
private:
    int x;
    int y;
    int health;
    int attack;
    bool magicAttackUsed;

public:
    Character();
    Character(int startX, int startY, int initialHealth, int initialAttack);

    // Getters
    int getX() const;
    int getY() const;
    int getHealth() const;
    int getAttack() const;
    bool hasMagicAttackUsed() const;

    // Setters
    void setX(int newX);
    void setY(int newY);
    void setHealth(int newHealth);
    void setAttack(int newAttack);
    void setMagicAttackUsed(bool used);

    // Movement
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    // Actions
    void decreaseHealth(int damage);
    void useMagicAttack();
};

#endif  // CHARACTER_H