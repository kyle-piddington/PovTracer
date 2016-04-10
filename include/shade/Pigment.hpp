#ifndef __PIGMENT_H__
#define __PIGMENT_H__
class Pigment
{
   virtual Color getColor(const Hit & hit);
};
#endif