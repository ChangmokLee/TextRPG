#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

class Character {
public:
    std::string name;
    int health;
    int attack;
    int defense;
    bool has_fire_spell;

    Character(std::string n, int h, int a, int d) : name(n), health(h), attack(a), defense(d), has_fire_spell(false) {}
};

void npc_interaction(Character& player) {
    std::cout << "\nYou encounter an old man who seems to have some useful information.\n";
    std::cout << "Old Man: Greetings, adventurer! I have heard about the Goblin terrorizing our village.\n";
    std::cout << "Old Man: It's said that the Goblin is weak to fire. Would you like to learn a fire spell? (yes/no)\n> ";
    std::string choice;
    std::cin >> choice;
    if (choice == "yes") {
        player.has_fire_spell = true;
        std::cout << "Old Man: Excellent! I have now taught you the fire spell. Use it wisely!\n";
    }
    else {
        std::cout << "Old Man: Very well. Good luck on your journey!\n";
    }
}

void npc_post_battle_interaction() {
    std::cout << "\nAs you return to the village, the old man greets you.\n";
    std::cout << "Old Man: Thank you for defeating the Goblin and saving our village, brave adventurer!\n";
}

int main() {
    std::cout << "Welcome to the Text RPG Adventure!\n";
    std::cout << "Enter your character's name: ";
    std::string name;
    std::cin >> name;

    Character player(name, 100, 10, 5);
    Character enemy("Goblin", 50, 7, 3);

    std::cout << "\nYou start your journey to save the village from the Goblin menace.\n";
    npc_interaction(player);

    std::cout << "\nAs you venture deeper into the forest, a wild " << enemy.name << " appears!\n";

    srand(time(0));
    while (player.health > 0 && enemy.health > 0) {
        std::cout << "\nChoose an action:\n";
        std::cout << "1. Attack\n2. Defend\n";
        if (player.has_fire_spell) {
            std::cout << "3. Use fire spell\n";
        }
        std::cout << "> ";
        int choice;
        std::cin >> choice;

        int playerDamage = rand() % (player.attack + 1);
        int enemyDamage = rand() % (enemy.attack + 1);

        if (choice == 1) {
            enemy.health -= playerDamage;
            std::cout << player.name << " dealt " << playerDamage << " damage to " << enemy.name << ".\n";
            if (enemy.health <= 0) {
                std::cout << "You have defeated the " << enemy.name << "!\n";
                npc_post_battle_interaction();
                break;
            }
            player.health -= enemyDamage;
            std::cout << enemy.name << " dealt " << enemyDamage << " damage to " << player.name << ".\n";
        }
        else if (choice == 2) {
            int reducedDamage = enemyDamage - player.defense;
            if (reducedDamage < 0) {
                reducedDamage = 0;
            }
            player.health -= reducedDamage;
            std::cout << player.name << " defended and received " << reducedDamage << " damage from " << enemy.name << ".\n";
        }
        else if (choice == 3 && player.has_fire_spell) {
            int fire_spell_damage = playerDamage + 5;
            enemy.health -= fire_spell_damage;
            std::cout << player.name << " used a fire spell and dealt " << fire_spell_damage << " damage to " << enemy.name << ".\n";
            if (enemy.health <= 0) {
                std::cout << "You have defeated the " << enemy.name << "!\n";
                npc_post_battle_interaction();
                break;
            }
            player.health -= enemyDamage;
            std::cout << enemy.name << " dealt " << enemyDamage << " damage to " << player.name << ".\n";
        }
        else {
            std::cout << "Invalid choice. Skipping turn.\n";
        }
    }

    return 0;
}