#include "hocsinh.h"
#include "diachi.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <random>
#include <fstream>
#include <errno.h>
#include <string.h>
#include <stack>
#include <queue>
#include <jsoncpp/json/json.h>

#define MONHOC 7

void remove_endline() {
  while ((getchar()) != '\n');
}
enum XEPLOAI {
  XUATSAC,
  GIOI,
  KHA,
  TRUNGBINH,
  YEU,
  KEM
};
std::string XepLoai(XEPLOAI xl) {
  std::string s;
  switch(xl) {
    case XEPLOAI::XUATSAC:
      s = "Xuat Sac";
      break;
    case XEPLOAI::GIOI:
      s = "Gioi";
      break;
    case XEPLOAI::KHA:
      s = "Kha";
      break;
    case XEPLOAI::TRUNGBINH:
      s = "Trung Binh";
      break;
    case XEPLOAI::YEU:
      s = "Yeu";
      break;
    case XEPLOAI::KEM:
      s = "Kem";
      break;
  }
  return s;
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
struct SV {
  std::string name;
  int age;
  std::string diachi;
  Diem d[7];
};
class QLSV {
  private:
    Hocsinh m_hs;
    Diem m_diem;
    DiemSo m_ds;
    static float dtb;
  public:
    QLSV() {}
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
    QLSV(const std::string &s, int tuoi, const std::string& addr, std::vector<float> vec) {
      m_hs.hoten = s;
      m_hs.tuoi = tuoi;
      m_hs.diachi = addr;
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
        os << "\t+------------------+------+----------+------+----+-----+------+-----+----+-----+---------+----------+\n";
        os << "\t|        Ten       | Tuoi | Dia Chi  | Toan | Li | Hoa | Sinh | Van | Su | Dia | Diem TB | Xep Loai |\n";
        os << "\t+------------------+------+----------+------+----+-----+------+-----+----+-----+---------+----------+\n"; 
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
      os << std::setprecision(2) << std::fixed <<sv.m_diem.diem[0];
      os << "|";
      os << std::setw(4);
      os << std::setprecision(2) << std::fixed <<sv.m_diem.diem[1];
      os << "|";
      os << std::setw(5);
      os << std::setprecision(2) << std::fixed <<sv.m_diem.diem[2];
      os << "|";
      os << std::setw(6);
      os << std::setprecision(2) << std::fixed <<sv.m_diem.diem[3];
      os << "|";
      os << std::setw(5);
      os <<std::setprecision(2) << std::fixed << sv.m_diem.diem[4];
      os << "|";
      os << std::setw(4);
      os << std::setprecision(2) << std::fixed <<sv.m_diem.diem[5];
      os << "|";
      os << std::setw(5);
      os << std::setprecision(2) << std::fixed <<sv.m_diem.diem[6];
      os << "|";
      os << std::setw(9);
      float d = 0.0f;
      for(int i = 0; i < 7; i++)
        d += sv.m_diem.diem[i];
      dtb = d / MONHOC;
      os << std::setprecision(2) << std::fixed << dtb << "|";
      if(dtb >= 9.0f) {
        os << std::setw(10);
        os << XepLoai(XEPLOAI::XUATSAC) << "|\n";
      } else if(dtb < 9.0f && dtb >= 8.0f) {
        os << std::setw(10);
        os << XepLoai(XEPLOAI::GIOI) << "|\n";
      } else if(dtb < 8.0f && dtb >= 6.5f) {
        os << std::setw(10);
        os << XepLoai(XEPLOAI::KHA) << "|\n";
      } else if(dtb < 6.5f && dtb >= 5.0f) {
        os << std::setw(9);
        os << XepLoai(XEPLOAI::TRUNGBINH) << "|\n";
      } else if(dtb < 5.0f && dtb >= 3.0f) {
        os << std::setw(10);
        os << XepLoai(XEPLOAI::YEU) << "|\n";
      } else {
        os << std::setw(10);
        os << XepLoai(XEPLOAI::KEM) << "|\n";
      }

      os << "\t+------------------+------+----------+------+----+-----+------+-----+----+-----+---------+----------+\n"; 
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
    void writeJSONFile(const char fname[]) {
      std::ofstream os("data.json", std::ios::out | std::ios::app);
      if (os.fail())
        throw std::ios_base::failure(strerror(errno));

      //make sure write fails with exception if something is wrong
      os.exceptions(os.exceptions()|std::ios::failbit|std::ifstream::badbit);
      os << "{ \n";
      os << "\t\"name\": \"" << m_hs.hoten << "\",\n";
      os << "\t\"age\": " << m_hs.tuoi << ",\n";
      os << "\t\"diachi\": \"" << m_hs.diachi << "\", \n";
      os << "\t\"diem\": { \n";
      os << "\t\t\"toan\": " << m_diem.diem[0] << ", \n";
      os << "\t\t\"ly\": " << m_diem.diem[1] << ", \n";
      os << "\t\t\"hoa\": " << m_diem.diem[2] << ", \n";
      os << "\t\t\"sinh\": " << m_diem.diem[3] << ", \n";
      os << "\t\t\"ngu_van\": " << m_diem.diem[4] << ", \n";
      os << "\t\t\"lich_su\": " << m_diem.diem[5] << ", \n";
      os << "\t\t\"dia_li\": " << m_diem.diem[6] << ", \n";
      os << "\t} \n";
      os << "},\n";
      os.close();
    }
    void loadJSONFile(const std::string& name) {
      std::ifstream ifs(name, std::ios::in);
      if (ifs.fail())
        throw std::ios_base::failure(strerror(errno));
      Json::Reader reader;
      Json::Value obj;
      reader.parse(ifs, obj);
      m_hs.hoten = obj["name"].asString();
      m_hs.tuoi = obj["age"].asInt();
      m_hs.hoten = obj["name"].asString();
      m_diem.diem[0] = obj["diem"]["toan"].asFloat();
      m_diem.diem[1] = obj["diem"]["ly"].asFloat();
      m_diem.diem[2] = obj["diem"]["hoa"].asFloat();
      m_diem.diem[3] = obj["diem"]["sinh"].asFloat();
      m_diem.diem[4] = obj["diem"]["ngu_van"].asFloat();
      m_diem.diem[5] = obj["diem"]["lich_su"].asFloat();
      m_diem.diem[6] = obj["diem"]["dia_li"].asFloat();
      ifs.close();
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

  QLSV *q[5];

  std::vector<QLSV*> sv;
  const std::string ten[] = { "Bich Loan", "Bich Nga",  "Bao Thuy",  "An Khang",  "Anh Duy" };

  for(int i = 0; i < 5; i++) {
    q[i] = new QLSV(ten[i], rand() % 30 + 20, tinhthanh[rand() % 63], rdDiem());
    sv.push_back(q[i]);
    q[i]->writeJSONFile("data.json");
  }

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
  h1->writeJSONFile("data.json");
  h2->writeJSONFile("data.json");
  h3->writeJSONFile("data.json");
  h4->writeJSONFile("data.json");
  h5->writeJSONFile("data.json");
  h6->writeJSONFile("data.json");

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
