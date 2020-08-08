#include <stdio.h>
#include <iostream>


struct Hocsinh {
  std::string hoten;
  int tuoi;
  std::string diachi;
};
struct DiemSo {
  float toan;
  float ly;
  float hoa;
  float sinh;
  float nguvan;
  float lichsu;
  float diali;
};
struct Diem {
  float diem[7];
};
struct HocLuc {
  struct Hocsinh hs;
  struct DiemSo ds;
};
