#include <iostream>
#include <vector>
using namespace std;

// Class to keep track of items in stock
class inventory {
    private:
        // Pair of item name and quantity
        vector<pair<string, int>> items;
    public:
        // Add item quantity to inventory
        void add_item(string item, int quantity) {
            // Loop through items vector
            for (int i = 0; i < items.size(); i++)
            if (items[i].first == item) { // If item is found
                // Add quantity to item
                items[i].second += quantity;
                break;
            }

            // If item is not found
            items.push_back(make_pair(item, quantity)); // Push pair
        }

        // Remove item from inventory
        void remove_item(string item, int quantity) {
            // Loop through items vector
            for (int i = 0; i < items.size(); i++)
            if (items[i].first == item) { // If item is found
                // Subtract quantity from item
                items[i].second -= quantity;
                // Delete item if quantity is 0
                if (items[i].second <= 0)
                items.erase(items.begin() + i);
                break;
            }
        }

        // List items in inventory
        void print_inventory() {
            // Loop through items vector
            cout << "Inventory:" << endl;
            for (int i = 0; i < items.size(); i++)
            cout << items[i].first << ": "
                 << items[i].second << endl;
            cout << endl;
        }
};

void inputloop(inventory &inv) {
    // Print menu
    cout << "1. Add item" << endl;
    cout << "2. Remove item" << endl;
    cout << "3. List inventory" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter choice: ";

    // Get user input
    int choice;
    cin >> choice;

    // Perform action based on choice
    switch (choice) {
        case 1: {
            // Add item
            cout << "Enter item name: ";
            string item;
            cin >> item;
            cout << "Enter quantity: ";
            int quantity;
            cin >> quantity;
            inv.add_item(item, quantity);
            break;
        }
        case 2: {
            // Remove item
            cout << "Enter item name: ";
            string item;
            cin >> item;
            cout << "Enter quantity: ";
            int quantity;
            cin >> quantity;
            inv.remove_item(item, quantity);
            break;
        }
        case 3: {
            // List inventory
            inv.print_inventory();
            break;
        }
        case 4: {
            // Exit
            return;
        }
        default: {
            // Invalid choice
            cout << "Invalid choice" << endl;
            break;
        }
    }
    inputloop(inv);
}

int main() {
    // Create inventory object
    inventory inv;
    inputloop(inv);

    return 0;
}