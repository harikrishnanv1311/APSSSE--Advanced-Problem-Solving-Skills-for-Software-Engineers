#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

// Returns the sum of two intals.
char* intal_add(const char* intal1, const char* intal2)
{
	int l1 = strlen(intal1);
	int l2 = strlen(intal2);
	int l1_greater = 0;
	int i,j,end;
	char *inter; 
	if(l1>=l2)
	{
		
		l1_greater = 1;
		inter = malloc(sizeof(char)*(l1+1));
		i = l1-1;
		j = l2-1;
		end = l1;
		inter[end--] = '\0';
	}
	else
	{
		inter = malloc(sizeof(char)*(l2+1));
		i = l2-1;
		j = l1-1;
		end = l2;
		inter[end--] = '\0';
	}
	int sum,digit,carry = 0;
	while(i>=0 && j>=0)
	{
		if(l1_greater)
			sum = carry + (intal1[i--] - '0') + (intal2[j--] - '0');
		else
			sum = carry + (intal1[j--] - '0') + (intal2[i--] - '0');

		carry = sum/10;
		digit = sum%10;
		inter[end--] = digit + '0';
	}
	if(i<0 && j<0)
    {
        if(carry==1)
        {
            if(l1_greater)
			{
				char *res = malloc(sizeof(char)*(l1+2));
				res[0] = '1';
				res[1] = '\0';
				// printf("Equal number of digits, Carry is 1  and inter:%s\n",inter);
				strcat(res,inter);
				free(inter);
				// printf("Equal number of digits, Carry is 1  and res:%s\n",res);
				return res;
				
			}
			else
			{
				char *res = malloc(sizeof(char)*(l2+2));
				res[0] = '1';
				res[1] = '\0';
				// printf("Equal number of digits, Carry is 1  and inter:%s\n",inter);
				strcat(res,inter);
				// printf("Equal number of digits, Carry is 1  and res:%s\n",res);
				free(inter);
				return res;
			}
			
        }
        else if(carry==0)
        {
            // printf("Equal number of digits, Carry is 0  and inter:%s\n",inter);
			return inter;
        }
    }
	while(i>=0)
	{
		
		if(l1_greater)
			sum = carry + (intal1[i--] - '0');
		else
			sum = carry + (intal2[i--] - '0');
		
		carry = sum/10;
		digit = sum%10;
		inter[end--] = digit + '0';

		if(i==-1)
		{
			if(carry == 1)
			{
				if(l1_greater)
				{
					char *res = malloc(sizeof(char)*(l1+2));
					res[0] = '1';
					res[1] = '\0';
					// printf("Unqual number of digits, Carry is 1 and inter:%s\n",inter);
					strcat(res,inter);
					// printf("Unequal number of digits, Carry is 1  and res:%s\n",res);
					free(inter);
					return res;
				}
				else
				{
					char *res = malloc(sizeof(char)*(l2+2));
					res[0] = '1';
					res[1] = '\0';
					// printf("Unequal number of digits, Carry is 1  and inter:%s\n",inter);
					strcat(res,inter);
					// printf("Unequal number of digits, Carry is 1  and res:%s\n",res);
					free(inter);
					return res;
				}	
			}
			else if(carry==0)
			{
            	// printf("Unequal number of digits, Carry is 0  and inter:%s\n",inter);
				return inter;
			}
		}
	}
	
}

// Returns the comparison value of two intals.
// Returns 0 when both are equal.
// Returns +1 when intal1 is greater, and -1 when intal2 is greater.
int intal_compare(const char* intal1, const char* intal2)
{
	int l1 = strlen(intal1);
	int l2 = strlen(intal2);
	if(l1>l2)
		return 1;
	else if(l1<l2)
		return -1;
	else if(l1==l2)
	{
		for(int i=0;i<l1;i++)
		{
			if(intal1[i]>intal2[i])
				return 1;
			else if(intal1[i]<intal2[i])
				return -1;
		}
		return 0;
	}
}


