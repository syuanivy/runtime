/*
The MIT License (MIT)

Copyright (c) 2015 Terence Parr, Hanzhou Shi, Shuai Yuan, Yuanyuan Zhang

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wich.h>
#include "vm.h"

#include <cunit.h>
#include <wloader.h>

static void setup()		{ }
static void teardown()	{ }

static void run(char *code) {
	save_string("/tmp/t.wasm", code);
	FILE *f = fopen("/tmp/t.wasm", "r");
	VM *vm = vm_load(f);
	fclose(f);
	vm_exec(vm, true);
}


void hello() {
	char *code =
		"1 strings\n"
		"\t0: 5/hello\n"
		"1 functions\n"
		"\t0: addr=0 args=0 locals=0 type=1 4/main\n"
		"3 instr, 5 bytes\n"
		"\tSCONST 0\n"
		"\tSPRINT\n"
		"\tHALT";

	run(code);
}

void string_add() {
    char *code =
        "2 strings\n"
        "\t0: 5/hello\n"
        "\t1: 5/world\n"
        "1 functions\n"
        "\t0: addr=0 args=0 locals=0 type=1 4/main\n"
        "5 instr, 9 bytes\n"
        "\tSCONST 1\n"
        "\tSCONST 0\n"
        "\tSADD\n"
        "\tSPRINT\n"
        "\tHALT";
    run(code);
}

void int_var_def() {
    char *code =
            "0 strings\n"
            "1 functions\n"
            "\t0: addr=0 args=0 locals=1 type=0 4/main\n"
            "3 instr, 9 bytes\n"
            "\tICONST 1\n"
            "\tSTORE 0\n"
            "\tHALT\n";
    run(code);
}
void string_var_def() {
    char *code =
            "1 strings\n"
            "\t0: 5/hello\n"
            "1 functions\n"
            "\t0: addr=0 args=0 locals=1 type=0 4/main\n"
            "3 instr, 7 bytes\n"
            "\tSCONST 0\n"
            "\tSTORE 0\n"
            "\tHALT\n";
    run(code);
}

void vector() {
    char *code =
            "0 strings\n"
            "1 functions\n"
            "\t0: addr=0 args=0 locals=1 type=0 4/main\n"
            "9 instr, 28 bytes\n"
            "\tFCONST 1.00\n"
            "\tFCONST 2.00\n"
            "\tFCONST 3.00\n"
            "\tICONST 3\n"
            "\tVECTOR\n"
            "\tSTORE 0\n"
            "\tVLOAD 0\n"
            "\tVPRINT\n"
            "\tHALT\n";
    run(code);
}

void func_call() {
    char *code =
            "0 strings\n"
            "3 functions\n"
            "\t0: addr=0 args=0 locals=0 type=0 1/f\n"
            "\t1: addr=9 args=1 locals=0 type=1 1/g\n"
            "\t2: addr=14 args=0 locals=0 type=0 4/main\n"
            "7 instr, 15 bytes\n"
            "\tICONST 3\n"
            "\tCALL 1\n"
            "\tRET\n"
            "\tILOAD 0\n"
            "\tRETV\n"
            "\tRET\n"
            "\tHALT\n";
    run(code);
}

void func_call_with_args() {
    char *code =
            "0 strings\n"
            "3 functions\n"
            "\t0: addr=0 args=1 locals=1 type=0 1/f\n"
            "\t1: addr=19 args=2 locals=0 type=1 1/g\n"
            "\t2: addr=28 args=0 locals=0 type=0 4/main\n"
            "15 instr, 37 bytes\n"
            "\tILOAD 0\n"
            "\tICONST 1\n"
            "\tCALL 1\n"
            "\tSTORE 1\n"
            "\tILOAD 1\n"
            "\tIPRINT\n"
            "\tRET\n"
            "\tILOAD 1\n"
            "\tIPRINT\n"
            "\tILOAD 0\n"
            "\tRETV\n"
            "\tRET\n"
            "\tICONST 1\n"
            "\tCALL 0\n"
            "\tHALT";
    run(code);
}

void if_stat() {
    char *code =
        "0 strings\n"
        "1 functions\n"
        "\t0: addr=0 args=0 locals=1 type=0 4/main\n"
        "9 instr, 25 bytes\n"
        "\tICONST 3\n"
        "\tSTORE 0\n"
        "\tILOAD 0\n"
        "\tICONST 0\n"
        "\tIGT\n"
        "\tBRF 7\n"
        "\tILOAD 0\n"
        "\tIPRINT\n"
        "\tHALT\n";
    run(code);
}

void if_else() {
    char *code =
        "1 strings\n"
        "\t0: 2/hi\n"
        "1 functions\n"
        "\t0: addr=0 args=0 locals=1 type=0 4/main\n"
        "12 instr, 32 bytes\n"
        "\tICONST 3\n"
        "\tSTORE 0\n"
        "\tILOAD 0\n"
        "\tICONST 0\n"
        "\tIGT\n"
        "\tBRF 14\n"
        "\tILOAD 0\n"
        "\tIPRINT\n"
        "\tBR 7\n"
        "\tSCONST 0\n"
        "\tSPRINT\n"
        "\tHALT\n";
    run(code);
}

void while_stat() {
    char *code =
        "0 strings\n"
        "1 functions\n"
        "0: addr=0 args=0 locals=1 type=0 4/main\n"
        "\t14 instr, 40 bytes\n"
        "\tICONST 0\n"
        "\tSTORE 0\n"
        "\tILOAD 0\n"
        "\tICONST 10\n"
        "\tILT\n"
        "\tBRF 18\n"
        "\tILOAD 0\n"
        "\tICONST 1\n"
        "\tIADD\n"
        "\tSTORE 0\n"
        "\tBR -24\n"
        "\tILOAD 0\n"
        "\tIPRINT\n"
        "\tHALT\n";
    run(code);
}

void vector_element_assign() {
    char *code =
        "0 strings\n"
        "1 functions\n"
        "\t0: addr=0 args=0 locals=1 type=0 4/main\n"
        "13 instr, 42 bytes\n"
        "\tFCONST 1.00\n"
        "\tFCONST 2.00\n"
        "\tFCONST 3.00\n"
        "\tICONST 3\n"
        "\tVECTOR\n"
        "\tSTORE 0\n"
        "\tVLOAD 0\n"
        "\tICONST 1\n"
        "\tFCONST 4.0\n"
        "\tSTORE_INDEX\n"
        "\tVLOAD 0\n"
        "\tVPRINT\n"
        "\tHALT\n";
    run(code);
}

void test_int_to_string() {
    char *code =
        "1 strings\n"
        "\t0:5/hello\n"
        "1 functions\n"
        "\t0: addr=0 args=0 locals=1 type=0 4/main\n"
        "6 instr, 12 bytes\n"
        "\tICONST 101\n"
        "\tI2S\n"
        "\tSCONST 0\n"
        "\tSADD\n"
        "\tSPRINT\n"
        "\tHALT\n";
    run(code);
}

void fun_call_with_return() {
    char *code =
        "0 strings\n"
        "3 functions\n"
        "\t0: addr=0 args=0 locals=1 type=0 1/f\n"
        "\t1: addr=16 args=1 locals=0 type=3 1/g\n"
        "\t2: addr=44 args=0 locals=0 type=0 4/main\n"
        "18 instr, 48 bytes\n"
        "\tICONST 3\n"
        "\tCALL 1\n"
        "\tSTORE 0\n"
        "\tILOAD 0\n"
        "\tIPRINT\n"
        "\tRET\n"
        "\tILOAD 0\n"
        "\tICONST 0\n"
        "\tIGT\n"
        "\tBRF 18\n"
        "\tICONST 1\n"
        "\tRETV\n"
        "\tBR 9\n"
        "\tICONST 0\n"
        "\tRETV\n"
        "\tRET\n"
        "\tCALL 0\n"
        "\tHALT\n";
    run(code);
}

void vector_add_int() {
    char *code =
        "0 strings\n"
        "1 functions\n"
        "\t0: addr=0 args=0 locals=2 type=0 4/main\n"
        "13 instr, 41 bytes\n"
        "\tFCONST 1.00\n"
        "\tFCONST 2.00\n"
        "\tFCONST 3.00\n"
        "\tICONST 3\n"
        "\tVECTOR\n"
        "\tSTORE 0\n"
        "\tICONST 1\n"
        "\tVLOAD 0\n"
        "\tVADDI\n"
        "\tSTORE 1\n"
        "\tVLOAD 1\n"
        "\tVPRINT\n"
        "\tHALT\n";
    run(code);
}

void string_index() {
    char *code =
    "2 strings\n"
    "\t0: 3/car\n"
    "\t1: 3/cat\n"
    "1 functions\n"
    "\t0: addr=0 args=0 locals=3 type=0 4/main\n"
    "15 instr, 39 bytes\n"
    "\tSCONST 0\n"
    "\tSTORE 0\n"
    "\tSCONST 1\n"
    "\tSTORE 1\n"
    "\tSLOAD 1\n"
    "\tICONST 2\n"
    "\tSLOAD_INDEX \n"
    "\tSLOAD 0\n"
    "\tICONST 1\n"
    "\tSLOAD_INDEX\n"
    "\tSADD\n"
    "\tSTORE 2\n"
    "\tSLOAD 2\n"
    "\tSPRINT\n"
    "\tHALT\n";
    run(code);
}

void func_call_two_args() {
    char *code =
        "0 strings\n"
        "3 functions\n"
        "\t0: addr=0 args=0 locals=1 type=0 1/f\n"
        "\t1: addr=21 args=2 locals=0 type=3 1/g\n"
        "\t2: addr=47 args=0 locals=0 type=0 4/main\n"
        "19 instr, 51 bytes\n"
        "\tICONST 3\n"
        "\tICONST 1\n"
        "\tCALL 1\n"
        "\tSTORE 0\n"
        "\tILOAD 0\n"
        "\tIPRINT\n"
        "\tRET\n"
        "\tILOAD 0\n"
        "\tILOAD 1\n"
        "\tIGT\n"
        "\tBRF 18\n"
        "\tICONST 1\n"
        "\tRETV\n"
        "\tBR 9\n"
        "\tICONST 0\n"
        "\tRETV\n"
        "\tRET\n"
        "\tCALL 0\n"
        "\tHALT\n";
    run(code);
}


int main(int argc, char *argv[]) {
    cunit_setup = setup;
    cunit_teardown = teardown;

    test(string_add);
    test(hello);
    test(int_var_def);
    test(string_var_def);
    test(vector);
    test(func_call);
    test(func_call_with_args);
    test(if_stat);
    test(if_else);
    test(while_stat);
    test(vector_element_assign);
    test(test_int_to_string);
    test(fun_call_with_return);
    test(vector_add_int);
    test(string_index);
    test(func_call_two_args);
    return 0;
}

