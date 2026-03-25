#ifndef UMBRA_GDB_H
#define UMBRA_GDB_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void umbra_gdb_trk_hook(void);
void umbra_gdb_auto_start(u16 port);
void umbra_gdb_poll(void);

#ifdef __cplusplus
}
#endif

#endif /* UMBRA_GDB_H */
