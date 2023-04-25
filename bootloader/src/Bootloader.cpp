
void printString(const char* string)
{
	char* videoMemory = (char*)0xb8000;

	for (int i = 0; 0 != string[i]; i++)
	{
		*videoMemory = string[i];
		videoMemory = videoMemory + 2;
	}
}

int main()
{
	printString("Hello C world!");

	while (1)
	{
	}
}
