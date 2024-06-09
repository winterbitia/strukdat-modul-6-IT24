#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

// Item object class
class Item {
private:
    int quantity;

public:
    string name;

    Item(string name, int quantity) {
        this->name = name;
        this->quantity = quantity;
    }

    void add(int q) {
        quantity += q;
    }

    void remove(int q) {
        quantity -= q;
    }

    int get_quantity() {
        return quantity;
    }
};

// Recipe object class
class Recipe {
private:
    vector<pair<string, int>> ingredients;

public:
    string name;

    Recipe(string name, vector<pair<string, int>> ingredients) {
        this->name = name;
        this->ingredients = ingredients;
    }

    void update(vector<pair<string, int>> ingredients) {
        this->ingredients = ingredients;
    }

    vector<pair<string, int>> get_recipe() {
        return ingredients;
    }

    virtual void show_recipe() {
        cout << "\nRECIPE: " << name << endl;
        for (auto& ingredient : ingredients) {
            cout << ingredient.first << ": " << ingredient.second << endl;
        }
    }
};

// SpecialRecipe object class inheriting from Recipe
class SpecialRecipe : public Recipe {
public:
    SpecialRecipe(string name, vector<pair<string, int>> ingredients)
        : Recipe(name, ingredients) {}

    void show_recipe() override {
        cout << "\nSPECIAL RECIPE: " << name << endl;
        for (auto& ingredient : get_recipe()) {
            cout << ingredient.first << ": " << ingredient.second << " (Special)" << endl;
        }
    }
};

// Function to log activities
void log_activity(const string& activity) {
    ofstream log_file("activity.log", ios_base::app);
    time_t now = time(0);
    char* dt = ctime(&now);
    log_file << dt << ": " << activity << endl;
    log_file.close();
}

// Main inventory tracking class
class Inventory {
private:
    vector<Item> items;
    vector<Recipe*> recipes;

    int find_item_index(string item) {
        for (int i = 0; i < items.size(); i++)
            if (items[i].name == item)
                return i;
        return -1;
    }

    int find_recipe_index(string recipe) {
        for (int i = 0; i < recipes.size(); i++)
            if (recipes[i]->name == recipe)
                return i;
        return -1;
    }

public:
    void add_item(string name, int quantity) {
        if (find_item_index(name) != -1) {
            items[find_item_index(name)].add(quantity);
            log_activity("Added " + to_string(quantity) + " of " + name);
            return;
        }

        items.push_back(Item(name, quantity));
        log_activity("Added new item " + name + " with quantity " + to_string(quantity));
    }

    void add_item(vector<pair<string, int>> input) {
        for (int i = 0; i < input.size(); i++) {
            if (find_item_index(input[i].first) != -1)
                items[find_item_index(input[i].first)].add(input[i].second);
            else
                items.push_back(Item(input[i].first, input[i].second));
        }

        log_activity("Added multiple items to inventory");
    }

    bool check_item(string name, int quantity) {
        if (find_item_index(name) != -1) {
            if (items[find_item_index(name)].get_quantity() < quantity)
                return false;
            return true;
        }
        return false;
    }

    void remove_item(string item, int quantity) {
        if (find_item_index(item) != -1) {
            if (items[find_item_index(item)].get_quantity() < quantity) {
                cout << "Not enough quantity" << endl;
                log_activity("Failed to remove " + to_string(quantity) + " of " + item + ": Not enough quantity");
                return;
            }
            if (items[find_item_index(item)].get_quantity() == quantity) {
                items.erase(items.begin() + find_item_index(item));
                log_activity("Removed all of " + item);
                return;
            }
            items[find_item_index(item)].remove(quantity);
            log_activity("Removed " + to_string(quantity) + " of " + item);
            return;
        }
    }

    void remove_item(vector<pair<string, int>> items) {
        for (int i = 0; i < items.size(); i++) {
            if (find_item_index(items[i].first) != -1) {
                if (this->items[find_item_index(items[i].first)].get_quantity() < items[i].second) {
                    cout << "Not enough quantity" << endl;
                    log_activity("Failed to remove multiple items: Not enough quantity");
                    return;
                } else if (this->items[find_item_index(items[i].first)].get_quantity() == items[i].second) {
                    this->items.erase(this->items.begin() + find_item_index(items[i].first));
                } else {
                    this->items[find_item_index(items[i].first)].remove(items[i].second);
                }
            }
        }
        log_activity("Removed multiple items from inventory");
    }

    void show_item(string item) {
        if (find_item_index(item) != -1) {
            cout << "\nITEM: " << item << endl
                << "Quantity: " << items[find_item_index(item)].get_quantity() << endl;
            log_activity("Displayed item " + item);
            return;
        }

        cout << "Item not found" << endl;
        log_activity("Failed to display item " + item + ": Item not found");
    }

