#include "DurationLines.hpp"
#include "DrawDurationLines.hpp"
#include "../Variables.hpp"
#include "../Utils.hpp"

using namespace geode::prelude;

void updateIndicators() {
    auto editor = LevelEditorLayer::get();
    
    Variables::durationDraw->clear();

    if (Variables::disableMod) return;

    auto batchLayer = editor->m_objectLayer;
    auto batchLayerPos = editor->m_objectLayer->getPosition();
    float zoom = batchLayer->getScale();
    float currentLayer = editor->m_currentLayer;

    Variables::zoom = Variables::scaleWithZoom ? std::min(Variables::zoomClamp, zoom) : 1.0f;
    Variables::halfLineThickness = (Variables::lineThickness / 2) / Variables::zoom;

    auto winSize = CCDirector::get()->getWinSize();
    auto centerPos = ccp(((winSize.width / 2) - batchLayerPos.x) / zoom, ((winSize.height / 2) - batchLayerPos.y) / zoom);

    Variables::speeds.clear();
    Variables::speeds.emplace_back(-FLT_MAX, speedEnumMap.at(editor->m_levelSettings->m_startSpeed));
    auto speedObjs = editor->m_drawGridLayer->m_speedObjects;
    for (auto obj : CCArrayExt<GameObject*>(speedObjs)) {
        auto id = obj->m_objectID;
        if (!speedIDMap.contains(id)) continue;
        Variables::speeds.emplace_back(obj->getPositionX(), speedIDMap.at(id));
    }
    std::sort( // i thiiiink it should be sorted by default but im not risking it
        Variables::speeds.begin(), Variables::speeds.end(),
        [](const auto& pair1, const auto& pair2) {return pair1.first < pair2.first;}
    );

    auto objs = editor->m_drawGridLayer->m_effectGameObjects;
    for (auto obj : CCArrayExt<EffectGameObject*>(objs)) {
        int id = obj->m_objectID;
        float duration = obj->m_duration;
        if (!maxTriggerTypeMap.contains(id) || Variables::triggerBlacklist.contains(id)) continue;
        if (maxTriggerTypeMap.contains(id) && maxTriggerTypeMap.at(id) == DurationTriggerType::Generic) {
            if (obj->m_duration == 0) continue;
            if (duration < 10.0f) {
                float cullDistance = winSize.width + duration * 350; // cuz getting the distance just for culling is kinda dumb this is a *rough* estimate
                cullDistance *= cullDistance;
                if (ccpDistanceSQ(centerPos, obj->getPosition()) > cullDistance / zoom) continue;
            }
        }

        Variables::currentLayerMultiplier = 1.0f;
        if (currentLayer != -1) Variables::currentLayerMultiplier = (obj->m_editorLayer == currentLayer) || (obj->m_editorLayer2 == currentLayer) ? 1.0f : 0.5f;
        drawDurationLineForTrigger(obj);
    }
    log::error("loop ran, {} objects", objs->count());
    log::error("--------------------------------------------------");
};