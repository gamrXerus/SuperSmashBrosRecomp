#if 0
#include "patches.h"

int dummyData = 1;
int dummyBss;
int logFirstDma = 0;

#include <ssb_types.h>
#include <PR/os.h>
#include <PR/ultratypes.h>

// loadovl.h? or a generic overlay header?
// all ends are exclusive (start..end)
typedef struct SYOverlay
{
    uintptr_t rom_start;
    uintptr_t rom_end;
    uintptr_t ram_load_start;
    uintptr_t ram_text_start;
    uintptr_t ram_text_end;
    uintptr_t ram_data_start;
    uintptr_t ram_data_end;
    uintptr_t ram_noload_start;
    uintptr_t ram_noload_end;

} SYOverlay;

typedef struct SYHuffmanNode
{
    struct SYHuffmanNode *left;
    struct SYHuffmanNode *right;
    s32 value;

} SYHuffmanNode;

extern OSPiHandle *gSYDmaRomPiHandle;

extern void syDmaCreateMesgQueue(void);
extern void syDmaCopy(OSPiHandle *handle, uintptr_t phys_addr, uintptr_t virtual, size_t size, u8 direction);
extern void syDmaLoadOverlay(struct SYOverlay *ovl);
extern void syDmaReadRom(uintptr_t rom_src, void *ram_src, size_t size);
extern void syDmaWriteRom(void *ram_src, uintptr_t rom_dst, size_t size);
extern OSPiHandle* syDmaSramPiInit(void);
extern void syDmaReadSram(uintptr_t rom_src, void *ram_dst, size_t size);
extern void syDmaWriteSram(void *ram_src, uintptr_t rom_dst, size_t size);
extern void syDmaDecodeVpk0(u16* data, size_t size, void (*update_stream)(void), u8* out_buf);
extern void syDmaInitVpk0Stream(uintptr_t dev_addr, void *ram_addr, size_t size);
extern void syDmaFillVpk0Buf(void);
extern void syDmaReadVpk0Buf(uintptr_t dev_addr, void *ram_dst, void *ram_addr, size_t size);
extern void syDmaReadVpk0(uintptr_t dev_addr, void *ram_dst);

RECOMP_PATCH void syDmaReadRom(uintptr_t rom_src, void *ram_dst, size_t size) {
    //log first dma that occurs as an example patch
    if (logFirstDma == 0) {
        logFirstDma = 1;
        recomp_printf("syDmaReadRom; rom:%x, ram:%x, size:%d\n", rom_src, ram_dst, size);
    }
    
    syDmaCopy(gSYDmaRomPiHandle, rom_src, (uintptr_t)ram_dst, size, 0);
}
    #else
    int dummyData = 1;
int dummyBss;
int logFirstDma = 0;
void dummyfunc(void) {
    return;
}
    #endif
