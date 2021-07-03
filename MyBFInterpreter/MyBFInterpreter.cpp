#include "MyBFInterpreter.h"

static char * paper;

ExecStatus Work(const char * ProgramCode, const bool isFirst, const bool isFindRightBracket)
{
	if (isFirst) Init();
	int len = strlen(ProgramCode);
	if (isFindRightBracket) {
		std::stack<int> st; st.push(-1);
		int i;
		for (i = 0; !st.empty() && i < len; i++) {
			const char & ch = ProgramCode[i];
			if (ch == '[') st.push(i);
			if (ch == ']') st.pop();
		}
		return ExecStatus(true, "No Info", i + 1);
	}
	for (int i = 0; i < len; i++) {
		switch (ProgramCode[i]) {
		case '+':
			bool tmp = AddVal();
			if (!tmp) return ExecStatus(false, "Not a avaliable ASCII character", -1);
			break;
		case '-':
			bool tmp = SubVal();
			if (!tmp) return ExecStatus(false, "Not a avaliable ASCII character", -1);
			break;
		case '>':
			bool tmp = NextChar();
			if (!tmp) return ExecStatus(false, "Paper overflow", -1);
			break;
		case '<':
			bool tmp = PrevChar();
			if (!tmp) return ExecStatus(false, "Paper overflow", -1);
			break;
		case '[':
			if (Check()) { i = Work(ProgramCode + i + 1, false, false).place; break; }
			i = Work(ProgramCode + i + 1, false, true).place; break;
		case ']':
			if (!Check()) {
				if (isFirst) return ExecStatus(false, "Mismatched brackets", -1);
				i = 0; break;
			}
			if (!isFirst) return ExecStatus(true, "No Info", i + 1);
			break;
		default:
			return ExecStatus(false, "Undefined Character", -1);
		}
	}
	return ExecStatus(true, "No Info", len);
}
