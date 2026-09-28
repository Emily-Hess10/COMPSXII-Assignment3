/*
 * Object Simulator Assignment
 * Computer Science XII - Computer Systems
 * 
 * This program simulates object-oriented programming using structs and
 * function pointers to understand how Python's class system works at the
 * implementation level.
 * 
 * You'll build an RPG character system with inheritance and polymorphism.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =============================================================================
// PART 1: BASE CHARACTER STRUCT
// =============================================================================

typedef struct Character {
    char name[50];
    int health;
    int level;

    void (*attack)(struct Character* self);
    void (*take_damage)(struct Character* self, int damage);

} Character;

// =============================================================================
// PART 2: CHARACTER METHODS
// =============================================================================

void character_attack(Character* self) {
    printf("%s performs a basic attack!\n", self->name);
}

void character_take_damage(Character* self, int damage) {
    self->health -= damage;

    printf("%s takes %d damage! Health: %d\n",
           self->name, damage, self->health);
}

void character_init(Character* self, const char* name, int health, int level) {
    strncpy(self->name, name, sizeof(self->name) - 1);
    self->name[sizeof(self->name) - 1] = '\0';

    self->health = health;
    self->level = level;

    self->attack = character_attack;
    self->take_damage = character_take_damage;
}

// =============================================================================
// PART 3: DERIVED CHARACTER TYPES
// =============================================================================

typedef struct Warrior {
    Character base;
    int strength;

} Warrior;

typedef struct Mage {
    Character base;
    int mana;

} Mage;

// =============================================================================
// PART 4: POLYMORPHIC METHODS
// =============================================================================

void warrior_attack(Character* self) {
    Warrior* w = (Warrior*)self;

    printf("%s swings sword with %d strength!\n",
           self->name, w->strength);
}

void mage_attack(Character* self) {
    Mage* m = (Mage*)self;

    if (m->mana < 10) {
        printf("%s is out of mana!\n", self->name);
        return;
    }

    m->mana -= 10;

    printf("%s casts fireball using %d mana!\n",
           self->name, m->mana);
}

void warrior_init(Warrior* w, const char* name, int health, int level, int strength) {
    character_init(&w->base, name, health, level);

    w->strength = strength;

    w->base.attack = warrior_attack;
}

void mage_init(Mage* m, const char* name, int health, int level, int mana) {
    character_init(&m->base, name, health, level);

    m->mana = mana;

    m->base.attack = mage_attack;
}

// =============================================================================
// MAIN FUNCTION
// =============================================================================

int main() {
    printf("=============================================================\n");
    printf("         OBJECT SIMULATOR: RPG Character System\n");
    printf("=============================================================\n");

    // Create a basic Character
    Character hero;
    character_init(&hero, "Hero", 100, 1);

    printf("\n--- Basic Character ---\n");
    hero.attack(&hero);
    hero.take_damage(&hero, 20);

    // Create a Warrior
    Warrior warrior;
    warrior_init(&warrior, "Thorin", 150, 5, 25);

    printf("\n--- Warrior ---\n");
    warrior.base.attack((Character*)&warrior);

    // Create a Mage
    Mage mage;
    mage_init(&mage, "Gandalf", 100, 5, 30);

    printf("\n--- Mage ---\n");
    mage.base.attack((Character*)&mage);
    mage.base.attack((Character*)&mage);
    mage.base.attack((Character*)&mage);
    mage.base.attack((Character*)&mage);

    // Demonstrate polymorphism
    printf("\n--- Polymorphism ---\n");

    Character* characters[3];

    characters[0] = &hero;
    characters[1] = (Character*)&warrior;
    characters[2] = (Character*)&mage;

    for (int i = 0; i < 3; i++) {
        characters[i]->attack(characters[i]);
    }

    printf("\n=============================================================\n");
    printf("Object simulation complete!\n");
    printf("=============================================================\n");

    return 0;
}