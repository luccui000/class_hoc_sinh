#include "hocsinh.h"
#include "diachi.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <random>

#define MONHOC 7

void remove_endline() {
  while ((getchar()) != '\n');
}
float rdFloat(int limit) {
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis(0.0, limit);
  return dis(gen);
}
std::vector<float> rdDiem() {
  std::vector<float> f;
  for(int i = 0; i < MONHOC; i++) {
    f.push_back(rdFloat(10));
  }
  return f;
}
void convertArrToS(const Diem& diem, DiemSo &ds) {
  ds.toan = diem.diem[0];
  ds.ly = diem.diem[1];
  ds.hoa = diem.diem[2];
  ds.sinh = diem.diem[3];
  ds.nguvan = diem.diem[4];
  ds.lichsu = diem.diem[5];
  ds.diali = diem.diem[6];
}
bool isF = true;
bool isE = true;
class QLSV {
  private:
    Hocsinh m_hs;
    Diem m_diem;
    DiemSo m_ds;
    static float dtb;
  public:
    QLSV(Hocsinh hs, DiemSo ds): m_hs(hs), m_ds(ds) { } 
    QLSV(const std::string &s, int tuoi, const std::string& diachi, std::initializer_list<float> ds) {
      m_hs.hoten = s;
      m_hs.tuoi = tuoi;
      m_hs.diachi = diachi;
      int i = 0; 
      for(auto it : ds) 
        this->m_diem.diem[i++] = it;
    };
    QLSV(const std::string &s, int tuoi, enum TINH t, std::vector<float> vec) {
      m_hs.hoten = s;
      m_hs.tuoi = tuoi;
      m_hs.diachi = tinhthanh[t];
      int i = 0; 
      for(auto it : vec) 
        this->m_diem.diem[i++] = it;
    };
    QLSV(const std::string &s, int tuoi, TINH t, std::initializer_list<float> ds) {
      m_hs.hoten = s;
      m_hs.tuoi = tuoi;
      m_hs.diachi = tinhthanh[t];
      int i = 0; 
      for(auto it : ds) 
        this->m_diem.diem[i++] = it;
    };
    QLSV(const std::string &s, int tuoi, const std::string& diachi, DiemSo ds){
      m_hs.hoten = s;
      m_hs.tuoi = tuoi;
      m_hs.diachi = diachi;
      convertArrToS(m_diem, ds);
    };
    QLSV* operator=(QLSV& sv) {
      this->m_hs = sv.m_hs;
      this->m_diem = sv.m_diem;
      this->m_ds = sv.m_ds;
      this->dtb = sv.dtb;
      return this; 
    }
    friend std::ostream& operator<<(std::ostream& os, const QLSV& sv) {
      if(isF) {
        os << "\n\t=================================== QUAN LI HOC SINH =====================================\n";
        os << "\t+------------------+------+----------+------+----+-----+------+-----+----+-----+---------+\n";
        os << "\t|        Ten       | Tuoi | Dia Chi  | Toan | Li | Hoa | Sinh | Van | Su | Dia | Diem TB |\n";
        os << "\t+------------------+------+----------+------+----+-----+------+-----+----+-----+---------+\n"; 
        isF = false;
      }
      os << "\t|";
      os << std::setw(18);
      os << sv.m_hs.hoten;
      os << "|";
      os << std::setw(6);
      os << sv.m_hs.tuoi;
      os << "|";
      os << std::setw(10);
      os << sv.m_hs.diachi;
      os << "|";
      os << std::setw(6);
      os << sv.m_diem.diem[0];
      os << "|";
      os << std::setw(4);
      os << sv.m_diem.diem[1];
      os << "|";
      os << std::setw(5);
      os << sv.m_diem.diem[2];
      os << "|";
      os << std::setw(6);
      os << sv.m_diem.diem[3];
      os << "|";
      os << std::setw(5);
      os << sv.m_diem.diem[4];
      os << "|";
      os << std::setw(4);
      os << sv.m_diem.diem[5];
      os << "|";
      os << std::setw(5);
      os << sv.m_diem.diem[6];
      os << "|";
      os << std::setw(9);
      float d = 0.0f;
      for(int i = 0; i < 7; i++)
        d += sv.m_diem.diem[i];
      dtb = d / MONHOC;
      os << std::setprecision(2) << std::fixed << dtb << "|\n";
      os << "\t+------------------+------+----------+------+----+-----+------+-----+----+-----+---------+\n"; 
      return os;
    }
    float getDTB() {
      float d = 0.0f;
      for(int i = 0; i < 7; i++)
        d += this->m_diem.diem[i];
      return d / MONHOC;
    }
    std::string getName() {
      return m_hs.hoten;
    }
};
float QLSV::dtb = 0.0f;
template<typename T>
void swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}
void bubblesort(std::vector<QLSV*>& sv) {
  for(int i = 0; i < sv.size(); i++) {
    for(int j = i + 1; j < sv.size(); j++) {
      float s1 = sv[i]->getDTB();
      float s2 = sv[j]->getDTB();
      if(s1 < s2) 
        swap<QLSV>(*sv[i], *sv[j]);
    }
  }
}
void fillChar(const std::vector<QLSV*> & sv) {
  std::cout << std::setfill(' ') << std::setw(60);
  std::cout << "BIEU DO\n\n";
  for(int i = 0; i < sv.size(); i++){
    std::cout << std::setfill(' ') << std::setw(20);
    std::cout << sv[i]->getName() << " | ";
    std::cout << std::setfill('=') << std::setw(sv[i]->getDTB() * 10) << ' ';
    std::cout << '\n';
  }

  std::cout << std::setfill(' ') << std::setw(22);
  std::cout << " |";
  std::cout << std::setfill('_') << std::setw(100) << '\n';

  std::cout << std::setfill(' ') << std::setw(12);
  std::cout << "  ";
  for(int i = 0; i <= 10; i++) {
    std::cout << std::setfill(' ') << std::setw(10);
    std::cout << i;
  }
  std::cout << '\n';
}
int main() {

  QLSV *h1 = new QLSV("Luc Cui", 20, "Tra Vinh", std::initializer_list<float>({10.0f, 7.5f, 8.9f, 7.3f, 8.9f, 5.8f, 7.5f}));
  QLSV *h2 = new QLSV("Nguyen Van A", 25, "Ha Noi", std::initializer_list<float>({6.8f, 2.5f, 6.0f, 9.7f, 4.6f, 7.8f, 8.0f}));
  QLSV *h3 = new QLSV("Bui Tan Tai", 23, "Vinh", std::initializer_list<float>({5.6f, 4.6f, 6.7f, 7.0f, 5.6f, 8.8f, 8.5f}));
  QLSV *h4 = new QLSV("Ngo Tan Tai", 21, "Da Nang", std::initializer_list<float>({7.6f, 9.6f, 5.7f, 7.0f, 7.6f, 7.8f, 6.5f}));
  QLSV *h5 = new QLSV("Tran Van Hang", 22, "Hue", std::initializer_list<float>({7.6f, 7.6f, 7.7f, 7.0f, 6.6f, 3.8f, 2.5f}));
  QLSV *h6 = new QLSV("Ngo Thi Hoa", 23, "Dong Nai", std::initializer_list<float>({7.6f, 9.6f, 9.7f, 9.0f, 9.6f, 9.8f, 10.0f}));
  QLSV *h7 = new QLSV("Nguyen Thi Tien", 20, "TpHCM", std::initializer_list<float>({4.6f, 4.6f, 4.7f, 1.0f, 5.6f, 4.8f, 4.5f}));
  QLSV *h8 = new QLSV("Le Tran Phu", 26, "TpHCM", std::initializer_list<float>({5.4f, 7.6f, 7.7f, 7.5f, 4.5f, 8.8f, 4.5f}));
  QLSV *h9 = new QLSV("Le Bao Ngoc", 26, TINH::ANGIANG, std::initializer_list<float>({8.4f, 6.6f, 9.7f, 7.5f, 5.5f, 8.8f, 4.5f}));
  QLSV *h10 = new QLSV("Dang Van Lam", 24, TINH::HANOI, std::vector<float>{8.4f, 6.6f, 9.7f, 7.5f, 5.5f, 8.8f, 4.5f});
  QLSV *h11 = new QLSV("Ngo Gia Bao", 24, TINH::SOCTRANG, rdDiem()); 

  std::vector<QLSV*> sv;
  
  sv.push_back(h1);
  sv.push_back(h2);
  sv.push_back(h3);
  sv.push_back(h4);
  sv.push_back(h5);
  sv.push_back(h6);
  sv.push_back(h7);
  sv.push_back(h8);
  sv.push_back(h9);
  sv.push_back(h10);
  sv.push_back(h11);

  for(auto i : sv) 
    std::cout << *i;
  fillChar(sv);
  bubblesort(sv);
  isF = true;
  for(auto i : sv) 
    std::cout << *i;
  std::cout << '\n';
  fillChar(sv);

  return 0;
}
