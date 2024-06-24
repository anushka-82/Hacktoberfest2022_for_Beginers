#include<bits/stdc++.h>
using namespace std;
static int c=0;
int binarysearch(int a[],int l,int r,int key)
{   
    c++;
    if(l>=r)
    {
        if(a[l]<key)
        {
            return l+1;
        }
        else
        {
            return l;
        }
    }
    int mid=(l+r)/2;
    if(a[mid]==key)
        return mid+1;
    if(a[mid]<key)
        return binarysearch(a,mid+1,r,key);
    return binarysearch(a,l,mid-1,key);
}
int main()
{
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<n;i++)
    {
        int j=i-1;
        int temp=a[i];
        int result=binarysearch(a,0,j,temp);
        
        while(result<=j)
        {
            swap(a[j],a[j+1]);
            j--;
        }
        a[j+1]=temp;
    }
    cout<<"Sorted array: ";
    for(int i=0;i<n;i++)
    {   
        cout<<a[i]<<" ";
    }
    cout<<endl<<c<<endl;
return 0;
}
