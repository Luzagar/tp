#include "d/dolzel.h" // IWYU pragma: keep

#include "gz/gz_menu_flags.h"
#include "gz/gz_menu_main.h"
#include "gz/gz_utility_draw.h"
#include "d/d_select_cursor.h"

// General flags
static gzBoolOption_s generalFlags[] = {
    {"boss flag", "sets the boss flag value", gzInfo_isFlag_BossFlag, gzInfo_onFlag_BossFlag,
     gzInfo_offFlag_BossFlag},
    {"coro td", "toggle temporary flag for coro text displacement", gzInfo_isTool_CoroTD,
     gzInfo_onTool_CoroTD, gzInfo_offTool_CoroTD},
    {"epona stolen", "toggle flag for epona being stolen", gzInfo_isFlag_EponaStolen,
     gzInfo_onFlag_EponaStolen, gzInfo_offFlag_EponaStolen},
    {"epona tamed", "toggle flag for epona being tamed", gzInfo_isFlag_EponaTamed, gzInfo_onFlag_EponaTamed,
     gzInfo_offFlag_EponaTamed},
    {"malo mart in castle town", "toggle flag for malo mart being open in castle town",
     gzInfo_isFlag_MaloMartCT, gzInfo_onFlag_MaloMartCT, gzInfo_offFlag_MaloMartCT},
    {"map warping", "toggle flag for map warping", gzInfo_isFlag_MapWarping, gzInfo_onFlag_MapWarping,
     gzInfo_offFlag_MapWarping},
    {"midna charge", "toggle flag for midna charge", gzInfo_isFlag_MidnaCharge, gzInfo_onFlag_MidnaCharge,
     gzInfo_offFlag_MidnaCharge},
    {"midna healed", "toggle flag for midna being healed", gzInfo_isFlag_MidnaHealthy,
     gzInfo_onFlag_MidnaHealthy, gzInfo_offFlag_MidnaHealthy},
    {"midna on back", "toggle flag for midna appearing on wolf link's back", gzInfo_isFlag_MidnaOnBack,
     gzInfo_onFlag_MidnaOnBack, gzInfo_offFlag_MidnaOnBack},
    {"midna available", "toggle flag for being able to call midna", gzInfo_isFlag_MidnaOnZ,
     gzInfo_onFlag_MidnaOnZ, gzInfo_offFlag_MidnaOnZ},
    {"rusl td", "toggle temporary flag for rusl text displacement", gzInfo_isFlag_RuslTD,
     gzInfo_onFlag_RuslTD, gzInfo_offFlag_RuslTD},
    {"transform/warp", "toggle flag for transforming/warping", gzInfo_isFlag_TransformWarp,
     gzInfo_onFlag_TransformWarp, gzInfo_offFlag_TransformWarp},
    {"wolf sense", "toggle flag for wolf sense", gzInfo_isFlag_WolfSense, gzInfo_onFlag_WolfSense,
     gzInfo_offFlag_WolfSense}
};

// Dungeon bool and int flags
static gzIntOption_s dungeonFlags[] = {
    {"have boss key", "Give selected dungeon boss key", gzInfo_isDungeonBossKey,
     gzInfo_onDungeonBossKey, gzInfo_offDungeonBossKey},
    {"have compass", "Give selected dungeon compass", gzInfo_isDungeonCompass,
     gzInfo_onDungeonCompass, gzInfo_offDungeonCompass},
    {"have heart container", "Give selected dungeon heart container",
     gzInfo_isDungeonHeartContainer, gzInfo_onDungeonHeartContainer,
     gzInfo_offDungeonHeartContainer},
    {"have map", "Give selected dungeon map", gzInfo_isDungeonMap, gzInfo_onDungeonMap,
     gzInfo_offDungeonMap},
    {"have ooccoo", "Give selected dungeon ooccoo", gzInfo_isDungeonOoccoo, gzInfo_onDungeonOoccoo,
     gzInfo_offDungeonOoccoo},
    {"boss defeated", "Selected dungeon boss is defeated", gzInfo_isBossDefeated,
     gzInfo_onBossDefeated, gzInfo_offBossDefeated},
    {"miniboss defeated", "Selected dungeon miniboss is defeated", gzInfo_isMiniBossDefeated,
     gzInfo_onMiniBossDefeated, gzInfo_offMiniBossDefeated},
};