// Returns the difference (obviously, nonnegative) of two intals.
char* intal_diff(const char* intal1, const char* intal2)
{
	int l1 = strlen(intal1);
	int l2 = strlen(intal2);
	int compare = intal_compare(intal1,intal2);
	char *bigger,*smaller,*inter;
	int end,end_b,end_s,digit,carry=0;
	if(compare == 0 || compare == 1)
	{
		bigger = malloc(sizeof(char)*(l1+1));
		inter = malloc(sizeof(char)*(l1+1));		
		end = l1;
		inter[end--] = '\0';
		strcpy(bigger,intal1);
		smaller = malloc(sizeof(char)*(l2+1));
		strcpy(smaller,intal2);
		end_b = l1-1;
		end_s = l2-1;
	}
	else if(compare == -1)
	{
		bigger = malloc(sizeof(char)*(l2+1));
		inter = malloc(sizeof(char)*(l1+1));
		end = l2;
		inter[end--] = '\0';
		strcpy(bigger,intal2);
		smaller = malloc(sizeof(char)*(l1+1));
		strcpy(smaller,intal1);
		end_b = l2-1;
		end_s = l1-1;
	}
	while(end_b>=0 && end_s>=0)
	{
		digit = bigger[end_b] - carry;
		if(digit<smaller[end_s])
		{
			digit = digit + 10 - (smaller[end_s]) + '0';
			inter[end--] = digit;
			carry = 1;
		}
		else
		{
			digit = digit - smaller[end_s] + '0';
			inter[end--] = digit;
			carry = 0;
		}
		end_b--;
		end_s--;
	}
	while(end_b>=0)
	{
		digit = bigger[end_b] - carry;
		if(digit<48)
		{
			digit = digit + 10;
			inter[end--] = digit;
			carry = 1;
		}
		else
		{
			inter[end--] = digit;
			carry = 0;
		}
		end_b--;
	}

	// printf("inter evaluated\n");
	free(bigger);
	free(smaller);
	//Removing leading zeroes
	long int sz = strlen(inter);
	// printf("Final size of inter is:%ld\n",sz);
	// printf("inter is:%s\n",inter);

	int c=0;

	while(inter[c]=='0')
		c++;
	
	// printf("Found %d leading zeroes\n",c);
	if(c != sz)
	{
		// printf("Hi\n");
		char *res = (char*)malloc(sizeof(char)*(sz-c+1));
		// printf("Allocation res array with size:%ld\n",sz-c+1);
		
	 	strcpy(res,inter+c);
	 	// printf("Size of res after copying is %ld\n",strlen(res));
		// printf("Subtraction of %s and %s is: %s\n",intal1,intal2,res);
	 	
		free(inter);
	 	return res;

	}	
	else
	{
		char *res = (char*)malloc(sizeof(char)*2);
		res[0] = '0';
		res[1] = '\0';
		// printf("Subtraction of %s and %s is: %s\n",intal1,intal2,res);

		free(inter);
		return res;
	} 
}


// Returns the product of two intals.
static int max(int a, int b)
{
    if(a>=b)
        return a;
    else 
        return b;
}

char* intal_multiply(const char* intal1, const char* intal2)
{
    
	int comp1 = intal_compare(intal1,"0");
	int comp2 = intal_compare(intal2,"0");

	if (comp1 == 0 || comp2 == 0)
    {
        char *res = (char *)malloc(sizeof(char) * 2);
        res[0] = '0';
        res[1] = '\0';
        return res;
    }
	int i,j,tmp,l1,l2;
    l1 = strlen(intal1);
    l2 = strlen(intal2);

    int *a = (int*)malloc(sizeof(int)*l1);
    int *b = (int*)malloc(sizeof(int)*l2);
    int *inter = (int*)malloc(sizeof(int)*(l1+l2+1));
    for(int i=0;i<=l1+l2;i++)
    {
        inter[i] = 0;
    }
    char *res = (char*)malloc(sizeof(char)*1001);
    for(i = l1-1,j=0;i>=0;i--,j++)
    {
        a[j] = intal1[i]-'0';
    }
    for(i = l2-1,j=0;i>=0;i--,j++)
    {
        b[j] = intal2[i]-'0';
    }
    for(i = 0;i < l2;i++)
    {
        for(j = 0;j < l1;j++)
        {
            inter[i+j] += b[i]*a[j];
        }
    }
    
    for(i = 0;i < l1+l2;i++)
    {
        tmp = inter[i]/10;
        inter[i] = inter[i]%10;
        inter[i+1] = inter[i+1] + tmp;
    }
    for(i = l1+l2; i>= 0;i--)
    {
        if(inter[i] > 0)
            break;
    }

    int iter = 0;
    for(;i >= 0;i--)
    {
        res[iter++] = inter[i] + '0';
    }
    res[iter] = '\0';
    free(inter);
    free(a);
    free(b);
    
    return res;
}


