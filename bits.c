/* 
 * CS:APP Data Lab 
 * 
 * 顾心怡 25300120166 <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
    return ~(x&y) & ~(~x&~y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
    int m = x >> 31;     // 负数得到0xffffffff(-1)，即111...1,则m&x为x本身;正数得到00..0，m&x为0
    return (~x+1) & m;
}

// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int origin=x;
  dst<<=3,src<<=3;
  int de_mask=~(0xff<<dst);
  x&=de_mask;
  int s_mask=(0xff&(origin>>src))<<dst;
  x|=s_mask;
  return x;
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int mask=~((1<<31)>>n<<1);//mask让原本算数右移高位补的1清零。原来的1个1+n个bit的1，多了一位，所以要再左移1位。
  return ((x>>n)&mask);
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  //参考上面掩码的思路，构造0001111
  //先擦除
  int m=0x0f;
  m=m|(m<<8);
  m=m|(m<<16);
  int highbits=(x&m)<<4;//把低位的换到高位。
  int lowbits=(x>>4)&m;//提取每个字节的高4位，右移4位到低半字节位置，并去除负数时候右移高位产生的1
  x=highbits|lowbits;//拼接起来
   return x;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {//输出最低位置上的0在哪里。//最左边0的特征：右边都是1，左边是任意数。可以用~x & (x + 1)来得到第一个最低位0的掩码。
    int low0 = ~x & (x + 1);  // 找第一个最低位0的掩码。输出只有第一位0是1，其余都是0的掩码（由于进位的关系）
    int x2 = x | low0;        // 把第一个0变成1
    return ~x2 & (x2 + 1);    // 找新数的最低位0，就是第二个
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {//偶数个1，返回1。想到异或的特点：偶数个1，返回0，奇数个1，返回1。可以通过不断异或折半，最后得到一个bit表示奇偶性。
  x^=x>>16;//高16位 ^ 低16位，结果存在低16位
  x^=x>>8;
  x^=x>>4;
  x^=x>>2;
  x^=x>>1;//第0位代表32位的奇偶性
  x&=1;//1的32位表示时，只有最后1位是1，前31位都是0，能作为掩码只保留最后一位。想保留第 n 位就用1<< n做掩码，想清除某几位就用对应位为 0 的掩码做按位与，
  return !x;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456//16进制数，每个数字占4bits
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {//反转n个数字。直接>>是算术右移（负数高位补 1）会破坏循环位，所以用逻辑右移保证高位补0
  int mask = ~(((1 << 31) >> n) << 1);
  int right = (x >> n) & mask;//逻辑右移
  int leftShift=32 + (~n + 1);
  int left = x << leftShift;
  return left | right;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.//偶数商不进位
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int neg1=~0;//-1
  int n_minus1=n+neg1;//n-1
  int half = 1<<n_minus1;//2^(n-1)
  int half_plus1=half+1;
  int one_n=1<<n;//2^n
  int lowmask=one_n+neg1;//低n位全1掩码，等价于(1<<n)-1
  int r=x&lowmask;//x的低n位
  int q=x>>n;//取商
  int q_bit=q&1;//取商的最低位，判断奇偶性
  int a = r+q_bit;  
  int diff=a+~half_plus1+1;//diff>=0时需要进位
  int sign=(diff>>31)&1;//diff的符号位，0表示不进位，1表示进位
  int cin=!sign;
  return(q+cin)<<n;//商加上进位标志，再左移
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  //直接int sum = x + y可能超出 32 位有符号整数范围，必须无溢出
  int floor_avg=(x>>1) +(y>>1)+((x&y)&1);// 各自右移1位相加 + 补低位进位
  int is_half=(x^y) & 1;//若两数和为奇数，则无法整除，有0.5
  int sx =x>>31;
  int sy =y>>31;
  int diff =x+~y+1;//x-y>0,
  int x_gt = ((!sx) & sy)|(!(sx ^ sy) & !(diff >> 31)); //判断是否x>y，异号分支|同号分支
  return floor_avg + (is_half & x_gt);// 半整数且x更大时，选大的那个
}

// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
   int sign_x = x >> 31;
   int sign_a = a >> 31;
   int sign_b = b >> 31;
   int xa_diff_sign=!!((!sign_x)&sign_a);  // 若x,a符号不同，则必有x不为负且a为负。取两次非，使得结果只能是0/1
   int xb_diff_sign=!!((!sign_x)&sign_b);
   int x_minus_a=x+~a;//用x-a-1>=0,符号位必然为0代替判断x-a>0 
   int x_minus_b=x+~b;
   int xa_same_sign=!(sign_x^sign_a)&!(x_minus_a >> 31);//若x,a符号相同，则必有x-a-1不为负（规避x=a的情况）
   int xb_same_sign=!(sign_x^sign_b)&!(x_minus_b >> 31);
   int x_bigger_a=xa_diff_sign |xa_same_sign;
   int x_bigger_b=xb_diff_sign |xb_same_sign;
   int eq_a=!(x^a);
   int eq_b = !(x ^ b);//判断端点是否相等
   int x_ge_a = x_bigger_a | eq_a;   // x >= a
    int x_ge_b = x_bigger_b | eq_b;   // x >= b
    int x_le_a = !x_bigger_a;         // x <= a（不严格大于等价于小于等于）
    int x_le_b = !x_bigger_b;         // x <= b
    return (x_ge_a & x_le_b) | (x_ge_b & x_le_a);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int x4=x<<2;//x*4
  int x5=x4+x;
  int shiftflow=!!((x4>>2)^x);//看是否能逆向还原
  int addflow=!!(((~(x^x4))&(x^x5))>>31);//加法溢出:两加数同号+结果与加数异号
  int isflow=~(shiftflow|addflow)+1;
  int mask=x>>31;//x符号位，x负，111111，x正，000000
  int tmin=1<<31;//011111...
  int tmax=~tmin;
  int flownumber=mask^tmax;//x负，tmax 01111；x正，tmin，1000…
  return ((~isflow)&x5)|(isflow&flownumber);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
int tmin=1<<31;
int ux=x^tmin;
int uy=y^tmin;
int uz=z^tmin;//异或翻转符号位，相当于加上下2^31
int add=ux+uy;//// 第一次无符号加法
int c1 = (((ux&uy)|((ux ^uy) & ~add)) >> 31) & 1;
int sum=add+uz;
int c2 = (((add & uz) | ((add^ uz) & ~sum)) >> 31) & 1;
int under = !(c1 + c2);//under=1表示无任何进位，真实和小于tmin
int over = c1 & c2;//over=1表示两次进位，大于 INT_MAX
return over + (~under + 1);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
int sign_mask=0x80000000u,exp_mask=0x7f800000u,frac_mask=0x7fffffu;
unsigned sign=uf&sign_mask,frac=uf&frac_mask;
unsigned exp=(uf&exp_mask)>>23;
unsigned triple;
unsigned q;
if (exp ==0xffu) {//exp全是1，值为255，为NAN或无穷大
  return uf;
}
if (exp == 0u) {//指数位为0，非规约数或正负0
  triple = frac + frac + frac;
  q = triple >> 1;
  q=q+((triple & 1u) & (q & 1u));//  triple为奇数表示有0.5；q为奇数表示低位整数是奇数，此时才加1。
  return sign|q;//如果q的第23位变成1，该位正好是指数字段最低位，所以结果会自动成为指数为1的规格化数。
}
unsigned sig = frac|0x800000u;
triple = sig + sig + sig;//规格化数：补上隐含的1
unsigned shift;
unsigned remainder;
unsigned half;
if (triple >= 0x2000000u) {
   shift = 2;
   exp = exp + 1; //目标有效数本来是 triple/2。如果 triple/2 >= 2^24，即 triple >= 2^25， 就要改成 triple/4，并让指数加1。
   } 
else {
  shift = 1;
}
q = triple >> shift;
remainder = triple & ((1u << shift) - 1u);
half = 1u << (shift - 1u);
if ((remainder > half) ||((remainder == half) && (q & 1u))) {
  q = q+ 1;//最近偶数舍入
}
if (q& 0x1000000u) {
  q = q>> 1;
  exp = exp + 1;//舍入后q可能达到 2^24，需要再右移一位，指数加1。
}
  /* 指数达到255，结果为同号无穷大 */
