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

        // Find item in inventory
        void find_item(string item) {
            for (int i = 0; i < items.size(); i++)
            if (items[i].first == item) {
                cout << items[i].first << ": "
                     << items[i].second << endl;
                return;
            }
            cout << "Item not found" << endl;
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

void loop_inv(inventory &inv) {
    // Print menu
    cout << "1. Add item" << endl
         << "2. Find item" << endl
         << "3. Remove item" << endl
         << "4. Print inventory" << endl
         << "5. Exit" << endl;

    // Get user input
    int choice;
    cin >> choice;

    // Perform action based on user input
    switch (choice) {
        case 1: {
            // Add item
            string item; int quantity;
            cout << "Enter item name: ";
            cin >> item;
            cout << "Enter quantity: ";
            cin >> quantity;
            inv.add_item(item, quantity);
            break;
        }
        case 2: {
            // Find item
            string item;
            cout << "Enter item name: ";
            cin >> item;
            inv.find_item(item);
            break;
        }
        case 3: {
            // Remove item
            string item; int quantity;
            cout << "Enter item name: ";
            cin >> item;
            cout << "Enter quantity: ";
            cin >> quantity;
            inv.remove_item(item, quantity);
            break;
        }
        case 4: {
            // List inventory
            inv.print_inventory();
            break;
        }
        case 5: {
            // Exit
            return;
        }
        default: {
            // Invalid choice
            cout << "Invalid choice" << endl;
            break;
        }
    }
    loop_inv(inv);
}

int main() {
    // Create inventory object
    inventory inv;
    loop_inv(inv);

    return 0;
}