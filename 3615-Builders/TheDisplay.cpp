#include "TheDisplay.hpp"

void TheDisplay::show(uint16_t size, const uint8_t bytes[])
{

}

void TheDisplay::showPage(MINITEL_PAGE page)
{
	switch(page)
	{
		case PageResultat:
			show(PAGE_RESULTAT_SIZE, page_resultat);
			break;
	}
}

bool TheDisplay::isKeyPress()
{
	return true;
}