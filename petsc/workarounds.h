
typedef int v4si __attribute__ ((vector_size (16)));
typedef float v4sf __attribute__ ((vector_size (16)));
typedef double v2df __attribute__ ((vector_size (16)));

extern v2df __builtin_ia32_cvtsi642sd (v2df, long long);
extern long long int __builtin_ia32_cvtss2si64 (v4sf);
extern long long int __builtin_ia32_cvttss2si64 (v4sf);
extern v4sf __builtin_ia32_cvtsi642ss(v4sf, long long);
extern long long int __builtin_ia32_cvtsd2si64(v2df);
extern long long int __builtin_ia32_cvttsd2si64(v2df);
