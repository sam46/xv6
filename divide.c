#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
   int num1 = 0, num2 = 0;
   int res = 0, rem = 0, prec = 2;
   
   if (argc != 3)
   {
      printf(1, "Invalid number of arguments!\n");
   }
   else
   {
      int i = 0, is_neg = 0;

      if (argv[1][i] == '-')
      {
         is_neg = 1;
         i++;
      }

      while (argv[1][i] != '\0')
      {
         num1 = 10*num1 + (argv[1][i]-'0');
         i++;
      }

      if (is_neg)
      {
         num1 = -num1;
      }

      i = 0;
      is_neg = 0;

      if (argv[2][i] == '-')
      {
         is_neg = 1;
         i++;
      }

      while (argv[2][i] != '\0')
      {
         num2 = 10*num2 + (argv[2][i]-'0');
         i++;
      }

      if (is_neg)
      {
         num2 = -num2;
      }

      if (num2 != 0)
      {
         res = (num1 / num2);
         rem = (num1 % num2);

         if (rem == 0)
         {
            printf(1, "%d / %d is %d\n", num1, num2, res);
         }
         else
         {
            int j=0;

            if (res != 0)
            {
               printf(1, "%d / %d is %d.", num1, num2, res);
            }
            else
            {
               if ((num1 < 0 && num2 < 0) || (num1 > 0 && num2 > 0))
               {
                  printf(1, "%d / %d is %d.", num1, num2, res);
               }
               else
               {
                  printf(1, "%d / %d is -%d.", num1, num2, res);
               }
            }

            if (num2 < 0)
            {
               num2 = -num2;
            }

            if(rem < 0)
            {
               rem = -rem;
            }

            while ((j < prec) && (rem != 0))
            {
               res = (rem*10) / num2;
               rem = (rem*10) % num2;
               j++;
               printf(1, "%d", res);
            }
            printf(1, "\n");
         }
      }
      else
      {
         printf(1, "%d / %d is undefined\n", num1, num2);
      }
   }
   exit();
}
