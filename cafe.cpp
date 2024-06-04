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

int main() {
    // Create inventory object
    inventory inv;

    // Add items to inventory
    inv.add_item("Coffee", 10);
    inv.add_item("Milk", 5);

    // Print inventory example 1
    inv.print_inventory();

    // Remove items from inventory
    inv.remove_item("Coffee", 5);
    inv.remove_item("Milk", 5);

    // Print inventory example 2
    inv.print_inventory();
    return 0;
}