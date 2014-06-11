//CLexer by NexusJ  (aka Vito Palumbo)
/*This is a test for a C-like lexer*/

int i ;
char c;
float f;
double d;
long l;

void func();
{
i = 10;
c = "L'ASILO";
f = 3.14f;
d = 120.1548;
l = 1045;

i = (1++) /2;
}

int main(int argc,char *argv[])
{

for(int i = 0; i !=10; i++)
func();

return 0;
}