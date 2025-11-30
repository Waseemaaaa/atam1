// You can edit anything you want in this file.
//However you need to implement all public Plains function, as provided below as a template

#include "plains25a1.h"
#include <exception>

Plains::Plains() = default;

Plains::~Plains() {
    horses.removeData(horses.root);
    /// horses tree is done with all the data inside
    emptyHerds.removeData(emptyHerds.root);
    /// empty herds is done

    herds.removeData(herds.root);
}

StatusType Plains::add_herd(int herdId) {
    if (herdId <= NO_ID) {
        return StatusType::INVALID_INPUT;
    }
    if (herds.nodeInTree(herdId) || emptyHerds.nodeInTree(herdId)) {
        return StatusType::FAILURE;
    }
    try {
        herd *newHerd = new herd();
        emptyHerds.insertNode(herdId, newHerd);
    } catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::remove_herd(int herdId) {
    if (herdId <= NO_ID) {
        return StatusType::INVALID_INPUT;
    }
    auto node = emptyHerds.findNode(emptyHerds.root, herdId);
    if (node == nullptr) {
        return StatusType::FAILURE;
    }
    try {
        delete node->data; // deletes the root ptr to the empty herd
        emptyHerds.removeNode(herdId);
    } catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::add_horse(int horseId, int speed) {
    if (horseId <= NO_ID || speed <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (horses.nodeInTree(horseId)) {
        return StatusType::FAILURE;
    }
    try {
        horse *newHorse = new horse(horseId, speed);
        horses.insertNode(horseId, newHorse);
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;

}

StatusType Plains::join_herd(int horseId, int herdId) {
    if (horseId <= NO_ID || herdId <= NO_ID) {
        return StatusType::INVALID_INPUT;
    }
    auto horseNode = horses.findNode(horses.root, horseId);
    if (!horseNode) {
        return StatusType::FAILURE;
    }
    horse *selectedHorse = horseNode->data;
    if (selectedHorse->getHerdID() != NO_ID) {
        return StatusType::FAILURE; // Horse is already assigned to a herd
    }
    herd *selectedHerd = nullptr;
    auto herdNode = emptyHerds.findNode(emptyHerds.root, herdId);
    if (herdNode) {
        selectedHerd = herdNode->data;
    } else {
        herdNode = herds.findNode(herds.root, herdId);
        if (herdNode) {
            selectedHerd = herdNode->data;
        }
    }
    if (!selectedHerd) {
        return StatusType::FAILURE;
    }
    try {
        selectedHorse->setHerdID(herdId);
        selectedHerd->addHorse(selectedHorse, horseId);
        if (emptyHerds.nodeInTree(herdId)) {
            //todo delete the data of the node of the herd in the empty herds
            delete selectedHerd;
            emptyHerds.removeNode(herdId);
            herds.insertNode(herdId, selectedHerd);
        }
    } catch (const std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::follow(int horseId, int horseToFollowId) {
    if (horseId <= NO_ID || horseToFollowId <= NO_ID || horseId == horseToFollowId) {
        return StatusType::INVALID_INPUT;
    }
    auto horseNode = horses.findNode(horses.root, horseId);
    auto toFollowNode = horses.findNode(horses.root, horseToFollowId);
    if (!horseNode || !toFollowNode) {
        return StatusType::FAILURE;
    }
    horse *follower = horseNode->data;
    horse *leader = toFollowNode->data;
    if (follower->getHerdID() == NO_ID || leader->getHerdID() == NO_ID ||
        follower->getHerdID() != leader->getHerdID()) {
        return StatusType::FAILURE;
    }
    //todo let me understand what u did ..
    /// didnt understand what are u trying to check here ...
    if (follower->getFollows() == leader && follower->getFollowVersion() == leader->getVersion()) {
        return StatusType::SUCCESS; //already following correctly
    }
    try {
        follower->setFollow(leader);
        follower->setFollowVersion(leader->getVersion());
    } catch (const std::bad_alloc &) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::leave_herd(int horseId) {
    if (horseId <= NO_ID) {
        return StatusType::INVALID_INPUT;
    }
    auto horseNode = horses.findNode(horses.root, horseId);
    if (!horseNode) {
        return StatusType::FAILURE;
    }
    horse *current_horse = horseNode->data;
    int herdID = current_horse->getHerdID();
    if (herdID <= NO_ID) {
        return StatusType::FAILURE;
    }
    auto herdNode = herds.findNode(herds.root, herdID);
    if (!herdNode) {
        return StatusType::FAILURE;
    }
    herd *current_Herd = herdNode->data;

    current_Herd->getHorses().removeNode(horseId); //todo here u delete the node but not the data ?
    if (current_Herd->getHorses().size == 0) {
        herds.removeNode(herdID);
        emptyHerds.insertNode(herdID, current_Herd);
    }
    current_horse->incrementVersion();
    current_horse->setHerdID(NO_ID);
    current_horse->setFollowVersion(-1);
    current_horse->setFollows(nullptr);
    return StatusType::SUCCESS;
}

output_t<int> Plains::get_speed(int horseId) {
    if (horseId <= NO_ID) {
        return StatusType::INVALID_INPUT;
    }
    auto node = horses.findNode(horses.root, horseId);
    if (node == nullptr) {
        return StatusType::FAILURE;
    }
    int speed = node->data->getHorseSpeed();
    return {speed};
}

output_t<bool> Plains::leads(int horseId, int otherHorseId) {
    if (horseId <= NO_ID || otherHorseId <= NO_ID || horseId == otherHorseId) {
        return {StatusType::INVALID_INPUT};
    }

    auto horseNode = horses.findNode(horses.root, horseId);
    auto otherHorseNode = horses.findNode(horses.root, otherHorseId);
    if (!horseNode || !otherHorseNode) {
        return {StatusType::FAILURE};
    }

    horse* leader = otherHorseNode->data;
    horse* follower = horseNode->data;

    if (follower->getHerdID() == NO_ID || leader->getHerdID() == NO_ID ||
        follower->getHerdID() != leader->getHerdID()) {
        return {false};
    }
    int traversalId = horseId; //unique traversal ID for this search
    if(leader->getFollows()!= nullptr)
    {
        return {false};
    }
    while (follower != nullptr) {
        if (follower == leader) {
            resetVisitedTraversalIdInHerd(follower->getHerdID());
            return {true};
        }
        if (follower->getVisitedTraversalId() == traversalId) {
            resetVisitedTraversalIdInHerd(follower->getHerdID());
            return {false};
        }
        follower->setVisitedTraversalId(traversalId);
        if (!follower->getFollows() ||
            follower->getFollowVersion() != follower->getFollows()->getVersion()) {
            resetVisitedTraversalIdInHerd(follower->getHerdID());
            return {false};
        }
        follower = follower->getFollows();
    }
    return {false}; //leader not found
}

output_t<bool> Plains::can_run_together(int herdId) {
    if (herdId <= NO_ID) {
        return {StatusType::INVALID_INPUT};
    }
    auto herdNode = herds.findNode(herds.root, herdId);
    if (!herdNode) {
        return {StatusType::FAILURE};
    }

    herd* targetHerd_data = herdNode->data;
    AVL<int, horse*>& herdHorses = targetHerd_data->getHorses();
    if (herdHorses.size == 0) {
        return {false};
    }
    if (herdHorses.size == 1) {
        return {true};
    }
    int* horseIds = nullptr;
    horse** horseData = nullptr;
    int herdSize = herdHorses.size;
    flattenHerd(herdHorses, horseIds, horseData);

    horse* leader = findLeader(horseData, herdSize);
    if (!leader) {
        delete[] horseIds;
        delete[] horseData;
        return {false};
    }

    bool isValid = validateConnections(horseData, herdSize, leader);

    resetVisitedTraversalId(horseData, herdSize);

    delete[] horseIds;
    delete[] horseData;

    return {isValid};
}

void Plains::flattenHerd(AVL<int, horse*>& herdHorses, int* horseIds, horse** horseData) {
    horseIds = new int[herdHorses.size];
    horseData = new horse*[herdHorses.size];
    int index = 0;
    herdHorses.fillArray(herdHorses.root, horseIds, horseData, &index, herdHorses.minNode->key, herdHorses.maxNode->key);
}

horse* Plains::findLeader(horse** horseData, int herdSize) {
    horse* leader = nullptr;

    for (int i = 0; i < herdSize; i++) {
        horse* currentHorse = horseData[i];
        if (currentHorse->getFollows() == nullptr) {
            if (leader != nullptr) {
                return nullptr; // More than one leader found
            }
            leader = currentHorse;
        } else {
            // Validate followship
            if (!validateFollowship(currentHorse)) {
                return nullptr;
            }
        }
    }
    return leader;
}

bool Plains::validateConnections(horse** horseData, int herdSize, horse* leader) {
    for (int i = 0; i < herdSize; i++) {
        horse* traverser = horseData[i];
        while (traverser != nullptr) {
            int currentTraversalId = traverser->getVisitedTraversalId();

            // Check if already validated
            if (currentTraversalId != -1 && currentTraversalId != i) {
                break;
            }

            // Detect cycle
            if (currentTraversalId == i) {
                return false; // Cycle detected
            }

            traverser->setVisitedTraversalId(i);

            // If reached the leader, stop traversal
            if (traverser == leader) {
                break;
            }

            // Validate followship
            if (!validateFollowship(traverser)) {
                return false;
            }

            traverser = traverser->getFollows();
        }

        if (traverser == nullptr) {
            return false; // Cannot reach the leader
        }
    }

    return true;
}

bool Plains::validateFollowship(horse* currentHorse) {
    horse* leader = currentHorse->getFollows();
    if (leader == nullptr) return true;

    // Validate followship version
    if (currentHorse->getFollowVersion() != leader->getVersion()) {
        return false;
    }
    return true;
}

void Plains::resetVisitedTraversalId(horse** horseData, int herdSize) {
    for (int i = 0; i < herdSize; ++i) {
        horseData[i]->setVisitedTraversalId(-1);
    }
}

void Plains::resetVisitedTraversalIdInHerd(int herdId) {
    auto herdNode = herds.findNode(herds.root, herdId);
    if (!herdNode) return;

    herd* targetHerd_data = herdNode->data;
    AVL<int, horse*>& herdHorses = targetHerd_data->getHorses();

    int herdSize = herdHorses.size;
    int* horseIds = nullptr;
    horse** horseData = nullptr;
    flattenHerd(herdHorses, horseIds, horseData);

    // Reset VisitedTraversalId for all horses
    for (int i = 0; i < herdSize; i++) {
        horseData[i]->setVisitedTraversalId(-1);
    }

    delete[] horseIds;
    delete[] horseData;
}
