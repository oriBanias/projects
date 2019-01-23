/**
 * mu_test.h
 * Mini Unit Test Framework 
 *     a tiny unit test framework for simple tests. 
 * Version: 0.42
 *      Author: Muhammad Zahalqa   
 * 	    MuhammadZ@experis.co.il
 */

#ifndef MU_TEST_H_
#define MU_TEST_H_
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MT__MU_VERSION (0.42)
#define MT_CAT(x,y,z)  x y z
#define MT_WITH []={
#define MT_ANSIESC(x) MT_CAT("\x1B[", #x, "m")
#define MT_CLR(c) MT_ANSIESC(c)
#define __MERGE_(a, b) a##b
#define __LABEL_(x, a) __MERGE_(x, a)
#define __UNIQUE_NAME_(x) __LABEL_(x, __LINE__)
#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MT_FAIL (1)
#define MT_PASS (0)
#define MT__GIVE __MERGE_(re,turn)
#define M__P fprintf(
#define M__VP vfprintf(
#define M__FP M__P stdout,
#define M__VFP M__VP stdout,
typedef   const char* MT_SYMBOL;
static MT_SYMBOL MT__ABCDEF MT_WITH
" ║Out beyond ideas of wrongdoingC++██████╗  █████╗ ███████╗███████╗ ",
" ║and rightdoing there is a field.C# ███████╗  █████╗  ██╗ ██╗       ",
" ║I'll meet you there.Scheme██╔══██╗██╔══██╗██╔════╝██╔════╝ ",
" ║When the soul lies down in that grassJava ██╔════╝ ██╔══██╗ ██║ ██║       ",
" ║the world is too full to talk about.Scala██████╔╝███████║███████╗███████╗ ",
" ║           ― Jalal Ad-Din RumiScheme █████╗   ███████║ ██║ ██║       ",
" ║██████████████████████████████████████████Fortran██╔═══╝ ██╔══██║╚════██║╚════██║ ",
" ║Look on my Works, ye Mighty, and despair!Pascal ██╔══╝   ██╔══██║ ██║ ██║       ",
" ║Nothing beside remains. Round the decayKotlin██║     ██║  ██║███████║███████║ ",
" ║Of that colossal Wreck, boundless and bareGO ██║      ██║  ██║ ██║ ███████╗  ",    
" ║The lone and level sands stretch far away.Basic?╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝ ",    
" ╚══════════════════════════════════════════Rust ╚═╝      ╚═╝  ╚═╝ ╚═╝ ╚══════╝  ",
" Every line of code is written without reasonPython",
" maintained out of weakness, and deleted by chance.",
"         Jean-Paul Sartre’s Programming in ANSI C  "};

/* put ansistring in array, index with enum */
#define KNRM 0
#define KRED 31
#define KGRN 32
#define KYEL 33
#define KBLU 34
#define KMAG 35
#define KCYN 36
#define KWHT 37

#define KBRED 91
#define KBGRN 92
#define KBYEL 93
#define KBBLU 94
#define KBMAG 95
#define KBCYN 96
#define KULN  4


enum MT_Cats {
    MT__V_MARK,
    MT__X_MARK,

    MT__GRIN_FACE,
    MT__ANGUISH,         
    MT__GRIMACE,         
    MT__LOUD_CRY,        
    MT__SCREAM,          

    MT__CAT_GRIN,
    MT__CAT_GRIN_SMILE,
    MT__CAT_JOY,
    MT__CAT_POUTING,
    MT__CAT_SAD,
    MT__CAT_WAERY,

    MT__STOP_WATCH,         
    MT__TIMER_CLOCK,        
    MT__HOUR_GLASS,         
    MT__CLOCK_FACE_2_OCLOCK,
    MT__THUMBS_UP,          
    MT__THUMBS_DOWN,

    MT__PASS_EMJ=MT__GRIN_FACE,
    MT_FAIL_ICN=MT__X_MARK,
    MT_PASS_ICN=MT__V_MARK
};

