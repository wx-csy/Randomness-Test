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

    // there's something wrong with this procedure
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

    int b2i(bool b){
        return b?1:0;
    }

    int linear_complexity(const bool* a, unsigned int M){
        int N_=0, L=0, m=-1, d=0;
        int *B_, *C, *P, *T;
        B_ = new int[M];
        C = new int[M];
        P = new int[M];
        T = new int[M];
        for (int i=0; i<M; i++ ) {
			B_[i] = 0;
			C[i] = 0;
			T[i] = 0;
			P[i] = 0;
		}
        C[0] = 1;
        B_[0] = 1;
		while ( N_ < M ) {
			d = b2i(a[N_]);
			for (int i=1; i<=L; i++ )
				d += C[i] * b2i(a[N_-i]);
			d = d%2;
			if ( d == 1 ) {
				for (int i=0; i<M; i++ ) {
					T[i] = C[i];
					P[i] = 0;
				}
				for (int j=0; j<M; j++ )
					if ( B_[j] == 1 )
						P[j+N_-m] = 1;
				for (int i=0; i<M; i++ )
					C[i] = (C[i] + P[i])%2;
				if ( L <= N_/2 ) {
					L = N_ + 1 - L;
					m = N_;
					for (int i=0; i<M; i++ )
						B_[i] = T[i];
				}
			}
			N_++;
		}
        delete[] B_;
        delete[] C;
        delete[] P;
        delete[] T;
        return L;
    }

}
