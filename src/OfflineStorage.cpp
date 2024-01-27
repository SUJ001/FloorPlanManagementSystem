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

int main() {
    // Example usage
    OfflineStorage offlineStorage;
    FloorPlan floorPlan;  // Assuming FloorPlan is defined similarly to the Java version
    offlineStorage.savePlan(floorPlan);

    vector<FloorPlan> loadedPlans = offlineStorage.loadPlans();
    for (const auto& plan : loadedPlans) {
        // Do something with each loaded plan
    }

    offlineStorage.clearStorage();

    return 0;
}
