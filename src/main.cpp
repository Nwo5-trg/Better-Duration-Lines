#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include "lines/DurationLines.hpp"
#include "Variables.hpp"

using namespace geode::prelude;

class $modify(LevelEditorLayer) {
    bool init(GJGameLevel* p0, bool p1) {	
		if (!LevelEditorLayer::init(p0, p1)) return false;
        
        Variables::durationDraw = nullptr;
        Variables::durationDrawChromaNode = nullptr;

        Variables::updateSettings();

        GameManager::sharedState()->setGameVariable("0058", Variables::disableMod); // hide default 

        auto layer = CCLayer::create();
        layer->setPosition(0.0f, 0.0f);
        layer->setZOrder(-1500);
        layer->setID("better-duration-lines-layer");
        m_objectLayer->addChild(layer);
        
        auto draw = CCDrawNode::create();
        draw->setPosition(0.0f, 0.0f);
        draw->setBlendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA});
        layer->addChild(draw);
        Variables::durationDraw = draw;

        { // silly stuff
            auto gayNode = CCNodeRGBA::create();
            Variables::durationDraw->addChild(gayNode);
            Variables::durationDrawChromaNode = gayNode;
            auto rgbtqiaplus16mcolultra4khd = CCRepeatForever::create(CCSequence::create( // we on that sillydoggo naming shit yeahhhh
            CCTintTo::create(Variables::sayoDeviceSensitivity, 255, 128, 128), CCTintTo::create(Variables::sayoDeviceSensitivity, 255, 255, 128),
            CCTintTo::create(Variables::sayoDeviceSensitivity, 128, 255, 128), CCTintTo::create(Variables::sayoDeviceSensitivity, 128, 255, 255),
            CCTintTo::create(Variables::sayoDeviceSensitivity, 128, 128, 255), CCTintTo::create(Variables::sayoDeviceSensitivity, 255, 128, 255),
            nullptr));
            gayNode->runAction(rgbtqiaplus16mcolultra4khd);
        }
        
        return true;
    }

    void updateDebugDraw() {
        LevelEditorLayer::updateDebugDraw();
        if (Variables::durationDraw) updateIndicators();
    }
};