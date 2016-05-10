#ifndef __FINISH_H__
#define __FINISH_H__
#include "Precision.hpp"
/**
 * Contains information
 * on a material's finish.
 */
/**
 * ambient        0.1
   diffuse          0.6
   specular        0.0
   roughness      0.05
   reflection      0.0
   refraction      0.0
   ior                 1.0

 */
class Finish
{
public:
   /**
    * Getters/setters
    */
   Finish();
   void setAmbient(Amount amb);
   void setDiffuse(Amount diffuse);
   void setSpecular(Amount specular);
   void setRoughness(Amount roughness);
   void setReflection(Amount reflection);
   void setRefraction(Amount refraction);
   void setIor(Amount ior);

   Amount getAmbient() const;
   Amount getDiffuse() const;
   Amount getSpecular() const;
   Amount getRoughness() const;
   Amount getReflection() const;
   bool getRefraction() const;
   Amount getIor() const;

private:
   Amount ambient;
   Amount diffuse;
   Amount specular;
   Amount roughness;
   Amount reflection;
   Amount refraction;
   Amount ior;
};
#endif