#include "../../Library/STD_TYPES.h"
#include "../../Library/BIT_MATH.h"

#include "GIE_reg.h"
#include "GIE_interface.h"

void GIE_voidEnableGlobal(void)
{
	__asm volatile("SEI"); 		/*inline assembly instruction: Set I-bit*/
	
	/*SET_BIT(SREG,SREG_I)*/ 
}
void GIE_voidDisableGlobal(void)
{
	__asm volatile("CLI");		/*inline assembly instruction: Clear I-bit*/
	
	/*CLR_BIT(SREG,SREG_I);*/
}
