#include <iostream>
 #include "math.h"
using namespace std;
 
int n, i, j, k;
 
double d, s;
 
int main()
{
    cout << "Kol-vo: " << endl;
    cin >> n;
   
    double **a = new double *[n];
   
    for (i = 0; i <= n; i++) a[i] = new double [n];
   
    double *b = new double [n];
    double *x = new double [n];
   
    cout << "Vvedite koefficienty i svobodnye chleny " << endl;
   
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            cout << "a[ " << i << "," << j << "]= ";
            cin >> a[i][j];
        }
        cout << "b[ " << i << "]= ";
        cin >> b[i];
    }
   
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            printf("%0.1f \t", a[i][j]);
        }
        printf("|%0.1f", b[i]);
        printf("\n");
    }
   
    
   double temp;
   int max;
    for (k = 1; k <= n; k++) // прямой ход
    {
    	printf("Zanulen %d stolbec\n", k );
    	max=k;
    	for (int t = k ; t <= n; t++)
        {
        	//cout<<a[t][k]<<",";
        	if(fabs(a[t][k])>fabs(a[max][k])){
        		max=t;
			}
        		
		}
		cout<<max;
		if(max!=k){
			for (int t = 1; t <= n; t++)
    			{
    				temp=a[k][t];
    				a[k][t]=a[max][t];
    				a[max][t]=temp;
    				temp=b[k];
    				b[k]=b[max];
    				b[max]=temp;
				}
		}
        for (j = k + 1; j <= n; j++)
        {
            d = a[j][k] / a[k][k];
            for (i = k; i <= n; i++)
            {
                a[j][i] = a[j][i] - d * a[k][i];
            }
            b[j] = b[j] - d * b[k];
        }
        printf("\n");
   
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            printf("%0.1f \t", a[i][j]);
        }
        printf("|%0.1f", b[i]);
        printf("\n");
    }
    }
   
    for (k = n; k >= 1; k--) // обратный ход
    {
        d = 0;
        for (j = k + 1; j <= n; j++)
        {
            s = a[k][j] * x[j];
            d = d + s;
        }
        x[k] = (b[k] - d) / a[k][k];
    }
   
    printf("\n");
   
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            printf("%0.1f \t", a[i][j]);
        }
        printf("|%0.1f", b[i]);
        printf("\n");
    }
   
    cout << "Resheniya: " << endl;
   
        for( i = 1; i <= n; i++)
        {
            printf("x[%d]=%0.1f", i,x[i]);
            printf("\n");
        }
    return 0;
}
