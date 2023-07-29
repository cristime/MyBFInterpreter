# Simple BF Interpreter in C

一个简易的 C 语言实现的 BF 解释器，仅仅是图一乐。

* <del>后续可能会制作 REPL（？</del>

## 一些说明

编译：直接编译 src 目录下 main.c 即可
```bash
cd src
gcc main.c -o main -O2
```

运行：
```bash
./main test.bf      # test.bf 可换作任意合法 BF 代码
# 如果没有错误则会输出 Hello World!
```

代码注释较为详细，个人认为逻辑比较清晰，可作为参考。