// Portal warp bool flags
static gzBoolOption_s warpFlags[] = {
    {"ordon spring", "Ordon Spring warp portal", isSpringWarp, onSpringWarp, offSpringWarp},
    {"south faron", "South Faron warp portal", isSFaronWarp, onSFaronWarp, offSFaronWarp},
    {"north faron", "North Faron warp portal", isNFaronWarp, onNFaronWarp, offNFaronWarp},
    {"sacred grove", "Sacred Grove warp portal", isGroveWarp, onGroveWarp, offGroveWarp},
    {"eldin gorge", "Eldin Gorge warp portal", isGorgeWarp, onGorgeWarp, offGorgeWarp},
    {"kak village", "Kakariko Village warp portal", isKakarikoWarp, onKakarikoWarp,
     offKakarikoWarp},
    {"death mountain", "Death Mountain warp portal", isMountainWarp, onMountainWarp,
     offMountainWarp},
    {"eldin bridge", "Bridge of Eldin warp portal", isBridgeWarp, onBridgeWarp, offBridgeWarp},
    {"castle town", "Castle Town warp portal", isTownWarp, onTownWarp, offTownWarp},
    {"lake hylia", "Lake Hylia warp portal", isLakeWarp, onLakeWarp, offLakeWarp},
    {"domain warp", "Zora's Domain warp portal", isDomainWarp, onDomainWarp, offDomainWarp},
    {"upper river", "Upper Zora's River warp portal", isUzrWarp, onUzrWarp, offUzrWarp},
    {"snowpeak", "Snowpeak warp portal", isSnowpeakWarp, onSnowpeakWarp, offSnowpeakWarp},
    {"gerudo mesa", "Gerudo Mesa warp portal", isMesaWarp, onMesaWarp, offMesaWarp},
    {"mirror chamber", "Mirror Chamber warp portal", isMirrorWarp, onMirrorWarp, offMirrorWarp}};

// Rupee bool flags
static gzBoolOption_s rupeeFlags[] = {
    {"fundraising 1", "Toggle flag for first fundraising being complete", isFundraising1, onFundraising1, offFundraising1},
    {"fundraising 2", "Toggle flag for second fundraising being complete", isFundraising2, onFundraising2, offFundraising2},
    {"rupee cutscenes", "Toggle rupee cutscenes being enabled", isRupeeCS, onRupeeCS, offRupeeCS}};

// Dungeon and region names
static const char* dungeonNames[] = {"Forest Temple",     "Goron Mines",        "Lakebed Temple",
                                     "Arbiter's Grounds", "Snowpeak Ruins",     "Temple of Time",
                                     "City in the Sky",   "Palace of Twilight", "Hyrule Castle"};

static const char* regionNames[] = {"ordon", "faron", "eldin", "lanayru", "desert", "snowpeak"};

// Static member definitions
int gzFlagsMenu_c::sSelectedDungeon = 0;
int gzFlagsMenu_c::sSelectedRegion = 0;

u32 gzFlagsMenu_c::nextDungeon() {
    sSelectedDungeon = (sSelectedDungeon + 1) % NUM_DUNGEONS;
    return sSelectedDungeon;
}

u32 gzFlagsMenu_c::prevDungeon() {
    sSelectedDungeon = (sSelectedDungeon - 1 + NUM_DUNGEONS) % NUM_DUNGEONS;
    return sSelectedDungeon;
}

u32 gzFlagsMenu_c::nextRegion() {
    sSelectedRegion = (sSelectedRegion + 1) % NUM_REGIONS;
    return sSelectedRegion;
}

u32 gzFlagsMenu_c::prevRegion() {
    sSelectedRegion = (sSelectedRegion - 1 + NUM_REGIONS) % NUM_REGIONS;
    return sSelectedRegion;
}

u32 gzFlagsMenu_c::addSmallKey() {
    int stageNo = getSelectedDungeonStageNo();
    u8 keys = getDungeonSmallKeys(stageNo);
    if (keys < 255) {
        setDungeonSmallKeys(stageNo, keys + 1);
    }
    return getDungeonSmallKeys(stageNo);
}

u32 gzFlagsMenu_c::removeSmallKey() {
    int stageNo = getSelectedDungeonStageNo();
    u8 keys = getDungeonSmallKeys(stageNo);
    if (keys > 0) {
        setDungeonSmallKeys(stageNo, keys - 1);
    }
    return getDungeonSmallKeys(stageNo);
}

