#include "Utils.hpp"
#include "Variables.hpp"

using namespace geode::prelude;

ccColor4F getTriggerCol(int id) {
    ccColor4F col = {};
    
    if (Variables::chroma && Variables::durationDrawChromaNode) {
        col = ccc4FFromccc3B(Variables::durationDrawChromaNode->getColor());
    }
    else if (Variables::mode == DurationMode::Light) col = Variables::lineColor;
    else if (colorMap.contains(id)) col = colorMap.at(id);
    else col = {1.0f, 1.0f, 1.0f, 1.0f};

    col.a = Variables::lineOpacity;
    return col;
}

float getLineDistance(float start, float duration) {
    if (duration == 0.0f) return 0.0f;
    
    float distance = 0.0f;
    float timeLeft = duration;
    float x = start;

    auto it = std::lower_bound( // oo did not know this existed, prolly faster than whatever shit i wouldve done
        Variables::speeds.begin(), Variables::speeds.end(), start,
        [] (const std::pair<float, float>& pair, float value) {return pair.first < value;}
    );
    int currentSpeedIndex = it == Variables::speeds.begin() ? 0 : (int)(it - Variables::speeds.begin() - 1);

    int speedPortalCount = Variables::speeds.size();
    while (timeLeft > 0.0f && currentSpeedIndex < speedPortalCount) {
        float speed = Variables::speeds[currentSpeedIndex].second;

        float nextSpeedX = (currentSpeedIndex + 1) < speedPortalCount ? Variables::speeds[currentSpeedIndex + 1].first : FLT_MAX;
        float nextSpeedDistance = nextSpeedX - x;
        float timeUntilNextSpeed = nextSpeedDistance / speed;

        if (timeUntilNextSpeed < timeLeft) {
            distance += nextSpeedDistance;
            timeLeft -= timeUntilNextSpeed;
            x = nextSpeedX;
            currentSpeedIndex++;
        } else {
            distance += speed * timeLeft;
            break;
        }
    }

    return distance;
}

float getStartOpacity(float alphaTriggerX, int group) {
    auto objs = LevelEditorLayer::get()->m_alphaTriggers;
    float closestPos = -FLT_MAX;
    EffectGameObject* closestObj = nullptr;
    for (auto obj : CCArrayExt<EffectGameObject*>(objs)) {
        if (obj->m_targetGroupID != group) continue;
        auto objPosX = obj->getPositionX();
        if (objPosX > closestPos && objPosX < alphaTriggerX) {
            closestPos = objPosX;
            closestObj = obj;
        }
    }
    if (closestObj) return closestObj->m_opacity;
    return 1.0f;
}

ccColor4F getStartColor(float colorTriggerX, int channel) {
    auto editor = LevelEditorLayer::get();
    auto objs = editor->m_colorTriggers;
    float closestPos = -FLT_MAX;
    EffectGameObject* closestObj = nullptr;
    for (auto obj : CCArrayExt<EffectGameObject*>(objs)) {
        if (obj->m_targetGroupID != channel) continue;
        auto objPosX = obj->getPositionX();
        if (objPosX > closestPos && objPosX < colorTriggerX) {
            closestPos = objPosX;
            closestObj = obj;
        }
    }
    if (closestObj) {
        auto col = ccc4FFromccc3B(closestObj->m_triggerTargetColor);
        col.a = closestObj->m_opacity;
        return col;
    }
    // no clue why fromcolor works and color doesnt but wtv
    auto action = editor->m_effectManager->getColorAction(channel);
    auto col = ccc4FFromccc3B(action->m_fromColor);
    col.a = action->m_fromOpacity;
    return col;
}

ccColor4F interpolateColor(const ccColor4F& start, const ccColor4F& end, float time) {
    return {
        start.r + (end.r - start.r) * time,
        start.g + (end.g - start.g) * time,
        start.b + (end.b - start.b) * time,
        start.a + (end.a - start.a) * time
    };
}

std::unordered_set<int> parseIntArray(const std::string& input) {
    std::unordered_set<int> intSet;
    auto start = 0;
    while (true) {
        auto comma = input.find(',', start);
        auto num = std::strtol(input.substr(start, comma - start).c_str(), nullptr, 10);
        if (num != 0) intSet.insert(num);
        if (comma == std::string::npos) break;
        start = comma + 1;
    }
    return intSet;
}