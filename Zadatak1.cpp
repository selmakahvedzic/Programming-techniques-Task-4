#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <stdexcept>
#include <memory>
#include <algorithm>


typedef std::pair <double, double> Tacka;

class Trougao {
    private:
    Tacka prva,druga,treca;
    public:
    
    Trougao(const Tacka &t1, const Tacka &t2, const Tacka &t3);
    void Postavi(const Tacka &t1, const Tacka &t2, const Tacka &t3);
    void Postavi(int indeks, const Tacka &t);
    static int Orijentacija(const Tacka &t1, const Tacka &t2, const Tacka &t3);
    Tacka DajTjeme(int indeks) const;
    double DajStranicu(int indeks) const;
    double DajUgao(int indeks) const;
    Tacka DajCentar() const;
    double DajObim() const;
    double DajPovrsinu() const;
    bool DaLiJePozitivnoOrijentiran() const;
    bool DaLiJeUnutra(const Tacka &t) const;
    void Ispisi() const;
    void Transliraj(double delta_x, double delta_y);
    void Centriraj(const Tacka &t);
    void Rotiraj(const Tacka &t, double ugao);
    void Skaliraj(const Tacka &t, double faktor);
    void Rotiraj(double ugao);
    void Skaliraj(double faktor);
    friend bool DaLiSuIdenticni(const Trougao &t1, const Trougao &t2);
    friend bool DaLiSuPodudarni(const Trougao &t1, const Trougao &t2);
    friend bool DaLiSuSlicni(const Trougao &t1, const Trougao &t2);
};

Trougao::Trougao(const Tacka &t1, const Tacka &t2, const Tacka &t3) { //ovo je konstruktor
    Postavi(t1,t2,t3);
}

void Trougao::Postavi(const Tacka &t1, const Tacka &t2,const Tacka &t3) {
    if(Orijentacija(t1,t2,t3)==0) throw std::domain_error("Nekorektne pozicije tjemena");
    Trougao::prva=t1;
    Trougao::druga=t2;
    Trougao::treca=t3;
}

void Trougao::Postavi(int indeks, const Tacka &t) {
    if(indeks!=1 && indeks!=2 && indeks!=3) throw std::range_error("Nekorektan indeks");
    if(indeks==1) Trougao::prva=t;
    if(indeks==2) Trougao::druga=t;
    if(indeks==3) Trougao::treca=t;
}

int Trougao::Orijentacija(const Tacka &t1, const Tacka &t2, const Tacka &t3) {
    double orijentacija=t1.first*(t2.second-t3.second)-t2.first*(t1.second-t3.second)+t3.first*(t1.second-t2.second);
    if(orijentacija>0) return 1;
    if(orijentacija<0) return -1;
    else return 0;
}

Tacka Trougao::DajTjeme(int indeks) const {
    if(indeks!=1 && indeks!=2 && indeks!=3) throw std::range_error("Nekorektan indeks");
    
    if(indeks==1) return prva;
    if(indeks==2) return druga;
    else return treca;
}

double Trougao::DajStranicu(int indeks) const {
    if(indeks!=1 && indeks!=2 && indeks!=3) throw std::range_error("Nekorektan indeks");
    
    if(indeks==1) {
        double duzina=sqrt(((druga.first-treca.first)*(druga.first-treca.first))+((druga.second-treca.second)*(druga.second-treca.second)));
        return duzina;
    }
    
    if(indeks==2) {
        double duzina=sqrt(((prva.first-treca.first)*(prva.first-treca.first))+((prva.second-treca.second)*(prva.second-treca.second)));
        return duzina;
    }
    
    if(indeks==3) {
        double duzina=sqrt(((prva.first-druga.first)*(prva.first-druga.first))+((prva.second-druga.second)*(prva.second-druga.second)));
        return duzina;
    }
}

double Trougao::DajUgao(int indeks) const {
    if(indeks!=1 && indeks!=2 && indeks!=3) throw std::range_error("Nekorektan indeks");
    
    if(indeks==1) {
        double a=DajStranicu(1);
        double b=DajStranicu(2);
        double c=DajStranicu(3);
        
        double alfa=((a*a-b*b-c*c)/(2*b*c))*(-1);
        alfa=acos(alfa);
        return alfa;
    }
    
    if(indeks==2) {
        double a=DajStranicu(2);
        double b=DajStranicu(1);
        double c=DajStranicu(3);
        
        double alfa=((a*a-b*b-c*c)/(2*b*c))*(-1);
        alfa=acos(alfa);
        return alfa;
    }
    
    if(indeks==3) {
        double a=DajStranicu(3);
        double b=DajStranicu(2);
        double c=DajStranicu(1);
        
        double alfa=((a*a-b*b-c*c)/(2*b*c))*(-1);
        alfa=acos(alfa);
        return alfa;
    }
}

