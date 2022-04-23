#pragma once

#include "../defines.hpp"
#include <any>

enum ANIMATEDVARTYPE {
    AVARTYPE_INVALID = -1,
    AVARTYPE_FLOAT,
    AVARTYPE_VECTOR,
    AVARTYPE_COLOR
};

class CAnimationManager;

class CAnimatedVariable {
public:
    CAnimatedVariable(); // dummy var

    void create(ANIMATEDVARTYPE, float* speed, int64_t* enabled, void* pWindow);
    void create(ANIMATEDVARTYPE, std::any val, float* speed, int64_t* enabled, void* pWindow);

    ~CAnimatedVariable();

    // gets the current vector value (real time)
    Vector2D vec() {
        ASSERT(m_eVarType == AVARTYPE_VECTOR);
        return m_vValue;
    }

    // gets the current float value (real time)
    float fl() {
        ASSERT(m_eVarType == AVARTYPE_FLOAT);
        return m_fValue;
    }

    // gets the current color value (real time)
    CColor col() {
        ASSERT(m_eVarType == AVARTYPE_COLOR);
        return m_cValue;
    }

    // gets the goal vector value
    Vector2D goalv() {
        ASSERT(m_eVarType == AVARTYPE_VECTOR);
        return m_vGoal;
    }

    // gets the goal float value
    float goalf() {
        ASSERT(m_eVarType == AVARTYPE_FLOAT);
        return m_fGoal;
    }

    // gets the goal color value
    CColor goalc() {
        ASSERT(m_eVarType == AVARTYPE_COLOR);
        return m_cGoal;
    }

    void operator=(const Vector2D& v) {
        ASSERT(m_eVarType == AVARTYPE_VECTOR);
        m_vGoal = v;
    }

    void operator=(const float& v) {
        ASSERT(m_eVarType == AVARTYPE_FLOAT);
        m_fGoal = v;
    }

    void operator=(const CColor& v) {
        ASSERT(m_eVarType == AVARTYPE_COLOR);
        m_cGoal = v;
    }

    // Sets the actual stored value, without affecting the goal
    void setValue(const Vector2D& v) {
        ASSERT(m_eVarType == AVARTYPE_VECTOR);
        m_vValue = v;
    }

    // Sets the actual stored value, without affecting the goal
    void setValue(const float& v) {
        ASSERT(m_eVarType == AVARTYPE_FLOAT);
        m_fValue = v;
    }

    // Sets the actual stored value, without affecting the goal
    void setValue(const CColor& v) {
        ASSERT(m_eVarType == AVARTYPE_COLOR);
        m_cValue = v;
    }

    // Sets the actual value and goal
    void setValueAndWarp(const Vector2D& v) {
        ASSERT(m_eVarType == AVARTYPE_VECTOR);
        m_vGoal = v;
        warp();
    }

    // Sets the actual value and goal
    void setValueAndWarp(const float& v) {
        ASSERT(m_eVarType == AVARTYPE_FLOAT);
        m_fGoal = v;
        warp();
    }

    // Sets the actual value and goal
    void setValueAndWarp(const CColor& v) {
        ASSERT(m_eVarType == AVARTYPE_COLOR);
        m_cGoal = v;
        warp();
    }

private:

    void warp() {
        switch (m_eVarType) {
            case AVARTYPE_FLOAT: {
                m_fValue = m_fGoal;
                break;
            }
            case AVARTYPE_VECTOR: {
                m_vValue = m_vGoal;
                break;
            }
            case AVARTYPE_COLOR: {
                m_cValue = m_cGoal;
                break;
            }
            default:
                break;
        }
    }

    Vector2D        m_vValue = Vector2D(0,0);
    float           m_fValue = 0;
    CColor          m_cValue;

    Vector2D        m_vGoal = Vector2D(0,0);
    float           m_fGoal = 0;
    CColor          m_cGoal;

    float*          m_pSpeed = nullptr;
    int64_t*        m_pEnabled = nullptr;
    void*           m_pWindow = nullptr;

    bool            m_bDummy = true;

    ANIMATEDVARTYPE m_eVarType = AVARTYPE_INVALID;

    friend class CAnimationManager;
};