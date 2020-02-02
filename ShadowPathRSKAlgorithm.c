//Shadow path algorithm for Robinson-Schensted-Knuth(RSK) correspondence
//Based on Viennot's ideas for finding the irreducible representations of the symmetric group


//Young Tableaux implementation. Note that the monotonic conditions must be satisfied

#include<iostream>
#include<vector>
using namespace std;

class RSKShadowPath{
    //Integer matrices that will provide the Young Tableaux
    vector<vector<int>> A;
    vector<vector<int>> S;//Shadow Matrix
    vector<vector<int>> MaxPoints;//Stores coordinate pairs for the maximal elements
    vector<vector<int>> ShadowPoints;//Obtained from the MaxPoints, see doc
    vector<int> p;//stores terminal column numbers
    vector<int> q;//stores terminal row numbers
    //Young Tableaux
    vector<vector<int>> P;
    vector<vector<int>> Q;

    public:
    //Constructor for RSKShadowPath Class
    RSKShadowPath(vector<vector<int>> X, vector<vector<int>> Y){ //A,S must be square matrices of the same size
        A=X;
        S=Y;
    }

    //Returns the coordiantes of the maximal points(see. doc for more info)
    void ShadowPath(){
        int n=A.size();
        if(A[0][0]!=0){
            int jmax=n;
            for(int i=0;i<n;i++){
                for(int j=0;j<jmax;j++){
                    if(A[i][j]!=0){
                        jmax=j;
                        MaxPoints.push_back({i,j});
                        if(q.size()==0)
                            q.push_back(i+1);//Inserts terminal row number
                        A[i][j]=A[i][j]-1; //Subtract 1 from the maximal points
                    }
                }
            }
            p.push_back(jmax); //Inserts terminal column number
            for(int k=0;k<MaxPoints.size()-1;k++){
                ShadowPoints.push_back({MaxPoints[k+1][0],MaxPoints[k][1]});//Calculating shadow points
                S[ShadowPoints[k][0]][ShadowPoints[k][1]]+=1;
            }
        }
    }

    void RSK(){
        //Keep running the Shadow Path algorithm until A is exhausted
        int i=0;
        vector<vector<int>> zero;zero.resize(S.size());
        for(int k=0;k<S.size();k++)
            zero[i].resize(S.size());
        while(!(S==zero)){
            while(!(A==zero)){
                ShadowPath();
            }
            //Append rows of the Semi-Standard Young Tableaux pair
            for(int j=0;j<P.size();j++){
                P[i][j]=p[j];
                Q[i][j]=q[j];
            }
            //Reinitialize p,q to 0
            p.clear();
            q.clear();
            //Repeat the algorithm on A replaced by S.
            A=S;
            S=zero;
        }
    }
};