    void print_items() {
        cout << "\nINVENTORY:" << endl;
        for (int i = 0; i < items.size(); i++)
            cout << items[i].name << ": "
            << items[i].get_quantity() << endl;
        cout << endl;
        log_activity("Displayed all items in inventory");
    }

    void create_recipe(string name, vector<pair<string, int>> ingredients) {
        if (find_recipe_index(name) != -1) {
            cout << "Recipe already exists" << endl;
            log_activity("Failed to create recipe " + name + ": Recipe already exists");
            return;
        }

        recipes.push_back(new Recipe(name, ingredients));
        log_activity("Created recipe " + name);
    }

    void create_special_recipe(string name, vector<pair<string, int>> ingredients) {
        if (find_recipe_index(name) != -1) {
            cout << "Recipe already exists" << endl;
            log_activity("Failed to create special recipe " + name + ": Recipe already exists");
            return;
        }

        recipes.push_back(new SpecialRecipe(name, ingredients));
        log_activity("Created special recipe " + name);
    }

    bool check_recipe(string name) {
        if (find_recipe_index(name) != -1) return true;
        return false;
    }

    void update_recipe(string name, vector<pair<string, int>> ingredients) {
        if (find_recipe_index(name) != -1) {
            recipes[find_recipe_index(name)]->update(ingredients);
            log_activity("Updated recipe " + name);
            return;
        }

        cout << "Recipe not found" << endl;
        log_activity("Failed to update recipe " + name + ": Recipe not found");
    }

    void remove_recipe(string name) {
        if (find_recipe_index(name) != -1) {
            recipes.erase(recipes.begin() + find_recipe_index(name));
            log_activity("Removed recipe " + name);
            return;
        }

        cout << "Recipe not found" << endl;
        log_activity("Failed to remove recipe " + name + ": Recipe not found");
    }

    void show_recipe(string name) {
        if (find_recipe_index(name) != -1) {
            recipes[find_recipe_index(name)]->show_recipe();
            log_activity("Displayed recipe " + name);
            return;
        }

        cout << "Recipe not found" << endl;
        log_activity("Failed to display recipe " + name + ": Recipe not found");
    }

    void print_recipes() {
        cout << "\nRECIPES:" << endl;
        for (int i = 0; i < recipes.size(); i++)
            recipes[i]->show_recipe();
        cout << endl;
        log_activity("Displayed all recipes");
    }
};

// Interactive Menu
void display_menu_item() {
    cout << "\nITEM DASHBOARD"
        << "\n1. Add Item"
        << "\n2. Multi-Add Item"
        << "\n3. Remove Item"
        << "\n4. Multi-Remove Item"
        << "\n5. Find Item"
        << "\n6. Print Items"
        << "\n0. Exit" << endl;
}

void display_menu_recipe() {
    cout << "\nRECIPE DASHBOARD"
        << "\n1. Create Recipe"
        << "\n2. Create Special Recipe"
        << "\n3. Update Recipe"
        << "\n4. Remove Recipe"
        << "\n5. Find Recipe"
        << "\n6. Print Recipes"
        << "\n0. Exit" << endl;
}

void display_menu() {
    cout << "\nCAFE MANAGEMENT SYSTEM"
        << "\n1. Item Dashboard"
        << "\n2. Recipe Dashboard"
        << "\n0. Exit" << endl;
}

