#include "../STD_TYPES.h"
#include "Mapping.h"

sint32 s32Map(sint32 Copy_s32InputRangeMin, sint32 Copy_s32InputRangeMax, sint32 Copy_s32OutputRangeMin, sint32 Copy_s32OutputRangeMax,sint32 Copy_s32InputValue)
{
	sint32 Local_s32OutputValue;

	Local_s32OutputValue=(((Copy_s32OutputRangeMax-Copy_s32OutputRangeMin)*(Copy_s32InputValue-Copy_s32InputRangeMin))/(Copy_s32InputRangeMax-Copy_s32InputRangeMin))+Copy_s32OutputRangeMin;

	return Local_s32OutputValue;
}

