#include <stdio.h>

long fatorial(int num) {
  long resul = 1;
  
  if ( num <= 1 )
    return (1);
  else {
    resul = num * fatorial(num - 1);
    return (resul);
  }
  return resul;
}

main() {
  int num;
  long result;
  printf("\nEntre com nro ate 10: ");
  scanf("%d", &num);
  result = fatorial(num);

  printf("\nO fatorial de %d = %d", num, result);
}