// Returns intal1 mod intal2
// The mod value should be in the range [0, intal2 - 1].
// intal2 > 1
// Implement a O(log intal1) time taking algorithm.
// O(intal1 / intal2) time taking algorithm may exceed time limit.
// O(intal1 / intal2) algorithm may repeatedly subtract intal2 from intal1.
// That will take intal1/intal2 iterations.
// You need to design a O(log intal1) time taking algorithm.
// Generate your own testcases at https://www.omnicalculator.com/math/modulo
char* intal_mod(const char* intal1, const char* intal2) {

    int l1, l2,comp, choice = 0;
	char *mult_res, *sub_res;

	l1 = strlen(intal1);
	l2 = strlen(intal2);
	
	char *inter_intal2 = malloc(sizeof(char)*1001); // Length can be same as length of intal2
    strcpy(inter_intal2, intal2);
	
	char *inter_mod = malloc(sizeof(char)*1001);
	strcpy(inter_mod, intal1);
    
	char *inter_multiply = malloc(sizeof(char)*1001);

    comp = intal_compare(inter_mod, inter_intal2);

    while(comp != -1) {
        strcpy(inter_multiply, inter_intal2);
		
		comp = intal_compare(inter_multiply, inter_mod);
        while(comp == -1) {
            mult_res = intal_multiply(inter_multiply, "2");
			strcpy(inter_multiply,mult_res);
			free(mult_res);
			comp = intal_compare(inter_multiply, inter_mod);
        }

		sub_res = intal_diff(inter_multiply, inter_mod);
        strcpy(inter_mod,sub_res); 
		free(sub_res);

		if(choice == 0)
			choice = 1;
		else if(choice == 1)
			choice = 0;

		comp = intal_compare(inter_mod, inter_intal2);
    }

	comp = intal_compare(inter_mod, "0");
    if(comp == 0)
	{
		free(inter_intal2);
    	free(inter_multiply);
		strcpy(inter_mod,"0");
		return inter_mod;
	}

    else if(choice == 1)
	{
		sub_res = intal_diff(inter_intal2, inter_mod);
		strcpy(inter_mod,sub_res);
		free(sub_res);
		free(inter_intal2);
    	free(inter_multiply);
		return inter_mod;
	}

    free(inter_intal2);
    free(inter_multiply);
    return inter_mod;
}



// Returns nth fibonacci number.
// intal_fibonacci(0) = intal "0".
// intal_fibonacci(1) = intal "1".clea
char* intal_fibonacci(unsigned int n)
{
	char *res = malloc(sizeof(char)*1001);
	if(n==0)
	{
		res[0] = '0';
		res[1] = '\0';
		// printf("Fibo of 0 is %s\n",res);
		return res;
	}
	if(n==1)
	{
		res[0] = '1';
		res[1] = '\0';
		// printf("Fibo of 1 is %s\n",res);
		return res;
	}
	char *a = malloc(sizeof(char)*1001);
	char *b = malloc(sizeof(char)*1001);
	char *c = malloc(sizeof(char)*1001);
	a[0] = '0'; a[1] = '\0';
	b[0] = '1'; b[1] = '\0';
	for(int i=1;i<=n;i++)
	{
		c = intal_add(a,b);
		// printf("c is %s, ",c);
		strcpy(a,b);
		// printf("a is %s, ",a);
		strcpy(b,c);
		// printf("b is %s\n",b);
	}
	free(b);
	free(res);
	free(c);
	// printf("Fibo of %d is %s\n",n,a);
	return a;
}