gzFlagsMenu_c::gzFlagsMenu_c() {
    OSReport("creating gzFlagsMenu_c\n");
    mXPos = g_gzInfo.mBackgroundXPos + 170.0f;

    for (int i = 0; i < TAB_MAX_e; i++) {
        mpTabHeaders[i] = gzTextBox_allocate();
        mpTabHeaders[i]->setFontSize(15.0f, 15.0f);
    }
    mpTabHeaders[TAB_GENERAL]->setString("general");
    mpTabHeaders[TAB_DUNGEON]->setString("dungeon");
    mpTabHeaders[TAB_PORTAL]->setString("portal");
    mpTabHeaders[TAB_RUPEE]->setString("rupee");

    // General tab - all gzBoolOptionLine
    for (int i = 0; i < G_FLAG_MAX; i++) {
        mpLinesGeneral[i] = new (gzHeap(GZ_GROUP_MENU), 4) gzBoolOptionLine(generalFlags[i].name, generalFlags[i].desc,
                                                  generalFlags[i].is, generalFlags[i].on, generalFlags[i].off);
    }

    // Dungeon tab
    mpLinesDungeon[D_FLAG_SELECT_DUNGEON] = new (gzHeap(GZ_GROUP_MENU), 4) gzListOptionLine("dungeon:", "Select dungeon to modify flags", nextDungeon, prevDungeon);
    mpLinesDungeon[D_FLAG_SMALL_KEY] = new (gzHeap(GZ_GROUP_MENU), 4) gzListOptionLine("small keys:", "Selected dungeon small keys", addSmallKey, removeSmallKey);
    for (int i = 0; i < 7; i++) {
        mpLinesDungeon[D_FLAG_BOSS_KEY + i] = new (gzHeap(GZ_GROUP_MENU), 4) gzBoolOptionLine(dungeonFlags[i].name, dungeonFlags[i].desc);
    }
    mpLinesDungeon[D_FLAG_CLEAR_DUNGEON] = new (gzHeap(GZ_GROUP_MENU), 4) gzLine("clear flags", "Clear all selected dungeon flags");

    // Portal tab
    mpLinesPortal[P_FLAG_SELECT_REGION] = new (gzHeap(GZ_GROUP_MENU), 4) gzListOptionLine("region:", "Select region to view flags", nextRegion, prevRegion);
    mpLinesPortal[P_FLAG_REGION] = new (gzHeap(GZ_GROUP_MENU), 4) gzBoolOptionLine("enabled:", "Toggle the selected region flag");
    for (int i = 0; i < 15; i++) {
        mpLinesPortal[P_FLAG_SPRING_WARP + i] = new (gzHeap(GZ_GROUP_MENU), 4) gzBoolOptionLine(warpFlags[i].name, warpFlags[i].desc,
                                                                      warpFlags[i].is, warpFlags[i].on, warpFlags[i].off);
    }

    // Rupee tab
    mpLinesRupee[R_FLAG_DONATION_AMT] = new (gzHeap(GZ_GROUP_MENU), 4) gzListOptionLine("donation amount:", "Sets the amount of rupees donated to Charlo");
    mpLinesRupee[R_FLAG_FUNDRAISING_AMT] = new (gzHeap(GZ_GROUP_MENU), 4) gzListOptionLine("fundraising amount:", "Sets the current fundraising amount");
    for (int i = 0; i < 3; i++) {
        mpLinesRupee[R_FLAG_FUNDRAISING_1 + i] = new (gzHeap(GZ_GROUP_MENU), 4) gzBoolOptionLine(rupeeFlags[i].name, rupeeFlags[i].desc,
                                                                       rupeeFlags[i].is, rupeeFlags[i].on, rupeeFlags[i].off);
    }

    mCurrentTab = TAB_GENERAL;
}

gzFlagsMenu_c::~gzFlagsMenu_c() {
    _delete();
}

void gzFlagsMenu_c::_delete() {
    OSReport("deleting gzFlagsMenu_c\n");
    for (int i = 0; i < TAB_MAX_e; i++) {
        gzTextBox_free(mpTabHeaders[i]);
        mpTabHeaders[i] = NULL;
    }
    for (int i = 0; i < G_FLAG_MAX; i++) {
        delete mpLinesGeneral[i];
        mpLinesGeneral[i] = NULL;
    }
    for (int i = 0; i < D_FLAG_MAX; i++) {
        delete mpLinesDungeon[i];
        mpLinesDungeon[i] = NULL;
    }
    for (int i = 0; i < P_FLAG_MAX; i++) {
        delete mpLinesPortal[i];
        mpLinesPortal[i] = NULL;
    }
    for (int i = 0; i < R_FLAG_MAX; i++) {
        delete mpLinesRupee[i];
        mpLinesRupee[i] = NULL;
    }
}

