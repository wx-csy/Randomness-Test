namespace test{

    double frequency_test_within_a_block(const vector<bool> &bits, int m){
        if (bits.size()==0 || m<=0 || bits.size()<m){
            cerr<<"Illegal parameter!"<<endl;
            throw;
        }

        int n = bits.size();
        int N = n/m;
        int n_disc = n%m;
        double Pi;
        double V=0;
        double P;

        vector<bool>::const_iterator it=bits.begin();
        for (int i=0; i<N; i++){
            Pi=0;
            for (int j=0; j<m; j++){
                if (*it) Pi++;
                it++;
            }
            Pi/=m;
            V+=(Pi-0.5)*(Pi-0.5);
        }
        V*=4.0*m;

        P=igamc(N/2.0, V/2.0);

        cout<<"Frequency test within a block:"<<endl;
        cout<<"    n   = "<<n<<endl;
        cout<<"    m   = "<<m<<endl;
        cout<<"    N   = "<<N<<endl;
        cout<<"    V   = "<<fixed<<setprecision(6)<<V<<endl;
        cout<<"    P   = "<<fixed<<setprecision(4)<<P*100<<"%"<<endl;
        cout<<"  "<<n_disc<<" bits are discarded."<<endl;
        return P;
    }

}
