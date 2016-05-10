#include "math/Transform.hpp"

Matrix4 Transform::createTranslationMatrix(const Vector3 & translation)
{
   Matrix4 tns = Matrix4::Identity();
   tns.block<3,1>(0,3) << translation;
   return tns;
}


Matrix4 Transform::createRotationMatirx(const Vector3 & rotation)
{
   Vector3 rotRads = (rotation/180.0)*M_PI;
   Matrix4 rot = Matrix4::Identity();
    //Apply X rotation
   if(fabs(rotRads.x()) > kEpsilon)
   {
      Matrix4 xRot = Matrix4::Identity();
      xRot.block<2,2>(1,1) << cos(rotRads.x()),-sin(rotRads.x()),
                              sin(rotRads.x()),cos(rotRads.x());
      rot = xRot;
   }


   if(fabs(rotRads.z()) > kEpsilon)
   {
      Matrix4 yRot = Matrix4::Identity();
      yRot.block<3,3>(0,0) << cos(rotRads.z()),0,sin(rotRads.z()),
                              0,1,0,
                              -sin(rotRads.z()),0,cos(rotRads.z());
      rot = yRot * rot;
   }

   if(fabs(rotRads.z()) > kEpsilon)
   {
      Matrix4 zRot = Matrix4::Identity();
      zRot.block<2,2>(0,0) << cos(rotRads.z()),-sin(rotRads.z()),
                              sin(rotRads.z()),cos(rotRads.z());
      rot = zRot * rot;
   }
   return rot;

}

Matrix4 Transform::createScaleMatrix(const Vector3 & scale)
{
   Matrix4 scl = Matrix4::Identity();
   scl(0,0) = scale.x();
   scl(1,1) = scale.y();
   scl(2,2) = scale.z();
   return scl;
}