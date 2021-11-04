#include "company.hpp"

std::string Company::getVAT(void)
{
	return this->vat;
}

void Company::setVAT(std::string vat)
{
	this->vat = vat;
}

int Company::getVolumeDiscount(void)
{
	return this->volumeDiscount;
}

void Company::setVolumeDiscount(int volumeDiscount)
{
	this->volumeDiscount = volumeDiscount;
}
