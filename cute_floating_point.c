#include "cute_floating_point.h"

typedef union {
  float f;
  unsigned int i;
} U;

float float2(float f) {
  U u;
  unsigned int u1;

  u.f = f;   // armazena float na union
  u1 = u.i;  // obtém a representação do float

  // descarta os bits da mantissa (0-22) e mascara os bits após o bit 7, efetivamente obtendo os bits do expoente
  unsigned int exp = (u.i >> 23) & 0xff;
  exp += 1;

  // desloca 0xFF para começar no bit 22 (inicio do expoente), e nega este valor. Após o AND, o efeito é de remover o expoente anterior
  u1 &= ~(0xff << 23);

  // coloca o novo expoente na posição esperada (bit 22) e faz OU INCLUSIVO para atualizar o nosso expoente
  u1 |= (exp << 23);

  u.i = u1;  // guarda representação do float * 2 na union

  return u.f;
}

int float2int(float f) {
  if (f == 0) return 0;
  U u;
  u.f = f;

  // Número muito próximo de INT_MAX para fazer com que esse if capture casos de overflow
  if (f > 2147483520.0f) {
    printf("float2int: float excede tamanho máximo de int! Retornando INT_MAX!\n");
    return INT_MAX;
  }

  if (f < INT_MIN) {
    printf("float2int: float excede tamanho mínimo de int! Retornando INT_MIN!\n");
    return INT_MIN;
  }

  uint8_t s, e;
  uint32_t m;

  s = (u.i >> 31) & 1;
  e = (u.i >> 23) & 0xff;
  m = u.i & 0x7fffff;

  uint32_t bitsDaMantissa = 0;
  bitsDaMantissa |= (1 << 23);  // adiciona 1 implícito da IEEE 754
  bitsDaMantissa |= m;

  // Divide por 2^23 pois tratamos bitsDaMantissa como um inteiro shiftado 23 bits para a direita
  float mantissaVerdadeira = bitsDaMantissa / (float)pow(2, 23);

  int expoenteVerdadeiro = e - 127;

  return (int)(pow(-1, s) * mantissaVerdadeira * pow(2, expoenteVerdadeiro));
}

float int2float(int i) {
  if (i == 0) {
    // Caso especial
    return 0.0;
  }
  U u;
  int s;
  unsigned mantissa = 0;
  unsigned intConvertido = 0;
  char floatBias = 127;

  if (i < 0) {
    s = 1;
    i = -i;  // precisamos do valor absoluto do numero negativo
  } else {
    s = 0;
  }

  char achouPrimeiroBit1 = 0;
  int posicaoMantissa = 22;
  int exp = 0;

  for (int count = 31; count >= 0; count--) {
    char bitAtual = (i >> count) & 1;
    if (bitAtual == 1 && !achouPrimeiroBit1) {
      achouPrimeiroBit1 = 1;
      exp = count;  // o expoente sem viés é justamente a posição do primeiro bit 1
      continue;     // pula pois o primeiro um é implícito em IEEE 754
    }

    if (achouPrimeiroBit1) {
      // o if abaixo descarta bits de números grandes (mais de 23 bits de mantissa), garantindo o tamanho máximo do float em IEEE 754
      if (posicaoMantissa >= 0) {
        mantissa |= (bitAtual << posicaoMantissa);
        posicaoMantissa--;
      }
    }
  }

  exp += floatBias;
  intConvertido |= (s << 31);
  intConvertido |= (exp << 23);
  intConvertido |= mantissa;

  u.i = intConvertido;
  return u.f;
}

double maxdouble(double a, double b) {
  typedef union {
    double d;
    unsigned long i;
  } U;

  U ua;
  U ub;

  ua.d = a;
  ub.d = b;

  uint8_t sa, sb;
  sa = (ua.i >> 63) & 1;
  sb = (ub.i >> 63) & 1;

  if (sa > sb) {
    return b;
  }
  if (sb > sa) {
    return a;
  }

  // A partir deste ponto, temos que comparar `m` e `e` pois os sinais são iguais
  uint16_t ea, eb;
  uint64_t ma, mb;

  ea = (ua.i >> 52) & 0x7ff;
  eb = (ub.i >> 52) & 0x7ff;

  ma = ua.i & 0xFFFFFFFFFFFFF;
  mb = ub.i & 0xFFFFFFFFFFFFF;

  uint64_t bitsDaMantissaA = 0;
  uint64_t bitsDaMantissaB = 0;

  // Usa explicitamente 1 de 64 bits para evitar aviso de overflow
  bitsDaMantissaA |= 1ULL << 52;
  bitsDaMantissaB |= 1ULL << 52;

  bitsDaMantissaA |= ma;
  bitsDaMantissaB |= mb;

  // Remove bias do double para obter expoente real
  int expA = ea - 1023;
  int expB = eb - 1023;

  // Comparamos os expontes primeiro
  // Como a mantissa (1.M) está sempre entre [1.0, 2.0), se seus expoentes forem distintos,
  // o maior expoente significa número maior (se positivos) ou menor (se negativos)
  if (expA != expB) {
    // Como os numeros tem sinais iguais, checamos qualquer um para saber se são positivos ou negativos
    if (sa == 0) {
      // São positivos: quem tiver maior expoente é maior
      return (expA > expB) ? a : b;
    } else {
      // São positivos: quem tiver maior expoente é menor
      return (expA < expB) ? a : b;
    }
  }

  // Se forem iguais, comparamos as mantissas
  if (bitsDaMantissaA != bitsDaMantissaB) {
    // Como os numeros tem sinais iguais, checamos qualquer um para saber se são positivos ou negativos
    if (sa == 0) {
      // Positive: larger mantissa means larger value
      return (bitsDaMantissaA > bitsDaMantissaB) ? a : b;
    } else {
      // Negative: larger mantissa means more negative → smaller
      return (bitsDaMantissaA < bitsDaMantissaB) ? a : b;
    }
  }

  // São iguais então retornamos qualquer um, no caso, o primeiro
  return a;
}

void print_mantissa(uint32_t mantissa) {
  for (int i = 22; i >= 0; i--) {
    printf("%d", (mantissa >> i) & 1);
    if (i % 4 == 0) {
      printf(" ");
    }
  }
  printf("\n");
}
