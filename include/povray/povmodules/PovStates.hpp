#ifndef __POVSTATES_H__
#define __POVSTATES_H__
#include "BaseState.hpp"
#include "CameraState.hpp"
#include "EndState.hpp"
struct PovStates
{
   static BaseState baseState;
   static CameraState cameraState;
   static EndState endState;
};
#endif