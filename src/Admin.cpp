#include <bits/stdc++.h>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

enum class UserRole {
    ADMIN,
    REGULAR_USER
};

class FloorPlan {
public:
    FloorPlan(int id, const string& name, int floorNumber)
        : id(id), name(name), floorNumber(floorNumber) {}

private:
    int id;
    string name;
    int floorNumber;
};

class ConflictResolver {
public:
    void resolveConflict(const FloorPlan& localPlan, const FloorPlan& serverPlan) {
        // Implementation of conflict resolution logic
    }

private:
    // Add any additional conflict resolution logic here
};

class Admin {
public:
    Admin(const string& username, const string& password, UserRole role, ConflictResolver& resolver)
        : username(username), hashedPassword(hashPassword(password)), role(role), conflictResolver(resolver) {}

    bool authenticate(const string& enteredPassword) const {
        const string enteredPasswordHash = hashPassword(enteredPassword);
        return enteredPasswordHash == hashedPassword;
    }

    void resolveConflict(const FloorPlan* localPlan, const FloorPlan* serverPlan) const {
        // Check if the pointers are not null
        if (localPlan == nullptr || serverPlan == nullptr) {
            throw invalid_argument("Floor plans cannot be null.");
        }
        conflictResolver.resolveConflict(*localPlan, *serverPlan);
    }

    // Provide a public method to access the ConflictResolver
    void performConflictResolution(const FloorPlan& localPlan, const FloorPlan& serverPlan) const {
        conflictResolver.resolveConflict(localPlan, serverPlan);
    }

private:
    string hashPassword(const string& password) const {
        try {
            stringstream hashedStream;
            for (unsigned char c : password) {
                hashedStream << hex << setw(2) << setfill('0') << static_cast<int>(c);
            }
            return hashedStream.str();
        } catch (const exception& e) {
            throw runtime_error("Error hashing password");
        }
    }

    string username;
    string hashedPassword;
    UserRole role;
    ConflictResolver& conflictResolver;  // Reference to the ConflictResolver
};

int main() {
    FloorPlan localPlan(1, "OfficeFloor", 1);
    FloorPlan serverPlan(1, "OfficeFloor", 1);

    ConflictResolver conflictResolver;
    Admin admin("admin", "admin_password", UserRole::ADMIN, conflictResolver);

    // Example of resolving conflict using Admin
    admin.resolveConflict(&localPlan, &serverPlan);

    return 0;
}

