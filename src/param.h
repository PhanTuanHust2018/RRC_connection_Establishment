#pragma once

#define RRC_CONNNECTED 0
#define RRC_INACTIVE 1
#define RRC_INDLE 2

#define NUMBER_UE 10

typedef struct UE
{
    int UE_ID;
    int state;
} UE;