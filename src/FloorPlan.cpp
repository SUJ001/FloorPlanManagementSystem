#include <bits/stdc++.h>
#include <vector>
#include <map>
#include <chrono>

using namespace std;

class Admin {
};

class Room {
public:
    int getId() const {
        return 0;
    }
};

class FloorPlan;

class DataCache {
private:
    map<string, Room> cache;

public:
    DataCache() {}

    Room getFromCache(const string& key) const {
        auto it = cache.find(key);
        if (it != cache.end()) {
            return it->second;
        }
        return Room();
    }

    void addToCache(const string& key, const Room& data) {
        cache[key] = data;
    }

    void removeFromCache(const string& key) {
        cache.erase(key);
    }

    void clearCache() {
        cache.clear();
    }
};

class FloorPlan {
private:
    int floorPlanId;
    string planName;
    int version;
    vector<Room> rooms;
    chrono::system_clock::time_point lastModified;
    chrono::system_clock::time_point createdDate;
    Admin createdBy;
    DataCache dataCache;  // Now DataCache is declared outside of FloorPlan
    int priority;
    string description;
    vector<string> tags;

public:
    FloorPlan(int floorPlanId, string planName, int version,
              chrono::system_clock::time_point lastModified,
              vector<Room> rooms, chrono::system_clock::time_point createdDate,
              Admin createdBy, string description, vector<string> tags)
        : floorPlanId(floorPlanId), planName(planName), version(version),
          lastModified(lastModified), rooms(rooms), createdDate(createdDate),
          createdBy(createdBy), description(description), tags(tags), priority(0) {}

    int getFloorPlanId() const {
        return floorPlanId;
    }

    string getPlanName() const {
        return planName;
    }

    int getVersion() const {
        return version;
    }

    chrono::system_clock::time_point getLastModified() const {
        return lastModified;
    }

    const vector<Room>& getRooms() const {
        return rooms;
    }

    chrono::system_clock::time_point getCreatedDate() const {
        return createdDate;
    }

    const Admin& getCreatedBy() const {
        return createdBy;
    }

    void setCreatedBy(const Admin& createdBy) {
        this->createdBy = createdBy;
    }

    string getDescription() const {
        return description;
    }

    void setDescription(const string& description) {
        this->description = description;
    }

    const vector<string>& getTags() const {
        return tags;
    }

    void setTags(const vector<string>& tags) {
        this->tags = tags;
    }

    void setPriority(int priority) {
        this->priority = priority;
    }

    int getPriority() const {
        return priority;
    }

    void addRoom(const Room& room) {
        rooms.push_back(room);
        dataCache.addToCache("Room_" + to_string(room.getId()), room);
    }

    void removeRoom(const Room& room) {
        auto it = find(rooms.begin(), rooms.end(), room);
        if (it != rooms.end()) {
            rooms.erase(it);
            dataCache.removeFromCache("Room_" + to_string(room.getId()));
        }
    }

    Room getRoomById(int roomId) const {
        Room cachedRoom = dataCache.getFromCache("Room_" + to_string(roomId));
        if (cachedRoom.getId() != 0) {
            cout << "Room found in cache!" << endl;
            return cachedRoom;
        } else {
            for (const Room& room : rooms) {
                if (room.getId() == roomId) {
                    return room;
                }
            }
        }
        return Room();
    }

    void uploadPlan() {
        version++;
        lastModified = chrono::system_clock::now();
        cout << "Floor plan uploaded. New version: " << version << endl;
    }
};

int main() {
    FloorPlan floorPlan(1, "OfficeFloor", 1, chrono::system_clock::now(),
                       vector<Room>(), chrono::system_clock::now(),
                       Admin(), "Description", vector<string>());
    return 0;
}
