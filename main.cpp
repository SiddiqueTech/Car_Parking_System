#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <ctime>
#include <sstream>
#include <stdexcept>
using namespace std;

template<typename T>
class ArrayList {
private:
    T* data;
    int capacity;
    int size;
    
    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for(int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
    
public:
    ArrayList(int initialCapacity = 10) {
        capacity = initialCapacity;
        size = 0;
        data = new T[capacity];
    }

    ArrayList(const ArrayList& other) {
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for(int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    ~ArrayList() {
        delete[] data;
    }

    void add(const T& element) {
        if(size == capacity) {
            resize(capacity * 2);
        }
        data[size++] = element;
    }

    void add(int index, const T& element) {
        if(index < 0 || index > size) {
            throw out_of_range("Index out of bounds");
        }
        
        if(size == capacity) {
            resize(capacity * 2);
        }

        for(int i = size; i > index; i--) {
            data[i] = data[i-1];
        }
        
        data[index] = element;
        size++;
    }

    T get(int index) const {
        if(index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }

    void set(int index, const T& element) {
        if(index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        data[index] = element;
    }

    T remove(int index) {
        if(index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        
        T removedElement = data[index];

        for(int i = index; i < size - 1; i++) {
            data[i] = data[i+1];
        }
        
        size--;

        if(size > 0 && size == capacity / 4) {
            resize(capacity / 2);
        }
        
        return removedElement;
    }

    bool removeElement(const T& element) {
        for(int i = 0; i < size; i++) {
            if(data[i] == element) {
                remove(i);
                return true;
            }
        }
        return false;
    }
    
    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }
    
    bool isEmpty() const {
        return size == 0;
    }

    void clear() {
        size = 0;

        if(capacity > 10) {
            delete[] data;
            capacity = 10;
            data = new T[capacity];
        }
    }

    bool contains(const T& element) const {
        for(int i = 0; i < size; i++) {
            if(data[i] == element) {
                return true;
            }
        }
        return false;
    }
    
    int indexOf(const T& element) const {
        for(int i = 0; i < size; i++) {
            if(data[i] == element) {
                return i;
            }
        }
        return -1;
    }

    T& operator[](int index) {
        if(index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    const T& operator[](int index) const {
        if(index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }

    ArrayList& operator=(const ArrayList& other) {
        if(this != &other) {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for(int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
};

string intToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

class Vehicle {
private:
    string registrationNumber;
    string driverName;
    string vehicleType;
    time_t entryTime;
    int slotNumber;
    
public:
    Vehicle() {
        registrationNumber = "";
        driverName = "";
        vehicleType = "";
        entryTime = 0;
        slotNumber = -1;
    }
    
    Vehicle(string reg, string driver, string type) {
        registrationNumber = reg;
        driverName = driver;
        vehicleType = type;
        entryTime = time(0);
        slotNumber = -1;
    }

    string getRegNumber() { return registrationNumber; }
    string getDriverName() { return driverName; }
    string getVehicleType() { return vehicleType; }
    time_t getEntryTime() { return entryTime; }
    int getSlotNumber() { return slotNumber; }

    void setSlotNumber(int slot) { slotNumber = slot; }
    
    void displayInfo() {
        cout << " Registration: " << registrationNumber 
             << " | Driver: " << driverName 
             << " | Type: " << vehicleType 
             << " | Slot: " << slotNumber;
    }
};

class ParkingSlot {
private:
    int slotNumber;
    bool isOccupied;
    Vehicle* parkedVehicle;
    string slotType;
    
public:
    ParkingSlot() {
        slotNumber = -1;
        isOccupied = false;
        parkedVehicle = NULL;
        slotType = "Regular";
    }
    
    ParkingSlot(int num, string type) {
        slotNumber = num;
        isOccupied = false;
        parkedVehicle = NULL;
        slotType = type;
    }
    
    bool isAvailable() { return !isOccupied; }
    int getSlotNumber() { return slotNumber; }
    string getSlotType() { return slotType; }
    Vehicle* getVehicle() { return parkedVehicle; }
    
    void setSlotNumber(int num) { slotNumber = num; }
    
    bool parkVehicle(Vehicle* vehicle) {
        if (!isOccupied && vehicle != NULL) {
            parkedVehicle = vehicle;
            isOccupied = true;
            vehicle->setSlotNumber(slotNumber);
            return true;
        }
        return false;
    }
    
    Vehicle* removeVehicle() {
        if (isOccupied && parkedVehicle != NULL) {
            Vehicle* temp = parkedVehicle;
            parkedVehicle = NULL;
            isOccupied = false;
            return temp;
        }
        return NULL;
    }
    
    void displaySlot() {
        cout << " Slot " << slotNumber << " [" << slotType << "]: ";
        if (isOccupied) {
            cout << "OCCUPIED";
            parkedVehicle->displayInfo();
        } else {
            cout << "VACANT";
        }
        cout << endl;
    }
};

class WaitingQueue {
private:
    queue<Vehicle*> vehicleQueue;
    int maxSize;
    
public:
    WaitingQueue(int size = 10) {
        maxSize = size;
    }
    
    bool addVehicle(Vehicle* vehicle) {
        if (vehicleQueue.size() < maxSize) {
            vehicleQueue.push(vehicle);
            return true;
        }
        return false;
    }
    
    Vehicle* getNextVehicle() {
        if (!vehicleQueue.empty()) {
            Vehicle* next = vehicleQueue.front();
            vehicleQueue.pop();
            return next;
        }
        return NULL;
    }
    
    Vehicle* peekNextVehicle() {
        if (!vehicleQueue.empty()) {
            return vehicleQueue.front();
        }
        return NULL;
    }
    
    bool isEmpty() { return vehicleQueue.empty(); }
    int getSize() { return vehicleQueue.size(); }
    
    void displayQueue() {
        if (vehicleQueue.empty()) {
            cout << " Waiting queue is empty." << endl;
            return;
        }
        
        cout << " Vehicles waiting: " << vehicleQueue.size() << endl;
        queue<Vehicle*> temp = vehicleQueue;
        int count = 1;
        while (!temp.empty()) {
            cout << "  " << count++ << ".";
            temp.front()->displayInfo();
            cout << endl;
            temp.pop();
        }
    }
};

class ParkingHistory {
private:
    stack<string> historyStack;
    
public:
    void addAction(string action) {
        historyStack.push(action);
    }
    
    string getLastAction() {
        if (!historyStack.empty()) {
            string action = historyStack.top();
            historyStack.pop();
            return action;
        }
        return "";
    }
    
    void displayHistory() {
        if (historyStack.empty()) {
            cout << " No history available." << endl;
            return;
        }
        
        cout << " Recent Actions (Last 5):" << endl;
        stack<string> temp = historyStack;
        int count = 0;
        while (!temp.empty() && count < 5) {
            cout << "  " << ++count << ". " << temp.top() << endl;
            temp.pop();
        }
    }
    
    bool isEmpty() { return historyStack.empty(); }
};

class BSTNode {
public:
    Vehicle* vehicle;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(Vehicle* v) {
        vehicle = v;
        left = right = NULL;
    }
};

class VehicleBST {
private:
    BSTNode* root;
    
    BSTNode* insertNode(BSTNode* node, Vehicle* vehicle) {
        if (node == NULL) return new BSTNode(vehicle);
        
        if (vehicle->getRegNumber() < node->vehicle->getRegNumber())
            node->left = insertNode(node->left, vehicle);
        else
            node->right = insertNode(node->right, vehicle);
            
        return node;
    }
    
    Vehicle* searchNode(BSTNode* node, string regNumber) {
        if (node == NULL || node->vehicle->getRegNumber() == regNumber)
            return (node != NULL) ? node->vehicle : NULL;
            
        if (regNumber < node->vehicle->getRegNumber())
            return searchNode(node->left, regNumber);
        else
            return searchNode(node->right, regNumber);
    }
    
    void inorderDisplay(BSTNode* node) {
        if (node != NULL) {
            inorderDisplay(node->left);
            node->vehicle->displayInfo();
            cout << endl;
            inorderDisplay(node->right);
        }
    }
    
public:
    VehicleBST() { root = NULL; }
    
    void insert(Vehicle* vehicle) {
        root = insertNode(root, vehicle);
    }
    
    Vehicle* search(string regNumber) {
        return searchNode(root, regNumber);
    }
    
    void displayAll() {
        if (root == NULL) {
            cout << " No vehicles in records." << endl;
            return;
        }
        inorderDisplay(root);
    }
};

class ParkingSystem {
private:
    ArrayList<ParkingSlot*> slots;
    WaitingQueue* waitingQueue;
    ParkingHistory* history;
    VehicleBST* vehicleBST;
    int totalSlots;
    int occupiedSlots;
    
public:
    ParkingSystem(int numSlots) {
        totalSlots = numSlots;
        occupiedSlots = 0;
        
        waitingQueue = new WaitingQueue();
        history = new ParkingHistory();
        vehicleBST = new VehicleBST();
        
        for (int i = 0; i < totalSlots; i++) {
            string type = "Regular";
            if (i < 2) type = "Handicapped";
            else if (i < 5) type = "Compact";
            
            slots.add(new ParkingSlot(i + 1, type));
        }
    }
    
    ~ParkingSystem() {
        for (int i = 0; i < slots.getSize(); i++) {
            delete slots[i];
        }
        
        while (!waitingQueue->isEmpty()) {
            Vehicle* v = waitingQueue->getNextVehicle();
            delete v;
        }
        
        delete waitingQueue;
        delete history;
        delete vehicleBST;
    }
    
    bool parkVehicle(string reg, string driver, string type) {
        if (vehicleBST->search(reg) != NULL) {
            cout << " ? Vehicle with registration " << reg << " is already parked!" << endl;
            return false;
        }
        
        if (occupiedSlots >= totalSlots) {
            Vehicle* waitingVehicle = new Vehicle(reg, driver, type);
            if (waitingQueue->addVehicle(waitingVehicle)) {
                cout << " Parking FULL! Vehicle added to waiting queue." << endl;
                cout << " Position in queue: " << waitingQueue->getSize() << endl;
                history->addAction("Added to queue: " + reg);
                return false;
            } else {
                cout << " ? Parking FULL and waiting queue also full!" << endl;
                delete waitingVehicle;
                return false;
            }
        }
        
        for (int i = 0; i < slots.getSize(); i++) {
            ParkingSlot* slot = slots[i];
            if (slot->isAvailable()) {
                Vehicle* newVehicle = new Vehicle(reg, driver, type);
                if (slot->parkVehicle(newVehicle)) {
                    occupiedSlots++;
                    vehicleBST->insert(newVehicle);
                    history->addAction("Parked: " + reg + " at Slot " + intToString(i + 1));
                    
                    cout << "\n ? VEHICLE PARKED SUCCESSFULLY!" << endl;
                    cout << " Slot Number: " << i + 1 << endl;
                    cout << " Vehicle Type: " << type << endl;
                    
                    time_t entryTime = newVehicle->getEntryTime();
                    cout << " Entry Time: " << ctime(&entryTime);
                    return true;
                }
            }
        }
        return false;
    }

    bool removeVehicle(string regNumber) {
        Vehicle* vehicle = vehicleBST->search(regNumber);
        
        if (vehicle == NULL) {
            cout << " Vehicle not found in parking!" << endl;
            return false;
        }
        
        int slotNum = vehicle->getSlotNumber() - 1;
        if (slotNum >= 0 && slotNum < slots.getSize()) {
            Vehicle* removed = slots[slotNum]->removeVehicle();
            if (removed != NULL) {
                occupiedSlots--;
                history->addAction("Removed: " + regNumber + " from Slot " + intToString(slotNum + 1));
                
                cout << "\n ? VEHICLE REMOVED SUCCESSFULLY!" << endl;
                cout << " Slot " << slotNum + 1 << " is now free." << endl;
                
                if (!waitingQueue->isEmpty()) {
                    Vehicle* nextVehicle = waitingQueue->getNextVehicle();
                    
                    if (slots[slotNum]->parkVehicle(nextVehicle)) {
                        occupiedSlots++;
                        vehicleBST->insert(nextVehicle);
                        nextVehicle->setSlotNumber(slotNum + 1);
                        
                        history->addAction("Auto-parked from queue: " + nextVehicle->getRegNumber() + " at Slot " + intToString(slotNum + 1));
                        
                        cout << "\n ? WAITING VEHICLE AUTO-PARKED!" << endl;
                        cout << " Vehicle: " << nextVehicle->getRegNumber() << endl;
                        cout << " Driver: " << nextVehicle->getDriverName() << endl;
                        cout << " Parked at Slot: " << slotNum + 1 << endl;
                        cout << " Queue position was: 1 (First in queue)" << endl;
                    } else {
                        waitingQueue->addVehicle(nextVehicle);
                        cout << " ? Failed to auto-park waiting vehicle!" << endl;
                    }
                }
                
                delete removed;
                return true;
            }
        }
        return false;
    }

    void searchVehicle(string regNumber) {
        Vehicle* vehicle = vehicleBST->search(regNumber);
        if (vehicle != NULL) {
            cout << "\n ? VEHICLE FOUND!" << endl;
            cout << " Details:";
            vehicle->displayInfo();
            cout << endl;
            cout << " Parked for: " << (time(0) - vehicle->getEntryTime()) << " seconds" << endl;
            cout << " Location: Slot " << vehicle->getSlotNumber() << endl;
        } else {
            cout << " ? Vehicle not found in parking!" << endl;
            cout << " Note: Check waiting queue if parking was full." << endl;
        }
    }

    void displayStatus() {
        cout << "\n=== PARKING STATUS ===" << endl;
        cout << " Total Slots: " << totalSlots << endl;
        cout << " Occupied: " << occupiedSlots << endl;
        cout << " Available: " << (totalSlots - occupiedSlots) << endl;
        cout << " Waiting Vehicles: " << waitingQueue->getSize() << endl;
        
        if (!waitingQueue->isEmpty()) {
            Vehicle* firstInQueue = waitingQueue->peekNextVehicle();
            if (firstInQueue != NULL) {
                cout << " Next in queue: ";
                firstInQueue->displayInfo();
                cout << endl;
            }
        }
        
        cout << "\n--- SLOT DETAILS ---" << endl;
        for (int i = 0; i < slots.getSize(); i++) {
            slots[i]->displaySlot();
        }
    }

    void displayAvailableSlots() {
        cout << "\n=== AVAILABLE SLOTS ===" << endl;
        bool found = false;
        for (int i = 0; i < slots.getSize(); i++) {
            if (slots[i]->isAvailable()) {
                slots[i]->displaySlot();
                found = true;
            }
        }
        if (!found) cout << " No available slots." << endl;
    }

    void displayOccupiedSlots() {
        cout << "\n=== OCCUPIED SLOTS ===" << endl;
        bool found = false;
        for (int i = 0; i < slots.getSize(); i++) {
            if (!slots[i]->isAvailable()) {
                slots[i]->displaySlot();
                found = true;
            }
        }
        if (!found) cout << " No occupied slots." << endl;
    }

    void displayWaitingQueue() {
        cout << "\n=== WAITING QUEUE ===" << endl;
        waitingQueue->displayQueue();
    }

    void displayAllVehicles() {
        cout << "\n=== ALL PARKED VEHICLES ===" << endl;
        vehicleBST->displayAll();
    }

    void undoLastAction() {
        if (!history->isEmpty()) {
            string lastAction = history->getLastAction();
            cout << " Undid: " << lastAction << endl;
        } else {
            cout << " No actions to undo." << endl;
        }
    }

    void displayHistory() {
        cout << "\n=== PARKING HISTORY ===" << endl;
        history->displayHistory();
    }

    void addNewParkingSlot(string type = "Regular") {
        int newSlotNumber = slots.getSize() + 1;
        slots.add(new ParkingSlot(newSlotNumber, type));
        totalSlots++;
        
        if (!waitingQueue->isEmpty()) {
            Vehicle* nextVehicle = waitingQueue->getNextVehicle();
            if (slots[slots.getSize() - 1]->parkVehicle(nextVehicle)) {
                occupiedSlots++;
                vehicleBST->insert(nextVehicle);
                history->addAction("Auto-parked from queue (new slot): " + nextVehicle->getRegNumber());
                cout << " ? New parking slot added and first waiting vehicle auto-parked!" << endl;
                cout << " Vehicle: " << nextVehicle->getRegNumber() << " parked at Slot " << newSlotNumber << endl;
            }
        } else {
            cout << " ? New parking slot added: Slot " << newSlotNumber << " [" << type << "]" << endl;
        }
    }

    bool removeParkingSlot(int slotNumber) {
        if (slotNumber <= 0 || slotNumber > slots.getSize()) {
            cout << " ? Invalid slot number!" << endl;
            return false;
        }
        
        ParkingSlot* slot = slots[slotNumber - 1];
        if (slot->isAvailable()) {
            delete slot;
            for (int i = slotNumber - 1; i < slots.getSize() - 1; i++) {
                slots[i] = slots[i + 1];
                slots[i]->setSlotNumber(i + 1);
            }
            slots.remove(slots.getSize() - 1);
            totalSlots--;
            cout << " ? Parking slot " << slotNumber << " removed successfully!" << endl;
            return true;
        } else {
            cout << " ? Cannot remove slot " << slotNumber << " - it is occupied!" << endl;
            return false;
        }
    }

    bool removeFromWaitingQueue(string regNumber) {
        cout << " Note: Queue doesn't support direct removal by registration." << endl;
        cout << " You need to wait for the vehicle to reach front of queue." << endl;
        return false;
    }
};

int main() {
    cout << "================================================" << endl;
    cout << "    CAR PARKING MANAGEMENT SYSTEM" << endl;
    cout << "    Using Data Structures in C++" << endl;
    cout << "================================================" << endl;
    cout << " Data Structures Used:" << endl;
    cout << " • ArrayList - For dynamic parking slots" << endl;
    cout << " • Queue - For waiting vehicles (FIFO)" << endl;
    cout << " • Stack - For undo operations" << endl;
    cout << " • BST - For fast vehicle search" << endl;
    cout << "================================================" << endl << endl;
    cout << " IMPORTANT FEATURE:" << endl;
    cout << " • When a vehicle is removed, FIRST vehicle from waiting" << endl;
    cout << "   queue automatically gets parked in the freed slot!" << endl;
    cout << "================================================" << endl << endl;
    
    int totalSlots;
    cout << "Enter total number of parking slots: ";
    cin >> totalSlots;
    cin.ignore();
    
    ParkingSystem parking(totalSlots);
    
    int choice;
    string regNumber, driverName, vehicleType;
    int slotNum;
    
    do {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << " 1. Park a Vehicle" << endl;
        cout << " 2. Remove a Vehicle" << endl;
        cout << " 3. Search Vehicle" << endl;
        cout << " 4. Display Parking Status" << endl;
        cout << " 5. Display Available Slots" << endl;
        cout << " 6. Display Occupied Slots" << endl;
        cout << " 7. Display Waiting Queue" << endl;
        cout << " 8. Display All Vehicles" << endl;
        cout << " 9. Undo Last Action" << endl;
        cout << "10. Display History" << endl;
        cout << "11. Add New Parking Slot" << endl;
        cout << "12. Remove Parking Slot" << endl;
        cout << "13. Display Queue Info" << endl;
        cout << " 0. Exit" << endl;
        cout << "=================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                cout << "\n--- PARK VEHICLE ---" << endl;
                cout << "Enter Registration Number: ";
                getline(cin, regNumber);
                cout << "Enter Driver Name: ";
                getline(cin, driverName);
                cout << "Enter Vehicle Type (Car/Bike/Truck): ";
                getline(cin, vehicleType);
                parking.parkVehicle(regNumber, driverName, vehicleType);
                break;
                
            case 2:
                cout << "\n--- REMOVE VEHICLE ---" << endl;
                cout << "Enter Registration Number: ";
                getline(cin, regNumber);
                parking.removeVehicle(regNumber);
                break;
                
            case 3:
                cout << "\n--- SEARCH VEHICLE ---" << endl;
                cout << "Enter Registration Number: ";
                getline(cin, regNumber);
                parking.searchVehicle(regNumber);
                break;
                
            case 4:
                parking.displayStatus();
                break;
                
            case 5:
                parking.displayAvailableSlots();
                break;
                
            case 6:
                parking.displayOccupiedSlots();
                break;
                
            case 7:
                parking.displayWaitingQueue();
                break;
                
            case 8:
                parking.displayAllVehicles();
                break;
                
            case 9:
                cout << "\n--- UNDO LAST ACTION ---" << endl;
                parking.undoLastAction();
                break;
                
            case 10:
                parking.displayHistory();
                break;
                
            case 11:
                cout << "\n--- ADD NEW PARKING SLOT ---" << endl;
                cout << "Enter slot type (Regular/Compact/Handicapped): ";
                getline(cin, vehicleType);
                parking.addNewParkingSlot(vehicleType);
                break;
                
            case 12:
                cout << "\n--- REMOVE PARKING SLOT ---" << endl;
                cout << "Enter slot number to remove: ";
                cin >> slotNum;
                cin.ignore();
                parking.removeParkingSlot(slotNum);
                break;
                
            case 13:
                cout << "\n--- WAITING QUEUE INFORMATION ---" << endl;
                cout << " First vehicle in queue gets priority when slot frees up." << endl;
                cout << " Queue works on FIFO (First In First Out) principle." << endl;
                parking.displayWaitingQueue();
                break;
                
            case 0:
                cout << "\nThank you for using Car Parking Management System!" << endl;
                cout << "Project submitted successfully!" << endl;
                break;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        
        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}
