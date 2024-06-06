#include <iostream>
#include <vector>
using namespace std;

/*
    CHECK LIST:
    [x] Class & objects
    [x] Attribute property & Method behavior
    [x] Constructor
    [x] Setter & Getter
    [x] Encapsulation & Data hiding
    [-] Inheritance
    [-] Overriding
    [+] Access Modifier / Visibility
    [+] Abstraction
    [+] Polymorphism
*/

// Item object class
class item {
    private:
        // Item details are hidden
        int quantity;

    public:
        // Item name
        string name;

        // Item constructor
        item(string name, int quantity) {
            this->name = name;
            this->quantity = quantity;
        }

        // Item quantity setters
        void add(int q) {
            quantity += q;
        }
        void remove(int q) {
            quantity -= q;
        }

        // Item details getter
        int get_quantity() {
            return quantity;
        }
};


// Recipe object class
class recipe {
    private:
        // Recipe details are hidden
        vector<pair<string, int> > ingredients;

    public:
        // Recipe name
        string name;

        // Recipe constructor
        recipe(string name, vector<pair<string, int> > ingredients) {
            this->name = name;
            this->ingredients = ingredients;
        }

        // Recipe details setter
        void update(vector<pair<string, int> > ingredients) {
            this->ingredients = ingredients;
        }

        // Recipe details getter
        vector<pair<string, int> > get_recipe() {
            return ingredients;
        }
};

// Main inventory tracking class
class inventory {
    private:
        // Data abstraction for items and recipes
        vector<class::item> items;
        vector<class::recipe> recipes;

        // Control abstraction for index finding
        int find_item_index(string item) {
            for (int i = 0; i < items.size(); i++)
            if (items[i].name == item)
            return i;
            return -1;
        }
        int find_recipe_index(string recipe) {
            for (int i = 0; i < recipes.size(); i++)
            if (recipes[i].name == recipe)
            return i;
            return -1;
        }

    public:
        //===================//
        // INVENTORY METHODS //
        //===================//

        // Add item quantity to inventory
        void add_item(string name, int quantity) {
            // Check if item is already in inventory
            if (find_item_index(name) != -1){
                items[find_item_index(name)].add(quantity);
                return;
            }

            // If item is not found
            items.push_back(item(name, quantity)); // Push item object
        }

        // TODO: ADD A MULTI-ADD INPUT
        // Add multiple items to inventory
        void add_item(vector<pair<string, int> > input) {
            // Loop through input items
            for (int i = 0; i < input.size(); i++)
            // Check if item is already in inventory
            if (find_item_index(input[i].first) != -1)
                items[find_item_index(input[i].first)].add(input[i].second);
            else
                items.push_back(item(input[i].first, input[i].second)); // Push item object
        }

        // Check item from inventory
        bool check_item(string name, int quantity) {
            // Check if item is already in inventory
            if (find_item_index(name) != -1){
                if (items[find_item_index(name)].get_quantity() < quantity) 
                    return false;
                return true;
            }
            return false;
        }

        // TODO: ADD A MULTI-DELETE INPUT
        // Remove item from inventory
        void remove_item(string item, int quantity) {
            // Check if item is already in inventory
            if (find_item_index(item) != -1){
                if (items[find_item_index(item)].get_quantity() < quantity) {
                    cout << "Not enough quantity" << endl;
                    return;
                }
                if (items[find_item_index(item)].get_quantity() == quantity) {
                    items.erase(items.begin() + find_item_index(item));
                    return;
                }
                items[find_item_index(item)].remove(quantity);
                return;
            }
        }

        // Remove multiple items from inventory
        void remove_item(vector<pair<string, int> > items) {
            // Loop through input items
             for (int i = 0; i < items.size(); i++) {
            // Check if item is already in inventory
             if (find_item_index(items[i].first) != -1) {
                     if (items[find_item_index(items[i].first)].second < items[i].second) {
                             cout << "Not enough quantity" << endl;
                         return;
                     } else if (items[find_item_index(items[i].first)].second == items[i].second) {
                         items.erase(items.begin() + find_item_index(items[i].first));
                     } else {
                         items[find_item_index(items[i].first)].second -= items[i].second;
                     }
                }
             }
        }

        // Show item from inventory
        void show_item(string item) {
            // Check if item is already in inventory
            if (find_item_index(item) != -1){
                cout << "\nITEM: " << item << endl
                     << "Quantity: " << items[find_item_index(item)].get_quantity() << endl;
                return;
            }

            // If item is not found
            cout << "Item not found" << endl;
        }

        // List items from inventory
        void print_items() {
            // Loop through items vector
            cout << "\nINVENTORY:" << endl;
            for (int i = 0; i < items.size(); i++)
                cout << items[i].name << ": "
                     << items[i].get_quantity() << endl;
            cout << endl;
        }

