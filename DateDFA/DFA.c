#include "DFA.h"

int scan(char* s)
{
	enum { S, A, B, C, D, E, G, H, I, L, K, POZZA } currentState = S;
	int i = 0,
		_state = 0;

	while ((s[i] != '\0' && s[i] != '\n') && currentState != POZZA)
	{
		switch (currentState)
		{
		case S:
			if (s[i] >= '0' && s[i] <= '1')
				currentState = A;
			else if (s[i] == '2')
				currentState = B;
			else if (s[i] >= '3' && s[i] <= '9')
				currentState = K;
			else
			{ 
				_state = 2;
				currentState = POZZA;
			}	
			break;
		case A:
			if ((s[i ] >= '0' && s[i] <= '9'))
					currentState = C;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case B:
			if ((s[i] >= '0' && s[i] <= '3'))
				currentState = C;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case C:
			if (s[i] == ':')
				currentState = D;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case D:
			if (s[i] >= '0' && s[i] <= '5')
				currentState = E;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case E:
			if (s[i] >= '0' && s[i] <= '9')
				currentState = H;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case H:
			if (s[i] == ':')
				currentState = G;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case G:
			if (s[i] >= '0' && s[i] <= '5')
				currentState = I;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case I:
			if (s[i] >= '0' && s[i] <= '9')
				currentState = L;
			else
			{
				_state = 2;
				currentState = POZZA;
			}
			break;
		case L:
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

	if (currentState != L && _state == 0)
		_state = 1;

	return _state;
}