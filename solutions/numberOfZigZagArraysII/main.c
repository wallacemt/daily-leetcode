#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")

#include <string.h>
#include <stdint.h>
#include <alloca.h>

const int mod = 1e9 + 7;
const int MAX_MATRIX_SIZE = 1000; // Limite de segurança

static int m, m2;
int* tmp;

// Transpõe matriz para melhorar cache locality
static inline void transpose(const int* A, int* AT) {
  for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
          AT[j * m + i] = A[i * m + j];
      }
  }
}

// Multiplicação otimizada com transposta e modulo incremental
static void mult(const int* A, const int* B, int* C) {
  // Transpõe B para melhor cache access pattern
  int* BT = (int*)alloca(m2 * sizeof(int));
  transpose(B, BT);
  
  memset(tmp, 0, m2 * sizeof(int));
  
  for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
          int64_t sum = 0;
          const int* row_A = &A[i * m];
          const int* col_B = &BT[j * m]; // Agora é row em BT
          
          // Unroll loop com modulo incremental para evitar overflow
          int k = 0;
          for (; k < m - 3; k += 4) {
              sum = (sum + (int64_t)row_A[k] * col_B[k]) % mod;
              sum = (sum + (int64_t)row_A[k+1] * col_B[k+1]) % mod;
              sum = (sum + (int64_t)row_A[k+2] * col_B[k+2]) % mod;
              sum = (sum + (int64_t)row_A[k+3] * col_B[k+3]) % mod;
          }
          
          // Resto
          for (; k < m; k++) {
              sum = (sum + (int64_t)row_A[k] * col_B[k]) % mod;
          }
          
          tmp[i * m + j] = sum;
      }
  }
  
  memcpy(C, tmp, m2 * sizeof(int));
}

// Exponenciação de matriz (binary exponentiation)
static void mat_pow(const int* M, int n, int* ans) {
  // Matriz identidade
  memset(ans, 0, m2 * sizeof(int));
  for (int i = 0; i < m; i++) {
      ans[i * m + i] = 1;
  }
  
  int* P = (int*)alloca(m2 * sizeof(int));
  memcpy(P, M, m2 * sizeof(int));

  while (n > 0) {
      if (n & 1) {
          mult(ans, P, ans);
      }
      if (n > 1) { // Evita multiplicação desnecessária na última iteração
          mult(P, P, P);
      }
      n >>= 1;
  }
}

// Validação e inicialização
static int zigZagArrays(int n, int l, int r) {
  m = r - l + 1;
  
  // Validações críticas
  if (m <= 0 || m > MAX_MATRIX_SIZE) {
      return 0;
  }
  
  if (n <= 0) {
      return 0;
  }
  
  // Verificar limite de stack (aproximado)
  size_t stack_needed = m * m * sizeof(int) * 5; // U, L, UL, P, tmp, BT
  if (stack_needed > 1024 * 1024) { // 1MB limite
      return -1; // Erro: stack overflow risk
  }
  
  m2 = m * m;
  tmp = (int*)alloca(m2 * sizeof(int));

  int* U = (int*)alloca(m2 * sizeof(int));
  int* L = (int*)alloca(m2 * sizeof(int));
  
  // Inicializar U (upper triangular) e L (lower triangular)
  memset(U, 0, m2 * sizeof(int));
  memset(L, 0, m2 * sizeof(int));
  
  for (int i = 0; i < m; i++) {
      for (int j = i + 1; j < m; j++) {
          U[i * m + j] = 1;
      }
      for (int j = 0; j < i; j++) {
          L[i * m + j] = 1;
      }
  }

  n--; 
  const int n0 = n >> 1;

  int* UL = (int*)alloca(m2 * sizeof(int));
  int* P = (int*)alloca(m2 * sizeof(int));

  mult(U, L, UL);    
  mat_pow(UL, n0, P); 
  
  if (n & 1) {
      mult(L, P, P);
  }

  int64_t Sum = 0;
  for (int i = 0; i < m2; i++) {
      Sum = (Sum + P[i]) % mod;
  }
  
  return (Sum * 2) % mod;
}