u8 gzFlagsMenu_c::getHaihaiFlags(int idx) {
    u8 haihai_flags = ARROW_LEFT | ARROW_RIGHT;

    switch (mCurrentTab) {
    case TAB_GENERAL:
        if (idx >= 0 && idx < G_FLAG_MAX) {
            if (generalFlags[idx].is()) {
                haihai_flags &= ~ARROW_RIGHT;
            } else {
                haihai_flags &= ~ARROW_LEFT;
            }
        }
        break;
    case TAB_DUNGEON:
        if (idx == D_FLAG_SELECT_DUNGEON || idx == D_FLAG_SMALL_KEY) {
            // List options - show both arrows
        } else if (idx == D_FLAG_CLEAR_DUNGEON) {
            haihai_flags = 0;
        } else if (idx >= D_FLAG_BOSS_KEY && idx <= D_FLAG_DEFEAT_MINIBOSS) {
            int bIdx = idx - D_FLAG_BOSS_KEY;
            if (bIdx >= 0 && bIdx < 7) {
                if (dungeonFlags[bIdx].is(sSelectedDungeon + 16)) {
                    haihai_flags &= ~ARROW_RIGHT;
                } else {
                    haihai_flags &= ~ARROW_LEFT;
                }
            }
        }
        break;
    case TAB_PORTAL:
        if (idx == P_FLAG_SELECT_REGION) {
            // List option - show both arrows
        } else if (idx == P_FLAG_REGION) {
            if (getRegionFlag(sSelectedRegion + 1)) {
                haihai_flags &= ~ARROW_RIGHT;
            } else {
                haihai_flags &= ~ARROW_LEFT;
            }
        } else if (idx >= P_FLAG_SPRING_WARP && idx < P_FLAG_MAX) {
            int wIdx = idx - P_FLAG_SPRING_WARP;
            if (wIdx >= 0 && wIdx < 15) {
                if (warpFlags[wIdx].is()) {
                    haihai_flags &= ~ARROW_RIGHT;
                } else {
                    haihai_flags &= ~ARROW_LEFT;
                }
            }
        }
        break;
    case TAB_RUPEE:
        if (idx == R_FLAG_DONATION_AMT || idx == R_FLAG_FUNDRAISING_AMT) {
            // List options - show both arrows
        } else if (idx >= R_FLAG_FUNDRAISING_1 && idx < R_FLAG_MAX) {
            int rIdx = idx - R_FLAG_FUNDRAISING_1;
            if (rIdx >= 0 && rIdx < 3) {
                if (rupeeFlags[rIdx].is()) {
                    haihai_flags &= ~ARROW_RIGHT;
                } else {
                    haihai_flags &= ~ARROW_LEFT;
                }
            }
        }
        break;
    }
    return haihai_flags;
}

int gzFlagsMenu_c::getCurrentLineNum() {
    switch (mCurrentTab) {
    case TAB_GENERAL:
        return G_FLAG_MAX;
    case TAB_DUNGEON:
        return D_FLAG_MAX;
    case TAB_PORTAL:
        return P_FLAG_MAX;
    case TAB_RUPEE:
        return R_FLAG_MAX;
    }
    return 0;
}

void gzFlagsMenu_c::updateDynamicLines() {
    gzLine** currentLines;
    int currentLineNum;
    switch (mCurrentTab) {
    case TAB_GENERAL:
        currentLines = mpLinesGeneral;
        currentLineNum = G_FLAG_MAX;
        for (int i = 0; i < G_FLAG_MAX; i++) {
            gzTextBox* opt = currentLines[i]->getOptionBox();
            if (opt) opt->setString("");
        }
        break;
    case TAB_DUNGEON:
        currentLines = mpLinesDungeon;
        currentLineNum = D_FLAG_MAX;
        {
            gzTextBox* dungeonOpt = currentLines[D_FLAG_SELECT_DUNGEON]->getOptionBox();
            if (dungeonOpt) dungeonOpt->setString(dungeonNames[sSelectedDungeon]);
            gzTextBox* smallKeyOpt = currentLines[D_FLAG_SMALL_KEY]->getOptionBox();
            if (smallKeyOpt) smallKeyOpt->setStringf("%d", getDungeonSmallKeys(getSelectedDungeonStageNo()));
        }
        for (int i = 0; i < 7; i++) {
            gzTextBox* opt = currentLines[D_FLAG_BOSS_KEY + i]->getOptionBox();
            if (opt) opt->setString("");
        }
        break;
    case TAB_PORTAL:
        currentLines = mpLinesPortal;
        currentLineNum = P_FLAG_MAX;
        {
            gzTextBox* regionOpt = currentLines[P_FLAG_SELECT_REGION]->getOptionBox();
            if (regionOpt) regionOpt->setString(regionNames[sSelectedRegion]);
            gzTextBox* regionEnabledOpt = currentLines[P_FLAG_REGION]->getOptionBox();
            if (regionEnabledOpt) regionEnabledOpt->setString("");
        }
        for (int i = 0; i < 15; i++) {
            gzTextBox* opt = currentLines[P_FLAG_SPRING_WARP + i]->getOptionBox();
            if (opt) opt->setString("");
        }
        break;
    case TAB_RUPEE:
        currentLines = mpLinesRupee;
        currentLineNum = R_FLAG_MAX;
        {
            gzTextBox* donationOpt = currentLines[R_FLAG_DONATION_AMT]->getOptionBox();
            if (donationOpt) donationOpt->setStringf("%d", getDonationAmt());
            gzTextBox* fundraisingOpt = currentLines[R_FLAG_FUNDRAISING_AMT]->getOptionBox();
            if (fundraisingOpt) fundraisingOpt->setStringf("%d", getFundraisingAmt());
        }
        for (int i = 0; i < 3; i++) {
            gzTextBox* opt = currentLines[R_FLAG_FUNDRAISING_1 + i]->getOptionBox();
            if (opt) opt->setString("");
        }
        break;
    default:
        return;
    }
    updateLineBounds((gzLine**)currentLines, currentLineNum);
}

