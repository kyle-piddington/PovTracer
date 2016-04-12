#ifndef __POINTLIGHT_H__
#define __POINTLIGHT_H__
#include "Precision.hpp"
/**
 * A pointLight is an infinitley small light
 * used in basic raytracing to illumiante a scene.
 */
class PointLight 
{
public:
   /**
    * Construct pointlight at the origin, with
    * no color.
    */
   PointLight();
   /**
    * Construct a pointlight with an initial position
    * and color
    */
   PointLight(Vector3 position, Vector3 color);
   /**
    * Set the point light's position in the world
    * @param position the new position
    */
   void setPosition(const Vector3 & position);

   /**
    * Set the light's color.
    * Colors can be greater than 1.0
    * @param color the light color
    */
   void setColor(const Vector3 & color);

   /**
    * Retrieve the location of the light
    * @return the light's location
    */
   Vector3 getPosition() const;
   /**
    * Retrieve the color of the light
    * @return the light's color
    */
   Color4 getColor() const;

private:
   Vector3 position;
   Color4 color;

};
#endif