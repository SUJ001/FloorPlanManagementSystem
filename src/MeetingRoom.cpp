#include <iostream>
#include <vector>

using namespace std;

class Booking {
public:
    string getStartTime() const {
        // Implement based on your actual Booking class
        return "";
    }

    string getEndTime() const {
        // Implement based on your actual Booking class
        return "";
    }
};

class MeetingRoom {
private:
    int roomId;
    string roomName;
    int capacity;
    string location;
    vector<Booking> bookings;

public:
    MeetingRoom(int roomId, string roomName, int capacity, string location)
        : roomId(roomId), roomName(roomName), capacity(capacity), location(location) {}

    bool isAvailable(const string& startTime, const string& endTime) {
        for (const Booking& booking : bookings) {
            if (isTimeConflict(startTime, endTime, booking.getStartTime(), booking.getEndTime())) {
                return false;
            }
        }
        return true;
    }

    bool hasCapacity(int participants) {
        return capacity >= participants;
    }

    string getRoomName() const {
        return roomName;
    }

    void addBooking(const Booking& booking) {
        bookings.push_back(booking);
    }

private:
    bool isTimeConflict(const string& start1, const string& end1, const string& start2, const string& end2) const {
        return !(end1.compare(start2) <= 0 || start1.compare(end2) >= 0);
    }
};