void gzFlagsMenu_c::onHighlight() {
}

void gzFlagsMenu_c::onUnhighlight() {
}

bool gzFlagsMenu_c::isBoolFlagLine(int idx) {
    switch (mCurrentTab) {
    case TAB_GENERAL:
        return true;
    case TAB_DUNGEON:
        return idx >= D_FLAG_BOSS_KEY && idx <= D_FLAG_DEFEAT_MINIBOSS;
    case TAB_PORTAL:
        return idx >= P_FLAG_REGION;
    case TAB_RUPEE:
        return idx >= R_FLAG_FUNDRAISING_1;
    default:
        return false;
    }
}

bool gzFlagsMenu_c::getBoolFlagState(int idx) {
    switch (mCurrentTab) {
    case TAB_GENERAL:
        return generalFlags[idx].is();
    case TAB_DUNGEON:
        return dungeonFlags[idx - D_FLAG_BOSS_KEY].is(sSelectedDungeon + 16);
    case TAB_PORTAL:
        if (idx == P_FLAG_REGION) return getRegionFlag(sSelectedRegion + 1);
        return warpFlags[idx - P_FLAG_SPRING_WARP].is();
    case TAB_RUPEE:
        return rupeeFlags[idx - R_FLAG_FUNDRAISING_1].is();
    default:
        return false;
    }
}

void gzFlagsMenu_c::toggleBoolFlag(int idx) {
    switch (mCurrentTab) {
    case TAB_GENERAL:
        if (generalFlags[idx].is())
            generalFlags[idx].off();
        else
            generalFlags[idx].on();
        break;
    case TAB_DUNGEON: {
        int bIdx = idx - D_FLAG_BOSS_KEY;
        int dungeonIdx = sSelectedDungeon + 16;
        if (dungeonFlags[bIdx].is(dungeonIdx))
            dungeonFlags[bIdx].off(dungeonIdx);
        else
            dungeonFlags[bIdx].on(dungeonIdx);
        break;
    }
    case TAB_PORTAL:
        if (idx == P_FLAG_REGION) {
            setRegionFlag(sSelectedRegion + 1);
        } else {
            int wIdx = idx - P_FLAG_SPRING_WARP;
            if (warpFlags[wIdx].is())
                warpFlags[wIdx].off();
            else
                warpFlags[wIdx].on();
        }
        break;
    case TAB_RUPEE: {
        int rIdx = idx - R_FLAG_FUNDRAISING_1;
        if (rupeeFlags[rIdx].is())
            rupeeFlags[rIdx].off();
        else
            rupeeFlags[rIdx].on();
        break;
    }
    }
}

void gzFlagsMenu_c::setRegionFlag(int regionBit) {
    u8 region = g_dComIfG_gameInfo.info.getPlayer().getPlayerFieldLastStayInfo().getRegion();
    g_dComIfG_gameInfo.info.getPlayer().getPlayerFieldLastStayInfo().setRegion(region ^=
                                                                               (1 << regionBit));
}

bool gzFlagsMenu_c::getRegionFlag(int regionBit) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerFieldLastStayInfo().getRegion() &
           (1 << regionBit);
}

