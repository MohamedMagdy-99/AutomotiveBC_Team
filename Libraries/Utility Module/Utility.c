/*****************************************************************************
* Module: Utility Module
* File Name: Utlity.c
* Description: Source file for Utility Module
* Author: Mohamed Magdy
* Date: 23-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "Utility.h"

#define A		65
#define B		66	
#define C		67
#define D		68
#define E		69
#define F		70
#define Initial_Value		0x00U
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/ 
static uint32_t power(uint8_t base, uint8_t power_val)
{
	uint8_t i;
	uint32_t result=1;
	if(power_val == 0) return 1;
	if(base == 0) return 0;
	for (i=0;i<power_val;i++)
	{
		result *= base;
	}
	return result;
}

void String_split(uint8_t *source, uint8_t *destination, uint8_t startIndex, uint8_t endIndex)
{
	uint8_t i=0;
	for (i=startIndex; i<endIndex; i++)
	{
		destination[i-startIndex] = source[i];
	}
}

uint16_t String_3ByteHexAddress_ToDecimal(uint8_t* u8_tempAddress)
{
	sint8_t u8_loopCounter = Initial_Value;
	
	for(u8_loopCounter = 2; u8_loopCounter >= 0; u8_loopCounter--)
	{
		if(u8_tempAddress[u8_loopCounter] >= 65 && u8_tempAddress[u8_loopCounter] <= 70)
		{
			switch(u8_tempAddress[u8_loopCounter])
			{
				case(A):
				{
					u8_tempAddress[u8_loopCounter] = 10;
					break;
				}
				case(B):
				{
					u8_tempAddress[u8_loopCounter] = 11;
					break;
				}
				case(C):
				{
					u8_tempAddress[u8_loopCounter] = 12;
					break;
				}
				case(D):
				{
					u8_tempAddress[u8_loopCounter] = 13;
					break;
				}
				case(E):
				{
					u8_tempAddress[u8_loopCounter] = 14;
					break;
				}
				case(F):
				{
					u8_tempAddress[u8_loopCounter] = 15;
					break;
				}
				default: break;
			}
		}
		else
		{
			u8_tempAddress[u8_loopCounter] -= 48;
		}
	}

	return ((u8_tempAddress[2]*1) + (u8_tempAddress[1]*16) + ( u8_tempAddress[0]*256));
}



void integerToString(uint16_t u16_Num, uint8_t *pu8_String, uint8_t u8_base)
{
	if(u8_base == DEC)
	{
		uint16_t i=Initial_Value, n=Initial_Value;
		
		n=u16_Num;
		
		for(i=Initial_Value;;i++)
		{
			n/=10;
			if(n==Initial_Value) break;
		}
		i++;
		pu8_String[i] = '\0';
		i--;
		while (u16_Num)
		{
			pu8_String[i--] = (u16_Num % 10) + '0';
			u16_Num /= 10;
		}
	}
	else if(u8_base == BIN)
	{

	}
	else if(u8_base == HEX)
	{

	}
}



uint32_t nPowerM(uint32_t n, uint32_t m)
{
	uint64_t result = 1;
	while(m != 0)
	{
		result  *= n;
		--m;
	}

	return result;
}



void stringToInteger(uint8_t* au8_string, uint32_t* u32_integer)
{
	uint32_t u32_loopCounter = Initial_Value;
	*u32_integer = Initial_Value;
	while(au8_string[u32_loopCounter]!= '\0')
	{
		u32_loopCounter++;
	}
	uint16_t numberOfchars = u32_loopCounter;
	uint16_t u16_power = numberOfchars;

	for(u32_loopCounter = 0; u32_loopCounter < numberOfchars; u32_loopCounter++)
	{
		*u32_integer += (au8_string[u32_loopCounter] - 48)* nPowerM(10,u16_power-1);
		--u16_power;

	}
}



uint8_t stringCmp(uint8_t * str1, uint8_t * str2)
{
	uint8_t u8_counter = Initial_Value;
	uint8_t u8_isEqual = TRUE;

	while(str1[u8_counter] != END_OF_STRING)
	{
		if(str1[u8_counter] != str2[u8_counter])
		{
			u8_isEqual = FALSE;
			u8_counter++;
			break;
		}
		u8_counter++;
	}
// 	if( str2[u8_counter] != END_OF_STRING )
// 	{
// 		u8_isEqual = FALSE;
// 	}
	return u8_isEqual;
}



void separateInteger(uint8_t* pau8_floatString, uint8_t* pau8_integerString, uint16_t u16_lengthToStop)
{
	uint16_t u16_loopCounter = Initial_Value;
	for(u16_loopCounter = Initial_Value; u16_loopCounter < u16_lengthToStop; u16_loopCounter++)
	{
		pau8_integerString[u16_loopCounter] = pau8_floatString[u16_loopCounter];
	}
	pau8_integerString[u16_lengthToStop] = END_OF_STRING;
}


void separateDecimal(uint8_t* pau8_floatString, uint8_t* pau8_decimalString, uint16_t u16_lengthToStart,  uint16_t u16_floatArraySize)
{
	uint16_t u16_loopCounter = Initial_Value;
	uint8_t u8_decimalLength = u16_floatArraySize-u16_lengthToStart;
	
	for(u16_loopCounter = Initial_Value; u16_loopCounter < u8_decimalLength; u16_loopCounter++)
	{
		pau8_decimalString[u16_loopCounter] = pau8_floatString[u16_lengthToStart-1];
		u16_lengthToStart++;
	}
	pau8_decimalString[u8_decimalLength] = END_OF_STRING;
}

uint8_t stringLength(uint8_t* string)
{
	uint8_t u8_loopIndex=0;
	while(string[u8_loopIndex] != '\0')
	{
		u8_loopIndex++;
	}
	return u8_loopIndex+1;
}

float32_t stringToFloat(uint8_t* string)
{
	uint8_t strLen = stringLength(string)-1;
	uint8_t u8_loopIndex=0;
	float32_t f32_digit = 1;
	float32_t f32_num = 0;
	for(u8_loopIndex=0 ;u8_loopIndex<strLen; u8_loopIndex++)
	{
		if(string[u8_loopIndex] == '.')
		{
			u8_loopIndex++;
			break;
		}
		f32_num += string[u8_loopIndex] - '0';
		f32_num *= 10;
	}
	f32_num /= 10;
	f32_digit = 1;
	for(;u8_loopIndex<strLen; u8_loopIndex++)
	{
		f32_digit/=10;
		f32_num += (string[u8_loopIndex] - '0')*f32_digit;
	}
	return f32_num;
}


void floatToString(float32_t f32_num, uint8_t* string)
{
	uint32_t u32_num = (uint32_t)f32_num;
	uint8_t u8_digitCount=0;
	uint8_t u8_indexDot=0;
	uint32_t temp = 0;
	while(u32_num !=0)
	{
		u32_num/=10;
		u8_digitCount++;
	}
	u32_num = (uint32_t)f32_num;
	u8_indexDot = u8_digitCount--;
	while (u32_num)
	{
		temp = (u32_num % 10)+ '0';
		string[u8_digitCount--] = temp;
		u32_num /= 10;
	}
	u32_num = (uint32_t)f32_num;
	f32_num -= u32_num;
	u32_num = f32_num*10;
	string[u8_indexDot++] = '.';
	string[u8_indexDot++] = u32_num + '0';
	f32_num *=10;
	f32_num -= u32_num;
	u32_num = f32_num*10;
	string[u8_indexDot] = u32_num + '0';
}



void stringConcatenate(uint8_t* destination, uint8_t* source)
{
	uint8_t index = 0;
	uint8_t sourceLength = stringLength(source);
	uint8_t destinationLength = stringLength(destination)-1;
	for(index=0;index<=(sourceLength-1);index++)
		destination[destinationLength+index] = source[index];
}


uint8_t Max_String_Num(uint8_t* string1, uint8_t* string2)
{
    uint8_t u8_retValue = stringCmp(string1,string2);

    switch(u8_retValue)
    {
    case 1:
        /* Two Numbers are equal */
        return 0;
    case 2:
        /* string 1 > string 2 */
        return 1;
    case 3:
        /* string 2 > string 1 */
        return 2;
    case 0:
        break;
    default:
        break;
    }
    uint8_t u8_loopIndex = 0;

    while(string1[u8_loopIndex] != '\0')
    {
        if(string1[u8_loopIndex] > string2[u8_loopIndex])
            return 1;
        else if(string1[u8_loopIndex] < string2[u8_loopIndex])
            return 2;
        u8_loopIndex++;
    }
    return 3;
}


