#pragma once
#include <tp/d_stage.h>

#include <cstdint>

// Allows to transform data as bytes 1:1 from A<-->B and vice versa
template<typename A, typename B>
union typeTransform
{
    A a;
    B b;
};

namespace mod
{
    // Console state
    uint32_t lastInput;
    bool state = true;
    uint8_t delayCounter;

    uint8_t hashCounter;

    void main();
    // runs every frame
    void run();

    void onActorInit( libtp::tp::d_stage::dzxChunkTypeInfo* chunkTypeInfo );

    uint16_t fletcher16( uint8_t* data, int32_t count );

    void ( *fapGm_Execute_return )() = nullptr;
    void ( *actorCommonLayerInit_return )( void* mStatus_roomControl,
                                           libtp::tp::d_stage::dzxChunkTypeInfo* chunkTypeInfo,
                                           int32_t unk3,
                                           void* unk4 ) = nullptr;
    void ( *actorInit_return )( void* mStatus_roomControl,
                                libtp::tp::d_stage::dzxChunkTypeInfo* chunkTypeInfo,
                                int32_t unk3,
                                void* unk4 ) = nullptr;
    void ( *actorInit_always_return )( void* mStatus_roomControl,
                                       libtp::tp::d_stage::dzxChunkTypeInfo* chunkTypeInfo,
                                       int32_t unk3,
                                       void* unk4 ) = nullptr;
}     // namespace mod