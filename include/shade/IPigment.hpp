#ifndef __IPIGMENT_H__
#define __IPIGMENT_H__
#include "Precision.hpp"
#include "base/Hit.hpp"
/**
 * A Pigment defines the base color
 * of a shaded object. the pigment interface can be used
 * to take data from other 
 */
class IPigment
{
public:
   virtual Color4 getColor(const Hit & hit) const = 0;
};
#endif