#include <iostream>
#include <string>
using namespace std;

//parcel structure
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

//tree node structure
struct TreeNode {
    string name;
    TreeNode* firstChild;
    TreeNode* nextSibling;
    TreeNode(string n) {
        name = n;
        firstChild = nullptr;
        nextSibling = nullptr;
    }
};

//parcel queue
class ParcelQueue {
private:
    Parcel* front;
    Parcel* rear;
public:
    ParcelQueue() {
        front = rear= nullptr;}

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

//stack for reversing
class ParcelStack {
private:
    Parcel* top;
public:
    ParcelStack() {top = nullptr;}

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

//sorted list with priority
class SortedParcels {
public:
    Parcel* head;
    SortedParcels(){head = nullptr;}

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

    void loadTruckByCity(const string& selectedCity, Parcel*& truckHead, Parcel*& deliveredHead) {
        Parcel* curr = head;
        Parcel* prev = nullptr;

        while (curr) {
            if (curr->city == selectedCity) {
                Parcel* toDeliver = curr;
                if (prev) prev->next = curr->next;
                else head = curr->next;
                curr = curr->next;

                toDeliver->next = truckHead;
                truckHead = toDeliver;
                toDeliver->status = "Delivered";

                // Add to delivered list
                Parcel* d = new Parcel(*toDeliver);
                d->next = deliveredHead;
                deliveredHead = d;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
};

//manual city/district arrays
const int NUM_CITIES = 6;
string cityList[NUM_CITIES] = {"Riyadh", "Jeddah", "Dammam", "Mecca", "Medina", "Abha"};
string districtList[NUM_CITIES][3] = {
    {"Al Olaya", "Al Malaz", "Al Nakheel"},
    {"Al Balad", "Al Salamah", "Al Hamra"},
    {"Al Faisaliyah", "Al Shatea", "Al Badiyah"},
    {"Ajyad", "Al Aziziyah", "Al Misfalah"},
    {"Al Haram", "Al Awali", "Quba"},
    {"Khamis Mushait", "Al Nuzhah", "Al Rayyan"}
};

//tree display function
void displayTree(TreeNode* node, int depth = 0) {
    for (int i = 0; i < depth; ++i) cout << "  ";
    cout << "- " << node->name << "\n";

    TreeNode* child = node->firstChild;
    while (child) {
        displayTree(child, depth + 1);
        child = child->nextSibling;
    }
}

//city,district selection function
void selectCityAndDistrict(string &selectedCity, string &selectedZone) {
    cout << "\n\U0001F4CD Select a City:\n";
    for (int i = 0; i < NUM_CITIES; ++i)
        cout << i + 1 << ". " << cityList[i] << "\n";
    int cityChoice;
    cin >> cityChoice;

    if (cityChoice < 1 || cityChoice > NUM_CITIES) {
        cout << "\u274C Invalid city. Defaulting to Riyadh.\n";
        cityChoice = 1;
    }
    selectedCity = cityList[cityChoice - 1];

    cout << "\n\U0001F3E0 Select a District in " << selectedCity << ":\n";
    for (int i = 0; i < 3; ++i)
        cout << i + 1 << ". " << districtList[cityChoice - 1][i] << "\n";
    int districtChoice;
    cin >> districtChoice;

    if (districtChoice < 1 || districtChoice > 3) {
        cout << "\u274C Invalid district. Defaulting to first.\n";
        districtChoice = 1;
    }
    selectedZone = districtList[cityChoice - 1][districtChoice - 1];
}

int main() {
    ParcelQueue queue;
    ParcelStack stack;
    SortedParcels sorted;
    Parcel* truckHead = nullptr;
    Parcel* deliveredHead = nullptr;

    //build tree
    TreeNode* saudi = new TreeNode("Saudi Arabia");
    TreeNode* lastCity = nullptr;
    for (int i = 0; i < NUM_CITIES; ++i) {
        TreeNode* city = new TreeNode(cityList[i]);
        TreeNode* lastDistrict = nullptr;
        for (int j = 0; j < 3; ++j) {
            TreeNode* district = new TreeNode(districtList[i][j]);
            if (!city->firstChild) city->firstChild = district;
            else lastDistrict->nextSibling = district;
            lastDistrict = district;
        }
        if (!saudi->firstChild) saudi->firstChild = city;
        else lastCity->nextSibling = city;
        lastCity = city;
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
            for (int i = 0; i < NUM_CITIES; ++i) cout << i + 1 << ". " << cityList[i] << "\n";
            int cityIndex;
            cin >> cityIndex;
            if (cityIndex < 1 || cityIndex > NUM_CITIES) {
                cout << "Invalid city. Aborting.\n";
                continue;
            }
            selectedCity = cityList[cityIndex - 1];
            sorted.loadTruckByCity(selectedCity, truckHead, deliveredHead);
            cout << "\U0001F69A Truck loaded for " << selectedCity << " and parcels delivered!\n";
        } else if (choice == 6) {
            if (!deliveredHead) cout << "No delivered parcels yet.\n";
            else {
                Parcel* temp = deliveredHead;
                while (temp) {
                    cout << "\U0001F4E6 Delivered - ID: " << temp->id << ", City: " << temp->city << ", Zone: " << temp->zone << "\n";
                    temp = temp->next;
                }
            }
        } else if (choice == 7) {
            displayTree(saudi);
        }

    } while (choice != 0);

    cout << "\U0001F44B Exiting. Have a great day!\n";
    return 0;
}