Tacka Trougao::DajCentar() const {
    double xt=(prva.first+druga.first+treca.first)/3;
    double yt=(prva.second+druga.second+treca.second)/3;
    
    Tacka centar(xt,yt);
    return centar;
}

double Trougao::DajObim() const {
    double obim = DajStranicu(1) + DajStranicu(2) + DajStranicu(3);
    return obim;
}

double Trougao::DajPovrsinu() const {
    //Tacka t1,t2,t3;
    //double povrsina = 0.5*(abs(t1.first*(t2.second-t3.second) - t2.first*(t1.second-t3.second) + t3.first*(t1.second-t2.second)));
    
    double s = DajObim()/2;
    double povrsina = sqrt(s*(s-DajStranicu(1))*(s-DajStranicu(2))*(s-DajStranicu(3)));
    return povrsina;
}

bool Trougao::DaLiJePozitivnoOrijentiran() const {
    if(Orijentacija(prva,druga,treca)==1) return true;
    else return false;
}

bool Trougao::DaLiJeUnutra(const Tacka &t) const {
    double F1(0),F2(0),F3(0);
    
    F1=(t.first-druga.first)*(prva.second-druga.second)-(prva.first-druga.first)*(t.second-druga.second);
    F2=(t.first-treca.first)*(druga.second-treca.second)-(druga.first-treca.first)*(t.second-treca.second);
    F3=(t.first-prva.first)*(treca.second-prva.second)-(treca.first-prva.first)*(t.second-prva.second);
    
    bool b1 {};
    if(F1<0.00) b1=true;
    
    bool b2 {};
    if(F2<0.00) b2=true;
    
    bool b3 {};
    if(F3<0.00) b3=true;
    
    if(b1==true && b2==true && b3==true) return true;
    if(b1==false && b2==false && b3==false) return true;
    
    else return false;
}

void Trougao::Ispisi() const {
    std::cout << "((" << prva.first << "," << prva.second << "),(" << druga.first << "," << druga.second << "),(" << treca.first << "," << treca.second << "))";
}

void Trougao::Transliraj(double delta_x, double delta_y) {
    
    Trougao::prva.first+=delta_x;
    Trougao::prva.second+=delta_y;
    
    Trougao::druga.first+=delta_x;
    Trougao::druga.second+=delta_y;
    
    Trougao::treca.first+=delta_x;
    Trougao::treca.second+=delta_y;
    
}

void Trougao::Centriraj(const Tacka &t) {
    
    Tacka centar=Trougao::DajCentar();
    
    Trougao::prva.first+=(t.first-centar.first);
    Trougao::prva.second+=(t.second-centar.second);
    
    Trougao::druga.first+=(t.first-centar.first);
    Trougao::druga.second+=(t.second-centar.second);
    
    Trougao::treca.first+=(t.first-centar.first);
    Trougao::druga.second+=(t.second-centar.second);
    
}

void Trougao::Rotiraj(const Tacka &t, double ugao) {
    double xr1=t.first+(prva.first-t.first)*cos(ugao)-(prva.second-t.second)*sin(ugao);
    double yr1=t.second+(prva.first-t.first)*sin(ugao)+(prva.second-t.second)*cos(ugao);
    
    double xr2=t.first+(druga.first-t.first)*cos(ugao)-(druga.second-t.second)*sin(ugao);
    double yr2=t.second+(druga.first-t.first)*sin(ugao)+(druga.second-t.second)*cos(ugao);
    
    double xr3=t.first+(treca.first-t.first)*cos(ugao)-(treca.second-t.second)*sin(ugao);
    double yr3=t.second+(treca.first-t.first)*sin(ugao)+(treca.second-t.second)*cos(ugao);
    
    Tacka rnova1(xr1,yr1);
    Tacka rnova2(xr2,yr2);
    Tacka rnova3(xr3,yr3);
    
    Postavi(1, rnova1);
    Postavi(2, rnova2);
    Postavi(3, rnova3);
}