// Returns the factorial of n.
char* intal_factorial(unsigned int n)
{
	char *res = malloc(sizeof(char)*1001);
	if(n==0 || n==1)
	{
		res[0]='1';
		res[1]='\0';
		return res;
	}
	sprintf(res,"%d",n);
	// printf("Initial res is:%s\n",res);
	int l = strlen(res);
	char *inter = malloc(sizeof(char)*1001);
	while(n>1)
	{
		n -= 1;
		sprintf(inter,"%d",n);
		// printf("inter is:%s, ",inter);
		res = intal_multiply(res,inter);
		// printf("res after multiplication is:%s\n",res);

	}
	free(inter);
	return res;
}


// Returns the Binomial Coefficient C(n,k).
// 0 <= k <= n
// C(n,k) < 10^1000 because the returning value is expected to be less than 10^1000.
// Use the Pascal's identity C(n,k) = C(n-1,k) + C(n-1,k-1)
// Make sure the intermediate intal values do not cross C(n,k).
// Use Dynamic Programming. Use extra space of not more than O(k) number of intals. Do not allocate the whole O(nk) DP table.
// Don't let C(1000,900) take more time than C(1000,500). Time limit may exceed otherwise.
static int min(int a, int b)
{
	if(a <= b)
		return a;
	else
		return b;
	
}
char* intal_bincoeff(unsigned int n, unsigned int k)
{
	
	char **dyn_coeff = malloc(sizeof(char*)*(k+1));
	for(int i=0;i<=k;i++)
	{
		dyn_coeff[i] = malloc(sizeof(char)*1001);
		strcpy(dyn_coeff[i],"0");
	}

	strcpy(dyn_coeff[0],"1");
	char *addition;
	for(int i=1; i<=n; i++)
	{
		for(int j=min(i,k);j>0;j--)
		{
			addition = intal_add(dyn_coeff[j],dyn_coeff[j-1]);
			strcpy(dyn_coeff[j],addition);
			free(addition);
		}
	}
	char *res = malloc(sizeof(char)*1001);
	strcpy(res,dyn_coeff[k]);
	free(dyn_coeff);
	// for(int i=0;i<=k;i++)
	// 	printf("%s ",dyn_coeff[i]);
	return res;

}



// Returns intal1 ^ intal2.
// Let 0 ^ n = 0, where n is an intal.
// Implement a O(log n) intal multiplications algorithm.
// 2^3000 has less than 1000 decimal digits. 3000 intal multiplications may exceed time limit.
char* intal_pow(const char* intal1, unsigned int n)
{
	char *result = malloc(sizeof(char)*1001);
	char zero[2] = "0";
	int comp = intal_compare(intal1,zero);
	if(comp == 0)
	{
		result[0] = '0';
		result[1] = '\0';
		return result;
	}

	char *base = malloc(sizeof(char)*1001);
	strcpy(base,intal1);
	result[0] = '1';
	result[1] = '\0';
    for (;;)
    {
        if (n & 1)
            result = intal_multiply(result,base);
        n >>= 1;
        if (!n)
            break;
        base = intal_multiply(base,base);
    }
	free(base);
    return result;
}



// Returns Greatest Common Devisor of intal1 and intal2.
// Let GCD be "0" if both intal1 and intal2 are "0" even though it is undefined, mathematically.
// Use Euclid's theorem to not exceed the time limit.
char* intal_gcd(const char* intal1, const char* intal2)
{
	char *res = malloc(sizeof(char)*1001);
	int comp1 = intal_compare(intal1,"0");
	int comp2 = intal_compare(intal2,"0");
	if(comp1==0 && comp2==0)
	{
		strcpy(res,"0");
		return res;
	}
	if(comp1==0)
	{
		strcpy(res,intal2);
		return res;
	}
	if(comp2==0)
	{
		strcpy(res,intal1);
		return res;
	}
	free(res);
	char *inter_intal1 = malloc(sizeof(char)*1001);
	char *inter_intal2 = malloc(sizeof(char)*1001);
	int comp3 = intal_compare(intal1,intal2);
	if(comp3 == 1 || comp3 == 0)
	{
		strcpy(inter_intal1,intal1);
		strcpy(inter_intal2,intal2);
	}
	else
	{
		strcpy(inter_intal2,intal1);
		strcpy(inter_intal1,intal2);
	}
	// printf("Here\n");
	char *mod;
	
	while(intal_compare(inter_intal2,"0") == 1)
	{
		// printf("----------------\n");
		// printf("inter_intal1 is %s\n",inter_intal1);
		// printf("inter_intal2 is %s\n",inter_intal2);
		// printf("Finding mod of inter_intal1 and inter_intal2\n");
		mod = intal_mod(inter_intal1,inter_intal2);
		// printf("mod is %s\n",mod);
		
		strcpy(inter_intal1,inter_intal2);
		// printf("inter_intal1 is changed to %s\n",inter_intal2);

		strcpy(inter_intal2,mod);
		// printf("inter_intal2 is changed to %s\n",mod);

		// printf("Free-ing mod now!");
		free(mod);
		// printf("mod FREED!");

	}
	// printf("Free-ing inter_intal2 now!");
	free(inter_intal2);
	// printf("mod FREED!");

	return inter_intal1;
}



