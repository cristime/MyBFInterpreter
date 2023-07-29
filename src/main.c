// My Brainfuck Interpreter

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#define LINEMAX ( 100000 + 10 )

FILE * ProcessCmd( int, char ** );      // 根据输入决定读取代码的位置
int Brainfuck( FILE * );

int main( int argc, char ** argv ) {
    FILE * fp = ProcessCmd( argc, argv );
    int retCode = Brainfuck( fp );
    fclose( fp );
    return retCode;
}

FILE * ProcessCmd( int argc, char ** argv ) {
    // 第二个参数是 -h 或者参数输入错误，打印用法信息
    if ( argc != 2 || strcmp( argv[1], "-h" ) == 0 ) {
        fputs( "USAGE:\n", stderr );
        fputs( "1. main\t---Input Brainfuck code directly from STDIN.\n", stderr );
        fputs( "2. main bfprogram.bf\t---Input Brainfuck code from file.\n", stderr );
        fputs( "3. main -h\t---Print this message.\n", stderr );
        exit( 1 );
    }
    
    FILE * fp = fopen( argv[1], "r" );      // 打开文件
    
    // 文件无法打开
    if ( fp == NULL ) {
        fprintf( stderr, "ERROR: Couldn't open file %s.\n", argv[1] );
        exit( 1 );
    }

    return fp;
}

int Brainfuck( FILE * fp ) {
    char tape[LINEMAX] = { 0 };             // 纸带
    int top = 0, stack[LINEMAX] = { 0 }, mapping[LINEMAX] = { 0 };    // 栈用于存储循环信息

    int ptr = ( LINEMAX - 1 ) >> 1;         // 初始指针位置
    char code[LINEMAX] = { 0 };             // 用于读取 Brainfuck 代码
    
    fgets( code, LINEMAX - 10, fp );        // 获取 Brainfuck 代码

    int codeLen = strlen( code );           // 读取代码长度

    // 生成映射：一对中括号互相映射
    for ( int i = 0; i < codeLen; ++i ) {
        if ( code[ i ] == '[' ) {
            ++top;
            stack[top] = i;
        }
        if ( code[ i ] == ']' ) {
            if ( top == 0 ) {       // 栈提前为空说明右括号多于左括号，报错
                fputs( "ERROR: Brackets do not pair.", stderr );
                return 1;
            }
            mapping[ i ] = stack[ top ];
            mapping[ stack[ top ] ] = i;
            --top;
        }
    }
    // 跑完后栈非空说明左括号多于右括号，报错
    if ( top ) {
        fputs( "ERROR: Brackets do not pair.", stderr );
        return 1;
    }

    int codePtr = 0;

    // 依次遍历每个字符
    while ( codePtr < codeLen ) {
        switch ( code[codePtr] ) {
            case '<':
                --ptr;
                if ( ptr < 0 ) {    // 超出纸带左端
                    fputs( "ERROR: Tape overflow!", stderr );
                    return 1;
                }
                ++codePtr; break;

            case '>':
                ++ptr;
                if ( ptr >= LINEMAX ) {     // 超出纸带右端
                    fputs( "ERROR: Tape overflow!", stderr );
                    return 1;
                }
                ++codePtr; break;
            
            case '+':
                if ( tape[ptr] == CHAR_MAX ) {      // 字符溢出
                    fputs( "ERROR: Tape character overflow!", stderr );
                    return 1;
                }
                ++tape[ptr]; ++codePtr; break;
            
            case '-':
                if ( tape[ptr] == CHAR_MIN ) {      // 字符溢出
                    fputs( "ERROR: Tape character overflow!", stderr ); 
                    return 1;
                }
                --tape[ptr]; ++codePtr; break;
            
            case '.':       // 输出当前字符
                putc( tape[ptr], stdout ); ++codePtr; break;
            
            case ',':       // 读取当前字符
                tape[ptr] = getc( stdin ); ++codePtr; break;
            
            case '[':   // 循环开始
                if ( !tape[ptr] ) {     // 若当前字符为 \0 则跳转至对应右括号后一个字符
                    codePtr = mapping[codePtr] + 1;
                    break;
                }
                ++codePtr; break;
            
            case ']':
                if ( tape[ptr] ) {      // 若当前字符非 \0 则跳转至对应左括号后一字符
                    codePtr = mapping[codePtr] + 1;
                    break;
                } 
                ++codePtr; break;  
        }
    }
    return 0;       // 运行正常
}