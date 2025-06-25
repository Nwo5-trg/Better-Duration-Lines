#pragma once

enum class DurationMode;

namespace Variables {
    inline cocos2d::CCDrawNode* durationDraw = nullptr;
    inline cocos2d::CCLayer* batchLayer = nullptr;

    inline float zoom;
    inline float halfLineThickness;
    inline float currentLayerMultiplier;
    inline std::vector<std::pair<float, float>> speeds;

    inline bool disableMod;
    inline bool scaleWithZoom;

    inline int gradientsSteps;

    inline float lineThickness;
    inline float lineOpacity;

    inline cocos2d::ccColor4F lineColor;
    inline cocos2d::ccColor4F pulseColor1;
    inline cocos2d::ccColor4F pulseColor2;
    inline cocos2d::ccColor4F pulseColor3;
    inline cocos2d::ccColor4F sfxColor1;
    inline cocos2d::ccColor4F sfxColor2;
    inline cocos2d::ccColor4F sfxColor3;
    
    inline DurationMode mode;

    inline std::unordered_set<int> triggerBlacklist;

    // the silly zone
    inline bool chroma;
    inline bool chromaOverride;
    inline float sayoDeviceSensitivity;
    inline cocos2d::CCNodeRGBA* durationDrawChromaNode = nullptr;

    void updateSettings();
}