// Returns the offset of the largest intal in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_max(char **arr, int n)
{
	int max=0,comp;
	for(int i=1;i<n;i++)
	{
		comp = intal_compare(arr[max],arr[i]);
		if(comp == -1)
		{
			max = i;
		}
	}
	return max;
}

// Returns the offset of the smallest intal in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_min(char **arr, int n)
{
	int min=0,comp;
	for(int i=1;i<n;i++)
	{
		comp = intal_compare(arr[min],arr[i]);
		if(comp == 1)
		{
			min = i;
		}
	}
	return min;
}

// Returns the offset of the first occurrence of the key intal in the array.
// Returns -1 if the key is not found.
// 1 <= n <= 1000
int intal_search(char **arr, int n, const char* key)
{
	int comp;
	for(int i=0;i<n;i++)
	{
		comp = intal_compare(arr[i],key);
		if(comp == 0)
		{
			return i;
		}
	}
	return -1;
}


// Returns the offset of the first occurrence of the key intal in the SORTED array.
// Returns -1 if the key is not found.
// The array is sorted in nondecreasing order.
// 1 <= n <= 1000
// The implementation should be a O(log n) algorithm.
static int binary_search_helper(char **arr,int l,int r,const char *x)
{
	int m,compare,res = -1;
	while (l <= r) { 
        m = l + (r - l) / 2; 
		compare = intal_compare(arr[m],x);
        if (compare == 0)
		{ 
            res = m;
			r = m-1; 
		}
        else if (compare == -1) 
            l = m + 1;  
        else if (compare == 1)
            r = m - 1; 
    } 
    return res;
}
int intal_binsearch(char **arr, int n, const char* key)
{
	int result = binary_search_helper(arr, 0, n - 1, key);
	return result;
}
 

// Sorts the array of n intals.
// 1 <= n <= 1000
// The implementation should be a O(n log n) algorithm.
static void merge(char **a,char **b,char **c,int n,int b_s,int c_s)
{
    int i=0,j=0,k=0;
	int comp=0;
    while(i<b_s && j<c_s)
    {
        comp = intal_compare(b[i],c[j]);
		if(comp == 0 || comp == -1)
        {
            strcpy(a[k++], b[i++]); 
        }
        else
        {
            strcpy(a[k++] ,c[j++]);
        }
    }
    if(i == b_s)
    {
        while(j<c_s)
        {
            strcpy(a[k++],c[j++]);
        }
    }
    else
    {
        while(i<b_s)
        {
            strcpy(a[k++],b[i++]);
        }
    }
}
static void mergeSort(char **a,int n)
{
    if(n>1)
    {
        int ind;
        ind = n/2;
        
        int b_s,c_s;
        b_s = ind;
        char **b = malloc(sizeof(char*)*b_s);
        
        if(n%2==0)
            c_s = ind;
        else
            c_s = ind+1;
        
        char **c = malloc(sizeof(char*)*c_s);

        int i=0;
        // COPY FIRST HALF(0..floor(n/2)-1) OF A to B and SECOND HALF(floor(n/2) to n-1) TO C
        for(int j=0;j<b_s;j++)
        {
            b[j] = malloc(sizeof(char)*(1001));
			strcpy(b[j],a[i++]);
        }
        for(int j=0;j<c_s;j++)
        {
            c[j] = malloc(sizeof(char)*(1001));
			strcpy(c[j],a[i++]);
        }

        mergeSort(b,b_s);
        mergeSort(c,c_s);
        merge(a,b,c,n,b_s,c_s);

    }
} 
void intal_sort(char **arr, int n)
{
	mergeSort(arr,n);
}


