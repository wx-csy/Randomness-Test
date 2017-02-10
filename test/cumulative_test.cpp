namespace test{

    double cumulative_test(const std::vector<bool> &bits){
        if(bits.size()==0){
            cerr<<"Illegal parameter!"<<endl;
            throw;
        }

        int n = bits.size();
        int S = 0;
        int Z = 0;
        double P = 1.0;
        for (int i=0; i<n; i++){
            if(bits[i]) S++; else S--;
            Z = max(Z, abs(S));
        }

        for (int i=((-n/Z)+1)/4; i<=((n/Z)-1)/4; i++){
            P-=normal_CDF((4*i+1)*Z/sqrt(n))-normal_CDF((4*i-1)*Z/sqrt(n));
        }
        for (int i=((-n/Z)-3)/4; i<=((n/Z)-1)/4; i++){
            P+=normal_CDF((4*i+3)*Z/sqrt(n))-normal_CDF((4*i+1)*Z/sqrt(n));
        }

        cout<<"Cumulative test:"<<endl;
        cout<<"    n   = "<<n<<endl;
        cout<<"    Z   = "<<Z<<endl;
        cout<<"    P   = "<<fixed<<setprecision(4)<<P*100<<"%"<<endl;
        return P;
    }

}
