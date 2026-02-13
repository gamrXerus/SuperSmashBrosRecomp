#if 1
#include "patches.h"

int unlockAllDummyData = 1;
int unlockAllDummyBss;

extern void syAudioSetQuality(u8 quality);
extern void syVideoSetCenterOffsets(s16 h1, s16 h2, s16 v1, s16 v2);

extern u8 gSCManagerBackupData;

extern s32 lbBackupCreateChecksum(void *backup);
extern void lbBackupWrite(void);

enum {
    nGRKindInishie = 8
};

enum {
    nFTKindLuigi = 4,
    nFTKindCaptain = 7,
    nFTKindPurin = 10,
    nFTKindNess = 11
};

enum {
    nLBBackupUnlockLuigi = 0,
    nLBBackupUnlockNess,
    nLBBackupUnlockCaptain,
    nLBBackupUnlockPurin,
    nLBBackupUnlockInishie,
    nLBBackupUnlockSoundTest,
    nLBBackupUnlockItemSwitch
};

#define LBBACKUP_UNLOCK_MASK_ALL ((1 << (nLBBackupUnlockItemSwitch + 1)) - 1)

#define LBBACKUP_CHARACTER_MASK_UNLOCK ( \
    (1 << nFTKindNess) | \
    (1 << nFTKindPurin) | \
    (1 << nFTKindCaptain) | \
    (1 << nFTKindLuigi) \
)

#define LBBACKUP_GROUND_MASK_INISHIE (1 << nGRKindInishie)

RECOMP_PATCH void lbBackupApplyOptions(void) {
    u8 *backup = &gSCManagerBackupData;
    
    u8 *unlock_mask = backup + 1111;
    u16 *fighter_mask = (u16 *)(backup + 1112);
    u16 *ground_mask = (u16 *)(backup + 1404);
    s32 *checksum = (s32 *)(backup + 1412);
    
    *unlock_mask = LBBACKUP_UNLOCK_MASK_ALL;
    *fighter_mask = LBBACKUP_CHARACTER_MASK_UNLOCK;
    *ground_mask |= LBBACKUP_GROUND_MASK_INISHIE;
    
    *checksum = lbBackupCreateChecksum(backup);
    
    syAudioSetQuality(backup[1107]);
    syVideoSetCenterOffsets(*(s16 *)(backup + 1108), *(s16 *)(backup + 1108), *(s16 *)(backup + 1110), *(s16 *)(backup + 1110));
}
#else
int unlockAllDummyData = 1;
int unlockAllDummyBss;
void unlockAllDummyfunc(void) {
    return;
}
#endif