MT_SYMBOL Catz MT_WITH
"\xE2\x9C\x94",
"\xE2\x9C\x98",
"\xF0\x9F\x98\x80",
"\xF0\x9F\x98\xA7", 
"\xF0\x9F\x98\xAC", 
"\xF0\x9F\x98\xAD", 
"\xF0\x9F\x98\xB1",
"\xF0\x9F\x98\xBA","\xF0\x9F\x98\xB8","\xF0\x9F\x98\xB9",
"\xF0\x9F\x98\xBE", "\xF0\x9F\x98\xBF", "\xF0\x9F\x99\x80",
"\xE2\x8F\xB1","\xE2\x8F\xB2","\xE2\x8F\xB3",
"\xF0\x9F\x95\x91",
"\xF0\x9F\x91\x8D","\xF0\x9F\x91\x8E"};
#define MT__STOP_WATCH "\xE2\x8F\xB1"
#define MT__TIMER_CLOCK "\xE2\x8F\xB2"
#define MT__HOUR_GLASS "\xE2\x8F\xB3"
#define MT__CLOCK_FACE_2_OCLOCK "\xF0\x9F\x95\x91"
#define MT__THUMBS_UP "\xF0\x9F\x91\x8D"
#define MT__THUMBS_DOWN "\xF0\x9F\x91\x8E"                           
#define MT__COLOR(f) (!f?MT_CLR(KGRN):MT_CLR(KRED))
#define ____b(l) M__FP MT_CLR(KYEL) "\n ╔" l "╗")
#define ____c(l) M__FP MT_CLR(KYEL) "\n ╚" l "╝")
#define ____x(l) M__FP MT_CLR(KYEL) "\n ║ " l )
#define ____z(l) M__FP MT_CLR(KYEL) "\n ║ " l
#define ____z0(l) M__FP MT_CLR(KYEL) "\n ║%s%s" MT_CLR(KYEL) "║" MT_CLR(KCYN) l MT_CLR(KYEL) " ║"
#define ____nl() M__FP "\n") 
static int mt__trace_on,mt__current_test_was_traced;
static MT_SYMBOL mt__current_test_name;
static double mt__total_time;
struct mt__AssertResult{int youShalN0tPass;int where;MT_SYMBOL message;MT_SYMBOL actual_expected;};
typedef struct MT__TestRec0rd{struct mt__AssertResult (*whatMayFail)(void);MT_SYMBOL whatName;int shouldaCoulda;} MT__TestRec0rd;
#define UNIT(name) static struct mt__AssertResult name(void){struct mt__AssertResult (*___unsed)(void) = name;struct mt__AssertResult __ok = {MT_PASS, 0, 0, 0};mt__current_test_name=#name; mt__current_test_was_traced=0;if(___unsed){
#define XUNIT(name) static int __UNIQUE_NAME_(name)(void){static const char* __testName = #name;
#define END_UNIT }MT__GIVE __ok;}
#define TEST_SUITE(name)    int main(int argc, const char**argv){MT_SYMBOL __test_name = #name;MT_SYMBOL*a___z = &MT__ABCDEF[0];MT__TestRec0rd mt_testRec0rds MT_WITH
#define TEST(unit)		            {unit, #unit, 0},
#define IGNORE_TEST(unit)           {unit, MT_CLR(KYEL) #unit, 1},
#define XIGNORE_TEST(unit)          {unit, 0, 1},
#define END_SUITE                   {NULL, NULL, 0}};long mt__passedAway=0;MT__TestRec0rd *mt__pUtRec = mt_testRec0rds;long mt__totalUtRec = 0;MT_SYMBOL mt__k001Ik0n = 0;long mt__failfails = 0, __ignored = 0;if(argc > 1)mt__trace_on = !strcmp(argv[1], "-v");\
                                ____b("═════════════════════════════════════"); \
                                ____x("••            inf           ••" MT_CLR(KRED) "•" MT_CLR(KCYN) " ▌ ▄ " MT_CLR(KRED) "·." MT_CLR(KCYN) " ▄" MT_CLR(KRED) "•" MT_CLR(KCYN) " ▄▌▄▄▄▄▄▄▄▄ " MT_CLR(KRED) ".." MT_CLR(KCYN) "▄▄ " MT_CLR(KRED) "·" MT_CLR(KCYN) " ▄▄▄▄▄" MT_CLR(KYEL) " ║"); \
                                ____x("••        1  ⌠  1     s   dx••" MT_CLR(KRED) "·"  MT_CLR(KCYN) "██ ▐███" MT_CLR(KRED) "▪" MT_CLR(KCYN) "█" MT_CLR(KRED) "▪" MT_CLR(KCYN) "██▌" MT_CLR(KRED)"•" MT_CLR(KCYN) "██  ▀▄" MT_CLR(KRED)"." MT_CLR(KCYN) "▀" MT_CLR(KRED)"·" MT_CLR(KCYN) "▐█ ▀" MT_CLR(KRED)". •" MT_CLR(KCYN) "██  " MT_CLR(KYEL) " ║"); \
                                ____x("••ζ(s)= ──── ⎮────── x  ⋅ ──••" MT_CLR(KCYN)  "▐█ ▌▐▌▐█" MT_CLR(KRED)"·" MT_CLR(KCYN) "█▌▐█▌ ▐█" MT_CLR(KRED)".▪" MT_CLR(KCYN) "▐▀▀▪▄▄▀▀▀█▄ ▐█" MT_CLR(KRED)".▪" MT_CLR(KYEL) " ║"); \
                                ____x("••      Γ(s) ⎮  x          2••" MT_CLR(KCYN)  "\xE2\x96\x88\xE2\x96\x88\x20\xE2\x96\x88\xE2\x96\x88\xE2\x96\x8C\xE2\x96\x90\xE2\x96\x88\xE2\x96\x8C\xE2\x96\x90\xE2\x96\x88\xE2\x96\x84\xE2\x96\x88\xE2\x96\x8C\x20\xE2\x96\x90\xE2\x96\x88\xE2\x96\x8C" MT_CLR(KRED)"·" MT_CLR(KCYN) "▐█▄▄▌▐█▄" MT_CLR(KRED)"▪" MT_CLR(KCYN) "▐█ ▐█▌" MT_CLR(KRED)"·" MT_CLR(KYEL) " ║"); \
                                ____x("••           ⌡ e - 1     x  ••" MT_CLR(KCYN)  "▀▀  █" MT_CLR(KRED)"▪" MT_CLR(KCYN) "\xE2\x96\x80\xE2\x96\x80\xE2\x96\x80\x20\xE2\x96\x80\xE2\x96\x80\xE2\x96\x80\x20\x20\xE2\x96\x80\xE2\x96\x80\xE2\x96\x80\x20\x20\xE2\x96\x80\xE2\x96\x80\xE2\x96\x80\x20\x20\xE2\x96\x80\xE2\x96\x80\xE2\x96\x80\xE2\x96\x80\x20\x20\xE2\x96\x80\xE2\x96\x80\xE2\x96\x80\x20" MT_CLR(KYEL) " ║"); \
                                ____z("••           0              ••" MT_CLR(KBGRN)  "%*.*s \x20\x20\xC2\xA9\xce\xbc\x5f\x74\x65\x73\x74%*.*f" MT_CLR(KYEL) " ║"), -20,19, "\x6D\x40\x74\x72\x79\x66\x69\x6E\x61\x6C\x6C\x79\x2E\x63\x6F\x6D", 5,2, MT__MU_VERSION); \
                                ____c("═════════════════════════════════════"); \
                                mt__fprintInBox(stdout, __test_name, 37);while(mt__pUtRec->whatMayFail){ \
                                    if(!mt__pUtRec->whatName){++mt__pUtRec; continue;}\
                                    ++mt__totalUtRec;\
                                    if(mt__pUtRec->shouldaCoulda){M__FP MT_CLR(KBYEL) "\t%s" MT_CLR(KBBLU) " %s", mt__trace_on ? "Ignoring    :" : "Ignore", mt__pUtRec->whatName);++__ignored;}else{ \
                                        clock_t __begin = clock();\
    					                struct mt__AssertResult __r = mt__pUtRec->whatMayFail();  \
                                        clock_t __end = clock();\
                                        double __time_spent = (double)(__end - __begin);\
                                        mt__total_time += __time_spent;\
    					                M__FP "%s", __r.youShalN0tPass == MT_PASS ? MT_CLR(KBGRN) "\tPASS -"  MT_CLR(KNRM): MT_CLR(KBRED) "\tFAIL -" MT_CLR(KNRM));\
                                        if(mt__trace_on)M__FP "[%5.0f]",  __time_spent); \
                                        M__FP MT_CLR(KBBLU) " %s",  mt__pUtRec->whatName); \
                                        if( __r.youShalN0tPass != MT_PASS){++mt__failfails; \
                                            M__FP MT_CLR(KCYN) "\n\t\t\tFailed at line:" MT_CLR(KRED)" %d\n" , __r.where);\
                                            M__FP MT_CLR(KYEL) "\t\t\t%s\n", __r.message); \
                                            M__FP "\t\t\t%s\n", __r.actual_expected); \
                                            free((void*)__r.actual_expected);}else{++mt__passedAway;}}M__FP "\n");  fflush(stdout);++mt__pUtRec;}\
                                if(mt__failfails>0)++a___z;mt__k001Ik0n=mt__failfails>mt__totalUtRec/2?Catz[MT__SCREAM]:mt__failfails>mt__totalUtRec/3?Catz[MT__LOUD_CRY]:mt__failfails>mt__totalUtRec/4?Catz[MT__GRIMACE]:mt__failfails==0?Catz[MT__PASS_EMJ]:Catz[MT__ANGUISH]; \
                                ____b("══════════════════════════════════╦════════════════"); \
                                ____z0("  Total:" MT_CLR(KBMAG) "%4ld %s"), MT__COLOR(mt__failfails), *(a___z--,++a___z), mt__totalUtRec,mt__k001Ik0n); \
                                ____z0(" Passed:" MT_CLR(KBGRN) "%4ld %s "), MT__COLOR(mt__failfails), *(a___z++,++a___z), mt__passedAway, Catz[MT_PASS_ICN]); \
                                ____z0(" Failed:" MT_CLR(KBRED) "%4ld %s "), MT__COLOR(mt__failfails), *(a___z++,++a___z), mt__failfails, Catz[MT_FAIL_ICN]); \
                                ____z0(" Ignore:" MT_CLR(KBYEL) "%4ld   " ), MT__COLOR(mt__failfails), *(a___z++,++a___z), __ignored); \
                                ____z0(" Time:" MT_CLR(KBYEL) "%6.0f ms" ), MT__COLOR(mt__failfails), *(a___z++,++a___z), mt__total_time); \
                                ____z0(" %*.*s%*c" ), MT__COLOR(mt__failfails), *(a___z++,++a___z), 10,10, mt__totalUtRec >= 10? Catz[MT__CAT_GRIN]:Catz[MT__CAT_POUTING],6,' '); \
                                ____c("══════════════════════════════════╩════════════════");____nl();\
                                MT__GIVE (int)mt__failfails;\
                            }
