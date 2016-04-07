#include "povray/povmodules/PovStates.hpp"
//Declarations of static states
BaseState PovStates::baseState;
CameraState PovStates::cameraState;
EndState PovStates::endState;
PigmentState PovStates::pigmentState;
FinishState PovStates::finishState;
SphereState PovStates::sphereState;
ObjectModifierState PovStates::objectState;


void PovStates::SetScene(std::shared_ptr<Scene> scenePtr)
{
   baseState.setScene(scenePtr);
   cameraState.setScene(scenePtr);
   endState.setScene(scenePtr);
   pigmentState.setScene(scenePtr);
   finishState.setScene(scenePtr);
   sphereState.setScene(scenePtr);
   objectState.setScene(scenePtr);
}