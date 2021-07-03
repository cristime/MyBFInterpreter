// MyBFInterpreter.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <cstdio>
#include <cstring>
#include <stack>

const int MAXLENGTH = 1e5 + 10;

struct ExecStatus {
	ExecStatus(bool st, char * in, int pl) { status = st; info = in; place = pl; }
	ExecStatus(const ExecStatus & old) { this->status = old.status; this->info = old.info; this->place = old.place; }
	bool status;
	char * info;
	int place;
};


void Init();	// TODO
ExecStatus Work(const char *, bool, bool);
inline bool AddVal();	// TODO
inline bool SubVal();	// TODO
inline bool NextChar();	// TODO
inline bool PrevChar();	// TODO
inline bool Check();	// TODO

// TODO: 在此处引用程序需要的其他标头。
