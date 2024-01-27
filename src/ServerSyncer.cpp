#include <iostream>
#include <vector>

using namespace std;

class FloorPlan {
public:
    string getPlanName() const {
        // Implement getPlanName() based on your actual FloorPlan class
        return "";
    }
};

class OfflineStorage {
private:
    vector<FloorPlan> localPlans;

public:
    OfflineStorage() {}

    void savePlan(const FloorPlan& floorPlan) {
        localPlans.push_back(floorPlan);
        cout << "Floor plan saved locally: " << floorPlan.getPlanName() << endl;
    }

    vector<FloorPlan> loadPlans() const {
        cout << "Loading locally stored floor plans..." << endl;
        return localPlans;
    }

    void clearStorage() {
        localPlans.clear();
        cout << "Local storage cleared." << endl;
    }
};

class ServerSyncer {
private:
    OfflineStorage offlineStorage;

public:
    ServerSyncer(const OfflineStorage& offlineStorage) : offlineStorage(offlineStorage) {}

    void synchronizeWithServer() {
        const bool isConnected = checkInternetConnection();

        if (isConnected) {
            vector<FloorPlan> localPlans = offlineStorage.loadPlans();

            for (const FloorPlan& floorPlan : localPlans) {
                updateFloorPlan(floorPlan);
                cout << "Synchronizing with server: " << floorPlan.getPlanName() << endl;
            }

            offlineStorage.clearStorage();
        } else {
            cerr << "No internet connection. Synchronization postponed." << endl;
            throw runtime_error("No internet connection. Synchronization postponed.");
        }
    }

private:
    bool checkInternetConnection() const {
        // Assume logic to check internet connection
        return true;
    }

    void updateFloorPlan(const FloorPlan& floorPlan) const {
        cout << "Floor plan updated to: " << floorPlan.getPlanName() << endl;
    }
};

int main() {
    // Example usage
    OfflineStorage offlineStorage;
    ServerSyncer serverSyncer(offlineStorage);

    // Assume there is a FloorPlan instance to save
    FloorPlan floorPlan;
    offlineStorage.savePlan(floorPlan);

    // Synchronize with the server
    serverSyncer.synchronizeWithServer();

    return 0;
}
