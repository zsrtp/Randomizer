#include "game_patch/game_patch.h"
#include "tp/d_a_alink.h"

namespace mod::game_patch
{
    void _03_increaseClimbSpeed()
    {
        // Adjust Link's climbing speeds
        libtp::tp::d_a_alink::ClimbVars* ClimbVars = &libtp::tp::d_a_alink::climbVars;
        libtp::tp::d_a_alink::WallMoveVars* WallMoveVars = &libtp::tp::d_a_alink::wallMoveVars;
        ClimbVars->ladderClimbInitSpeed = 1.8;
        ClimbVars->ladderReachTopClimbUpSpeed = 1.765;
        ClimbVars->ladderTopStartClimbDownSpeed = 1.8;
        ClimbVars->ladderBottomGetOffSpeed = 1.8;
        ClimbVars->ladderClimbSpeed = 1.575;
        ClimbVars->wallClimbHorizontalSpeed = 2.0;
        ClimbVars->wallClimbVerticalSpeed = 1.875;
        WallMoveVars->moveSidewaysStickNotHeld = 2.0;
        WallMoveVars->movesidewaysStickHeld = 2.0;
    }
} // namespace mod::game_patch