// Coin-Row Problem - Dynamic Programming Solution
// There is a row of n coins whose values are some positive integers C[0..n-1].
// The goal is to pick up the maximum amount of money subject to the constraint that
// no two coins adjacent in the initial row can be picked up.
// 1 <= n <= 1000
// The implementation should be O(n) time and O(1) extra space even though the DP table may be of O(n) size.
// Eg: Coins = [10, 2, 4, 6, 3, 9, 5] returns 25
char* coin_row_problem(char **arr, int n)
{
	int comp;
	char *res = malloc(sizeof(char)*1001);
	if(n==0)
	{
		res[0] = '0';
		res[1] = '\0';
		return res;
	}
	if(n==1)
	{
		strcpy(res,arr[0]);
		return res;
	}
	if(n==2)
	{
		comp = intal_compare(arr[0],arr[1]);
		if(comp == 1 || comp == 0)
			strcpy(res,arr[0]);
		else
			strcpy(res,arr[1]);
		
		return res;
	} 
	
	free(res);

	
	char *first = malloc(sizeof(char)*1001);
	char *second = malloc(sizeof(char)*1001);
	char *highest = malloc(sizeof(char)*1001);

	strcpy(first,arr[0]);

	comp = intal_compare(first,arr[1]);
	if(comp == 1 || comp == 0)
		strcpy(second,first);
	else
		strcpy(second,arr[1]);
	
	// printf("Initial first is %s\n",first);
	// printf("Initial second is %s\n",second);
	int i=2;
	char *prev;
	while(i<n)
	{
		// printf("---------");
		// printf("i is : %d\n",i);
		prev = intal_add(first,arr[i]);
		// printf("prev is %s\n",prev);
		comp = intal_compare(prev,second);
		if(comp == 1 || comp ==0)
		{
			// free(first);
			strcpy(first,second);
			// printf("first is %s\n",first);

			strcpy(highest,prev);
			// printf("highest is %s\n",highest);

			// free(second);
			strcpy(second,highest);
			// printf("second is %s\n",second);

		}
		else
		{
			// free(first);
			strcpy(first,second);
			// printf("first is %s\n",first);
			strcpy(highest,second);
			// printf("highest is %s\n",highest);
			// free(second);
			strcpy(second,highest);
			// printf("second is %s\n",second);

		}
		i++;
		free(prev);
	}
	// printf("Hi\n");
	return highest;
}



// int main()
// {
// 	int n = 12;
// 	char **a = (char**) malloc(n * sizeof(char*));
// 	for(int i = 0; i < n; i++) {
// 		a[i] = (char*) malloc(1001 * sizeof(char));
// 	}
	
// 	strcpy(a[0], "1234512345123451234512345");
// 	strcpy(a[1], "543215432154321543215432154321");
// 	strcpy(a[2], "0");
// 	strcpy(a[3], "1234512345123451234512345");
// 	strcpy(a[4], "1234512345123451234512344");
// 	strcpy(a[5], "12");
// 	strcpy(a[6], "265252859812191058636308480000000");
// 	strcpy(a[7], "265252859812191058636308480000000");
// 	strcpy(a[8], "5432154321543215432154321");
// 	strcpy(a[9], "3");
// 	strcpy(a[10],
// 	"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
// 	strcpy(a[11], 		"1230231922161117176931558813276752514640713895736833715766118029160058800614672948775360067838593459582429649254051804908512884180898236823585082482065348331234959350355845017413023320111360666922624728239756880416434478315693675013413090757208690376793296658810662941824493488451726505303712916005346747908623702673480919353936813105736620402352744776903840477883651100322409301983488363802930540482487909763484098253940728685132044408863734754271212592471778643949486688511721051561970432780747454823776808464180697103083861812184348565522740195796682622205511845512080552010310050255801589349645928001133745474220715013683413907542779063759833876101354235184245096670042160720629411581502371248008430447184842098610320580417992206662247328722122088513643683907670360209162653670641130936997002170500675501374723998766005827579300723253474890612250135171889174899079911291512399773872178519018229989376");

