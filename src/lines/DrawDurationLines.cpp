#include "DrawDurationLines.hpp"
#include "../Variables.hpp"
#include "../Utils.hpp"

using namespace geode::prelude;

void drawDurationLineForTrigger(EffectGameObject* obj) {
    int id = obj->m_objectID;
    float duration = obj->m_duration;
    auto objPos = obj->getPosition();
    auto type = Variables::mode == DurationMode::Max ? maxTriggerTypeMap.at(id) : triggerTypeMap.at(id);
    switch (type) {
        case DurationTriggerType::Generic: {
            drawDurationLine(objPos, getLineDistance(objPos.x, duration), getTriggerCol(id));
            break;
        }
        case DurationTriggerType::Pulse: { // could i save like 3 additions or smth, yes, is it worth it, prolly ont
            float fade = getLineDistance(objPos.x, obj->m_fadeInDuration);
            float hold = getLineDistance(objPos.x + fade, obj->m_holdDuration);
            float out = getLineDistance(objPos.x + fade + hold, obj->m_fadeOutDuration);
            drawDurationLine(objPos, fade, Variables::pulseColor1);
            drawDurationLine({objPos.x + fade, objPos.y}, hold, Variables::pulseColor2);
            drawDurationLine({objPos.x + fade + hold, objPos.y}, out, Variables::pulseColor3);
            break;
        }
        case DurationTriggerType::Alpha: {
            float start = getStartOpacity(objPos.x, obj->m_targetGroupID);
            float end = obj->m_opacity;

            float segmentDuration = duration / Variables::gradientsSteps;
            float lastSegmentStart = objPos.x;
            for (int i = 0; i < Variables::gradientsSteps; i++) {
                float time = (float)i / (Variables::gradientsSteps - 1);
                float alpha = start + (end - start) * time;

                float segment = getLineDistance(lastSegmentStart, segmentDuration);
                ccColor4F col = {1.0f, 1.0f, 1.0f, alpha};
                if (Variables::chroma) {
                    col = getTriggerCol(id);
                    col.a = alpha;
                }
                drawDurationLine({lastSegmentStart, objPos.y}, segment, col);

                lastSegmentStart += segment;
            }
            break;
        }
        case DurationTriggerType::Color: {
            auto start = getStartColor(objPos.x, obj->m_targetGroupID);
            auto end = ccc4FFromccc3B(obj->m_triggerTargetColor);
            end.a = obj->m_opacity;

            float segmentDuration = duration / Variables::gradientsSteps;
            float lastSegmentStart = objPos.x;
            for (int i = 0; i < Variables::gradientsSteps; i++) {
                float time = (float)i / (Variables::gradientsSteps - 1); 
                auto col = interpolateColor(start, end, time);
                if (Variables::chromaOverride) {
                    auto triggerCol = getTriggerCol(id);
                    triggerCol.a = col.a;
                    col = triggerCol;
                }

                float segment = getLineDistance(lastSegmentStart, segmentDuration);
                drawDurationLine({lastSegmentStart, objPos.y}, segment, col);

                lastSegmentStart += segment;
            }
            break;
        }
        case DurationTriggerType::Time: {
            auto timer = static_cast<TimerTriggerGameObject*>(obj);
            if (timer->m_stopTimeEnabled) {
                float timeMod = timer->m_timeMod == 0 ? 0.001f : timer->m_timeMod;
                float time = fabs(timer->m_startTime - timer->m_targetTime) / timeMod;
                drawDurationLine(objPos, getLineDistance(objPos.x, time), getTriggerCol(id));
            }
            break;
        }
        case DurationTriggerType::Sound: {
            auto sfxTrigger = static_cast<SFXTriggerGameObject*>(obj);
            float soundDuration = sfxTrigger->m_soundDuration;
            if (sfxTrigger->m_start != 0) soundDuration -= sfxTrigger->m_start / 1000.0f;
            if (sfxTrigger->m_end != 0) soundDuration -= sfxTrigger->m_end / 1000.0f;
            float speed = powf(2.0f, sfxTrigger->m_speed / 12.0f);
            soundDuration *= speed;
            float fade = (sfxTrigger->m_fadeIn/ 1000.0f) * speed;
            float out = (sfxTrigger->m_fadeOut / 1000.0f) * speed;
            soundDuration -= fade + out;

            // kinda scuffed but i kinda like it
            fade = getLineDistance(objPos.x, fade);
            soundDuration = getLineDistance(objPos.x + fade, soundDuration);
            out = getLineDistance(objPos.x + fade + soundDuration, out);
            drawDurationLine(objPos, fade, Variables::sfxColor1);
            drawDurationLine({objPos.x + fade, objPos.y}, soundDuration, Variables::sfxColor2);
            drawDurationLine({objPos.x + fade + soundDuration, objPos.y}, out, Variables::sfxColor3);
            break;
        }
    }
};

void drawDurationLine(CCPoint pos, float distance, const ccColor4F& col) {
    float startX = pos.x + Variables::halfLineThickness;
    float endX = (pos.x + distance) - Variables::halfLineThickness;
    Variables::durationDraw->drawSegment({startX, pos.y}, {endX, pos.y}, Variables::halfLineThickness * 2, col);
}

// float rad = rotation * 0.017453;
// CCPoint endPos = {objPos.x + std::cosf(rad) * distance, objPos.y + std::sinf(rad) * distance};

// auto col = getTriggerCol(id);
// Variables::durationDraw->drawSegment(objPos, endPos, Variables::halfLineThickness * 2, col);