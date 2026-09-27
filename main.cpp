/**
 * @file main.cpp
 * @brief Système de surveillance de capteurs avec alertes en temps réel.
 * @filiere TRSE - Télécommunications, Réseaux et Systèmes Embarqués
 * @author Otman HANNAOUI
 */

#include <iostream>
#include <chrono>
#include <thread>

const float TEMP_CRITICAL = 45.0; // Seuil de température en °C
const float DIST_MIN = 10.0;      // Distance minimale de sécurité en cm

enum SystemStatus {
    SYSTEM_OK,
    WARNING_TEMP,
    WARNING_DISTANCE,
    CRITICAL_ALERT
};

class SensorNode {
private:
    float temperature;
    float distance;
    SystemStatus status;

public:
    SensorNode() : temperature(25.0), distance(50.0), status(SYSTEM_OK) {}

    void readSensors(float newTemp, float newDist) {
        temperature = newTemp;
        distance = newDist;
        updateSystemStatus();
    }

    void updateSystemStatus() {
        if (temperature >= TEMP_CRITICAL && distance <= DIST_MIN) {
            status = CRITICAL_ALERT;
        } else if (temperature >= TEMP_CRITICAL) {
            status = WARNING_TEMP;
        } else if (distance <= DIST_MIN) {
            status = WARNING_DISTANCE;
        } else {
            status = SYSTEM_OK;
        }
    }

    void displayStatus() const {
        std::cout << "[TELEMETRIE] Temp: " << temperature << " °C | Distance: " << distance << " cm --> Statut: ";
        switch (status) {
            case SYSTEM_OK:
                std::cout << "[OK] Systeme Nominale" << std::endl;
                break;
            case WARNING_TEMP:
                std::cout << "[ATTENTION] Surchauffe Detectee!" << std::endl;
                break;
            case WARNING_DISTANCE:
                std::cout << "[ATTENTION] Obstacle Proche!" << std::endl;
                break;
            case CRITICAL_ALERT:
                std::cout << "[ALERTE CRITIQUE] Arret d'urgence requis!" << std::endl;
                break;
        }
    }
};

int main() {
    std::cout << "=================================================" << std::endl;
    std::cout << "   INITIALISATION DU SYSTEME EMBARQUE TRSE      " << std::endl;
    std::cout << "   Développé par Otman HANNAOUI                  " << std::endl;
    std::cout << "=================================================" << std::endl;

    SensorNode node;

    float testData[5][2] = {
        {25.5, 60.0},
        {30.0, 40.0},
        {46.5, 35.0},
        {28.0, 8.0},
        {50.0, 5.0}
    };

    for (int i = 0; i < 5; ++i) {
        node.readSensors(testData[i][0], testData[i][1]);
        node.displayStatus();
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }

    return 0;
}