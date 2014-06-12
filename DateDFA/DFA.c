#include "DFA.h"

int scan(char* s)
{
	enum { S, A, B, C, D, E, G, H, I, K, POZZA } currentState = S;
	int i = 0,
		_state = 0;

	while ((s[i] != '\0' && s[i] != '\n') && currentState != POZZA)
	{
		switch (currentState)
		{
		case S:
			if (s[i] >= '0' && s[i] <= '2')
				currentState = A;
			else if (s[i] >= '3' && s[i] <= '9')
				currentState = K;
			else
			{ 
				_state = 2;
				currentState = POZZA;
			}	
			break;
		case A:
			if ((s[i - 1] <= '2' && s[i] < '4') || (s[i - 1] < '2' && s[i] <= '9'))
					currentState = B;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case B:
			if (s[i] == ':')
				currentState = C;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case C:
			if (s[i] >= '0' && s[i] <= '5')
				currentState = D;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case D:
			if (s[i] >= '0' && s[i] <= '9')
				currentState = E;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case E:
			if (s[i] == ':')
				currentState = H;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case H:
			if (s[i] >= '0' && s[i] <= '5')
				currentState = G;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case G:
			if (s[i] >= '0' && s[i] <= '9')
				currentState = I;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case I:
			if (!isalnum(s[i]))
				_state = 0;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case K:
			_state = 3;
			currentState = POZZA;
			break;
		}
		++i;
	}

	if (currentState != I && _state == 0)
		_state = 1;

	return _state;
}