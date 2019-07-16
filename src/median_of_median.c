#include <stdio.h>

// 素数
#define N 2999

int A[N];

// *p と *q の値を入れ替える関数
void swap(int *p, int *q){
  int tmp;
  tmp = *p;
  *p = *q;
  *q = tmp;
}

int quick_select(int A[], int n, int k){
  int i, j, pivot;

// 真ん中の要素をピボットとする
  pivot = A[n/2];
  A[n/2] = A[0];
  A[0] = pivot ;
  int same = 0;
  for(i = j = 1; i < n; i++){
    if(A[i] < pivot){
      swap(A+i, A+j);
      j++;
    }
    else if(A[i] == pivot){
        swap(A+i,A+j);
        swap(A+same,A+j);
        same++;
        j++;
    }
  }
  if(j == k) return pivot;
  else if(j < k) return quick_select(A+j+same, n-j-same, k-j);
  else return quick_select(A+1+same, j-1, k);

}


int median(int A[], int n, int k){
  int i,j;
  int B[N];
  int length = (n+4)/5;
  if (n <= 5){
      return quick_select(A,n,n/2);
    }
  else{
    for(int i = 0; i < n;i++){
      B[i] = A[i];
    }
    int l = n;
    while(l > 5){
      for(i = j = 0; 5*i < l-5; i++) {
        B[i] = quick_select(B+5*i,5,2);
        j++;
      }
      B[j] = quick_select(B+5*j,l-5*5,(l-5*j)/2);
      l = j + 1;
    }

    int pivot = median(B,length,length/2);
    int i,j,same;
    same = 0;
    for(i = j = 0; i < n; i++){
      if(A[i] < pivot){
        swap(A+i, A+j);
        j++;
      }
      else if(A[i] == pivot){
          swap(A+i,A+j);
          swap(A+same,A+j);
          same++;
          j++;
      }
    }


    for(i=0; i<=same;i++){
     swap(A+i,A+j-i-1);   /*pivotはj-same番目に小さい要素*/
    }
    int r = j;
    if (j-same <= k && j >= k+1) return pivot;
    else if (r < k) return median(A+j,n-r,k-r);
    else  return median(A,j-same-1,k);
  }

  }




int main(){
  int i;
  A[0] = 0;
  A[1] = 17; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  median(A,N,N/2);
  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
