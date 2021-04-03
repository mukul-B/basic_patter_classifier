#include<stdio.h>
#include<math.h>
#include <cstdio>
/*double determinant(double [][25], double);
void cofactor(double [][25], double);
void transpose(double [][25], double [][25], double);*/
/*For calculating Determinant of the Matrix */
double determinant(double a[][5], int k)
{
    double s = 1, det = 0, b[5][5];
    int i, j, m, n, c;
    if (k == 1)
    {
        return (a[0][0]);
    }
    else
    {
        det = 0;
        for (c = 0; c < k; c++)
        {
            m = 0;
            n = 0;
            for (i = 0;i < k; i++)
            {
                for (j = 0 ;j < k; j++)
                {
                    b[i][j] = 0;
                    if (i != 0 && j != c)
                    {
                        b[m][n] = a[i][j];
                        if (n < (k - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (a[0][c] * determinant(b, k - 1));
            s = -1 * s;
        }
    }

    return (det);
}
/*Finding transpose of matrix*/
double** transpose(double fac[][5], int r)
{
    double **b= new double*[r];;

    for (int i = 0;i < r; i++)
    {
        b[i] = new double[r];
        for (int j = 0;j < r; j++)
        {
            b[i][j] = fac[j][i];
        }
    }

    return b;
}
double** cofactor(double num[][5], int f)
{
    double b[5][5];
    double** fac= new double*[f];
    int  m, n;
    for (int q = 0;q < f; q++)
    {
        fac[q] = new double[f];

        for (int p = 0;p < f; p++)
        {
            m = 0;
            n = 0;
            for (int i = 0;i < f; i++)
            {
                for (int j = 0;j < f; j++)
                {
                    if (i != q && j != p)
                    {
                        b[m][n] = num[i][j];
                        if (n < (f - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);

        }
    }
    return fac;
}


double**  inverse(double a[][5], int k)
{
    double  d;
    int i, j;
    double** fac;
   // double  inverse[25][25];
    double** inverse= new double*[k];
    d = determinant(a, k);
    if (d == 0)
        printf("\nInverse of Entered Matrix is not possible\n");
    else
    {
        fac=cofactor(a, k);
        for (int i = 0;i < k; i++)
        {
            inverse[i] = new double[k];
            for (int j = 0;j < k; j++)
            {
                inverse[i][j] = fac[j][i] / d;
            }
        }
        printf("\n\n\nThe inverse of matrix is : \n");


    }

    return inverse;
}


double* addVector (double vect1[5], double vect2[5], int n)
{

    double* result=new double[5];	/* result vector */
    int i;

    /* perform vector addition */
    for (i = 0; i < n; i++)
        result[i] = vect1[i] + vect2[i];

    /* print addition vector C */
    printf ("Addition vector:\n");

    return result;
}

double* subtractVector (double vect1[][5], double vect2[][5], int n)
{

    double* result=new double[5];	/* result vector */
    int i;

    /* perform vector addition */
    for (i = 0; i < n; i++)
        result[i] = vect1[i] - vect2[i];

    /* print addition vector C */
    printf ("Addition vector:\n");

    return result;
}

/*double* scalarMulVector (double vect1[][5], double factor, int n)
{

    double* result=new double[5];	*//* result vector *//*
    int i;

    *//* perform vector addition *//*
    for (i = 0; i < n; i++)
        result[i] = vect1[i] * factor;

    *//* print addition vector C *//*
    printf ("Addition vector:\n");

    return result;
}*/


