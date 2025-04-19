#include <iostream>
#include <string>
#include <vector>
using namespace std;
     
// Parcel structure
struct Parcel {
    int id;
    string recipient;
    string region = "Saudi Arabia";
    string city;
    string zone;
    string priority;
    string status;
    Parcel* next;
};

// Tree structure for region-city-district
struct TreeNode {
    string name;
    vector<TreeNode*> children;
    TreeNode(string n) : name(n) {}
};

// Parcel Queue
class ParcelQueue {
private:
    Parcel* front;
    Parcel* rear;
public:
    ParcelQueue() : front(nullptr), rear(nullptr) {}

    void enqueue(int id, string recipient, string city, string zone, string priority) {
        Parcel* newParcel = new Parcel{id, recipient, "Saudi Arabia", city, zone, priority, "Queued", nullptr};
        if (!rear) front = rear = newParcel;
        else {
            rear->next = newParcel;
            rear = newParcel;
        }
        cout << "\u2705 Parcel added to queue.\n";
    }

    Parcel* dequeue() {
        if (!front) return nullptr;
        Parcel* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        temp->status = "Reversed";
        return temp;
    }

    void display() {
        if (!front) {
            cout << "\U0001F4ED Queue is empty.\n";
            return;
        }
        Parcel* temp = front;
        while (temp) {
            cout << "\U0001F4E6 ID: " << temp->id << ", Priority: " << temp->priority
                 << ", City: " << temp->city << ", Zone: " << temp->zone
                 << ", Status: " << temp->status << "\n";
            temp = temp->next;
        }
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

// Stack for reversing
class ParcelStack {
private:
    Parcel* top;
public:
    ParcelStack() : top(nullptr) {}

    void push(Parcel* p) {
        p->next = top;
        top = p;
    }

    Parcel* pop() {
        if (!top) return nullptr;
        Parcel* temp = top;
        top = top->next;
        temp->status = "Sorted";
        return temp;
    }

    void display() {
        if (!top) {
            cout << "\U0001F4E6 Stack is empty.\n";
            return;
        }
        Parcel* temp = top;
        while (temp) {
            cout << "\U0001F501 Reversed Parcel - ID: " << temp->id << ", City: " << temp->city
                 << ", Zone: " << temp->zone << ", Priority: " << temp->priority << "\n";
            temp = temp->next;
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

// Sorted list with priority
class SortedParcels {
public:
    Parcel* head;
    SortedParcels() : head(nullptr) {}

    void insert(Parcel* p) {
        p->next = nullptr;
        if (!head || isHigherPriority(p, head)) {
            p->next = head;
            head = p;
        } else {
            Parcel* temp = head;
            while (temp->next && !isHigherPriority(p, temp->next)) {
                temp = temp->next;
            }
            p->next = temp->next;
            temp->next = p;
        }
    }

    bool isHigherPriority(Parcel* a, Parcel* b) {
        if (a->priority == b->priority)
            return a->id < b->id;
        return a->priority == "overnight";
    }

    void display() {
        if (!head) {
            cout << "\U0001F4E6 No sorted parcels.\n";
            return;
        }
        Parcel* temp = head;
        while (temp) {
            cout << "\u2705 Sorted - ID: " << temp->id << ", Priority: " << temp->priority
                 << ", City: " << temp->city << ", Zone: " << temp->zone
                 << ", Status: " << temp->status << "\n";
            temp = temp->next;
        }
    }

    void loadTruckByCity(const string& selectedCity, vector<Parcel*>& truck, vector<Parcel*>& delivered) {
        Parcel* curr = head;
        Parcel* prev = nullptr;

        while (curr) {
            if (curr->city == selectedCity) {
                Parcel* toDeliver = curr;
                if (prev) prev->next = curr->next;
                else head = curr->next;
                curr = curr->next;

                toDeliver->next = nullptr;
                toDeliver->status = "Delivered";
                truck.push_back(toDeliver);
                delivered.push_back(toDeliver);
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
};

// City/district data
vector<string> cities = {"Riyadh", "Jeddah", "Dammam", "Mecca", "Medina", "Abha"};
vector<vector<string>> districts = {
    {"Al Olaya", "Al Malaz", "Al Nakheel"},
    {"Al Balad", "Al Salamah", "Al Hamra"},
    {"Al Faisaliyah", "Al Shatea", "Al Badiyah"},
    {"Ajyad", "Al Aziziyah", "Al Misfalah"},
    {"Al Haram", "Al Awali", "Quba"},
    {"Khamis Mushait", "Al Nuzhah", "Al Rayyan"}
};

void displayTree(TreeNode* node, int depth = 0) {
    for (int i = 0; i < depth; ++i) cout << "  ";
    cout << "- " << node->name << "\n";
    for (TreeNode* child : node->children) {
        displayTree(child, depth + 1);
    }
}

void selectCityAndDistrict(string &selectedCity, string &selectedZone) {
    cout << "\n\U0001F4CD Select a City:\n";
    for (size_t i = 0; i < cities.size(); ++i)
        cout << i + 1 << ". " << cities[i] << "\n";
    int cityChoice;
    cin >> cityChoice;

    if (cityChoice < 1 || cityChoice > cities.size()) {
        cout << "\u274C Invalid city. Defaulting to Riyadh.\n";
        cityChoice = 1;
    }
    selectedCity = cities[cityChoice - 1];

    cout << "\n\U0001F3E0 Select a District in " << selectedCity << ":\n";
    for (size_t i = 0; i < districts[cityChoice - 1].size(); ++i)
        cout << i + 1 << ". " << districts[cityChoice - 1][i] << "\n";
    int districtChoice;
    cin >> districtChoice;

    if (districtChoice < 1 || districtChoice > districts[cityChoice - 1].size()) {
        cout << "\u274C Invalid district. Defaulting to first.\n";
        districtChoice = 1;
    }
    selectedZone = districts[cityChoice - 1][districtChoice - 1];
}

int main() {
    ParcelQueue queue;
    ParcelStack stack;
    SortedParcels sorted;
    vector<Parcel*> truck;
    vector<Parcel*> delivered;

    TreeNode* saudi = new TreeNode("Saudi Arabia");
    for (size_t i = 0; i < cities.size(); ++i) {
        TreeNode* city = new TreeNode(cities[i]);
        for (string d : districts[i]) {
            city->children.push_back(new TreeNode(d));
        }
        saudi->children.push_back(city);
    }

    int choice;
    do {
        cout << "\n\U0001F4E6=== Smart Parcel Sorting System ===\U0001F4E6\n";
        cout << "1. Add Parcel to Queue\n";
        cout << "2. Display Incoming Parcels\n";
        cout << "3. Process Batch (Reverse & Show)\n";
        cout << "4. Sort, Store & Display Parcels\n";
        cout << "5. Load Parcels into Truck\n";
        cout << "6. Display Delivered Parcels\n";
        cout << "7. Display Region-City-District Tree\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string recipient, priority, city, zone;
            cout << "Enter Parcel ID: "; cin >> id;
            cout << "Recipient Name: "; cin >> recipient;
            selectCityAndDistrict(city, zone);
            cout << "Priority (standard/overnight): "; cin >> priority;
            queue.enqueue(id, recipient, city, zone, priority);
        } else if (choice == 2) {
            queue.display();
        } else if (choice == 3) {
            while (!queue.isEmpty()) {
                Parcel* p = queue.dequeue();
                stack.push(p);
            }
            cout << "\u2705 Batch reversed.\n";
            stack.display();
        } else if (choice == 4) {
            while (!stack.isEmpty()) {
                Parcel* p = stack.pop();
                sorted.insert(p);
            }
            cout << "\u2705 Parcels sorted and stored:\n";
            sorted.display();
        } else if (choice == 5) {
            string selectedCity;
            cout << "Select city to load truck for:\n";
            for (size_t i = 0; i < cities.size(); ++i) cout << i + 1 << ". " << cities[i] << "\n";
            int cityIndex;
            cin >> cityIndex;
            if (cityIndex < 1 || cityIndex > cities.size()) {
                cout << "Invalid city. Aborting.\n";
                continue;
            }
            selectedCity = cities[cityIndex - 1];
            sorted.loadTruckByCity(selectedCity, truck, delivered);
            cout << "\U0001F69A Truck loaded for " << selectedCity << " and parcels delivered!\n";
        } else if (choice == 6) {
            if (delivered.empty()) cout << "No delivered parcels yet.\n";
            else {
                for (auto p : delivered) {
                    cout << "\U0001F4E6 Delivered - ID: " << p->id << ", City: " << p->city << ", Zone: " << p->zone << "\n";
                }
            }
        } else if (choice == 7) {
            displayTree(saudi);
        }

    } while (choice != 0);

    cout << "\U0001F44B Exiting. Have a great day!\n";
    return 0;
}