if (exp >= 0xffu) {
  return sign | 0x7f800000u;
}
  return sign|(exp<<23)|(q& 0x7fffffu);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {//浮点数变为整数
  unsigned sign=(uf>>31)&1u;
  unsigned biased_exp=(uf>>23)&0xFFu;
  unsigned frac=uf&0x7fffff;
  if(biased_exp==0xff)
    return uf;//NaN或无穷大，直接返回
  int exp=(int)biased_exp-127;
  if(exp<-1)
    return sign<<31;//E<=-2,绝对值小于0.5，舍入为0保留符号
  if(exp>=23)
    return uf;//尾数位是整数
int shift=23-exp;//当指数为exp时，低23-exp 位位于小数点之后,是小数部分。
unsigned val=(1<<23)|frac;//24位有效数
//最近偶数舍入
unsigned round=val&((1u<<shift)-1u);//要被丢弃的部分
unsigned half =1u<<(shift-1);
unsigned q=val>>shift;//整数部分
if (round>half||(round==half&&(q & 1u))) {
  q = q + 1u;
}
if(q==0u){
  return sign<<31;//整数结果为0，必须返回带符号零
}
val = q << shift;//根据舍入后的整数重新构造，保证原来的小数位全部清零
if(val&(1u<<24)){//进位溢出，第24位变成了1
  val=val>>1;
  biased_exp+=1u;//如果舍入后的有效数达到2^24，说明24位字段放不下，需要有效数右移一位,指数加 1。
}
frac = val & 0x7fffffu;
frac = val & 0x7FFFFF;// 获取新的尾数
return (sign<<31)|(biased_exp<<23)|frac;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {//整数转为浮点数
  unsigned sign=(x>>31)&1,exp,frac,round;
  int x_exp,frac_mask;
  if(!x) 
    return 0;//x=0
  if(!(x^(1<<31))) 
    return 0xcf<<24;//x=Tmin,biased exp=31+127=158=0x9E,符号位是1
  if (sign)
    x=-x;
  x_exp=31;//x_exp代表x的最高有效位，利用while循环找到
  while(!(x>>x_exp))
    x_exp--;
  exp=x_exp+0x7f;//exp+bias
  x<<=(31-x_exp);//左移后，最高位的1恰好落在bit 31，它下面的31位是完整的小数部分
  frac_mask=0x7fffff;
  frac=(x>>8)&frac_mask;//右移8位，和float的精度匹配，尾数位对齐
  round=x&0xff;//要被舍入的部分
  frac+=((round>0x80)||((round==0x80)&&(frac&1)));//判断是否大于128，或者等于128且最低位为1，即向偶数舍入
  if(frac>>23){
    frac&=frac_mask;
    exp+=1;//舍入后如果进位溢出，最高位从23变成24，则用掩码清掉溢出的那一位，尾数归 0，指数加1
  }
  return sign<<31|exp<<23|frac;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {//把32位切成若干小块，每块各自数 1 的个数，再两两归并
  int m1,m2,m4,m8,m16;
  m1 = 0x55;//0000 0000 0101 0101
  m1=m1|(m1<<8);//0x00005555
  m1 =m1|(m1<<16); //0x55555555,交替0/1,把相邻两位中的1的个数存在一位，不断折半。每 2 位一组独立相加，结果范围 0~2，正好塞进 2 位，不会溢出到邻组。
  m2 = 0x33;// 0011 0011，2位一块 → 4位一块
  m2=m2|(m2<<8);
  m2 =m2|(m2<<16); //每4位两个1
  m4=0x0F;
  m4=m4|(m4<<8);
  m4=m4|(m4<<16); //每字节抵4位
  m8=0xFF;
  m8=m8|(m8<<16);//0x00FF00FF 
  m16=0xFF;
  m16=m16|(m16<<8);//0x0000FFFF
  x = (x & m1) + ((x>>1) & m1);//交错开来，用mask使得每一块和自己的另一半相加
  x = (x & m2) + ((x>>2) & m2);//把2位作为1块
  x = (x & m4) + ((x>>4) & m4);
  x = (x & m8) + ((x>>8) & m8);
  x = (x & m16) + ((x>>16) & m16);
  return x;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int m1, m2, m4, m8,m16;
  m16=0xFF|(0xFF<<8);//由于只允许0x00~0xFF 常量，所以利用位移构造掩码0x0000FFFF
  m8=m16^(m16<<8);// 0x00FF00FF
  m4=m8^(m8<<4);//0x0F0F0F0F
  m2= m4^(m4<<2);//0x33333333
  m1= m2^(m2<<1);//0x55555555
  x = ((x >> 1) & m1) | ((x & m1) << 1);//相邻一位互换
  x = ((x >> 2) & m2) | ((x & m2) << 2);
  x = ((x >> 4) & m4) | ((x & m4) << 4);
  x = ((x >> 8) & m8) | ((x & m8) << 8);
  x = (x << 16) | ((x >> 16)&m16);
  return x;
}