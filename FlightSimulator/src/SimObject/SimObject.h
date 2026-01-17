#pragma once

#include <string>
#include <cstdint>

/*
Tamam, isteðini tam olarak anladým. Ýleride bana þu kalýpla gelirsen hem hiyerarþik/girintili listeyi hem de Visual Studio uyumlu tek satýr listeyi hazýrlarým:

"Verdiðim pathleri klasör yapýsýna göre hiyerarþik (girintili) olarak sýrala VE ardýndan bu sýralamaya uygun þekilde tek satýrda noktalý virgül ile ayrýlmýþ halini de ver."

Örnek bir komut taslaðý:

"Þu listeyi al, önce klasörlerin alt alta hiyerarþisini gösteren girintili bir liste yap. Sonra hemen altýna, bu mantýklý sýraya göre dizilmiþ, aralarýnda noktalý virgül olan tek satýrlýk (VS Include formatýnda) versiyonunu ekle."

Bu komutu kullandýðýnda sana iki çýktýyý da (Tree View + VS Include String) tek seferde veririm.
*/

// Forward declaration
class CSimEngine;

enum class EObjectType : int
{
    Unknown = 0,
    SimEngine,
    PhysicalEntity,
    Platform,
    AirPlatform,
    Aircraft,
    Fighter,
    UAV,
    Helicopter,
    SeaPlatform,
    Ship,
    Submarine,
    Weapon,
    Missile,
    Component,
    Sensor
};

namespace AFS {

class CSimObject
{
protected:
    uint64_t m_objectId;
    std::string m_objectName;
    EObjectType m_objectType;
    bool m_isActive;
    double m_creationTime;
    CSimEngine* m_pSimEngine;  // Reference to SimEngine

public:
    // Constructor
    CSimObject(CSimEngine* pEngine);

    // Virtual destructor
    virtual ~CSimObject();

    // Pure virtual methods - must be implemented by derived classes
    virtual void update(double deltaTime) = 0;
    virtual void initialize() = 0;
    virtual void destroy() = 0;

    // Getters
    uint64_t getId() const { return m_objectId; }
    std::string getName() const { return m_objectName; }
    EObjectType getType() const { return m_objectType; }
    bool getActive() const { return m_isActive; }
    double getCreationTime() const { return m_creationTime; }
    CSimEngine* getSimEngine() const { return m_pSimEngine; }

    // Setters
    void setName(const std::string& name) { m_objectName = name; }
    void setActive(bool active) { m_isActive = active; }
    void setType(EObjectType type) { m_objectType = type; }

protected:
    // Protected method to set object ID (called during creation)
    void setId(uint64_t id) { m_objectId = id; }
    void setCreationTime(double time) { m_creationTime = time; }
};

} // namespace AFS
