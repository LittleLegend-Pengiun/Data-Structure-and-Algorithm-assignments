import unittest
from test_processing import run_test

class Test(unittest.TestCase):
    def test_100_sample(self):
        str_in = """
iconst 3
top
        """
        expect = """3\n"""
        num = 100
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_101_sample(self):
        str_in = """
iconst 3
istore 0
val 0
        """
        expect = """3\n"""
        num = 101
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_102_sample(self):
        str_in = """
iconst 3
iconst 2
imul
top
        """
        expect = """6\n"""
        num = 102
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_103_sample(self):
        str_in = """
iconst 3
iconst 2
imul
top
istore 0
iload 0
top
        """
        expect = """6\n6\n"""
        num = 103
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_104_sample(self):
        str_in = """
fconst 4.0
fconst 5.0
iadd
        """
        expect = """Type mismatch: line 3"""
        num = 104
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_105_fadd(self):
        str_in = """
fconst 4.5
fconst 5.4
fadd
top
        """
        expect = """9.9\n"""
        num = 105
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_106_fconst(self):
        str_in = """
fconst 4.0
top
        """
        expect = """4\n"""
        num = 106
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_107_isub(self):
        str_in = """
iconst 4
iconst 3
isub
top
        """
        expect = """1\n"""
        num = 107
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_108_fsub(self):
        str_in = """
fconst 4
fconst 3.33
fsub
top
        """
        expect = """0.67\n"""
        num = 108
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_109_fmul(self):
        str_in = """
fconst 4
fconst 1.11
fmul
top
        """
        expect = """4.44\n"""
        num = 109
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_110_idiv(self):
        str_in = """
iconst 4
iconst 3
idiv
top
        """
        expect = """1\n"""
        num = 110
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_111_fdiv(self):
        str_in = """
fconst 4
fconst 3
fdiv
top
        """
        expect = """1.33333\n"""
        num = 111
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_112_irem(self):
        str_in = """
iconst 44
iconst 3
irem
top
        """
        expect = """2\n"""
        num = 112
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_113_ineg(self):
        str_in = """
iconst 4
iconst 3
ineg
top
        """
        expect = """-3\n"""
        num = 113
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_114_fneg(self):
        str_in = """
iconst 4
fconst 3.444
fneg
fadd
top
        """
        expect = """0.556\n"""
        num = 114
        self.assertTrue(run_test.check(str_in, expect, num))

    def test_115_iand(self):
        str_in = """
iconst 2
iconst 1
iand
top
        """
        expect = """0\n"""
        num = 115
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_116_ior(self):
        str_in = """
iconst 4
iconst 5
ior
top
        """
        expect = """5\n"""
        num = 116
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_117_feq(self):
        str_in = """
iconst 4
fconst 4.00
feq
top
        """
        expect = """1\n"""
        num = 117
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_118_ilt(self):
        str_in = """
iconst 4
iconst 3
ilt
top
        """
        expect = """0\n"""
        num = 118
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_119_flt(self):
        str_in = """
iconst 4
iconst 3
flt
top
        """
        expect = """0\n"""
        num = 119
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_120_igt(self):
        str_in = """
iconst 4
iconst 3
igt
top
        """
        expect = """1\n"""
        num = 120
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_121_fgt(self):
        str_in = """
iconst 4
iconst 3
fgt
top
        """
        expect = """1\n"""
        num = 121
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_122_ibnot(self):
        str_in = """
iconst 4
iconst 3
ibnot
top
        """
        expect = """0\n"""
        num = 122
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_123_iload_istore(self):
        str_in = """
iconst 4
iconst 3
isub
top
istore 4
iconst 3
iload 4
isub
top
        """
        expect = """1\n2\n"""
        num = 123
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_124_fload_fstore(self):
        str_in = """
iconst 4
iconst 3
fsub
top
fstore 4
fconst 3.3
fload 4
fsub
top
        """
        expect = """1\n2.3\n"""
        num = 124
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_125_i2f(self):
        str_in = """
iconst 4
i2f
fstore 0
fload 0
top
        """
        expect = """4\n"""
        num = 125
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_126_f2i(self):
        str_in = """
fconst 3.9
f2i
top
        """
        expect = """3\n"""
        num = 126
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_127_val(self):
        str_in = """
iconst 3
istore 4
val 4
        """
        expect = """3\n"""
        num = 127
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_128_exception_type_mismatch(self):
        str_in = """
iconst 4
iconst 3
imul
top
fstore 0
fload 0
top
        """
        expect = """12\nType mismatch: line 5"""
        num = 128
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_129_divide_by_0(self):
        str_in = """
iconst 4
iconst 3
idiv
top
        """
        expect = """1\n"""
        num = 129
        self.assertTrue(run_test.check(str_in, expect, num))

    
    def test_130_StackFull(self):
        str_in = """
iconst 4
iconst 3
iconst 4
iconst 3
iconst 4
iconst 3
iconst 4
iconst 3
iconst 4
iconst 3
iconst 4
iconst 3
iconst 4
iconst 3
iconst 4
iconst 3
iconst 4
iconst 3
top
        """
        expect = """Stack full: line 17"""
        num = 130
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_131_StackEmpty(self):
        str_in = """
iconst 4
istore 0
istore 2
top
        """
        expect = """Stack empty: line 3"""
        num = 131
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_132_Array_out_of_range(self):
        str_in = """
iconst 4
istore 256
idiv
top
        """
        expect = """Array out of range: line 2"""
        num = 132
        self.assertTrue(run_test.check(str_in, expect, num))

    def test_133_Undefined_var(self):
        str_in = """
iconst 4
istore 0
iload 2
top
        """
        expect = """Undefined variable: line 3"""
        num = 133
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_134_ieq(self):
        str_in = """
iconst 4
iconst 3
ieq
top
        """
        expect = """0\n"""
        num = 134
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_135_ineq(self):
        str_in = """
iconst 4
iconst 3
feq
top
iconst 1
ineq
top
        """
        expect = """0\n1\n"""
        num = 135
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_136_StackEmpty(self):
        str_in = """
top
iconst 4
        """
        expect = """Stack empty: line 1"""
        num = 136
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_137_StackEmpty(self):
        str_in = """
iconst 1
iconst 2
istore 0
istore 2
fconst 3.3
fstore 3
top
iload 2
top
        """
        expect = """Stack empty: line 7"""
        num = 137
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_138_Type_mismatch(self):
        str_in = """
fconst 3.0
f2i
fstore 0
        """
        expect = """Type mismatch: line 3"""
        num = 138
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_139_f2i_with_negative_num(self):
        str_in = """
fconst -3.9
f2i
top
iconst 2
iadd
top    
        """
        expect = """-3\n-1\n"""
        num = 139
        self.assertTrue(run_test.check(str_in, expect, num))
      
    def test_140_fconst_neg_0(self):
        str_in = """
fconst 0
fneg
top  
        """
        expect = """-0\n"""
        num = 140
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_141_fconst_neg_0(self):
        str_in = """
fconst -0
fconst 90
fmul
top 
        """
        expect = """-0\n"""
        num = 141
        self.assertTrue(run_test.check(str_in, expect, num))
    
    def test_142_fconst_neg_0(self):
        str_in = """
iconst 0
ineg
iconst 10
imul
top
        """
        expect = """0\n"""
        num = 142
        self.assertTrue(run_test.check(str_in, expect, num))