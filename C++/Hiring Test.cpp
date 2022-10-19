#include <iostream>
#include<bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    int n,m,l=0;
	    cin>>n>>m;
	    int x,y;
	    cin>>x>>y;
	    string arr[n];
	    int ans[n];
	    int full=0,partial=0,unsolved=0;
	    for(int i=0;i<n;i++){
	        cin>>arr[i];
	    }
	   for(int j=0;j<n;j++){
	       string str=arr[j];
	       for(int k=0;k<m;k++){
	           if(str[k]=='F'){
	           full++;}
	           else if(str[k]=='P'){
	           partial++;}
	           else if(str[k]=='U'){
	           unsolved++;}
	       }
	       if(full>=x || ((full==(x-1)) && (partial>=y))){
	           ans[l]=1;
	       }
	       else{
	           ans[l]=0;
	       }
	       full=0;
	       partial=0;
	       unsolved=0;
	       l++;
	   }  
	   for(int p=0;p<n;p++){
	       cout<<ans[p];
	   }
	   cout<<endl;
	}
	return 0;
}
