#include "MyBFInterpreter.h"

void PrintHelp(); // TODO
void InterpFile(const char *); // TODO

int main(int argc, char ** argv) {
	if (argc == 1) {
		while (true) {
			char * input = new char[MAXLENGTH];
			puts("Input Program Code(Ctrl+C to exit):");
			fgets(input, MAXLENGTH, stdin);
			ExecStatus st = Work(input, true, false);
			if (st.status) continue;
			printf("Error: %s\n", st.info);
			delete[] input;
		}
	}
	else if (strcmp(argv[1], "-h") == 0) PrintHelp();
	else InterpFile(argv[1]);
	return 0;
}