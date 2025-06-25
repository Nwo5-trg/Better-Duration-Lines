#pragma once

enum class DurationMode {
    Max = 0,
    Full = 1,
    Light = 2
};

enum class DurationTriggerType {
    Generic = 0,
    Alpha = 1,
    Pulse = 2,
    Color = 3,
    Time = 4,
    Sound = 5
};

inline const std::unordered_map<int, DurationTriggerType> maxTriggerTypeMap = {
    {901, DurationTriggerType::Generic}, {1346, DurationTriggerType::Generic}, {2067, DurationTriggerType::Generic},
    {1347, DurationTriggerType::Generic}, {1814, DurationTriggerType::Generic}, {3012, DurationTriggerType::Generic},
    {3011, DurationTriggerType::Generic}, {3013, DurationTriggerType::Generic}, {3014, DurationTriggerType::Generic}, 
    {3015, DurationTriggerType::Generic}, {1913, DurationTriggerType::Generic}, {1914, DurationTriggerType::Generic},
    {1916, DurationTriggerType::Generic}, {2015, DurationTriggerType::Generic}, {3603, DurationTriggerType::Generic},
    {2999, DurationTriggerType::Generic}, {3606, DurationTriggerType::Generic},  {3612, DurationTriggerType::Generic},

    {1007, DurationTriggerType::Alpha},

    {1006, DurationTriggerType::Pulse},

    {899, DurationTriggerType::Color},

    // {3006, DurationTriggerType::Area}, {3007, DurationTriggerType::Area}, {3008, DurationTriggerType::Area}, 
    // {3009, DurationTriggerType::Area}, {3010, DurationTriggerType::Area},

    {3614, DurationTriggerType::Time},

    {3602, DurationTriggerType::Sound},
};

inline const std::unordered_map<int, DurationTriggerType> triggerTypeMap = {
    {901, DurationTriggerType::Generic}, {1346, DurationTriggerType::Generic}, {2067, DurationTriggerType::Generic},
    {1347, DurationTriggerType::Generic}, {1814, DurationTriggerType::Generic}, {3012, DurationTriggerType::Generic},
    {3011, DurationTriggerType::Generic}, {3013, DurationTriggerType::Generic}, {3014, DurationTriggerType::Generic}, 
    {3015, DurationTriggerType::Generic}, {1913, DurationTriggerType::Generic}, {1914, DurationTriggerType::Generic},
    {1916, DurationTriggerType::Generic}, {2015, DurationTriggerType::Generic}, {3603, DurationTriggerType::Generic},
    {2999, DurationTriggerType::Generic}, {3606, DurationTriggerType::Generic}, {3612, DurationTriggerType::Generic},
    {3006, DurationTriggerType::Generic}, {3007, DurationTriggerType::Generic}, {3008, DurationTriggerType::Generic}, 
    {3009, DurationTriggerType::Generic}, {3010, DurationTriggerType::Generic}, {3614, DurationTriggerType::Generic}, 
    {1007, DurationTriggerType::Generic}, {899, DurationTriggerType::Generic},

    {1006, DurationTriggerType::Pulse},

    {3602, DurationTriggerType::Sound}
};

inline const std::unordered_map<int, cocos2d::ccColor4F> colorMap = {
    {901, {1.0f, 0.0f, 1.0f, 1.0f}}, {1346, {0.498f, 0.498f, 1.0f, 1.0f}}, {2067, {0.247f, 0.749f, 1.0f, 1.0f}},
    {1347, {1.0f, 0.498f, 0.498f, 1.0f}}, {1814, {1.0f, 1.0f, 0.498f, 1.0f}}, {3012, {0.498f, 0.498f, 1.0f, 1.0f}},
    {3011, {1.0f, 0.0f, 1.0f, 1.0f}}, {3013, {0.247f, 0.749f, 1.0f, 1.0f}}, {3014, {0.0f, 1.0f, 1.0f, 1.0f}},
    {3015, {1.0f, 1.0f, 0.0f, 1.0f}}, {1913, {0.498f, 0.498f, 1.0f, 1.0f}}, {1914, {1.0f, 0.498f, 0.498f, 1.0f}},
    {2015, {1.0f, 1.0f, 0.0f, 1.0f}}, {3603, {1.0f, 1.0f, 1.0f, 1.0f}}, {2999, {1.0f, 0.498f, 1.0f, 1.0f}},
    {3606, {0.498f, 1.0f, 1.0f, 1.0f}}, {3612, {1.0f, 0.498f, 1.0f, 1.0f}}, {1007, {0.0f, 1.0f, 1.0f, 1.0f}}, 
    {1006, {1.0f, 1.0f, 0.0f, 1.0f}}, {899, {1.0f, 1.0f, 1.0f, 1.0f}/**/}, {3006, {1.0f, 0.0f, 1.0f, 1.0f}}, 
    {3007, {0.498f, 0.498f, 1.0f, 1.0f}}, {3008, {0.247f, 0.749f, 1.0f, 1.0f}}, {3009, {0.0f, 1.0f, 1.0f, 1.0f}}, 
    {3010, {1.0f, 1.0f, 0.0f, 1.0f}}, {3614, {1.0f, 1.0f, 1.0f, 1.0f}/**/}, {3602, {1.0f, 1.0f, 1.0f, 1.0f}}, 
    {1916, {1.0f, 1.0f, 1.0f, 1.0f}/**/}
};

inline const std::unordered_map<int, float> speedIDMap = {
    {200, 251.16f}, {201, 311.58f}, {202, 387.42f}, {203, 468.0f}, {1334, 576.0f}
};

inline const std::unordered_map<Speed, float> speedEnumMap = {
    {Speed::Slow, 251.16f}, {Speed::Normal, 311.58f}, {Speed::Fast, 387.42f}, {Speed::Faster, 468.0f}, {Speed::Fastest, 576.0f}
};

cocos2d::ccColor4F getTriggerCol(int id);

float getLineDistance(float start, float duration);
float getStartOpacity(float alphaTriggerX, int group);
cocos2d::ccColor4F getStartColor(float colorTriggerX, int channel);
cocos2d::ccColor4F interpolateColor(const cocos2d::ccColor4F& start, const cocos2d::ccColor4F& end, float time);

std::unordered_set<int> parseIntArray(const std::string& input);