void gzFlagsMenu_c::execute() {
    if (checkInputWait()) return;
    if (handleBackButton(gzMainMenu_c::MENU_FLAGS)) return;

    gzCursor* l_cursor = gzInfo_getCursor();
    int maxLines = getCurrentLineNum();

    if (!gzInfo_isMenuOption()) {
        if (gzPad::getTrigR()) {
            mCurrentTab = (mCurrentTab + 1) % TAB_MAX_e;
            l_cursor->y = 0;
            gzInfo_resetTopLine();
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
        }
        if (gzPad::getTrigL()) {
            mCurrentTab = (mCurrentTab - 1 + TAB_MAX_e) % TAB_MAX_e;
            l_cursor->y = 0;
            gzInfo_resetTopLine();
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
        }
    } else {
        if (gzPad::getTrigR()) {
            switch (mCurrentTab) {
            case TAB_GENERAL:
                if (l_cursor->y < G_FLAG_MAX && !generalFlags[l_cursor->y].is()) {
                    generalFlags[l_cursor->y].on();
                    gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                }
                break;
            case TAB_DUNGEON:
                if (l_cursor->y == D_FLAG_SELECT_DUNGEON) {
                    nextDungeon();
                    gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                } else if (l_cursor->y == D_FLAG_SMALL_KEY) {
                    addSmallKey();
                    gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                } else if (l_cursor->y >= D_FLAG_BOSS_KEY && l_cursor->y <= D_FLAG_DEFEAT_MINIBOSS)
                {
                    int bIdx = l_cursor->y - D_FLAG_BOSS_KEY;
                    if (!dungeonFlags[bIdx].is(sSelectedDungeon + 16)) {
                        dungeonFlags[bIdx].on(sSelectedDungeon + 16);
                        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                    }
                }
                break;
            case TAB_PORTAL:
                if (l_cursor->y == P_FLAG_SELECT_REGION) {
                    nextRegion();
                    gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                } else if (l_cursor->y == P_FLAG_REGION) {
                    if (!getRegionFlag(sSelectedRegion + 1)) {
                        setRegionFlag(sSelectedRegion + 1);
                        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                    }
                } else if (l_cursor->y >= P_FLAG_SPRING_WARP && l_cursor->y < P_FLAG_MAX) {
                    int wIdx = l_cursor->y - P_FLAG_SPRING_WARP;
                    if (!warpFlags[wIdx].is()) {
                        warpFlags[wIdx].on();
                        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                    }
                }
                break;
            case TAB_RUPEE:
                if (l_cursor->y == R_FLAG_DONATION_AMT) {
                    u16 val = getDonationAmt();
                    if (val >= 1000) {
                        val = 0;
                    } else {
                        val = val + 1;
                    }
                    setDonationAmt(val);
                    gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                } else if (l_cursor->y == R_FLAG_FUNDRAISING_AMT) {
                    u16 val = getFundraisingAmt();
                    if (val >= 2000) {
                        val = 0;
                    } else {
                        val = val + 1;
                    }
                    setFundraisingAmt(val);
                    gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                } else if (l_cursor->y >= R_FLAG_FUNDRAISING_1 && l_cursor->y < R_FLAG_MAX) {
                    int rIdx = l_cursor->y - R_FLAG_FUNDRAISING_1;
                    if (!rupeeFlags[rIdx].is()) {
                        rupeeFlags[rIdx].on();
                        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                    }
                }
                break;
            }
        }
        if (gzPad::getTrigL()) {
            switch (mCurrentTab) {
            case TAB_GENERAL:
                if (l_cursor->y < G_FLAG_MAX && generalFlags[l_cursor->y].is()) {
                    generalFlags[l_cursor->y].off();
                    gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                }
                break;
            case TAB_DUNGEON:
                if (l_cursor->y == D_FLAG_SELECT_DUNGEON) {
                    prevDungeon();
                    gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                } else if (l_cursor->y == D_FLAG_SMALL_KEY) {
                    removeSmallKey();
                    gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                } else if (l_cursor->y >= D_FLAG_BOSS_KEY && l_cursor->y <= D_FLAG_DEFEAT_MINIBOSS)
                {
                    int bIdx = l_cursor->y - D_FLAG_BOSS_KEY;
                    if (dungeonFlags[bIdx].is(sSelectedDungeon + 16)) {
                        dungeonFlags[bIdx].off(sSelectedDungeon + 16);
                        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                    }
                }
                break;
            case TAB_PORTAL:
                if (l_cursor->y == P_FLAG_SELECT_REGION) {
                    prevRegion();
                    gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                } else if (l_cursor->y == P_FLAG_REGION) {
                    if (getRegionFlag(sSelectedRegion + 1)) {
                        setRegionFlag(sSelectedRegion + 1);
                        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                    }
                } else if (l_cursor->y >= P_FLAG_SPRING_WARP && l_cursor->y < P_FLAG_MAX) {
                    int wIdx = l_cursor->y - P_FLAG_SPRING_WARP;
                    if (warpFlags[wIdx].is()) {
                        warpFlags[wIdx].off();
                        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                    }
                }
                break;
            case TAB_RUPEE:
                if (l_cursor->y == R_FLAG_DONATION_AMT) {
                    u16 val = getDonationAmt();
                    if (val == 0) {
                        val = 1000;
                    } else {
                        val = val - 1;
                    }
                    setDonationAmt(val);
                    gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                } else if (l_cursor->y == R_FLAG_FUNDRAISING_AMT) {
                    u16 val = getFundraisingAmt();
                    if (val == 0) {
                        val = 2000;
                    } else {
                        val = val - 1;
                    }
                    setFundraisingAmt(val);
                    gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                } else if (l_cursor->y >= R_FLAG_FUNDRAISING_1 && l_cursor->y < R_FLAG_MAX) {
                    int rIdx = l_cursor->y - R_FLAG_FUNDRAISING_1;
                    if (rupeeFlags[rIdx].is()) {
                        rupeeFlags[rIdx].off();
                        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
                    }
                }
                break;
            }
        }
    }

    if (gzPad::getTrigA()) {
        if (mCurrentTab == TAB_DUNGEON && l_cursor->y == D_FLAG_CLEAR_DUNGEON) {
            int dungeonIdx = sSelectedDungeon + 16;

            for (int i = 0; i < 7; i++) {
                dungeonFlags[i].off(dungeonIdx);
            }

            setDungeonSmallKeys(dungeonIdx, 0);
            gzInfo_seStart(Z2SE_SY_CONTINUE_OK);
        } else if (isBoolFlagLine(l_cursor->y)) {
            toggleBoolFlag(l_cursor->y);
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
        } else {
            gzInfo_setMenuOption(!gzInfo_isMenuOption());
            if (gzInfo_isMenuOption()) {
                gzInfo_seStart(Z2SE_SY_TALK_CURSOR_OK);
            } else {
                gzInfo_seStart(Z2SE_SY_CURSOR_CANCEL);
            }
        }
    }

    handleNavigation(maxLines);
    finishExecute(maxLines);
}

