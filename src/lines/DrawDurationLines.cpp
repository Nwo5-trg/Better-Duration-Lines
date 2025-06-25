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
            drawDurationLine(objPos, getLineDistance(objPos.x, duration), getTriggerCol(id, false));
            break;
        }
        case DurationTriggerType::Pulse: { // could i save like 3 additions or smth, yes, is it worth it, prolly ont
            float fade = getLineDistance(objPos.x, obj->m_fadeInDuration);
            float hold = getLineDistance(objPos.x + fade, obj->m_holdDuration);
            float out = getLineDistance(objPos.x + fade + hold, obj->m_fadeOutDuration);
            drawDurationLine({objPos.x + fade + hold, objPos.y}, out, getColWithAlpha(Variables::pulseColor3, true)); // flipped cuz it fixes a bug im too lazy to fix otherwise
            drawDurationLine({objPos.x + fade, objPos.y}, hold, getColWithAlpha(Variables::pulseColor2, true));
            drawDurationLine(objPos, fade, getColWithAlpha(Variables::pulseColor1, true));
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
                    col = getTriggerCol(id, true);
                    col.a *= alpha;
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
                    auto triggerCol = getTriggerCol(id, true);
                    triggerCol.a *= col.a;
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
                drawDurationLine(objPos, getLineDistance(objPos.x, time), getTriggerCol(id, false));
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
            drawDurationLine({objPos.x + fade + soundDuration, objPos.y}, out, getColWithAlpha(Variables::sfxColor3, true));
            drawDurationLine({objPos.x + fade, objPos.y}, soundDuration, getColWithAlpha(Variables::sfxColor2, true));
            drawDurationLine(objPos, fade, getColWithAlpha(Variables::sfxColor1, true));
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