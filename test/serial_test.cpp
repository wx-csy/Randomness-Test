namespace test{

    double serial_test_P2;
    double serial_test(vector<bool> &bits, unsigned int m){
        if (bits.size()==0 || m<2 || m>30){
            cerr<<"Illegal parameter!"<<endl;
            throw;
        }

        int* patterns1 = new int[1<<m];
        int* patterns2 = new int[1<<(m-1)];
        int* patterns3 = new int[1<<(m-2)];
        int n = bits.size();
        double Phi1=0, Phi2=0, Phi3=0;
        double DPhi2, D2Phi2;
        double P1, P2;
        unsigned int mask1=(1<<m)-1, mask2=(1<<(m-1))-1, mask3=(1<<(m-2))-1;
        unsigned int tmp;

        for (int i=0; i<m-1; i++){
            bits.push_back(bits[i]);
        }

        memset(patterns1, 0, sizeof(int)<<m);
        memset(patterns2, 0, sizeof(int)<<(m-1));
        memset(patterns3, 0, sizeof(int)<<(m-2));
        vector<bool>::const_iterator it=bits.begin();

        for (int i=0; i<m-1; i++){
            tmp<<=1;
            if (*it) tmp++;
            it++;
        }
        for (int i=0; i<n; i++){
            tmp<<=1;
            if (*it) tmp++;
            it++;
            patterns1[tmp&mask1]++;
            patterns2[tmp&mask2]++;
            patterns3[tmp&mask3]++;
        }

        for (int i=0; i<=mask1; i++)
            Phi1+=pow(patterns1[i],2.0);
        Phi1*=(mask1+1); Phi1/=n; Phi1-=n;
        for (int i=0; i<=mask2; i++)
            Phi2+=pow(patterns2[i],2.0);
        Phi2*=(mask2+1); Phi2/=n; Phi2-=n;
        for (int i=0; i<=mask3; i++)
            Phi3+=pow(patterns3[i],2.0);
        Phi3*=(mask3+1); Phi3/=n; Phi3-=n;

        DPhi2=Phi1-Phi2;
        D2Phi2=Phi1-2*Phi2+Phi3;

        P1=igamc((1<<m)/4.0, DPhi2/2.0);
        P2=igamc((1<<m)/8.0, D2Phi2/2.0);

        for (int i=0; i<m-1; i++){
            bits.pop_back();
        }

        cout<<"Serial test:"<<endl;
        cout<<"    n   = "<<n<<endl;
        cout<<"    m   = "<<m<<endl;
        cout<<"  Phi1  = "<<fixed<<setprecision(6)<<Phi1<<endl;
        cout<<"  Phi2  = "<<fixed<<setprecision(6)<<Phi2<<endl;
        cout<<"  Phi3  = "<<fixed<<setprecision(6)<<Phi3<<endl;
        cout<<"  DPhi2 = "<<fixed<<setprecision(6)<<DPhi2<<endl;
        cout<<" D2Phi2 = "<<fixed<<setprecision(6)<<D2Phi2<<endl;
        cout<<"    P1  = "<<fixed<<setprecision(4)<<P1*100<<"%"<<endl;
        cout<<"    P2  = "<<fixed<<setprecision(4)<<P2*100<<"%"<<endl;

        serial_test_P2=P2;

        delete[] patterns1;
        delete[] patterns2;
        delete[] patterns3;
        return P1;
    }

    double serial_test2(const vector<bool> &bits){
        return serial_test_P2;
    }
}
