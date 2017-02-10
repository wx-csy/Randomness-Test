namespace algo{

    bool* newBoolArray(unsigned int n){
        bool* tmp;
        tmp = new bool[n];
        memset(tmp, false, sizeof(bool)*n);
        return tmp;
    }

    void shlBoolArray(bool* a, unsigned int n, unsigned int c){
        for (int i=n-c-1; i>=0; i--) a[i+c]=a[i];
        for (int i=0; i<c ;i++) a[i]=0;
    }

    void addBoolArray(bool* a, const bool* b, unsigned int n){
        for (int i=0; i<n; i++){
            a[i] = a[i] ^ b[i];
        }
    }

    void copyBoolArray(bool* a, const bool* b, unsigned int n){
        for (int i=0; i<n; i++){
            a[i] = b[i];
        }
    }

    bool computeConvolution(const bool* a, const bool* b, unsigned int n){
        bool tmp=false;
        for (int i=0; i<n; i++){
            if (*(a+i) && *(b-i)) tmp=!tmp;
        }
        return tmp;
    }

    int berlekamp_massey(const bool* a, unsigned int n) {
        int* l;
        bool** f;
        bool d;
        int m;
        l = new int[n+1];
        f = new bool*[n+1];
        for (int i=0; i<=n; i++) f[i] = newBoolArray(n);
        f[0][0]=true; l[0]=0;
        for (int i=0; i<n; i++){
            d = computeConvolution(f[i], a+i, l[i]+1);
            if (d){
                if (l[i]==0){
                    f[i+1][0]=true;
                    f[i+1][i+1]=true;
                    l[i+1]=i+1;
                } else {
                    m = lower_bound(l, l+i, l[i]) - l - 1;
                    copyBoolArray(f[i+1], f[m], n);
                    shlBoolArray(f[i+1], n, i-m);
                    addBoolArray(f[i+1], f[i], n);
                    l[i+1]=max(l[i], i+1-l[i]);
                }
            } else {
                copyBoolArray(f[i+1], f[i], n);
                l[i+1]=l[i];
            }
        }
        for (int i=0; i<=n; i++) delete[] f[i];
        delete[] f;
        m=l[n-1];
        delete[] l;
        return m;
    }

}