void Trougao::Skaliraj(const Tacka &t, double faktor) {
    
    if(faktor==0.00) throw std::domain_error("Nekorektan faktor skaliranja");
    
    double xs1=t.first+faktor*(prva.first-t.first);
    double ys1=t.second+faktor*(prva.second-t.second);
    
    double xs2=t.first+faktor*(druga.first-t.first);
    double ys2=t.second+faktor*(druga.second-t.second);
    
    double xs3=t.first+faktor*(treca.first-t.first);
    double ys3=t.second+faktor*(treca.second-t.second);
    
    Tacka snova1(xs1,ys1);
    Tacka snova2(xs2,ys2);
    Tacka snova3(xs3,ys3);
    
    Postavi(1, snova1);
    Postavi(2, snova2);
    Postavi(3, snova3);
    
}

void Trougao::Rotiraj(double ugao) {
    Tacka t=DajCentar();
    Rotiraj(t,ugao);
}

void Trougao::Skaliraj(double faktor) {
    Tacka t=DajCentar();
    Skaliraj(t,faktor);
}

bool DaLiSuIdenticni(const Trougao &t1, const Trougao &t2) {
    
    if((t1.DajTjeme(1)==t2.DajTjeme(1) || t1.DajTjeme(1)==t2.DajTjeme(2) || t1.DajTjeme(1)==t2.DajTjeme(3)) &&
       (t1.DajTjeme(2)==t2.DajTjeme(1) || t1.DajTjeme(2)==t2.DajTjeme(2) || t1.DajTjeme(2)==t2.DajTjeme(3)) &&
       (t1.DajTjeme(3)==t2.DajTjeme(1) || t1.DajTjeme(3)==t2.DajTjeme(2) || t1.DajTjeme(3)==t2.DajTjeme(3)))
       return true;
       else return false;
}


bool DaLiSuPodudarni(const Trougao &t1, const Trougao &t2) {
    
    if((Trougao::Orijentacija(t1.DajTjeme(1),t1.DajTjeme(2),t1.DajTjeme(3))<0 && Trougao::Orijentacija(t2.DajTjeme(1),t2.DajTjeme(2),t2.DajTjeme(3))<0)
    || (Trougao::Orijentacija(t1.DajTjeme(1),t1.DajTjeme(2),t1.DajTjeme(3))>0 && Trougao::Orijentacija(t2.DajTjeme(1),t2.DajTjeme(2),t2.DajTjeme(3))>0)) {
        if((t1.DajStranicu(1)==t2.DajStranicu(2) && t1.DajStranicu(2)==t2.DajStranicu(3) && t1.DajStranicu(3)==t2.DajStranicu(1)) 
        || (t1.DajStranicu(1)==t2.DajStranicu(1) || t1.DajStranicu(2)==t1.DajStranicu(2) || t1.DajStranicu(3)==t1.DajStranicu(3))
        || (t1.DajStranicu(1)==t2.DajStranicu(3) || t1.DajStranicu(2)==t2.DajStranicu(1) || t1.DajStranicu(3)==t2.DajStranicu(2))) 
        
        return true;
        else return false;
         
        } else {
            if((t1.DajStranicu(1)==t2.DajStranicu(1) && t1.DajStranicu(2)==t2.DajStranicu(3) && t1.DajStranicu(3)==t2.DajStranicu(2))
            || (t1.DajStranicu(1)==t2.DajStranicu(3) && t1.DajStranicu(2)==t2.DajStranicu(2) && t1.DajStranicu(3)==t2.DajStranicu(1))
            || (t1.DajStranicu(1)==t2.DajStranicu(2) && t1.DajStranicu(2)==t2.DajStranicu(1) && t1.DajStranicu(3)==t2.DajStranicu(3))) 
            
            return true;
            else return false;
            }
        }
        

bool DaLiSuSlicni(const Trougao &t1, const Trougao &t2) {
    
    if((Trougao::Orijentacija(t1.DajTjeme(1),t1.DajTjeme(2),t1.DajTjeme(3))<0 && Trougao::Orijentacija(t2.DajTjeme(1),t2.DajTjeme(2),t2.DajTjeme(3))<0)
    || (Trougao::Orijentacija(t1.DajTjeme(1),t1.DajTjeme(2),t1.DajTjeme(3))>0 && Trougao::Orijentacija(t2.DajTjeme(1),t2.DajTjeme(2),t2.DajTjeme(3))>0)) {
        if((t1.DajUgao(1)==t2.DajUgao(2) && t1.DajUgao(2)==t2.DajUgao(3) && t1.DajUgao(3)==t2.DajUgao(1))
        || (t1.DajUgao(1)==t2.DajUgao(3) && t1.DajUgao(2)==t2.DajUgao(1) && t1.DajUgao(3)==t2.DajUgao(2)))
        return true;
        else return false;
    } else {
        if((t1.DajUgao(1)==t2.DajUgao(1) && t1.DajUgao(2)==t2.DajUgao(3) && t1.DajUgao(3)==t2.DajUgao(2))
        || (t1.DajUgao(1)==t2.DajUgao(3) && t1.DajUgao(2)==t2.DajUgao(2) && t1.DajUgao(3)==t2.DajUgao(1))
        || (t1.DajUgao(1)==t2.DajUgao(2) && t1.DajUgao(2)==t2.DajUgao(1) && t1.DajUgao(3)==t2.DajUgao(3)))
        return true;
        else return false;
    }
}


