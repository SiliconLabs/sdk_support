
#ifndef __FW_GIT_INFO_H__
#define __FW_GIT_INFO_H__

//=============================================================================
//
//  WARNING: Auto-Generated Git Info Header  -  DO NOT EDIT
//
//=============================================================================

#include <stdint.h>
#include <stdbool.h>

//-----------------------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------------------

typedef enum
{
    GIT_TAG = 0,            // built from formal tag, pristine conditions
    GIT_DEV_BRANCH = 1,     // built from dev branch, not tagged and/or not
                            //   pristine conditions
    GIT_MASTER_BRANCH = 2   // built from master release branch, not tagged
                            //   and/or not pristine conditions
} GIT_INFO_LOCATION_e;

// Additional notes for details byte in FW_GIT_INFO_t:
//   DIRTY_FLAG: The combination of the index and the tracked files in the
//               working tree have changes with respect to HEAD.
//   LOCAL_COMMITS_FLAG: There are unpushed commits (ahead of the origin)
//   UNTRACKED_FILES_FLAG: Indicates untracked and not-ignored files found.

typedef struct
{
    uint32_t short_hash;  // first 32-bits of the git SHA-1 hash
    uint8_t  tag_major;   // tag major number    (<tag name>_major_minor_rev_build)
    uint8_t  tag_minor;   // tag minor number    (<tag name>_major_minor_rev_build)
    uint8_t  tag_rev;     // tag revision number (<tag name>_major_minor_rev_build)
    uint8_t  tag_build;   // tag revision number (<tag name>_major_minor_rev_build)
    uint8_t  details;     // (GIT_INFO_LOCATION_e << 4 |
                          //  UNTRACKED_FILES_FLAG << 2 |
                          //  LOCAL_COMMITS_FLAG << 1 | DIRTY_FLAG)
} FW_GIT_INFO_t;

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------

const FW_GIT_INFO_t rail_ver = {
    .short_hash = 0x3ed30b2bUL,
    .tag_major = 2,
    .tag_minor = 8,
    .tag_rev = 6,
    .tag_build = 0,
    .details = 0x00,
};

#endif  // __FW_GIT_INFO_H__