void gzFlagsMenu_c::draw() {
    // Set up tab header x positions based on text width + padding
    static const f32 TAB_PADDING = 5.0f;
    f32 tabXPositions[TAB_MAX_e];
    f32 tabBaseX = mXPos;
    tabXPositions[0] = tabBaseX;
    for (int i = 1; i < TAB_MAX_e; i++) {
        mpTabHeaders[i - 1]->updateBounds();
        tabXPositions[i] = tabXPositions[i - 1] + mpTabHeaders[i - 1]->mBounds.f.x + TAB_PADDING;
    }

    updateDynamicLines();

    // Get current tab's lines
    gzLine** currentLines;
    int currentLineNum;
    switch (mCurrentTab) {
    case TAB_GENERAL:
        currentLines = mpLinesGeneral;
        currentLineNum = G_FLAG_MAX;
        break;
    case TAB_DUNGEON:
        currentLines = mpLinesDungeon;
        currentLineNum = D_FLAG_MAX;
        break;
    case TAB_PORTAL:
        currentLines = mpLinesPortal;
        currentLineNum = P_FLAG_MAX;
        break;
    case TAB_RUPEE:
        currentLines = mpLinesRupee;
        currentLineNum = R_FLAG_MAX;
        break;
    }

    // Draw tab headers
    f32 yHeader = g_gzInfo.mBackgroundYPos + gzMenuLayout::TAB_HEADER_Y_OFFSET;
    drawTabHeaders(mpTabHeaders, tabXPositions, TAB_MAX_e, mCurrentTab, yHeader, gzInfo_getCursorColor());

    static const f32 ICON_SIZE = 14.0f;
    static const u32 COLOR_DIM = 0x808080FFu;

    gzCursor* l_cursor = gzInfo_getCursor();
    u32 cursorColor = gzInfo_getCursorColor();
    f32 lineX = mXPos;
    f32 optionX = mXPos + getCurrentOptionsXOffset();
    f32 lineY_start = g_gzInfo.mBackgroundYPos + mLineYStart;
    s32 topLine = gzInfo_getTopLine();
    s32 endLine = topLine + gzMenuLayout::VISIBLE_LINES;
    if (endLine > currentLineNum) endLine = currentLineNum;

    if (currentLineNum > 0 && currentLines[0] != NULL) {
        J2DTextBox::TFontSize font_size;
        currentLines[0]->mText->getFontSize(font_size);
        mpHaihai->setScale(font_size.mSizeY * gzMenuLayout::HAIHAI_SCALE_FACTOR);
    }

    for (s32 i = topLine; i < endLine; i++) {
        gzLine* line = currentLines[i];
        if (line == NULL) continue;

        s32 screenIdx = i - topLine;
        f32 lineY = lineY_start + (screenIdx * gzMenuLayout::LINE_SPACING);
        bool isSelected = (l_cursor->y == i && gzInfo_isSubMenuVisible());
        bool isBool = isBoolFlagLine(i);
        bool isOn = isBool && getBoolFlagState(i);
        bool classicHL = isSelected && gzInfo_isCursorTypeClassic();
        u32 color = classicHL ? cursorColor : (isBool && !isOn ? COLOR_DIM : COLOR_WHITE);

        line->mText->draw(lineX, lineY, color);

        if (isBool) {
            ResTIMG* atlas = gzInfo_getIconAtlas();
            if (atlas != NULL) {
                f32 iconY = lineY - 17.0f + (gzMenuLayout::LINE_SPACING - ICON_SIZE) / 2.0f;
                GXColor iconColor = isOn ? (GXColor){76, 175, 80, 255}
                                         : (GXColor){244, 67, 54, 255};
                gzDrawAtlasIcon(atlas, gzMainMenu_c::MENU_FLAGS, 24,
                                gzMainMenu_c::LINE_NUM, optionX, iconY,
                                ICON_SIZE, ICON_SIZE, iconColor);
            }
        } else {
            gzTextBox* opt = line->getOptionBox();
            f32 haihaiX = optionX + gzMenuLayout::HAIHAI_X_OFFSET;
            if (opt != NULL) {
                haihaiX = optionX + (opt->mBounds.f.x / 2.0f) + gzMenuLayout::HAIHAI_X_OFFSET;
                opt->draw(optionX, lineY, color, HBIND_LEFT);

                if (isSelected && gzInfo_isMenuOption()) {
                    u8 flags = getHaihaiFlags(i);
                    if (flags != 0) {
                        f32 haihaiY = lineY + gzMenuLayout::HAIHAI_Y_OFFSET;
                        f32 haihaiWidth = opt->mBounds.f.x + gzMenuLayout::HAIHAI_EXTRA_SPACING;
                        gzSetup2DContext();
                        mpHaihai->drawHaihai(flags, haihaiX, haihaiY, haihaiWidth, 0.0f);
                    }
                }
            }
        }

        if (isSelected && gzInfo_isCursorTypeTP() && gzInfo_getTPCursor() != NULL) {
            line->mText->updateBounds();
            f32 totalWidth = line->mText->getWidth();
            f32 cursorX = lineX + (totalWidth / 2.0f) + gzMenuLayout::TP_CURSOR_X_OFFSET;
            f32 cursorY = lineY + (line->mText->getHeight() / 2.0f) + gzMenuLayout::TP_CURSOR_Y_OFFSET;
            gzInfo_getTPCursor()->setPos(cursorX, cursorY, (J2DPane*)line->mText, false);
            gzSetup2DContext();
            gzInfo_getTPCursor()->draw();
        }
    }

    if (l_cursor->y < currentLineNum && currentLines[l_cursor->y] != NULL) {
        drawDescription(currentLines[l_cursor->y]->m_description);
    }
}

gzTabInfo_s gzFlagsMenu_c::getTabInfo() {
    gzTabInfo_s info;
    info.hasTabs = true;
    info.currentTab = mCurrentTab;
    info.numTabs = TAB_MAX_e;

    // Calculate positions and widths based on text content
    static const f32 TAB_PADDING = 5.0f;
    f32 tabBaseX = mXPos;
    info.tabX[0] = tabBaseX;
    for (int i = 0; i < TAB_MAX_e; i++) {
        mpTabHeaders[i]->updateBounds();
        info.tabWidth[i] = mpTabHeaders[i]->mBounds.f.x;
        if (i < TAB_MAX_e - 1) {
            info.tabX[i + 1] = info.tabX[i] + info.tabWidth[i] + TAB_PADDING;
        }
    }

    return info;
}
