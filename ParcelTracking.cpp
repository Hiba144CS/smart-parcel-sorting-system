#include <iostream>
#include <string>
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

// Tree Node structure
struct TreeNode {
    string name;
    TreeNode* firstChild;
    TreeNode* nextSibling;
    TreeNode(string n) : name(n), firstChild(nullptr), nextSibling(nullptr) {}
};

// Parcel Queue
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

// Stack for reversing
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

// Sorted list with priority
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
