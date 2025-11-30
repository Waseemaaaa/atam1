#ifndef DS_WET1_WINTER_2024_2025_HORSE_H
#define DS_WET1_WINTER_2024_2025_HORSE_H

class horse {
private:
    int ID;
    int speed;
    int herdID;
    horse *following;
    int version;
    int followVersion;
    int visitedTraversalId;

public:

     horse(int ID, int speed) : ID(ID), speed(speed), herdID(0),
                               following(nullptr), version(0),
                               followVersion(-1), visitedTraversalId(-1) {}

    ~horse() = default;

    horse(const horse &other) = default;

    horse &operator=(const horse &other) = default;

    int getHorseSpeed() const {
        return speed;
    }

    int getID() const {
        return ID;
    }
    void setHerdID(int newHerdID) {
        herdID = newHerdID;
    }

    void setFollow(horse *leader) {
        following = leader;
        followVersion = (leader) ? leader->getVersion() : -1;
    }

    int getHerdID() const {
        return herdID;
    }

    horse *getFollows() const {
        return following;
    }

    void setFollows(horse *toFollow) {
        following = toFollow;
    }

    int getVersion() const {
        return version;
    }

    int getFollowVersion() const {
        return followVersion;
    }

    void incrementVersion() {
        version++;
    }

    void setFollowVersion(int ver) {
        followVersion = ver;
    }

    void setVisitedTraversalId(int id) {
        visitedTraversalId = id;
    }

    int getVisitedTraversalId() const {
        return visitedTraversalId;
    }

};

#endif // DS_WET1_WINTER_2024_2025_HORSE_H
