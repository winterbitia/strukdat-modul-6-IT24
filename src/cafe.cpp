#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <stdexcept>

using namespace std;

/*
    CHECK LIST:
    [x] Class & objects
    [x] Attribute property & Method behavior
    [x] Constructor
    [x] Setter & Getter
    [x] Encapsulation & Data hiding
    [x] Inheritance - udah dibuat
    [x] Overriding - masih bingung tapi mungkin udah ke implementasi
    [+] Access Modifier / Visibility 
    [+] Abstraction
    [+] Polymorphism
*/

// Base class recipe
class Recipe {
public:
    string name;
    vector<pair<string, int> > ingredients;

    Recipe(string n, vector<pair<string, int> > ing)
        : name(n), ingredients(ing) {}

    virtual void update(vector<pair<string, int> > ing) {
        ingredients = ing;
    }

    vector<pair<string, int> > get_recipe() const {
        return ingredients;
    }
};

// Derived class special_recipe
class SpecialRecipe : public Recipe {
public:
    SpecialRecipe(string n, vector<pair<string, int> > ing)
        : Recipe(n, ing) {}

    void update(vector<pair<string, int> > ing) override {
        ingredients = ing;
        // Perform additional updates specific to special_recipe
    }
};

// Main inventory tracking class
class Inventory {
private:
    vector<Recipe*> recipes;
    ofstream log_file;

    void write_log(const string& message) {
        log_file.open("program_log.txt", ios::app);
        log_file << message << endl;
        log_file.close();
    }

    int find_recipe_index(string name) const {
        for (int i = 0; i < recipes.size(); ++i) {
            if (recipes[i]->name == name) {
                return i;
            }
        }
        return -1;
    }

public:
    Inventory() {
        log_file.open("program_log.txt", ios::trunc);
        log_file.close();
    }

    void create_recipe(string name, vector<pair<string, int> > ingredients) {
        if (find_recipe_index(name) != -1) {
            cout << "Recipe already exists" << endl;
            write_log("Failed to create recipe: " + name + " - Already exists");
            return;
        }
        recipes.push_back(new Recipe(name, ingredients));
        write_log("Created recipe: " + name);
    }

    void create_special_recipe(string name, vector<pair<string, int> > ingredients) {
        if (find_recipe_index(name) != -1) {
            cout << "Recipe already exists" << endl;
            write_log("Failed to create special recipe: " + name + " - Already exists");
            return;
        }
        recipes.push_back(new SpecialRecipe(name, ingredients));
        write_log("Created special recipe: " + name);
    }

    void update_recipe(string name, vector<pair<string, int> > ingredients) {
        int index = find_recipe_index(name);
        if (index != -1) {
            recipes[index]->update(ingredients);
            write_log("Updated recipe: " + name);
        } else {
            cout << "Recipe not found" << endl;
            write_log("Failed to update recipe: " + name + " - Not found");
        }
    }

    void delete_recipe(string name) {
        int index = find_recipe_index(name);
        if (index != -1) {
            delete recipes[index];
            recipes.erase(recipes.begin() + index);
            write_log("Deleted recipe: " + name);
        } else {
            cout << "Recipe not found" << endl;
            write_log("Failed to delete recipe: " + name + " - Not found");
        }
    }

    void use_recipe(string name) {
        int index = find_recipe_index(name);
        if (index != -1) {
            vector<pair<string, int> > recipe_ingredients = recipes[index]->get_recipe();
            cout << "Recipe " << name << " has been used" << endl;
            write_log("Used recipe: " + name);
        } else {
            cout << "Recipe not found" << endl;
            write_log("Failed to use recipe: " + name + " - Not found");
        }
    }

    void find_recipe(string name) const {
        int index = find_recipe_index(name);
        if (index != -1) {
            vector<pair<string, int> > recipe_ingredients = recipes[index]->get_recipe();
            cout << "\nRECIPE: " << name << endl;
            for (const auto& ingredient : recipe_ingredients) {
                cout << ingredient.first << ": " << ingredient.second << endl;
            }
        } else {
            cout << "Recipe not found" << endl;
        }
    }

    void list_recipes() const {
        cout << "\nRECIPES:" << endl;
        for (const auto& recipe : recipes) {
            cout << recipe->name << endl;
        }
        cout << endl;
    }
};

// Control function for recipe loop
void loop_recipe(Inventory& inv) {
    while (true) {
        cout << "RECIPE INVENTORY:" << endl;
        cout << "1. Add Recipe" << endl;
        cout << "2. Add Special Recipe" << endl;
        cout << "3. Update Recipe" << endl;
        cout << "4. Remove Recipe" << endl;
        cout << "5. Use Recipe" << endl;
        cout << "6. Find Recipe" << endl;
        cout << "7. List Recipes" << endl;
        cout << "8. Quit" << endl;
        cout << "> ";

        int input;
        cin >> input;

        // Clear input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (input < 1 || input > 8) {
            cout << "Invalid input" << endl;
            continue;
        }

        string name;
        int n;
        vector<pair<string, int> > ingredients;

        switch (input) {
        case 1:
            cout << "Enter recipe name: ";
            getline(cin, name);
            cout << "Enter number of ingredients: ";
            cin >> n;
            ingredients.resize(n);
            for (int i = 0; i < n; ++i) {
                cout << "Enter ingredient " << i + 1 << " name: ";
                cin >> ingredients[i].first;
                cout << "Enter ingredient " << i + 1 << " quantity: ";
                cin >> ingredients[i].second;
            }
            inv.create_recipe(name, ingredients);
            break;

        case 2:
            cout << "Enter recipe name: ";
            getline(cin, name);
            cout << "Enter number of ingredients: ";
            cin >> n;
            ingredients.resize(n);
            for (int i = 0; i < n; ++i) {
                cout << "Enter ingredient " << i + 1 << " name: ";
                cin >> ingredients[i].first;
                cout << "Enter ingredient " << i + 1 << " quantity: ";
                cin >> ingredients[i].second;
            }
            inv.create_special_recipe(name, ingredients);
            break;

        case 3:
            cout << "Enter recipe name: ";
            getline(cin, name);
            cout << "Enter number of ingredients: ";
            cin >> n;
            ingredients.resize(n);
            for (int i = 0; i < n; ++i) {
                cout << "Enter ingredient " << i + 1 << " name: ";
                cin >> ingredients[i].first;
                cout << "Enter ingredient " << i + 1 << " quantity: ";
                cin >> ingredients[i].second;
            }
            inv.update_recipe(name, ingredients);
            break;

        case 4:
            cout << "Enter recipe name: ";
            getline(cin, name);
            inv.delete_recipe(name);
            break;

        case 5:
            cout << "Enter recipe name: ";
            getline(cin, name);
            inv.use_recipe(name);
            break;

        case 6:
            cout << "Enter recipe name: ";
            getline(cin, name);
            inv.find_recipe(name);
            break;

        case 7:
            inv.list_recipes();
            break;

        case 8:
            return;
        }

        // Setelah operasi selesai, kembali ke menu utama
        cout << "\nPress Enter to continue...";
        cin.get();
    }
}

int main() {
    Inventory inv;
    loop_recipe(inv);
    return 0;
}


