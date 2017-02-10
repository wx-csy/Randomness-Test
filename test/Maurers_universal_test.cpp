namespace test{

    double Maurers_universal_test(const vector<bool> &bits, unsigned int L, unsigned int Q){
        if (bits.size()==0 || L<=5 || L>16 || bits.size()<L*(Q+1)){
            cerr<<"Illegal parameter!"<<endl;
            throw;
        }

        int* T = new int[1<<L];
        int mask = 1<<L-1;
        int n = bits.size();
        int K = n/L-Q;
        int n_disc = n%L;
        double sum=0.0;
        double V=0;
        double P;
        const double expected_value[17] = { 0, 0, 0, 0, 0, 0, 5.2177052, 6.1962507, 7.1836656,
				8.1764248, 9.1723243, 10.170032, 11.168765,
				12.168070, 13.167693, 14.167488, 15.167379 };
        const double variance[17] = { 0, 0, 0, 0, 0, 0, 2.954, 3.125, 3.238, 3.311, 3.356, 3.384,
				3.401, 3.410, 3.416, 3.419, 3.421 };

        unsigned int tmp;
        memset(T, 0, sizeof(int)<<L);
        vector<bool>::const_iterator it=bits.begin();
        for (int i=1; i<=Q; i++){
            for (int j=0; j<L; j++){
                tmp<<=1;
                if (*it) tmp++;
                it++;
            }
            T[tmp&mask]=i;
        }

        for (int i=Q+1; i<=Q+K; i++){
            for (int j=0; j<L; j++){
                tmp<<=1;
                if (*it) tmp++;
                it++;
            }
            sum+=log(i-T[tmp&mask])/log(2.0);
            T[tmp&mask]=i;
        }

        V=(sum/K-expected_value[L])/variance[L];
        P=erfc(fabs(V)/sqrt(2.0));

        cout<<"Maurer's universal test:"<<endl;
        cout<<"    n   = "<<n<<endl;
        cout<<"    L   = "<<L<<endl;
        cout<<"    K   = "<<K<<endl;
        cout<<"    Q   = "<<Q<<endl;
        cout<<"   sum  = "<<fixed<<setprecision(6)<<sum<<endl;
        cout<<"    V   = "<<fixed<<setprecision(6)<<V<<endl;
        cout<<"    P   = "<<fixed<<setprecision(4)<<P*100<<"%"<<endl;
        cout<<"  "<<n_disc<<" bits are discarded."<<endl;

        delete[] T;
        return P;
    }

}
