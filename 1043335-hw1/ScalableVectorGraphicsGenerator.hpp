#pragma once
#include <fstream>
#include <list>
#include <string>
#include <vector>
class ScalableVectorGraphicsGenerator {

public:
    ScalableVectorGraphicsGenerator();
    ~ScalableVectorGraphicsGenerator();
    void SVGBegin(std::string, int, int);
    void SVGEnd();
    void setGateSize(int);
    int getGateSize();

    void drawRectangle(int, int, int, int, std::string);
    void drawAND(int, int);
    void drawOR(int, int);
    void drawINV(int, int);  // invert gate
    void drawBuff(int, int);
    void drawNAND(int, int);
    void drawNOR(int, int);
    void drawXOR(int, int);
    void drawXNOR(int, int);
    void drawIOBox(int, int, int);
    void drawPath(std::vector< int >&);
    void drawText(int, int, std::string&);

private:
    int gateSize;
    int canvasWidth, canvasHeight;
    std::ofstream out;
};