int main ()
{
    
    std::cout << "Koliko želite kreirati trouglova: ";
    int n(0);
    std::cin >> n;
    
    std::vector<std::shared_ptr<Trougao>> v(n);
    
    double x,y;
    
    for(int i=0; i<n; i++) {
        Tacka t1,t2,t3;
        std::cout << "Unesite podatke za " << i+1 << ". trougao (x1 y1 x2 y2 x3 y3): ";
        for(int t=1; t<=3; t++) {
            std::cin >> x >> y;
            
            if(t==1) t1=std::pair<double,double>(x,y);
            if(t==2) t2=std::pair<double,double>(x,y);
            if(t==3) t3=std::pair<double,double>(x,y);
        }
        
        while((t1.first*(t2.second-t3.first)-t2.first*(t1.second-t3.second)+t3.first*(t1.second-t2.second))==0) {
            std::cout << "Nekorektne pozcije tjemena" << ", ponovite unos!" << std::endl;

            
            std::cout << "Unesite podatke za " << i+1 << ". trougao (x1 y1 x2 y2 x3 y3): ";
            for(int t=1; t<=3; t++) {
                std::cin >> x >> y;
                
                if(t==1) t1=std::pair<double,double>(x,y);
                if(t==2) t2=std::pair<double,double>(x,y);
                if(t==3) t3=std::pair<double,double>(x,y);
            }
        }
    }
    
    double faktor, ugao, delta_x, delta_y;
    
    std::cout << "Unesite vektor translacije (dx dy): ";
    std::cin >> delta_x >> delta_y;
    
    std::cout << "Unesite ugao translacije: ";
    std::cin >> ugao;
    
    std::cout << "Unesite faktor skaliranja: ";
    std::cin >> faktor;
    
    std::transform(v.begin(), v.end(), v.begin(), [faktor, ugao, delta_x, delta_y] (std::shared_ptr<Trougao> x) {
        x->Transliraj(delta_x,delta_y);
        x->Rotiraj(x->DajCentar(),ugao);
        x->Skaliraj(x->DajTjeme(1),faktor);
        return x;
    });
    
    std::sort(v.begin(), v.end(), [] (std::shared_ptr<Trougao> x, std::shared_ptr<Trougao> y) {
        return x->DajPovrsinu() < y->DajPovrsinu();
    });
    
    std::cout << "Trouglovi nakon obavljenih transformacija: " << std::for_each(v.begin(), v.end(), [] (std::shared_ptr<Trougao> x) {
        x->Ispisi();
    });;
    
    std::cout << "\nTrougao sa najmanjim obimom: "; 
    (*std::min_element(v.begin(),v.end(), [] (std::shared_ptr<Trougao>x, std::shared_ptr<Trougao>y) {
        return x->DajObim() > y->DajObim();
    })) -> Ispisi();;;
    
    Tacka t1{0,1},t2{0,1},t3{0,1};
    Trougao t11(t1,t2,t3), t22(t1,t2,t3);
    
    bool NisuIdenticni=true;
    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(DaLiSuIdenticni(t11,t22))
            std::cout << "\nParovi identicnih trouglova:";
            t11.Ispisi();
            t22.Ispisi();
        }
    }
    if(NisuIdenticni) std::cout << "\nNema identicnih trouglova!";
    
    bool NisuPodudarni=true;
    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(DaLiSuPodudarni(t11,t22))
            std::cout << "\nParovi podudarnih trouglova:";
            t11.Ispisi();
            t22.Ispisi();
        }
    }
    if(NisuPodudarni) std::cout << "\nNema podudarnih trouglova!";
    
    bool NisuSlicni=true;
    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(DaLiSuSlicni(t11,t22))
            
            std::cout << "\nParovi slicnih trouglova:";
            t11.Ispisi();
            t22.Ispisi();
        }
    }
    if(NisuSlicni) std::cout << "\nNema slicnih trouglova!";
    
	return 0;
}
