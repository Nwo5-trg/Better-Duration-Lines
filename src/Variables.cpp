#include "Variables.hpp"
#include "Utils.hpp"

using namespace geode::prelude;
using namespace Variables;

ccColor4F getColor(Mod* mod, const std::string& settingName) {
    auto col = ccc4FFromccc3B(mod->getSettingValue<ccColor3B>(settingName));
    return col;
}

void Variables::updateSettings() { // kinda randomly sorted but its an organised mess so good enough
    auto mod = Mod::get();

    disableMod = mod->getSettingValue<bool>("disable-mod");
    scaleWithZoom = mod->getSettingValue<bool>("scale-with-zoom");

    gradientsSteps = mod->getSettingValue<int64_t>("gradients-steps");

    lineThickness = mod->getSettingValue<double>("line-thickness");
    lineOpacity = mod->getSettingValue<double>("line-opacity");

    lineColor = getColor(mod, "line-color");
    pulseColor1 = getColor(mod, "pulse-color-one");
    pulseColor2 = getColor(mod, "pulse-color-two");
    pulseColor3 = getColor(mod, "pulse-color-three");
    sfxColor1 = getColor(mod, "sfx-color-one");
    sfxColor2 = getColor(mod, "sfx-color-two");
    sfxColor3 = getColor(mod, "sfx-color-three");
    
    auto modeString = mod->getSettingValue<std::string>("mode");
    if (modeString == "Max") mode = DurationMode::Max;
    else if (modeString == "Full") mode = DurationMode::Full;
    else mode = DurationMode::Light;

    triggerBlacklist = parseIntArray(mod->getSettingValue<std::string>("trigger-blacklist"));

    chroma = mod->getSettingValue<bool>("chroma");
    chromaOverride = chroma ? mod->getSettingValue<bool>("chroma-override") : false;
    sayoDeviceSensitivity = mod->getSettingValue<double>("sayo-device-sensitivity");
}