        //================//
        // RECIPE METHODS //
        //================//

        // Create recipe
        void create_recipe(string name, vector<pair<string, int> > ingredients) {
            // Check if recipe is in inventory
            if (find_recipe_index(name) != -1){
                cout << "Recipe already exists" << endl;
                return;
            }

            // If recipe is not found
            recipes.push_back(recipe(name, ingredients)); // Push recipe object
        }

        // Check recipe
        bool check_recipe(string name) {
            // Check if recipe is in inventory
            if (find_recipe_index(name) != -1)
                return true;
            return false;
        }

        // Update recipe
        void update_recipe(string name, vector<pair<string, int> > ingredients) {
            // Check if recipe is in inventory
            if (find_recipe_index(name) != -1){
                recipes[find_recipe_index(name)].update(ingredients);
                return;
            }

            // If recipe is not found
            cout << "Recipe not found" << endl;
        }

        // Remove recipe
        void remove_recipe(string name) {
            // Check if recipe is in inventory
            if (find_recipe_index(name) != -1){
                recipes.erase(recipes.begin() + find_recipe_index(name));
                return;
            }

            // If recipe is not found
            cout << "Recipe not found" << endl;
        }

        // Show recipe
        void show_recipe(string name) {
            // Check if recipe is in inventory
            if (find_recipe_index(name) != -1){
                cout << "\nRECIPE: " << name << endl;
                vector<pair<string, int> > ingredients = recipes[find_recipe_index(name)].get_recipe();
                
                // Loop through ingredients vector
                for (int i = 0; i < ingredients.size(); i++)
                cout << ingredients[i].first << ": "
                     << ingredients[i].second << endl;
                cout << endl;
                return;
            }

            // If recipe is not found
            cout << "Recipe not found" << endl;
        }

        // Use recipe
        void use_recipe(string name) {
            // Check if recipe is in inventory
            if (find_recipe_index(name) != -1){
                vector<pair<string, int> > ingredients = recipes[find_recipe_index(name)].get_recipe();
                
                // Check if enough ingredients are available
                for (int i = 0; i < ingredients.size(); i++)
                if (!check_item(ingredients[i].first, ingredients[i].second)){
                    cout << "Not enough ingredients" << endl;
                    return;
                }

                // If enough ingredients are available
                for (int i = 0; i < ingredients.size(); i++)
                    remove_item(ingredients[i].first, ingredients[i].second);
                cout << "Recipe " << name << " used" << endl;
                return;
            }

            // If recipe is not found
            cout << "Recipe not found" << endl;
        }

};

void loop_inv(inventory &inv) {
    // Print menu
    cout << "\nINVENTORY DASHBOARD" << endl
         << "1. Add item" << endl
         << "2. Multi-add item" << endl
         << "3. Remove item" << endl
         << "4. Multi-remove item" << endl
         << "5. Find item" << endl
         << "6. List inventory" << endl
         << "0. Exit" << endl;

    // Get user input
    cout << "> ";
    int choice;
    cin >> choice;
    cout << endl;

    // Perform action based on user input
    switch (choice) {
        case 1: {
            // Add item
            string item; int quantity;
            cout << "[!] Enter item name & quanity" << endl
                 << "  Syntax: <item_name> <quantity>" << endl
                 << "> ";
            cin >> item >> quantity;
            inv.add_item(item, quantity);
            break;
        }
        case 2: {
            // Multi-add item
            string item; int quantity;
            cout << "[!] Enter item name & quanity" << endl
                 << "  Syntax: <item_name> <quantity>" << endl
                 << "  Enter 'exit' to stop" << endl
                 << "Example: " << endl
                 << "  sugar 50" << endl
                 << "  exit" << endl;

            // Creates vector for items
            vector<pair<string, int> > items;
            while(1) {
                // Loops until user enters 'exit'
                cout << "> ";
                cin >> item;
                if (item == "exit") break;
                cin >> quantity;

                // Pushes item to vector
                items.push_back(make_pair(item, quantity));
            }

            // Adds items to inventory
            inv.add_item(items);
            break;
        }
        case 3: {
            // Remove item
            string item; int quantity;
            cout << "[!] Enter item name & quanity" << endl
                 << "  Syntax: <item_name> <quantity>" << endl
                 << "> ";
            cin >> item >> quantity;
            inv.remove_item(item, quantity);
            break;
        }
        case 4: {
            // Multi-remove item
            string item; int quantity;

            // Instructions for user
            cout << "[!] Enter item name & quanity" << endl
                 << "  Syntax: <item_name> <quantity>" << endl
                 << "  Enter 'exit' to stop" << endl
                 << "Example: " << endl
                 << "  sugar 50" << endl
                 << "  exit" << endl;

            // Creates vector for items
            vector<pair<string, int> > items;
            while (1) {
                // Loops until user enters 'exit'
                cout << "> ";
                cin >> item;
                if (item == "exit") break;
                cin >> quantity;

                // Pushes item to vector
                items.push_back(make_pair(item, quantity));
            }

            // Removes items from inventory
            inv.remove_item(items);
            break;
        }
        case 5: {
            // Find item
            string item;
            cout << "[!] Enter item name" << endl
                 << "> ";
            cin >> item;
            inv.show_item(item);
            break;
        }
        case 6: {
            // List inventory
            inv.print_items();
            break;
        }
        case 0: {
            // Exit
            return;
        }
        default: {
            // Invalid choice
            cout << "Invalid choice" << endl;
            loop_inv(inv);
        }
    }
    loop_inv(inv);
}

