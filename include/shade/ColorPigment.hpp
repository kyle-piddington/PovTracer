#ifndef __ColorPigment_H__
#define __ColorPigment_H__
#include "shade/IPigment.hpp"
/**
 * A ColorPigment 
 */
class ColorPigment : public IPigment
{
public:
   ColorPigment(const Color4 & color);
   ColorPigment(const Color3 & color);
   virtual Color4 getColor(const Hit & hit) const;
private:
   Color4 thisColor;
};
#endif