void EmptyString(uint8_t *string)
{
	uint8_t u8_loopIndex=0;
	while(string[u8_loopIndex] != '\0')
		string[u8_loopIndex++] = '\0';
}

void arrayCopy(uint8_t* source, uint8_t* destination, uint16_t size)
{
    uint8_t u8_loopIndex=0;
    while(size != u8_loopIndex)
    {
	    destination[u8_loopIndex] = source[u8_loopIndex];
	    u8_loopIndex++;
    }
}
void stringCopy(uint8_t* source, uint8_t* destination)
{
	uint8_t u8_loopIndex=0;
	while(source[u8_loopIndex] != '\0')
	{
		destination[u8_loopIndex] = source[u8_loopIndex];
		u8_loopIndex++;
	}
	destination[u8_loopIndex] = '\0';
}
void stringHexToNum(uint8_t *pu8_String, uint16_t *pu16_Num)
{
	sint8_t s8_loopIndex=0;
	uint8_t u8_powerValue=0;
	uint8_t temp_val=0;
	uint8_t u8_stringLength = stringLength(pu8_String)-1;
	*pu16_Num = 0;
	for(s8_loopIndex=u8_stringLength-1 ; s8_loopIndex>=0 ; s8_loopIndex--)
	{
		if ((pu8_String[s8_loopIndex]>='0') && (pu8_String[s8_loopIndex]<='9'))
		{
			temp_val = pu8_String[s8_loopIndex] - '0';
			*pu16_Num += temp_val*power(16,u8_powerValue++);
		}else if((pu8_String[s8_loopIndex]>='A') && (pu8_String[s8_loopIndex]<='F'))
		{
			temp_val = pu8_String[s8_loopIndex] - 55;
			*pu16_Num += temp_val*power(16,u8_powerValue++);
		}else if((pu8_String[s8_loopIndex]>='a') && (pu8_String[s8_loopIndex]<='f'))
		{
			temp_val = pu8_String[s8_loopIndex] - 87;
			*pu16_Num += temp_val*power(16,u8_powerValue++);
		}

	}
}