void loop_recipe(inventory &inv) {
    // Print menu
    cout << "\nRECIPE DASHBOARD" << endl
         << "1. Create recipe" << endl
         << "2. Update recipe" << endl
         << "3. Search recipe" << endl
         << "4. Remove recipe" << endl
         << "5. Use recipe" << endl
         << "6. List inventory" << endl
         << "0. Exit" << endl;

    // Get user input
    cout << "> ";
    int choice;
    cin >> choice;
    cout << endl;

    // Perform action based on user input
    switch (choice) {
        case 1: {
            // Create recipe
            string name, item; int quantity;
            cout << "[!] Enter recipe name" << endl
                 << "> ";
            cin >> name;

            // Instructions for users
            cout << "[!] Enter item name & quantity" << endl
                 << "  Syntax: <item_name> <quantity>" << endl
                 << "  Enter 'exit' to stop" << endl
                 << "Example: " << endl
                 << "  sugar 50" << endl
                 << "  exit" << endl;

            // Creates vector for ingredients
            vector<pair<string, int> > ingredients;
            while (1) {
                // Loops until user enters 'exit'
                cout << "> ";
                cin >> item;
                if (item == "exit") break;
                cin >> quantity;

                // Pushes item to vector
                ingredients.push_back(make_pair(item, quantity));
            }

            // Creates recipe
            inv.create_recipe(name, ingredients);
            break;
        }
        case 2: {
            // Update recipe
            string name, item; int quantity;
            cout << "[!] Enter recipe name" << endl
                 << "> ";
            cin >> name;

            // Check if recipe exists
            if (!inv.check_recipe(name)) {
                cout << "Recipe not found" << endl;
                break;
            }

            // Instructions for users
            cout << "[!] Enter item name & quantity" << endl
                 << "  Syntax: <item_name> <quantity>" << endl
                 << "  Enter 'exit' to stop" << endl
                 << "Example: " << endl
                 << "  sugar 50" << endl
                 << "  exit" << endl;

            // Creates vector for ingredients
            vector<pair<string, int> > ingredients;
            while (1) {
                // Loops until user enters 'exit'
                cout << "> ";
                cin >> item;
                if (item == "exit") break;
                cin >> quantity;

                // Pushes item to vector
                ingredients.push_back(make_pair(item, quantity));
            }

            // Updates recipe
            inv.update_recipe(name, ingredients);
            break;
        }
        case 3: {
            // Find recipe
            string name;
            cout << "[!] Enter recipe name" << endl
                 << "> ";
            cin >> name;
            inv.show_recipe(name);
            break;
        }
        case 4: {
            // Remove recipe
            string name;
            cout << "[!] Enter recipe name" << endl
                 << "> ";
            cin >> name;
            inv.remove_recipe(name);
            break;
        }
        case 5: {
            // Use recipe
            string name;
            cout << "[!] Enter recipe name" << endl
                 << "> ";
            cin >> name;
            inv.use_recipe(name);
            break;
        }
        case 6: {
            // List inventory
            inv.print_items();
            break;
        }
        case 0: {
            // Exit
            return;
        }
        default: {
            // Invalid choice
            cout << "Invalid choice" << endl;
            loop_recipe(inv);
        }
    }
    loop_recipe(inv);
}

void loop_branch(inventory &inv) {
    // Print menu
    cout << "\nMAIN DASHBOARD" << endl
         << "1. Inventory" << endl
         << "2. Recipe" << endl
         << "0. Exit" << endl;

    // Get user input
    cout << "> ";
    int choice;
    cin >> choice;
    cout << endl;

    // Perform action based on user input
    switch (choice) {
        case 1: {
            // Inventory
            loop_inv(inv);
            break;
        }
        case 2: {
            // Recipe
            loop_recipe(inv);
            break;
        }
        case 0: {
            // Exit
            return;
        }
        default: {
            // Invalid choice
            cout << "Invalid choice" << endl;
            loop_branch(inv);
        }
    }
    loop_branch(inv);
}

int main() {
    // Create inventory object
    inventory inv;
    loop_branch(inv);

    return 0;
}