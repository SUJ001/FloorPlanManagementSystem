#include <iostream>
#include <stdexcept>

using namespace std;

enum class UserRole {
    ADMIN,
    REGULAR_USER
};

class Admin {
public:
    bool authenticate(const string& enteredPassword) const {
        return enteredPassword == "admin_password";
    }

    UserRole getRole() const {
        return UserRole::ADMIN;
    }
};

class FloorPlan {
public:
    int getPriority() const {
        return priority;
    }

    int getLastModified() const {
        return lastModified;
    }

    void uploadPlan() const {
        cout << "Uploading floor plan..." << endl;
    }

private:
    int priority;
    int lastModified;
};

class ConflictResolver {
public:
    void resolveConflict(const FloorPlan& localPlan, const FloorPlan& serverPlan, const Admin& admin) const {
        if (admin.authenticate("admin_password") && admin.getRole() == UserRole::ADMIN) {
            cout << "Admin resolving conflict. Admin's version takes priority." << endl;
            serverPlan.uploadPlan();
        } else {
            int priorityComparison = localPlan.getPriority() - serverPlan.getPriority();

            if (priorityComparison > 0) {
                cout << "Conflict resolved. Uploading local version based on priority..." << endl;
                serverPlan.uploadPlan();
            } else if (priorityComparison < 0) {
                cout << "Conflict resolved. Merging server version based on priority..." << endl;
                localPlan.uploadPlan();
            } else {
                int timestampComparison = localPlan.getLastModified() - serverPlan.getLastModified();

                if (timestampComparison > 0) {
                    cout << "Conflict resolved. Uploading local version based on timestamp..." << endl;
                    serverPlan.uploadPlan();
                } else if (timestampComparison < 0) {
                    cout << "Conflict resolved. Merging server version based on timestamp..." << endl;
                    localPlan.uploadPlan();
                } else {
                    cerr << "Conflict detected. Additional resolution needed." << endl;
                    throw runtime_error("Conflict detected. Additional resolution needed.");
                }
            }
        }
    }
};

int main() {
    ConflictResolver conflictResolver;
    FloorPlan localPlan;
    FloorPlan serverPlan;
    Admin admin;

    conflictResolver.resolveConflict(localPlan, serverPlan, admin);

    return 0;
}