void loop_item(Inventory& tracker) {
    int choice;
    string item;
    int quantity;
    vector<pair<string, int>> items;

    display_menu_item();

    cout << "> ";
    cin >> choice;
    cout << endl;

    switch (choice) {
    case 1: {
        // Add item
        cout << "[!] Enter item name & quanity" << endl
                << "  Syntax: <item> <quantity>" << endl
                << "> ";
        cin >> item >> quantity;
        tracker.add_item(item, quantity);
        break;
    }
    case 2:
        // Multi-Add item
        cout << "[!] Enter item name & quanity" << endl
                << "  Syntax: <item> <quantity>" << endl
                << "  Enter 'exit' to stop" << endl
                << "Example: " << endl
                << "  sugar 50" << endl
                << "  exit" << endl;

        // Creates vector for items
        while(1) {
            // Loops until user enters 'exit'
            cout << "> ";
            cin >> item;
            if (item == "exit") break;
            cin >> quantity;

            // Pushes item to vector
            items.push_back(make_pair(item, quantity));
        }
        tracker.add_item(items);
        break;

    case 3:
        // Remove item
        cout << "[!] Enter item name & quanity" << endl
                << "  Syntax: <item> <quantity>" << endl
                << "> ";
        cin >> item >> quantity;
        tracker.remove_item(item, quantity);
        break;

    case 4:
        // Multi-Remove item
        cout << "[!] Enter item name & quanity" << endl
                << "  Syntax: <item> <quantity>" << endl
                << "  Enter 'exit' to stop" << endl
                << "Example: " << endl
                << "  sugar 50" << endl
                << "  exit" << endl;

        // Creates vector for items
        while(1) {
            // Loops until user enters 'exit'
            cout << "> ";
            cin >> item;
            if (item == "exit") break;
            cin >> quantity;

            // Pushes item to vector
            items.push_back(make_pair(item, quantity));
        }
        tracker.remove_item(items);
        break;

    case 5:
        cout << "[!] Enter item name" << endl
                << "> ";
        cin >> item;
        tracker.show_item(item);
        break;

    case 6:
        tracker.print_items();
        break;

    case 0:
        cout << "Exiting..." << endl;
        return;

    default:
        cout << "Invalid choice. Please try again." << endl;
    }
    loop_item(tracker);
}

void loop_recipe(Inventory& tracker) {
    int choice;
    string name, item;
    int quantity;
    vector<pair<string, int>> ingredients;

    display_menu_recipe();

    cout << "> ";
    cin >> choice;
    cout << endl;

    switch (choice) {
    case 1:
        cout << "[!] Enter recipe name" << endl
                << "> ";
        cin >> name;

        cout << "[!] Enter ingredient & quantity" << endl
                << "  Syntax: <item> <quantity>" << endl
                << "  Enter 'exit' to stop" << endl
                << "Example: " << endl
                << "  sugar 50" << endl
                << "  exit" << endl;

        // Creates vector for ingredients
        while(1) {
            // Loops until user enters 'exit'
            cout << "> ";
            cin >> item;
            if (item == "exit") break;
            cin >> quantity;

            // Pushes item to vector
            ingredients.push_back(make_pair(item, quantity));
        }
        tracker.create_recipe(name, ingredients);
        break;

    case 2:
        cout << "[!] Enter special recipe name" << endl
                << "> ";
        cin >> name;

        cout << "[!] Enter ingredient & quantity" << endl
                << "  Syntax: <item> <quantity>" << endl
                << "  Enter 'exit' to stop" << endl
                << "Example: " << endl
                << "  sugar 50" << endl
                << "  exit" << endl;

        // Creates vector for ingredients
        while(1) {
            // Loops until user enters 'exit'
            cout << "> ";
            cin >> item;
            if (item == "exit") break;
            cin >> quantity;

            // Pushes item to vector
            ingredients.push_back(make_pair(item, quantity));
        }
        tracker.create_special_recipe(name, ingredients);
        break;

    case 3:
        cout << "[!] Enter recipe name" << endl
                << "> ";
        cin >> name;

        if (!tracker.check_recipe(name)) {
            cout << "Recipe not found" << endl;
            break;
        }

        cout << "[!] Enter ingredient & quantity" << endl
                << "  Syntax: <item> <quantity>" << endl
                << "  Enter 'exit' to stop" << endl
                << "Example: " << endl
                << "  sugar 50" << endl
                << "  exit" << endl;
        
        // Creates vector for ingredients
        while(1) {
            // Loops until user enters 'exit'
            cout << "> ";
            cin >> item;
            if (item == "exit") break;
            cin >> quantity;

            // Pushes item to vector
            ingredients.push_back(make_pair(item, quantity));
        }
        tracker.update_recipe(name, ingredients);

    case 4:
        cout << "[!] Enter recipe name" << endl
                << "> ";
        cin >> name;
        tracker.remove_recipe(name);
        break;

    case 5:
        cout << "[!] Enter recipe name" << endl
                << "> ";
        cin >> name;
        tracker.show_recipe(name);
        break;

    case 6:
        tracker.print_recipes();
        break;

    case 0:
        cout << "Exiting..." << endl;
        return;

    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }

    loop_recipe(tracker);
}

void loop_main(Inventory& tracker) {
    int choice;

    display_menu();

    cout << "> ";
    cin >> choice;
    cout << endl;

    switch (choice) {
    case 1:
        loop_item(tracker);
        break;

    case 2:
        loop_recipe(tracker);
        break;

    case 0:
        cout << "Exiting..." << endl;
        return;

    default:
        cout << "Invalid choice. Please try again." << endl;
    }

    loop_main(tracker);
}

int main() {
    Inventory tracker;
    int choice;

    loop_main(tracker);

    return 0;
}