#define mt__STATEMENTS(s)  do {s;} while((void)0, 0)
#define MT_BLOCK(b)        do {b} while((void)0,0)
#define mt__fprintCharN(fp, s, repeat)  MT_BLOCK({int n = repeat;while(n--) fprintf(fp, "%s", s);})
#define mtt__fprintInBox(fp, s, minWidth)   mt__STATEMENTS({int ml=0, mr=0,mw=minWidth,len = (int)strlen(s);if(len+1 < mw){mr=ml=(mw-len)/2; mr += (mw-len) % 2;}else{mw=len+2;}M__P fp, "\n");M__P fp\
,MT_CLR(KYEL) " ╔");mt__fprintCharN(fp, "═", mw);M__P fp, MT_CLR(KYEL) "╗\n");M__P fp, MT_CLR(KYEL) " ║" MT_CLR(KCYN) "%*s%s%*s" MT_CLR(KYEL) "║\n", mr, " ", s, ml, " ");M__P fp, MT_CLR(KYEL) " ╚");mt__fprintCharN(fp, "═", mw);M__P fp, MT_CLR(KYEL) "╝\n");})
#define mt__fprintInBox(fp, s, minWidth)    do{int ml=0, mr=0,mw=minWidth,len = (int)strlen(s);if(len+1 < mw){mr=ml=(mw-len)/2; mr += (mw-len)\
%2;}else{mw=len+2;}M__P fp, "\n");M__P fp, MT_CLR(KYEL) " ╔");mt__fprintCharN(fp, "═", mw);M__P fp, MT_CLR(KYEL) "╗\n");M__P fp, MT_CLR(KYEL) " ║" MT_CLR(KCYN) "%*s%s%*s" MT_CLR(KYEL) "║\n", mr," ", s, ml," ");\
M__P fp, MT_CLR(KYEL) " ╚");mt__fprintCharN(fp, "═", mw);M__P fp, MT_CLR(KYEL) "╝\n");}while((void)0,0)
#define mt__EXPECTED MT_CLR(KCYN) "expected  :" MT_CLR(KGRN)
#define mt__ACTUALL  MT_CLR(KCYN) "but actual:" MT_CLR(KRED)
static char* mt__EXPECTED_i(long a, long e){char* p = (char*) malloc(1024);if(p) sprintf(p, mt__EXPECTED " %ld\n\t\t\t" mt__ACTUALL " %ld", e, a);MT__GIVE p;}
static char* mt__EXPECTED_s(MT_SYMBOL a, MT_SYMBOL e){char* p = (char*) malloc(1024);if(p) sprintf(p, mt__EXPECTED " '%s'\n\t\t\t" mt__ACTUALL " '%s'", e, a);MT__GIVE p;}
static char* mt__EXPECTED_p(const volatile void* volatile const a, const volatile void* volatile const e){char* p = (char*) malloc(1024);if(p) sprintf(p, mt__EXPECTED " %p\n\t\t\t" mt__ACTUALL " %p", e, a);MT__GIVE p;}
static void mt__trace_log(MT_SYMBOL fmt, ...){va_list arg;if(!mt__trace_on) return;va_start(arg, fmt);if(!mt__current_test_was_traced){
mt__current_test_was_traced=1;M__FP MT_CLR(KYEL) "\tTracing   -   " MT_CLR(KBBLU) "%s\n", mt__current_test_name);}M__FP "\t\t\t" MT_CLR(KBYEL));M__VFP fmt, arg); fprintf(stdout,"\n");fflush(stdout);va_end (arg);}void (*mt__fancy_pointers[])()=
{(void(*)())mt__trace_log, (void(*)())mt__EXPECTED_s, (void(*)())mt__EXPECTED_i, (void(*)())mt__EXPECTED_p};
#define mt__ASSERT(cond, where, msg, expected) do if(!(cond)) { struct mt__AssertResult __r = {MT_FAIL, where, msg, 0}; __r.actual_expected = expected; MT__GIVE __r; } while((void)0,0)    
#define mt__ASSERT_INT(a,op,e,n) mt__STATEMENTS({ long _a = (long)(a); long _e = (long)(e); mt__ASSERT( _a op _e, __LINE__, n "(" #a " == " #e ")", mt__EXPECTED_i(_a,_e)); }) 
#define mt__ASSERT_STR(a,op,e,n) mt__STATEMENTS({ const char* _a = (const char*)(a); const char* _e = (const char*)(e); mt__ASSERT( strcmp(_a,_e) op 0, __LINE__, n "(" #a "," #e ")", mt__EXPECTED_s(_a,_e)); }) 
#define mt__ASSERT_PTR(a,op,e,n) mt__STATEMENTS({ const void* _a = (const void*)(a); const void* _e = (const void*)(e); mt__ASSERT( _a op _e, __LINE__, "ASSERT_EQUAL_PTR(" #a " == " #e ")", mt__EXPECTED_p(_a,_e)); })  
#define TRACE_LOG                   mt__trace_log
#define ASSERT_EQUAL_INT(a,e)       mt__ASSERT_INT(a, ==, e, "ASSERT(_EQUAL_)::INT")
#define ASSERT_NOT_EQUAL_INT(a,e)   mt__ASSERT_INT(a, !=, e, "ASSERT(_NOT_EQUAL_)::INT")
#define ASSERT_EQUAL_STR(a,e)       mt__ASSERT_STR(a, ==, e,"ASSERT(_EQUAL_)::STR")
#define ASSERT_NOT_EQUAL_STR(a,e)   mt__ASSERT_STR(a, !=, e,"ASSERT(_NOT_EQUAL_)::STR")
#define ASSERT_EQUAL_PTR(a,e)       mt__ASSERT_PTR(a, ==, e, "ASSERT(_EQUAL_)::PTR")
#define ASSERT_NOT_EQUAL_PTR(a,e)   mt__ASSERT_PTR(a, !=, e, "ASSERT(_EQUAL_)::PTR")
#define ASSERT_THAT(e)              mt__STATEMENTS({int _e = (int)(e); mt__ASSERT((_e), __LINE__, "ASSERT_THAT(" #e ")", mt__EXPECTED_s("false","true")); })
#endif /* MU_TEST_H_ */
