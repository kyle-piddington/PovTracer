#ifndef __POVSTATES_H__
#define __POVSTATES_H__
#include "BaseState.hpp"
#include "CameraState.hpp"
#include "EndState.hpp"
#include "PigmentState.hpp"
#include "FinishState.hpp"
#include "SphereState.hpp"
#include "PlaneState.hpp"
#include "ObjectModifierState.hpp"
#include "LightState.hpp"
#include "TriangleState.hpp"
#include "BoxState.hpp"
#include "scene/Scene.hpp"

struct PovStates
{
   static BaseState baseState;
   static CameraState cameraState;
   static EndState endState;
   static PigmentState pigmentState;
   static FinishState finishState;
   static SphereState sphereState;
   static PlaneState planeState;
   static ObjectModifierState objectState;
   static LightState lightState;
   static TriangleState triangleState;
   static BoxState boxState;
   static void SetScene(std::shared_ptr<Scene> scenePtr);
};
#endif