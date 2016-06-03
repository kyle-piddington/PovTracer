#pragma once
#include "shade/IPigment.hpp"
#include "base/Hit.hpp"
#include "shade/ISampleable.hpp"
class SamplerPigment : public IPigment
{
public:
   SamplerPigment(std::shared_ptr<ISampleable> samplable);
   virtual Color4 getColor(const Hit & hit) const override;
private:
   std::shared_ptr<ISampleable> samplable;
};