// // 	//Below "a" is a sorted "a"
// // 	// strcpy(a[0], "0");
// // 	// strcpy(a[1], "3");
// // 	// strcpy(a[2], "12");
// // 	// strcpy(a[3], "1234512345123451234512344");
// // 	// strcpy(a[4], "1234512345123451234512345");
// // 	// strcpy(a[5], "1234512345123451234512345");
// // 	// strcpy(a[6], "5432154321543215432154321");
// // 	// strcpy(a[7], "543215432154321543215432154321");
// // 	// strcpy(a[8], "265252859812191058636308480000000");
// // 	// strcpy(a[9], "265252859812191058636308480000000");
// // 	// strcpy(a[10], "1230231922161117176931558813276752514640713895736833715766118029160058800614672948775360067838593459582429649254051804908512884180898236823585082482065348331234959350355845017413023320111360666922624728239756880416434478315693675013413090757208690376793296658810662941824493488451726505303712916005346747908623702673480919353936813105736620402352744776903840477883651100322409301983488363802930540482487909763484098253940728685132044408863734754271212592471778643949486688511721051561970432780747454823776808464180697103083861812184348565522740195796682622205511845512080552010310050255801589349645928001133745474220715013683413907542779063759833876101354235184245096670042160720629411581502371248008430447184842098610320580417992206662247328722122088513643683907670360209162653670641130936997002170500675501374723998766005827579300723253474890612250135171889174899079911291512399773872178519018229989376" );
// // 	// strcpy(a[11], "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	
// // 	//For Coin Problem
// // 	// strcpy(a[0], "10");
// // 	// strcpy(a[1], "2");
// // 	// strcpy(a[2], "4");
// // 	// strcpy(a[3], "6");
// // 	// strcpy(a[4], "3");
// // 	// strcpy(a[5], "9");
// // 	// strcpy(a[6], "5");
	
	



// // 	// char *answer = intal_add("1234512345123451234512345","543215432154321543215432154321");
// // 	// int answer = intal_compare("1234512345123451234512345","543215432154321543215432154321");
// // 	//  char *answer = intal_diff("113200917110","99999090909");
// // 	// char *answer = intal_diff("52","52");

// // 	// int answer = intal_min(a,n);
// // 	// int answer = intal_max(a,n);
// // 	// int answer = intal_search(a,n,"543215432154321543215432");
// // 	// int answer = intal_binsearch(a,n,"11");
// // 	// intal_sort(a,n);
// // 	// char *answer = intal_fibonacci(300);
// // 	// char *answer = intal_multiply("76843625476325784617596748631576475610956405054873205208975489276829735082375084327589407832859743829751057432897544893678932157398012750193787589275083247548139075983125738192758937452375874329587432856472365743627523945432015367564327854647320564732564736573248","713883172881812213345844635768546522825168751161147417187751717742283562388771481142485263114311818135283616132755511146184885133651556411455128145782441154531831734167424765751731615215426872844656577264818284858885635361525544227154825437388271611175827525618817258732238388624875711161837318822486861121162147143738513437877638754568327548227861386614771113164238118152647183435614815");
// // 	// char *answer = intal_factorial(449);
// // 	// char *answer = intal_pow(a[5], 3);
// // 	// char *answer = coin_row_problem(a,n);
// // 	char *answer = intal_bincoeff(1000, 900);
// 	// char *answer = intal_mod(a[0], a[5]);
// // 	// char *answer = intal_mod("978", "979");
// // 	// char *answer = intal_gcd("5", "0");
// 	// char *result1;
// 	// char *answer = DivideBy2("3");
// 	char *answer = find_quotient("31","3");

// 	// result1 = intal_mod("20, "10");
//     // if (!result1)
//     // {
//     //     printf("Test intal_gcd FAILED.\n");
//     // }
//     // else
//     // {
//     //     if (0 == strcmp(result1, "3"))
//     //     {
//     //         printf("Test intal_gcd_1 PASSED\n");
//     //     }
//     //     else
//     //     {
//     //         printf("Test intal_gcd_1 FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "3");
//     //     }
//     //     free(result1);
//     // }

// 	 printf("Answer:%s \n",answer);

// }

